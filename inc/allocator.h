#pragma once

#include <bitset>

namespace custom {
    template<typename T, size_t N = 1>
    struct allocator {
        using value_type = T;

        allocator() = default;

        ~allocator() = default;

        template<typename U>
        struct rebind {
            using other = allocator<U, N>;
        };

        T *allocate(std::size_t n) {
            auto p = addNote(n);
            if (p == nullptr) {
                throw std::bad_alloc(); //"Error allocating memory."
            }
            return p;
        }

        void deallocate(T *p, std::size_t n) {
            if (!delNote(p, n)) {
                throw std::bad_alloc(); //"Error releasing memory."
            }
        }

        template<typename U, typename ...Args>
        void construct(U *p, Args &&...args) {
            new(p) U(std::forward<Args>(args)...);
        }

        void destroy(T *p) {
            p->~T();
        }

    private:
        T *addNote(size_t n) {
            size_t cnt = 0;
            for (size_t i = 0; i < N; ++i) {
                cnt = (!mask_.test(i)) ? cnt + 1 : 0;
                if (cnt == n) {
                    auto firstElement = i + 1 - n;
                    mask_.set(firstElement);
                    return &data_[firstElement];
                }
            }
            return nullptr;
        }

        bool delNote(T *p, std::size_t n) {
            if (n > N || p < &data_[0] || p > &data_[N - 1]) {
                return false;
            }

            for (size_t i = p - data_.data(); i < n; ++i) {
                mask_.reset(static_cast<size_t>(i));
            }
            return true;
        }

    private:
        std::bitset<N> mask_{0};
        std::array<T, N> data_;

        static_assert(N >= 1, "N must be greater than or equal to 1.");
    };
}