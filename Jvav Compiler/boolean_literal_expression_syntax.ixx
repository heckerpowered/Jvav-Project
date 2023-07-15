export module compiler.boolean_literal_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class boolean_literal_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<syntax_token> literal_token;

		[[nodiscard]] boolean_literal_expression_syntax(const std::shared_ptr<syntax_token>& literal_token)
			noexcept : literal_token(literal_token)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::boolean_literal_expression;
		}

		const std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {literal_token};
		}
	};
}
