#include <format>
#include <iostream>
#include <variant>
#include <fcntl.h>
#include <unistd.h>
#include <span>

#include "tl-expected.hpp"


enum class login_errc {
	success = 0,
	not_valid_pass,
	not_login,
};

std::error_code make_error_code(login_errc ec) {
	static const struct : std::error_category {
		[[nodiscard]] std::string message(int val) const override {
			switch ((login_errc)val) {
				case login_errc::success:
					return "登录成功！";
				case login_errc::not_valid_pass:
					return "密码不正确！";
				case login_errc::not_login:
					return "用户未登录！";
				default:
					return "未知错误！";
			}
		}
		[[nodiscard]] const char * name() const noexcept override {
			return "login";
		}
	} instance;
	return {(int)ec, instance};
}


tl::expected<int, std::error_code> sqrt(int x) {
	if (x < 0) {
		return tl::unexpected{make_error_code(std::errc::argument_out_of_domain)};
	}
	if (x == 4) {
		return tl::unexpected{make_error_code(login_errc::not_login)};
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			return i;
		}
	}
}

template <>
struct tl::bad_expected_access<std::error_code> : std::system_error {
	explicit bad_expected_access(std::error_code ec) : std::system_error(ec, "expected") {}
};

template <class T>
using expected = tl::expected<T, std::error_code>;

//expected<int> check_error(int ret) {
//	if (ret < 0) {
//		return tl::unexpected{std::error_code(errno, std::generic_category())};
//	}
//	return ret;
//}
//
//expected<ssize_t> check_error(ssize_t ret) {
//	if (ret < 0) {
//		return tl::unexpected{std::error_code(errno, std::generic_category())};
//	}
//	return ret;
//}

template <class T>
struct PolicyNegative {
    bool operator()(T ret) const {
        return ret < 0;
    }
};

template <class T, class _policy = PolicyNegative<T>>
requires std::is_same_v<T, int>
    || std::is_same_v<T, ssize_t>
    && std::is_invocable_v<_policy, T>
    && std::is_same_v<std::invoke_result_t<_policy, T>, bool>
expected<T> check_error(T ret) {
	if (_policy()(ret)) {
		return tl::unexpected{make_error_code(std::errc(errno))};
	}
	return ret;
}


int main() {
    if (auto fd = check_error(open("not_exist", O_RDONLY))) {
        std::cout << "open success\n";
    } else {
        std::cout << "open failed: " << fd.error().message() << '\n';
    }
	return 0;
}