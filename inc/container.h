#pragma once

#include <iterator>

namespace custom {
template<typename T, typename A = std::allocator<T> >
class container {
  public:
    struct node {
        node() = default;
        explicit node(const T &_data) : data{_data} {}

        T    data;
        node *next = nullptr;
    };

    struct iterator : std::iterator<std::forward_iterator_tag, T> {
        explicit iterator(node *_ptr = nullptr) : ptr_(_ptr) {}
        iterator() = delete;

        iterator &operator++() {
            if (ptr_ != nullptr) {
                ptr_ = ptr_->next;
            }
            return *this;
        }

        T &operator*() {
            return ptr_->data;
        }

        bool operator==(iterator &other) {
            return ptr_ == other.ptr_;
        }

        bool operator!=(iterator &other) {
            return !(*this == other);
        }

      private:
        node *ptr_;
    };

    void push_back(const T &value) {
        node *p = alloc_.allocate(1);
        alloc_.construct(p, value);

        if (tail_ == nullptr) {
            head_ = p;
        } else {
            tail_->next = p;
        }
        tail_ = p;
        tail_->next = nullptr;
    }

    iterator begin() {
        return iterator(head_);
    }

    iterator end() {
        return iterator(nullptr);
    }

    container() = default;
    ~container() {
        auto h = head_;
        while (h != nullptr) {
            auto p = h;
            h = h->next;
            alloc_.destroy(p);
            alloc_.deallocate(p, 1);
        }
        head_  = nullptr;
    }

  private:
    node *head_ = nullptr;
    node *tail_ = nullptr;

    using alloc_t = typename A::template rebind<node>::other;
    alloc_t alloc_;
};
}