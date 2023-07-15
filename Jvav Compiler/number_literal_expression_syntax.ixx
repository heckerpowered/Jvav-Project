export module compiler.number_literal_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class number_literal_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<syntax_token> literal_token;

		number_literal_expression_syntax(const std::shared_ptr<syntax_token>& literal_token)
			noexcept : literal_token(literal_token)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::number_literal_expression;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {literal_token};
		}
	};
}
