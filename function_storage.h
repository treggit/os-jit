//
// Created by Anton Shelepov on 2019-05-05.
//

#ifndef OS_JIT_FUNCTION_STORAGE_H
#define OS_JIT_FUNCTION_STORAGE_H

#include <cstddef>
#include <sys/mman.h>
#include <algorithm>

template <typename>
struct function_storage {
};

template <typename R, typename ...Args>
struct function_storage<R(*)(Args...)> {

    template <typename Pointer>
    function_storage(Pointer ptr, size_t len) {
        auto mapped = mmap(nullptr, len, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        if (mapped == MAP_FAILED) {
            return;
        }

        std::copy_n(ptr, len, reinterpret_cast<uint8_t*>(mapped));
        int prot_status = mprotect(mapped, len, PROT_READ | PROT_EXEC);
        if (prot_status == -1) {
            munmap(mapped, len);
        } else {
            func = reinterpret_cast<R(*)(Args...)>(mapped);
            size = len;
        }
    }

    bool loaded() {
        return func != nullptr;
    }

    template <typename ...A>
    R call(A&&... a) {
        return func(std::forward<A>(a)...);
    }

    ~function_storage() {
        if (loaded()) {
            munmap(reinterpret_cast<void*>(func), size);
        }
    }

private:
    R(*func)(Args...) = nullptr;
    size_t size = 0;
};

#endif //OS_JIT_FUNCTION_STORAGE_H
