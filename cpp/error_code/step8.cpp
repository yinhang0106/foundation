#include <format>
#include <iostream>
#include <cerrno>
#include <cstring>


// 如果x可以是任意整数，我们需要传入错误类型指针
// int : [INT_MIN, INT_MAX]
// optional<int> : [INT_MIN, INT_MAX] | {nullopt}

// std::error_category
struct ErrorCategory {
	virtual const char *message(int val) const = 0;

};

// std::error_code
struct ErrorCode {
	int value;
	ErrorCategory *category;
};

// std::generic_category()
auto *std_error_category() {
	struct StdErrorCategory : ErrorCategory {
		virtual const char *message(int val) const override {
			return strerror(val);
		}
	};
	static StdErrorCategory instance;
	return &instance;
};

// std::make_error_code
ErrorCode makeErrorCode(std::errc ec) {
	return {(int)ec, std_error_category()};
}


enum class LoginErrc {
	success = 0,
	not_valid_pass,
	not_login,
};

const char *login_strerror(LoginErrc &ec) {
	switch (ec) {
		case LoginErrc::success:
			return "登录成功！";
		case LoginErrc::not_valid_pass:
			return "密码不正确！";
		case LoginErrc::not_login:
			return "用户未登录！";
		default:
			return "未知错误！";
	};
}

auto const &login_category() {
	struct LoginErrorCategory : std::error_category {
		[[nodiscard]] std::string message(int val) const override {
			return login_strerror((LoginErrc &)val);
		}
		[[nodiscard]] const char * name() const noexcept override {
			return "login";
		}
	};
	static LoginErrorCategory const instance;
	return instance;
};

//auto const &login_category() {
//	static const struct LoginErrorCategory : std::error_category {
//		[[nodiscard]] std::string message(int val) const override {
//			return login_strerror((LoginErrc &)val);
//		}
//		[[nodiscard]] const char * name() const noexcept override {
//			return "login";
//		}
//	} instance;
//	return instance;
//};

std::error_code make_error_code(LoginErrc ec) {
	return {(int)ec, login_category()};
}

int sqrt(int x, std::error_code &ec) {
	if (x < 0) {
		ec = make_error_code(std::errc::argument_out_of_domain);
		return -1;
	}
	if (x == 4) {
		ec = make_error_code(LoginErrc::not_login);
		return -1;
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			ec = make_error_code(LoginErrc::success);
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