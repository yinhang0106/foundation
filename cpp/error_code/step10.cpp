#include <format>
#include <iostream>
#include <variant>

#include "tl-expected.hpp"

// int : [INT_MIN, INT_MAX]
// optional<int> : [INT_MIN, INT_MAX] | {nullopt}
// variant<int, std::error_code> : [INT_MIN, INT_MAX] | {error_code}
// expected<int, std::error_code> : [INT_MIN, INT_MAX] | {error_code}


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
			};
		}
		[[nodiscard]] const char * name() const noexcept override {
			return "login";
		}
	} instance;
	return {(int)ec, instance};
}

std::variant<int, std::error_code> sqrt(int x) {
	if (x < 0) {
		return make_error_code(std::errc::argument_out_of_domain);
	}
	if (x == 4) {
		return make_error_code(login_errc::not_login);
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			return i;
		}
	}
}

tl::expected<int, std::error_code> sqrt2(int x) {
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

int main() {
	{	// variant version
		auto ret = sqrt(4);
		if (ret.index() == 0) {
			std::cout << std::format("结果: {}\n", std::get<0>(ret));
		} else {
			std::cerr << std::format("sqrt: {}\n", std::get<1>(ret).message());
		}
	}
	{	// expected version
		auto ret = sqrt2(3);
		if (ret) {
			std::cout << std::format("结果: {}\n", ret.value());
		} else {
			std::cerr << std::format("sqrt: {}\n", ret.error().message());
		}
	}
	return 0;
}