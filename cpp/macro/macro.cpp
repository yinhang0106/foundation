#include <format>
#include <iostream>

// constant define
#define PI 3.14159

// x-macro technique
#define FOREACH_LOG_LEVEL(x) \
    x(error)      \
    x(warning)    \
    x(info)       \
    x(debug)      \
    x(trace)

enum class LogLevel {
#define FUNC(level) level,
    FOREACH_LOG_LEVEL(FUNC)
#undef FUNC
};

std::string int2level(int num) {
    switch (num) {
#define FUNC(level) case static_cast<int>(LogLevel::level) : return #level;
        FOREACH_LOG_LEVEL(FUNC)
#undef FUNC
        default:
            return "unknown";
    }
}

#define FUNC(level) \
    void log_##level(std::string const & msg) { \
        std::cout << #level << ": " << msg << std::endl; \
    }
    FOREACH_LOG_LEVEL(FUNC)
#undef FUNC

// assert macro
#define ASSET_GT(x, y) do { \
    auto _x = (x); \
    auto _y = (y); \
    if (_x < _y) { \
        std::cout << "assert failed: " << #x << "(" << _x << ") > " << #y << std::endl; \
    } \
} while(0)

// macro function
#define MIN(x, y) ({ \
    auto _x = (x); \
    auto _y = (y); \
    _x < _y ? _x : _y; \
})

// ... macro
#define PRINT(fmt, ...) \
    std::cout << std::format(fmt __VA_OPT__(,) __VA_ARGS__)

// debug or release mode
#if !defined(NDEBUG) /* DEBUG Mode */
#define CHECK_ERROR(x) do { \
    (x); \
    PRINT("ERROR: {}:{}:\"{}\" occurs error!\n", __FILE_NAME__, __LINE__, #x); \
} while(0)
#else /* NDEBUG */
#define CHECK_ERROR(x) (x)
#endif

// c++ version
#if __cplusplus >= 202002L
template <class T>
requires (std::is_signed_v<T>)
#elif __cplusplus >= 201402L
template <class T, std::enable_if_t<std::is_signed_v<T>, int> = 0>
#else
template <class T, typename std::enable_if<std::is_signed<T>::value>::type = 0>
#endif
auto abs(T x) {
    return x < 0 ? -x : x;
}

// os version
#if defined(__GNUC__) || defined(__clang__)
#define NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE
#endif
NOINLINE void foo() {
    std::cout << "foo" << std::endl;
}

int main() {
    {   // basic define
        std::cout << "PI: " << PI << std::endl;
    }

    {   // enum class
        std::cout << "LogLevel: " << int2level(3) << std::endl;
        log_error("error message");
        log_warning("warning message");
    }

    {
        PRINT("{}, {}, {}\n", "hello", 3, 5.0);
    }

    {
        auto i = 10;
        CHECK_ERROR(i = 20);
    }

    {
        int x = 3, y = 5;
        ASSET_GT(x++, y);
    }

    {   // macro function
        // auto ret = MIN(3, 5);
        std::cout << "MIN(3, 5): " << MIN(3, 5) << std::endl;
    }

    {
        auto ret = abs(-3);
        std::cout << "abs(-3): " << ret << std::endl;
    }

    return 0;
}