export module compiler.noexception;

import std;

namespace compiler
{
	template<typename return_type, typename... argument_types>
	struct make_noexcept
	{
	};

	template<typename return_type, typename... argument_types>
	struct make_noexcept<return_type(argument_types...)>
	{
		using type = return_type(argument_types...) noexcept;
	};

	template<typename return_type, typename... argument_types>
	struct make_noexcept<return_type(argument_types...) noexcept>
	{
		using type = return_type(argument_types...) noexcept;
	};

	template<typename R, typename ...Args>
	using make_noexcept_t = typename make_noexcept<R, Args...>::type;

	template<typename function_type> requires std::is_function_v<function_type>
	constexpr auto noexcept_cast(function_type* function) noexcept -> make_noexcept_t<function_type>*
	{
		return reinterpret_cast<make_noexcept_t<function_type>*>(function);
	}

	export template<typename function_type, typename... argument_types> requires std::is_function_v<function_type>
	constexpr decltype(auto) noexcept_call(function_type* function, argument_types&&... arguments) noexcept
	{
		if (std::is_constant_evaluated())
		{
			return function(std::forward<argument_types>(arguments)...);
		}
		else
		{
			return noexcept_cast(function)(std::forward<argument_types>(arguments)...);
		}
	}
}