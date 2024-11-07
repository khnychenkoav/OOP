#ifndef MEMORY_RESOURCE_HPP
#define MEMORY_RESOURCE_HPP

#include <cstddef>
#include <vector>
#include <mutex>
#include <memory_resource>
#include <memory>

struct MemoryBlock {
    void* ptr;
    size_t size;
    size_t alignment;
};

class MemoryResource : public std::pmr::memory_resource {
public:
    MemoryResource();
    ~MemoryResource();

    std::vector<MemoryBlock> get_allocated_blocks_info() const;
    std::vector<MemoryBlock> get_free_blocks_info() const;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    std::vector<MemoryBlock, std::allocator<MemoryBlock>> allocated_blocks_;
    std::vector<MemoryBlock, std::allocator<MemoryBlock>> free_blocks_;
    mutable std::mutex mutex_;
};

#endif
