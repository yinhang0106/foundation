#include <utility>
#include <cstdio>
#include <type_traits>
#include <iostream>

#if 0
template <size_t... Is>
void static_for_impl(auto &&lambda, std::index_sequence<Is...>) {
	(lambda(std::integral_constant<size_t, Is>{}), ...);
}

template <size_t N>
void static_for(auto &&lambda) {
	static_for_impl(lambda, std::make_index_sequence<N>());
}

template <bool BreakStrategy, size_t ...Is>
void static_break_for_impl(auto &&lambda, std::index_sequence<Is...>) {
	if constexpr (BreakStrategy) {
		(lambda(std::integral_constant<size_t, Is>{}) || ...);
	} else {
		(lambda(std::integral_constant<size_t, Is>{}) && ...);
	}
}

template <size_t N, bool BreakStrategy, typename Lambda>
requires std::is_same_v<std::invoke_result_t<Lambda, std::integral_constant<size_t, N>>, bool>
void static_break_for(Lambda &&lambda) {
	static_break_for_impl<BreakStrategy>(lambda, std::make_index_sequence<N>());
}
#else
template <size_t N>
void static_for(auto &&lambda) {
	[&] <size_t ...Is> (std::index_sequence<Is...>) {
		(lambda(std::integral_constant<size_t, Is>{}), ...);
	} (std::make_index_sequence<N>());
}

template <size_t N, bool BreakStrategy, typename Lambda>
requires std::is_same_v<std::invoke_result_t<Lambda, std::integral_constant<size_t, N>>, bool>
void static_break_for(Lambda &&lambda) {
	[&] <size_t ...Is> (std::index_sequence<Is...>) {
		if constexpr (BreakStrategy) {
			(lambda(std::integral_constant<size_t, Is>{}) || ...);
		} else {
			(lambda(std::integral_constant<size_t, Is>{}) && ...);
		}
	} (std::make_index_sequence<N>());
}
#endif


int main() {

	static_for<10>([](int i) {
		std::printf("%d\n", i);
	});

	std::cout << "======================\n";

	static_break_for<10, true>([](int i) {
		std::printf("%d\n", i);
		return i < 5;
	});

	std::cout << "======================\n";

}