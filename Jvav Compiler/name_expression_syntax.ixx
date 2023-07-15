export module compiler.name_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class name_expression_syntax final : public expression_syntax
	{
	public:
		using super = expression_syntax;

		const std::shared_ptr<syntax_token> identifier_token;

		[[nodiscard]] name_expression_syntax(const std::shared_ptr<syntax_token>& identifier_token)
			noexcept : identifier_token(identifier_token)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::name_expression;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {identifier_token};
		}
	};
}
