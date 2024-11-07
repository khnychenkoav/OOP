#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif
#include "MemoryResource.hpp"
#include "List.hpp"
#include <string>
#include <map>
#include <vector>

MemoryResource mem_resource;

template <typename T>
using pmr_allocator = std::pmr::polymorphic_allocator<T>;

std::map<std::string, void*> lists;

struct MemoryBlockJS {
    uintptr_t pointer;
    size_t size;
    size_t alignment;
};

#ifdef __EMSCRIPTEN__
void create_list(const std::string& type) {
    if (type == "int") {
        List<int>* int_list = new List<int>(pmr_allocator<int>(&mem_resource));
        lists[type] = int_list;
    } else if (type == "string") {
        List<std::string>* string_list = new List<std::string>(pmr_allocator<std::string>(&mem_resource));
        lists[type] = string_list;
    }
}

void push_back_int(int value) {
    List<int>* int_list = static_cast<List<int>*>(lists["int"]);
    int_list->push_back(value);
}

void push_front_int(int value) {
    List<int>* int_list = static_cast<List<int>*>(lists["int"]);
    int_list->push_front(value);
}

void pop_back_int() {
    List<int>* int_list = static_cast<List<int>*>(lists["int"]);
    int_list->pop_back();
}

void pop_front_int() {
    List<int>* int_list = static_cast<List<int>*>(lists["int"]);
    int_list->pop_front();
}

std::vector<int> get_list_contents_int() {
    std::vector<int> array;
    List<int>* int_list = static_cast<List<int>*>(lists["int"]);
    for (const auto& val : *int_list) {
        array.push_back(val);
    }
    return array;
}

void push_back_string(std::string value) {
    List<std::string>* string_list = static_cast<List<std::string>*>(lists["string"]);
    string_list->push_back(value);
}

void push_front_string(std::string value) {
    List<std::string>* string_list = static_cast<List<std::string>*>(lists["string"]);
    string_list->push_front(value);
}

void pop_back_string() {
    List<std::string>* string_list = static_cast<List<std::string>*>(lists["string"]);
    string_list->pop_back();
}

void pop_front_string() {
    List<std::string>* string_list = static_cast<List<std::string>*>(lists["string"]);
    string_list->pop_front();
}

std::vector<std::string> get_list_contents_string() {
    std::vector<std::string> array;
    List<std::string>* string_list = static_cast<List<std::string>*>(lists["string"]);
    for (const auto& val : *string_list) {
        array.push_back(val);
    }
    return array;
}

void sort_list_int() {
    List<int>* int_list = static_cast<List<int>*>(lists["int"]);
    int_list->sort();
}

void sort_list_string() {
    List<std::string>* string_list = static_cast<List<std::string>*>(lists["string"]);
    string_list->sort();
}

bool search_list_int(int value) {
    List<int>* int_list = static_cast<List<int>*>(lists["int"]);
    for (const auto& val : *int_list) {
        if (val == value) {
            return true;
        }
    }
    return false;
}

bool search_list_string(std::string value) {
    List<std::string>* string_list = static_cast<List<std::string>*>(lists["string"]);
    for (const auto& val : *string_list) {
        if (val == value) {
            return true;
        }
    }
    return false;
}

std::vector<MemoryBlockJS> get_allocated_blocks() {
    std::vector<MemoryBlockJS> blocks_js;
    for (const auto& block : mem_resource.get_allocated_blocks_info()) {
        blocks_js.push_back({
            reinterpret_cast<uintptr_t>(block.ptr),
            block.size,
            block.alignment
        });
    }
    return blocks_js;
}

std::vector<MemoryBlockJS> get_free_blocks() {
    std::vector<MemoryBlockJS> blocks_js;
    for (const auto& block : mem_resource.get_free_blocks_info()) {
        blocks_js.push_back({
            reinterpret_cast<uintptr_t>(block.ptr),
            block.size,
            block.alignment
        });
    }
    return blocks_js;
}

void clear_all() {
    for (auto& pair : lists) {
        if (pair.first == "int") {
            delete static_cast<List<int>*>(pair.second);
        } else if (pair.first == "string") {
            delete static_cast<List<std::string>*>(pair.second);
        }
    }
    lists.clear();
}
#endif

int main() {
    return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::value_object<MemoryBlockJS>("MemoryBlock")
        .field("pointer", &MemoryBlockJS::pointer)
        .field("size", &MemoryBlockJS::size)
        .field("alignment", &MemoryBlockJS::alignment);

    emscripten::register_vector<int>("vector<int>");
    emscripten::register_vector<std::string>("vector<string>");
    emscripten::register_vector<MemoryBlockJS>("vector<MemoryBlock>");

    emscripten::function("create_list", &create_list);
    emscripten::function("push_back_int", &push_back_int);
    emscripten::function("push_front_int", &push_front_int);
    emscripten::function("pop_back_int", &pop_back_int);
    emscripten::function("pop_front_int", &pop_front_int);
    emscripten::function("get_list_contents_int", &get_list_contents_int);
    emscripten::function("push_back_string", &push_back_string);
    emscripten::function("push_front_string", &push_front_string);
    emscripten::function("pop_back_string", &pop_back_string);
    emscripten::function("pop_front_string", &pop_front_string);
    emscripten::function("get_list_contents_string", &get_list_contents_string);
    emscripten::function("sort_list_int", &sort_list_int);
    emscripten::function("sort_list_string", &sort_list_string);
    emscripten::function("search_list_int", &search_list_int);
    emscripten::function("search_list_string", &search_list_string);
    emscripten::function("get_allocated_blocks", &get_allocated_blocks);
    emscripten::function("get_free_blocks", &get_free_blocks);
    emscripten::function("clear_all", &clear_all);
}
#endif
