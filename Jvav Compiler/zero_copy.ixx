export module compiler.zero_copy;

import std;

namespace compiler
{
	export template <typename T>
	struct zero_copy final
	{
		T hatcher;

		constexpr operator decltype(std::declval<T&>()())()
			noexcept(noexcept(std::declval<T&>()())) requires std::same_as<zero_copy&, decltype(*this)>
		{
			return hatcher();
		}

		constexpr operator decltype(std::declval<const T&>()())()
			noexcept(noexcept(std::declval<const T&>()())) requires std::same_as<const zero_copy&, decltype(*this)>
		{
			return hatcher();
		}

		constexpr operator decltype(std::declval<T&&>()())()
			noexcept(noexcept(std::declval<T&&>()())) requires std::same_as<zero_copy&&, decltype(*this)>
		{
			return std::move(hatcher)();
		}

		constexpr operator decltype(std::declval<const T&&>()())()
			noexcept(noexcept(std::declval<const T&&>()())) requires std::same_as<const zero_copy&&, decltype(*this)>
		{
			return std::move(hatcher)();
		}
	};
}
