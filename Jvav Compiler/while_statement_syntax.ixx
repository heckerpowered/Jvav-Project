export module compiler.while_statement_syntax;

import std;

import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class while_statement_syntax final : public statement_syntax
	{
	public:
		using super = statement_syntax;

		const std::shared_ptr<syntax_token> keyword;
		const std::shared_ptr<expression_syntax> condition;
		const std::shared_ptr<statement_syntax> body;

		[[nodiscard]] while_statement_syntax(const std::shared_ptr<syntax_token>& keyword,
		                                     const std::shared_ptr<expression_syntax>& condition,
		                                     const std::shared_ptr<statement_syntax>& body)
			noexcept : keyword(keyword), condition(condition), body(body)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::while_statement;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {keyword, condition, body};
		}
	};
}
