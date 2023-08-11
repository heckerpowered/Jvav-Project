export module compiler.literal_variant;

import std;

namespace compiler
{
	export using builtin_literal_type = std::variant<bool, std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t,
		std::int8_t, std::int16_t, std::int32_t, std::int64_t, float, double, long double>;
}