export module compiler.zero_copy;

import std;

namespace compiler
{
	export template <typename stream_type>
	struct zero_copy final
	{
		stream_type hatcher;

		constexpr operator decltype(std::declval<stream_type&>()())()
			noexcept(noexcept(std::declval<stream_type&>()())) requires std::same_as<zero_copy&, decltype(*this)>
		{
			return hatcher();
		}

		constexpr operator decltype(std::declval<const stream_type&>()())()
			noexcept(noexcept(std::declval<const stream_type&>()())) requires std::same_as<const zero_copy&, decltype(*this)>
		{
			return hatcher();
		}

		constexpr operator decltype(std::declval<stream_type&&>()())()
			noexcept(noexcept(std::declval<stream_type&&>()())) requires std::same_as<zero_copy&&, decltype(*this)>
		{
			return std::move(hatcher)();
		}

		constexpr operator decltype(std::declval<const stream_type&&>()())()
			noexcept(noexcept(std::declval<const stream_type&&>()())) requires std::same_as<const zero_copy&&, decltype(*this)>
		{
			return std::move(hatcher)();
		}
	};
}
