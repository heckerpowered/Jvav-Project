export module compiler.parenthesized_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class parenthesized_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<syntax_token> open_parenthesis_token;
		const std::shared_ptr<expression_syntax> expression;
		const std::shared_ptr<syntax_token> close_parenthesis_token;

		[[nodiscard]] parenthesized_expression_syntax(const std::shared_ptr<syntax_token>& open_parenthesis_token,
		                                              const std::shared_ptr<expression_syntax>& expression,
		                                              const std::shared_ptr<syntax_token>& close_parenthesis_token)
			noexcept :
			open_parenthesis_token(open_parenthesis_token), expression(expression),
			close_parenthesis_token(close_parenthesis_token)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::parenthesized_expression;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {open_parenthesis_token, expression, close_parenthesis_token};
		}
	};
}
