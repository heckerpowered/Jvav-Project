export module compiler.assignment_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class assignment_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<syntax_token> identifier_token;
		const std::shared_ptr<syntax_token> equals_token;
		const std::shared_ptr<expression_syntax> expression;

		[[nodiscard]] assignment_expression_syntax(const std::shared_ptr<syntax_token>& identifier_token,
		                                           const std::shared_ptr<syntax_token>& equals_token,
		                                           const std::shared_ptr<expression_syntax>& expression) noexcept :
			identifier_token(identifier_token), equals_token(equals_token), expression(expression)
		{
		};

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::assignment_expression;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {identifier_token, equals_token, expression};
		}
	};
}
