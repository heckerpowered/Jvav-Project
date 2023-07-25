export module compiler.lexical_analyzer;

import std;

import compiler.syntax_facts;
import compiler.syntax_token;
import compiler.syntax_kind;
import compiler.diagnostic_list;

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
				diagnostic_list->report_bad_character(text_span(start, length), current());
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
			while (std::isalpha(current()) || std::isdigit(current()) || current() == '_')
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
			const auto start{ position };
			while (std::isdigit(current()))
			{
				next();
			}

			const auto length{ position - start };
			return std::make_shared<syntax_token>(syntax_kind::literal_token, start, text.substr(start, length));
		}
	};

	using lexer = lexical_analyzer;
	using scanner = lexer;
}
