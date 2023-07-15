export module compiler.variable_declaration_syntax;

import std;

import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class variable_declaration_syntax final : public statement_syntax
	{
	public:
		using super = statement_syntax;

		const std::shared_ptr<syntax_token> type_identifier_token;
		const std::shared_ptr<syntax_token> identifier_token;
		const std::shared_ptr<syntax_token> equals_token;
		const std::shared_ptr<expression_syntax> initializer;

		[[nodiscard]] variable_declaration_syntax(const std::shared_ptr<syntax_token>& type_identifier_token,
		                                          const std::shared_ptr<syntax_token>& identifier_token,
		                                          const std::shared_ptr<syntax_token>& equals_token,
		                                          const std::shared_ptr<expression_syntax>& initializer)
			noexcept : type_identifier_token(type_identifier_token),
			           identifier_token(identifier_token),
			           equals_token(equals_token),
			           initializer(initializer)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::variable_declaration;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {type_identifier_token, identifier_token, equals_token, initializer};
		}
	};
}
