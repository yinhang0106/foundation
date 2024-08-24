#include <format>
#include <iostream>
#include <cerrno>
#include <cstring>



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

int sqrt(int x, std::error_code &ec) {
	if (x < 0) {
		ec = make_error_code(std::errc::argument_out_of_domain);
		return -1;
	}
	if (x == 4) {
		ec = make_error_code(login_errc::not_login);
		return -1;
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			ec = make_error_code(login_errc::success);
			return i;
		}
	}
}

int main() {
	std::error_code ec;
	auto ret = sqrt(4, ec);
	if (ec.value() == 0) {
		std::cout << std::format("结果: {}\n", ret);
	} else {
		std::cerr << std::format("sqrt: {}\n", ec.message());
	}
	return 0;
}