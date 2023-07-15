export module compiler.binder;

import std;

import compiler.diagnostic_list;
import compiler.bound_scope;

namespace compiler
{
	export class binder final
	{
		diagnostic_list& diagnostics;
		std::shared_ptr<bound_scope> scope;

	public:
		[[nodiscard]] binder(const std::shared_ptr<bound_scope>& parent, diagnostic_list& diagnostics)
			noexcept : diagnostics(diagnostics), scope(scope)
		{
		}
	};
}
