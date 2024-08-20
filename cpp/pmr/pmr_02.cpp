#include "ticktock.h"
#include "memory_resource_inspector.h"
#include <memory_resource>
#include <list>

int main() {
    {
        std::list<char, std::allocator<char>> a;
        TICK(list);
        for (int i = 0; i < 65536; ++i) {
            a.push_back(42);
        }
        TOCK(list);
    }
    {
        std::vector<char, std::allocator<char>> a;
        TICK(vector);
        for (int i = 0; i < 65536; ++i) {
            a.push_back(42);
        }
        TOCK(vector);
    }
    {   // C style
        char *p = (char *)malloc(42);
        free(p);
    }
    {   // C++ without allocator
        char *p = new char[42];
        delete[] p;
    }
    {   // C++ with allocator
        std::allocator<char> alloc;
        char *p = alloc.allocate(42);
        alloc.deallocate(p, 42);
    }
    {   // Custom allocator
        struct my_custom_allocator {
            char local_buf[1024];

            char *allocate(size_t n) {
                return local_buf;
            }
            void deallocate(char *p, size_t n) {
            }
        };
        my_custom_allocator alloc{};
        char *p = alloc.allocate(42);
        alloc.deallocate(p, 42);
    }
}
