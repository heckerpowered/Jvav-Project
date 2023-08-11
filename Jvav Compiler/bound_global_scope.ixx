export module combound_global_scope;

import std;

import compiler.diagnostic_list;
import compiler.variable_symbol;
import compiler.bound_statement;

namespace compiler
{
	export class bound_global_scope final
	{
	public:
		std::shared_ptr<bound_global_scope> previous;
		const std::shared_ptr<diagnostic_list>& diagnostics;
		const std::vector<variable_symbol> variables;
		const std::shared_ptr<bound_statement> statement;

		[[nodiscard]] bound_global_scope(const std::shared_ptr<bound_global_scope>& previous,
										 const std::shared_ptr<diagnostic_list>& diagnostics,
										 const std::vector<variable_symbol>& variables,
										 const std::shared_ptr<bound_statement>& statement) noexcept :
			previous{ previous },
			diagnostics{ diagnostics },
			variables{ variables },
			statement{ statement }
		{
		}
	};
}