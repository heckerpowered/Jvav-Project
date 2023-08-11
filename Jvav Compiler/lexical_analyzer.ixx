export module compiler.lexical_analyzer;

import std;

import compiler.diagnostic_list;
import compiler.integer_type;
import compiler.syntax_facts;
import compiler.syntax_token;
import compiler.syntax_kind;


namespace compiler
{
	export class lexical_analyzer
	{
	private:
		const std::string_view text;
		std::size_t position;
		const std::shared_ptr<diagnostic_list> diagnostic_list;

	public:
		[[nodiscard]] lexical_analyzer(const std::string_view& text, const std::shared_ptr<compiler::diagnostic_list>& diagnostic_list)
			noexcept : text(text), position(), diagnostic_list(diagnostic_list)
		{
		}

	private:
		[[nodiscard]] char current() noexcept
		{
			return peek(0);
		}

		[[nodiscard]] char lookahead() noexcept
		{
			return peek(1);
		}

		[[nodiscard]] char peek(const std::size_t offset) noexcept
		{
			const auto index{ position + offset };

			if (index >= text.length())
			{
				return '\0';
			}

			return text[index];
		}

		std::size_t next() noexcept
		{
			return position++;
		}

	public:
		std::shared_ptr<syntax_token> analyze() noexcept
		{
			const auto start{ position };
			auto kind{ syntax_kind::bad_token };

			switch (current())
			{
			case '\0':
				kind = syntax_kind::end_token;
				next();
				break;

			case '+':
				kind = syntax_kind::plus_token;
				next();
				break;

			case '-':
				kind = syntax_kind::minus_token;
				next();
				break;

			case '*':
				kind = syntax_kind::multiplication_token;
				next();
				break;

			case '/':
				kind = syntax_kind::slash_token;
				next();
				break;

			case '(':
				kind = syntax_kind::open_parenthesis_token;
				next();
				break;

			case ')':
				kind = syntax_kind::close_parenthesis_token;
				next();
				break;

			case '{':
				kind = syntax_kind::open_brace_token;
				next();
				break;

			case '}':
				kind = syntax_kind::close_brace_token;
				next();
				break;

			case '&':
				if (lookahead() == '&')
				{
					kind = syntax_kind::ampersand_token;
					position += 2;
				}
				else
				{
					kind = syntax_kind::ampersand_ampersand_token;
					next();
				}
				break;

			case '|':
				if (lookahead() == '|')
				{
					kind = syntax_kind::pipe_pipe_token;
					position += 2;
				}
				else
				{
					kind = syntax_kind::pipe_token;
					next();
				}
				break;

			case '=':
				if (lookahead() == '=')
				{
					kind = syntax_kind::equals_equals_token;
					position += 2;
				}
				else
				{
					kind = syntax_kind::equals_token;
					next();
				}
				break;

			case '~':
				kind = syntax_kind::tilde_token;
				next();
				break;

			case '^':
				kind = syntax_kind::hat_token;
				next();
				break;

			case '!':
				if (lookahead() == '=')
				{
					kind = syntax_kind::bang_equals_token;
					position += 2;
				}
				else
				{
					kind = syntax_kind::bang_token;
					next();
				}
				break;

			case '<':
				if (lookahead() == '=')
				{
					kind = syntax_kind::less_or_equals_token;
					position += 2;
				}
				else
				{
					kind = syntax_kind::less_token;
					next();
				}
				break;

			case '>':
				if (lookahead() == '=')
				{
					kind = syntax_kind::greater_or_equals_token;
					position += 2;
				}
				else
				{
					kind = syntax_kind::greater_token;
					next();
				}
				break;
			case '.':
				if (std::isdigit(lookahead()))
				{
					return analyze_number_token();
				}
				else
				{
					kind = syntax_kind::dot_token;
					next();
				}
				break;

			default:
				if (std::isdigit(current()))
				{
					return analyze_number_token();
				}
				if (std::isspace(current()))
				{
					return analyze_whitespace();
				}
				if (std::isalpha(current()))
				{
					return analyze_alpha();
				}
			}

			const auto length{ position - start };
			const auto text{ this->text.substr(start, length) };
			if (kind == syntax_kind::bad_token) [[unlikely]]
			{
				diagnostic_list->report_bad_character(text_span{ start, length }, current());
				next();
			}
			return std::make_shared<syntax_token>(kind, start, text);
		}

	private:
		[[nodiscard]] std::shared_ptr<syntax_token> analyze_alpha() noexcept
		{
			const auto start{ position };

			// Digits can be part of an identifier, but not at the beginning
			// of an identifier
			while (std::isalpha(current()) || 
				   std::isdigit(current()) || 
				   current() == '_' ||
				   current() == '-')
			{
				next();
			}

			const auto length{ position - start };
			const auto text{ this->text.substr(start, length) };
			return std::make_shared<syntax_token>(syntax_facts::get_keyword_kind(text), start, text);
		}

		[[nodiscard]] std::shared_ptr<syntax_token> analyze_whitespace() noexcept
		{
			const auto start{ position };
			while (std::isspace(current()))
			{
				next();
			}

			const auto length{ position - start };
			return std::make_shared<syntax_token>(syntax_kind::whitespace_token, start, text.substr(start, length));
		}

		[[nodiscard]] std::shared_ptr<syntax_token> analyze_number_token() noexcept
		{
			if (current() == '0')
			{
				if (lookahead() == 'x' || lookahead() == 'X')
				{
					return analyze_hexadecimal();
				}
				else if (lookahead() == 'b' || lookahead() == 'B')
				{
					return analyze_binary();
				}
				else
				{
					return analyze_octal();
				}
			}
			else if (std::isdigit(current()))
			{
				return analyze_decimal();
			}
			else if (current() == '.')
			{
				return analyze_floating_point();
			}

			std::unreachable();
		}

		[[nodiscard]] std::shared_ptr<syntax_token> analyze_binary() noexcept
		{
			// Skip 0b prefix
			position += 2;

			const auto start{ position };
			while (current() == '0' ||
				   current() == '1')
			{
				next();
			}

			const auto length{ position - start };
			const auto integer_string{ text.substr(start, length) };
			auto integer{ std::uintmax_t{} };

			const auto begin{ integer_string.data() };
			const auto end{ integer_string.data() + integer_string.size() };
			if (auto [ptr, ec]
			{
				std::from_chars(begin, end, integer, 8)
			}; ec == std::errc())
			{
				return std::make_shared<syntax_token>(get_minimum_syntax_kind(integer), start, integer_string,
													  integer);
			}
			diagnostic_list->report_invalid_number({ start, length }, integer_string);
			return std::make_shared<syntax_token>(syntax_kind::bad_token, start, integer_string);
		}

		[[nodiscard]] std::shared_ptr<syntax_token> analyze_octal() noexcept
		{
			// Skip 0 prefix
			next();

			const auto start{ position };
			while (current() >= '0' &&
				   current() < '8')
			{
				next();
			}

			const auto length{ position - start };
			const auto integer_string{ text.substr(start, length) };
			auto integer{ std::uintmax_t{} };

			const auto begin{ integer_string.data() };
			const auto end{ integer_string.data() + integer_string.size() };
			if (auto [ptr, ec]
			{
				std::from_chars(begin, end, integer, 8)
			}; ec == std::errc())
			{
				return std::make_shared<syntax_token>(get_minimum_syntax_kind(integer), start, integer_string,
													  integer);
			}
			diagnostic_list->report_invalid_number({ start, length }, integer_string);
			return std::make_shared<syntax_token>(syntax_kind::bad_token, start, integer_string);
		}

		[[nodiscard]] std::shared_ptr<syntax_token> analyze_hexadecimal() noexcept
		{
			// Skip 0x prefix
			position += 2;

			const auto start{ position };
			while (std::isdigit(current()) ||
				   (current() >= 'a' && current() <= 'f') ||
				   (current() >= 'A' && current() <= 'F'))
			{
				next();
			}

			const auto length{ position - start };
			const auto integer_string{ text.substr(start, length) };
			auto integer{ std::uintmax_t{} };

			const auto begin{ integer_string.data() };
			const auto end{ integer_string.data() + integer_string.size() };
			if (auto [ptr, ec]
			{
				std::from_chars(begin, end, integer, 16)
			}; ec == std::errc())
			{
				return std::make_shared<syntax_token>(get_minimum_syntax_kind(integer), start, integer_string,
													  integer);
			}
			diagnostic_list->report_invalid_number({ start, length }, integer_string);
			return std::make_shared<syntax_token>(syntax_kind::bad_token, start, integer_string);
		}

		[[nodiscard]] std::shared_ptr<syntax_token> analyze_decimal() noexcept
		{
			const auto start{ position };
			while (std::isdigit(current()))
			{
				if (current() == 'E' ||
					current() == 'e')
				{
					position = start;
					return analyze_floating_point();
				}
				next();
			}

			const auto length{ position - start };
			const auto integer_string{ text.substr(start, length) };
			auto integer{ std::uintmax_t{} };

			const auto begin{ integer_string.data() };
			const auto end{ integer_string.data() + integer_string.size() };
			if (auto [ptr, ec]
			{
				std::from_chars(begin, end, integer, 10)
			}; ec == std::errc())
			{
				return std::make_shared<syntax_token>(get_minimum_syntax_kind(integer), start, integer_string, 
													  integer);
			}
			diagnostic_list->report_invalid_number({ start, length }, integer_string);
			return std::make_shared<syntax_token>(syntax_kind::bad_token, start, integer_string);
		}

		[[nodiscard]] std::shared_ptr<syntax_token> analyze_floating_point() noexcept
		{
			const auto starts_with_dot{ current() == '.' };
			const auto start{ position };
			while (std::isdigit(current()) ||
				   current() == 'e' ||
				   current() == 'E' ||
				   current() == '+' ||
				   current() == '-' ||
				   current() == '.' ||
				   current() == 'F' ||
				   current() == 'f')
			{
				if (current() == 'f' ||
					current() == 'F')
				{
					const auto length{ position - start };
					const auto floating_point_string{ text.substr(start, length) };
					auto floating_point{ float{} };

					const auto begin{ floating_point_string.data() };
					const auto end{ floating_point_string.data() + floating_point_string.size() };
					if (auto [ptr, ec]
					{
						std::from_chars(begin, end, floating_point, std::chars_format::general)
					}; ec == std::errc())
					{
						return std::make_shared<syntax_token>(syntax_kind::floating_point_token, start, floating_point_string,
															  floating_point);
					}
					diagnostic_list->report_invalid_number({ start, length }, floating_point_string);
					return std::make_shared<syntax_token>(syntax_kind::bad_token, start, floating_point_string);
				}
				next();
			}

			const auto length{ position - start };
			const auto floating_point_string{ text.substr(start, length) };
			auto floating_point{ double{} };

			const auto begin{ floating_point_string.data() };
			const auto end{ floating_point_string.data() + floating_point_string.size() };
			if (auto [ptr, ec]
			{
				std::from_chars(begin, end, floating_point, std::chars_format::general)
			}; ec == std::errc())
			{
				return std::make_shared<syntax_token>(syntax_kind::double_precision_floating_point_token, start, floating_point_string,
													  floating_point);
			}
			diagnostic_list->report_invalid_number({ start, length }, floating_point_string);
			return std::make_shared<syntax_token>(syntax_kind::bad_token, start, floating_point_string);
		}
	};

	using lexer = lexical_analyzer;
	using scanner = lexer;
}
