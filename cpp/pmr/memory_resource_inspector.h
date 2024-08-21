#pragma once

#include <memory_resource>
#include <iostream>
#include <format>

struct memory_resource_inspector : std::pmr::memory_resource {
public:
    explicit memory_resource_inspector(std::pmr::memory_resource *upstream)
    : m_upstream(upstream) {}

private:
    void *do_allocate(size_t bytes, size_t alignment) override {
        void *p = m_upstream->allocate(bytes, alignment);
        std::cout << std::format("allocate    {}  {:>5d}  {:>5d}\n", p, bytes, alignment) << "\n";
        return p;
    }

    [[nodiscard]] bool do_is_equal(std::pmr::memory_resource const &other) const noexcept override {
        return other.is_equal(*m_upstream);
    }

    void do_deallocate(void *p, size_t bytes, size_t alignment) override {
        std::cout << std::format("deallocate  {}  {:>5d}  {:>5d}\n", p, bytes, alignment) << "\n";
        return m_upstream->deallocate(p, bytes, alignment);
    }

    std::pmr::memory_resource *m_upstream;
};