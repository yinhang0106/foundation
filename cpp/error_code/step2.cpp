#include <format>
#include <iostream>

// 通过错误码返回错误信息
//int sqrt(int x) {
//	if (x < 0) {
//		return -1;
//	}
//	for (int i = 0;; i++) {
//		if (i * i >= x) {
//			return i;
//		}
//	}
//}

// 如果我们认为当 x == 4 时，客户没有登录，将程序修改如下：
int sqrt(int x) {
	if (x < 0) {
		return -1;	// 逻辑错误
	}
	if (x == 4) {
		return -2;	// 业务错误
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			return i;
		}
	}
}


int main() {
	auto ret = sqrt(2);
	if (ret == -1) {
		std::cerr << "x < 0\n";
	} else {
		std::cout << std::format("结果: {}\n", ret);
	}
	return 0;
}