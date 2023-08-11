export module compiler.literal_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.literal_variant;
import compiler.syntax_token;

namespace compiler
{
	export class literal_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<syntax_token> literal_token;
		const builtin_literal_type value;

		literal_expression_syntax(const std::shared_ptr<syntax_token>& literal_token)
			noexcept : literal_token{ literal_token }, value{ literal_token->value }
		{
		}

		literal_expression_syntax(const std::shared_ptr<syntax_token>& literal_token, const builtin_literal_type& value)
			noexcept : literal_token{ literal_token }, value{ value }
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::number_literal_expression;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return { literal_token };
		}
	};
}
