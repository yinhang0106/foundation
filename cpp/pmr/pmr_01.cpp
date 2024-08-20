#include "ticktock.h"
#include "memory_resource_inspector.h"
#include <memory_resource>
#include <list>

int main() {
    {
        std::list<char> a;
        TICK(list);
        for (int i = 0; i < 65536; ++i) {
            a.push_back(42);
        }
        TOCK(list);
    }
    {
        std::vector<char> a;
        TICK(vector);
        for (int i = 0; i < 65536; ++i) {
            a.push_back(42);
        }
        TOCK(vector);
    }
}

// Output:
// list: 0.00102887s.
// vector: 0.000270469s.