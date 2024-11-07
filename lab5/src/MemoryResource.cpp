#include "MemoryResource.hpp"
#include <cstdlib>
#include <new>
#include <algorithm>
#include <stdexcept>

MemoryResource::MemoryResource() {}

MemoryResource::~MemoryResource() {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& block : allocated_blocks_) {
        ::operator delete(block.ptr, std::align_val_t(block.alignment));
    }
    allocated_blocks_.clear();
    for (auto& block : free_blocks_) {
        ::operator delete(block.ptr, std::align_val_t(block.alignment));
    }
    free_blocks_.clear();
}

void* MemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    std::lock_guard<std::mutex> lock(mutex_);

    alignment = alignment == 0 ? alignof(std::max_align_t) : alignment;

    auto it = std::find_if(free_blocks_.begin(), free_blocks_.end(),
        [bytes, alignment](const MemoryBlock& block) {
            return block.size >= bytes && block.alignment >= alignment;
        });

    if (it != free_blocks_.end()) {
        void* ptr = it->ptr;
        allocated_blocks_.push_back(*it);
        free_blocks_.erase(it);
        return ptr;
    }

    void* p = ::operator new(bytes, std::align_val_t(alignment));
    allocated_blocks_.push_back({p, bytes, alignment});
    return p;
}

void MemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    std::lock_guard<std::mutex> lock(mutex_);

    alignment = alignment == 0 ? alignof(std::max_align_t) : alignment;

    auto it = std::find_if(allocated_blocks_.begin(), allocated_blocks_.end(),
        [p](const MemoryBlock& block) {
            return block.ptr == p;
        });

    if (it != allocated_blocks_.end()) {
        it->size = bytes;
        it->alignment = alignment;

        free_blocks_.push_back(*it);
        allocated_blocks_.erase(it);
    }
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

std::vector<MemoryBlock> MemoryResource::get_allocated_blocks_info() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return allocated_blocks_;
}

std::vector<MemoryBlock> MemoryResource::get_free_blocks_info() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return free_blocks_;
}
