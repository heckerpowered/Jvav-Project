export module compiler.unary_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class unary_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<syntax_token> operator_token;
		const std::shared_ptr<expression_syntax> operand;

		[[nodiscard]] unary_expression_syntax(const std::shared_ptr<syntax_token>& operator_token,
		                                      const std::shared_ptr<expression_syntax>& operand)
			noexcept : operator_token(operator_token), operand(operand)
		{
		}

		virtual syntax_kind kind() const noexcept override
		{
			return syntax_kind::unary_expression;
		}

		virtual const std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {operator_token, operand};
		}
	};
}
