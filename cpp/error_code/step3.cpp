#include <format>
#include <iostream>

// 如果x可以是任意整数，我们需要传入错误类型指针
// int : [INT_MIN, INT_MAX]
int sqrt(int x, int *errc) {
	if (x < 0) {
		*errc = -1;
		return 0;	// 逻辑错误
	}
	if (x == 4) {
		*errc = -2;
		return 0;	// 业务错误
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			return i;
		}
	}
}


int main() {
	int errc = 0;
	auto ret = sqrt(4, &errc);
	if (errc == -1) {
		std::cerr << "x < 0";
	} else if (errc == -2) {
		std::cerr << "not login";
	} else {
		std::cout << std::format("结果: {}\n", ret);
	}
	return 0;
}