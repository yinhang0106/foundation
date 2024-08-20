#include "ticktock.h"
#include "memory_resource_inspector.h"
#include <memory_resource>
#include <list>

static char buf[65536 * 30];    // must be large enough
static size_t watermark = 0;

template <class T>
struct my_custom_allocator {

    using value_type = T;

    T *allocate(size_t n) {
        char *p = buf + watermark;
        watermark += n * sizeof(T);
        return (T *)p;
    }

    void deallocate(T *p, size_t n) {
        // Do nothing
    }

    my_custom_allocator() = default;

    template <class U>
    constexpr explicit my_custom_allocator(my_custom_allocator<U> const &) noexcept {}

    constexpr bool operator==(my_custom_allocator const &other) const noexcept {
        return this == &other;
    }
};

int main() {
    {
        std::list<char, my_custom_allocator<char>> a;
        // prev8 next8 char1 padding7 --> Node<char>24
        TICK(list);
        for (int i = 0; i < 65536; ++i) {
            a.push_back(42);
        }
        TOCK(list);
    }
    {
        std::vector<char, my_custom_allocator<char>> a;
        TICK(vector);
        for (int i = 0; i < 65536; ++i) {
            a.push_back(42);
        }
        TOCK(vector);
    }
}

// Output:
// list: 0.000101016s.  (10x faster)
// vector: 3.3189e-05s. (8x faster)

// Old Output:
// list: 0.00102887s.
// vector: 0.000270469s.