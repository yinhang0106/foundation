#include "ticktock.h"
#include "memory_resource_inspector.h"
#include <memory_resource>
#include <list>

// for type erasure
struct memory_resource {
    size_t m_watermark = 0;
    virtual char *data() = 0;
    virtual ~memory_resource() = default;
};

struct memory_resource_stack : memory_resource {
    char m_buf[65536 * 30]{};    // must be large enough
    char* data() override {
        return m_buf;
    }
};

// memory resource heap version
// if we want a big buffer which is not available on the stack
struct memory_resource_heap : memory_resource {
    std::vector<char> m_buf = std::vector<char>(65536 * 30);
    char* data() override {
        return m_buf.data();
    }
};

template <class T>
struct custom_allocator {

    using value_type = T;

    memory_resource *m_resource;


    T *allocate(size_t n) {
        char *p = m_resource->data() + m_resource->m_watermark;
        m_resource->m_watermark += n * sizeof(T);
        return (T *)p;
    }

    void deallocate(T *p, size_t n) {}

    custom_allocator() = default;

    custom_allocator(memory_resource *resource) : m_resource(resource) {}

    template <class U>
    constexpr custom_allocator(custom_allocator<U> const &other) noexcept : m_resource(other.m_resource) {}

    constexpr bool operator==(custom_allocator const &other) const noexcept {
        return m_resource == other.m_resource;
    }
};

int main() {

    {
        memory_resource *mem = new memory_resource_stack{};
        std::list<char, custom_allocator<char>> a{mem};
        // prev8 next8 char1 padding7 --> 24
        TICK(list);
        for (int i = 0; i < 65536; ++i)
            a.push_back(42);
        TOCK(list);
    }
    {
        memory_resource *mem = new memory_resource_heap{};
        std::vector<char, custom_allocator<char>> a{mem};
        TICK(vector);
        for (int i = 0; i < 65536; ++i)
            a.push_back(42);
        TOCK(vector);
    }
}

// Output:
// list: 0.000140816s.
// vector: 2.541e-05s.