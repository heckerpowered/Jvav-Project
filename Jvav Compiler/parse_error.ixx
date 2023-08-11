export module compiler.parse_error;

namespace compiler
{
	export enum class parse_error
	{
		invalid_octal,
		invalid_hexadecimal,
		invalid_decimal,
		invalid_binary,
		invalid_prefix,
		invalid_suffix,
		invalid_floating_point,
		invalid_number
	};
}