export module compiler.integer_type;

import std;

import compiler.syntax_kind;

namespace compiler
{
	export constexpr syntax_kind get_minimum_syntax_kind(const std::uintmax_t integer) noexcept
	{
		if (std::numeric_limits<std::uint8_t>::max() >= integer)
		{
			return syntax_kind::int8_token;
		}

		if (std::numeric_limits<std::uint16_t>::max() >= integer)
		{
			return syntax_kind::int16_token;
		}

		if (std::numeric_limits<std::uint32_t>::max() >= integer)
		{
			return syntax_kind::int32_token;
		}

		return syntax_kind::int64_token;
	}
}