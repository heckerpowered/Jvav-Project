export module compiler.number_literal_parser;

import std;

import compiler.literal_variant;
import compiler.diagnostic_list;
import compiler.syntax_token;
import compiler.noexception;
import compiler.parse_error;

export namespace compiler
{
	export enum class number_literal_system : std::uint8_t
	{
		decimal,
		hexadecimal,
		binary,
		octal
	};

	export enum class number_literal_type : std::uint8_t
	{
		int8,
		int16,
		int32,
		int64
	};

	export struct number_literal
	{
		bool success : 1;
		number_literal_system system : 2;
		number_literal_type type : 3;
		builtin_literal_type literal;
	};

	constexpr number_literal_type get_minimum_type(const std::uintmax_t integer) noexcept
	{
		if (std::numeric_limits<std::uint8_t>::max() >= integer)
		{
			return number_literal_type::int8;
		}

		if (std::numeric_limits<std::uint16_t>::max() >= integer)
		{
			return number_literal_type::int16;
		}

		if (std::numeric_limits<std::uint32_t>::max() >= integer)
		{
			return number_literal_type::int32;
		}

		return number_literal_type::int64;
	}

	int get_base_for_system(const number_literal_system system) noexcept
	{
		switch (system)
		{
		case number_literal_system::decimal:
			return 10;
		case number_literal_system::hexadecimal:
			return 16;
		case number_literal_system::octal:
			return 8;
		case number_literal_system::binary:
			return 2;
		default:
			std::unreachable();
		}
	}

	number_literal parse(const std::string_view& number_literal, const number_literal_system system, 
						 std::errc& error_code) noexcept
	{
		auto integer{ std::uintmax_t{} };

		const auto begin = number_literal.data();
		const auto end = number_literal.data() + number_literal.size();

		[[likely]]
		if (auto [ptr, ec]
		{
			std::from_chars(begin, end, integer, get_base_for_system(system))
		}; ec == std::errc())
		{
			return { true, system, get_minimum_type(integer), integer };
		}
		else
		{
			error_code = ec;
		}

		return {};
	}

	number_literal parse_hexadecimal(const std::shared_ptr<syntax_token>& number_token,
									 const std::shared_ptr<diagnostic_list>& diagnostics) noexcept
	{
		const auto& literal{ number_token->text };
		auto error_code{ std::errc{} };
		const auto number_literal{ parse(literal, number_literal_system::hexadecimal, error_code) };
		[[unlikely]] if (error_code != std::errc())
		{
			diagnostics->report_invalid_hexadecimal(number_token->span());
		}

		return number_literal;
	}

	number_literal parse_octal(const std::shared_ptr<syntax_token>& number_token,
							   const std::shared_ptr<diagnostic_list>& diagnostics) noexcept
	{
		const auto& literal{ number_token->text };
		auto error_code{ std::errc{} };
		const auto number_literal{ parse(literal, number_literal_system::hexadecimal, error_code) };
		[[unlikely]] if (error_code != std::errc())
		{
			diagnostics->report_invalid_hexadecimal(number_token->span(), number_token->text);
		}
	}

	number_literal parse_binary(const std::shared_ptr<syntax_token>& number_token,
								const std::shared_ptr<diagnostic_list>& diagnostics) noexcept
	{
		const auto& literal{ number_token->text };
		auto error_code{ std::errc{} };
		const auto number_literal{ parse(literal, number_literal_system::octal, error_code) };
		[[unlikely]] if (error_code != std::errc())
		{
			diagnostics->report_invalid_hexadecimal(number_token->span(), number_token->text);
		}
	}

	number_literal parse_decimal(const std::shared_ptr<syntax_token>& number_token,
								 const std::shared_ptr<diagnostic_list>& diagnostics) noexcept
	{
		const auto& literal{ number_token->text };
		auto error_code{ std::errc{} };
		const auto number_literal{ parse(literal, number_literal_system::decimal, error_code) };
		[[unlikely]] if (error_code != std::errc())
		{
			diagnostics->report_invalid_decimal(number_token->span(), number_token->text);
		}
	}

	number_literal parse_floating_point(const std::string_view& number_literal) noexcept
	{
	}
}