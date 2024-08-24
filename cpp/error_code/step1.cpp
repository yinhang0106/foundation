#include <format>
#include <iostream>

int sqrt(int x) {
	if (x < 0) {
		throw std::invalid_argument("x < 0");
	}
	for (int i = 0;; i++) {
		if (i * i >= x) {
			return i;
		}
	}
}

int main() {
	auto ret = sqrt(2);
	std::cout << std::format("结果: {}\n", ret);
	return 0;
}