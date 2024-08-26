#include <iostream>

#define PI 3.14159

#define XMACRO(x) \
    x(error)      \
    x(warning)    \
    x(info)       \
    x(debug)      \
    x(trace)

enum class LogLevel {
#define FUNC(level) level,
    XMACRO(FUNC)
#undef FUNC
};

LogLevel string2level(std::string str) {
    switch (str) {
        case 0: return LogLevel::error;
#define FUNC(x) case #x: return LogLevel::##x;
        XMACRO(FUNC)
#undef FUNC
    }



int main() {
    {   // basic define
        std::cout << "PI: " << PI << std::endl;
    }

    {

    }


    return 0;
}