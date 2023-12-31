export module compiler.binary_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class binary_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<expression_syntax> left;
		const std::shared_ptr<syntax_token> operator_token;
		const std::shared_ptr<expression_syntax> right;

		[[nodiscard]] binary_expression_syntax(const std::shared_ptr<expression_syntax>& left,
		                                       const std::shared_ptr<syntax_token>& operator_token,
		                                       const std::shared_ptr<expression_syntax>& right)
			noexcept : left(left), operator_token(operator_token), right(right)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::binary_expression;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {left, operator_token, right};
		}
	};
}
