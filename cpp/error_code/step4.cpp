#include <format>
#include <iostream>
#include <cerrno>
#include <cstring>


// 如果x可以是任意整数，我们需要传入错误类型指针
// int : [INT_MIN, INT_MAX]
// optional<int> : [INT_MIN, INT_MAX] | {nullopt}

//thread_local int my_errno;

int sqrt(int x) {
	if (x < 0) {
		errno = EDOM;
		return -1;	// 逻辑错误
	}
	if (x == 4) {
		errno = EINVAL;
		return -1;	// 业务错误
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			return i;
		}
	}
}


int main() {
	auto ret = sqrt(4);
	if (ret == -1) {
//		std::cerr << "sqrt: " << strerror(errno) << '\n';
		perror("sqrt");
	} else {
		perror("sqrt");
		std::cout << std::format("结果: {}\n", ret);
	}
	return 0;
}