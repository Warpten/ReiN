#pragma once

#include <cstdint>

/**
 * This files provides utilities to explicitely manipulate the game's types virtual method table.
 * 
 * 1. SDK::VirtualMethodTable<T, O>:
 *    Provides utilities to explicitely access the virtual method table of an object, implemented by the T
 *    type (usually a simple structure made of function pointers). 
 */

namespace SDK {
    template <typename R, typename I, typename... Args>
    struct VirtualMethod<R(I::*)(Args...)> final {
        using PointerType = R(I::*)(Args...);

        R operator () (I* instance, Args... args) const {
            return (instance->*_method)(std::forward<Args>(args)...);
        }

    private:
        PointerType _method;
    };

    template <typename V, size_t BaseOffset = 0>
    struct VirtualMethodTable final {
        explicit VirtualMethodTable(uintptr_t self) noexcept {
            _self = self;
        }

        /**
         * Returns a pointer to the virtual method table associated with the object being wrapped.
         */
        const V* operator -> () const {
            return reinterpret_cast<const V*>(_self + BaseOffset);
        }

    private:
        /**
         * The memory location of the object being accessed.
         */
        uintptr_t _self;
    };
}