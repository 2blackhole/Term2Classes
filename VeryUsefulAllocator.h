//
// Created by Lenovo on 2025-03-11.
//

#ifndef VERYUSEFULALLOCATOR_H
#define VERYUSEFULALLOCATOR_H
#include <deque>
#include <vector>
#include <cassert>

template <class T>
class VeryUsefulAllocator {
public:
    using value_type = T;

    ~VeryUsefulAllocator() {
        assert(allocations == 0);
    }

    T* allocate(std::size_t n);
    void deallocate(T* ptr, std::size_t n);
private:
    std::deque<std::vector<T>> chunks;
    std::size_t available_size = 0;
    std::size_t allocations = 0;
    T* memory_ptr;
};



#endif //VERYUSEFULALLOCATOR_H
