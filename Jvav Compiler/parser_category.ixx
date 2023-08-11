export module compiler.parser_category;

import std;

import compiler.parse_error;

namespace compiler
{
	export class parser_category final : public std::error_category
	{
	public:
		using super = std::error_category;

		const char* name() const noexcept override
		{
			return "parser";
		}

		std::string message(const int error_code) const override
		{
			switch (static_cast<parse_error>(error_code))
			{
			case parse_error::invalid_octal:
				return "Invalid octal number";
			case parse_error::invalid_hexadecimal:
				return "Invalid hexadecimal number";
			case parse_error::invalid_decimal:
				return "Invalid decimal number";
			case parse_error::invalid_binary:
				return "Invalid binary number";
			case parse_error::invalid_number:
				return "Invalid number";
			case parse_error::invalid_prefix:
				return "Invalid prefix";
			case parse_error::invalid_suffix:
				return "Invalid suffix";
			case parse_error::invalid_floating_point:
				return "Invalid floating point";
			default:
				return "Unknown";
			}
		}
	};
}