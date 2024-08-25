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

std::string login_strerror(LoginErrc ec) {
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


int sqrt(int x, LoginErrc &ec) {
	if (x < 0) {
		ec = LoginErrc::not_valid_pass;
		return -1;
	}
	if (x == 4) {
		ec = LoginErrc::not_login;
		return -1;
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			ec = LoginErrc::success;
			return i;
		}
	}
}


int main() {
	auto ec = LoginErrc::success;
	auto ret = sqrt(4, ec);
	if (ec != LoginErrc::success) {
		std::cerr << "sqrt: " << login_strerror(ec) << '\n';
//		perror("sqrt");
	} else {
//		perror("sqrt");
		std::cout << std::format("结果: {}\n", ret);
	}
	return 0;
}