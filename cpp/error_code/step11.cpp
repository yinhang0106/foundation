#include <format>
#include <iostream>
#include <variant>

#include "tl-expected.hpp"

// int : [INT_MIN, INT_MAX]
// optional<int> : [INT_MIN, INT_MAX] | {nullopt}
// variant<int, std::error_code> : [INT_MIN, INT_MAX] | {error_code}
// expected<int, std::error_code> : [INT_MIN, INT_MAX] | {error_code}

// 错误码的本质是我们希望根据不同的错误类型，进行不同的处理
// 如果我们完全不进行错误处理，那么错误码就没有意义
// 只需要抛出异常即可

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

int main() {
	// 将error_code转换为异常
    std::error_code ec = make_error_code(login_errc::not_login);
    std::string what_str = std::format("\n{} : {}", __FILE__, __func__);
    throw std::system_error(ec, what_str + ": " + std::to_string(__LINE__));
}