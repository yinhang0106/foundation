#include <format>
#include <iostream>
#include <cerrno>
#include <cstring>


// 如果x可以是任意整数，我们需要传入错误类型指针
// int : [INT_MIN, INT_MAX]
// optional<int> : [INT_MIN, INT_MAX] | {nullopt}

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

struct ErrorCategory {
	virtual const char *message(int val) const = 0;

};

struct StdErrorCategory : ErrorCategory {
	virtual const char *message(int val) const override {
		return strerror(val);
	}
};

struct LoginErrorCategory : ErrorCategory {
	virtual const char *message(int val) const override {
		return login_strerror((LoginErrc &)val);
	}
};

struct ErrorCode {
	int value;
	ErrorCategory *category;
};

StdErrorCategory *std_error_category() {
	static StdErrorCategory instance;
	return &instance;
};

LoginErrorCategory *login_error_category() {
	static LoginErrorCategory instance;
	return &instance;
};

ErrorCode makeErrorCode(std::errc ec) {
	return {(int)ec, std_error_category()};
}

ErrorCode makeErrorCode(LoginErrc ec) {
	return {static_cast<int>(ec), login_error_category()};
}

int sqrt(int x, ErrorCode &ec) {
	if (x < 0) {
		ec = makeErrorCode(std::errc::argument_out_of_domain);
		return -1;
	}
	if (x == 4) {
		ec = makeErrorCode(LoginErrc::not_login);
		return -1;
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			ec = makeErrorCode(LoginErrc::success);
			return i;
		}
	}
}

int main() {
	auto ec = ErrorCode{};
	auto ret = sqrt(4, ec);
	if (ec.value == 0) {
		std::cout << std::format("结果: {}\n", ret);
	} else {
		std::cerr << std::format("sqrt: {}\n", ec.category->message(ec.value));
	}
	return 0;
}