export module combound_global_scope;

import std;

import compiler.diagnostic_list;

namespace compiler
{
	export class bound_global_scope final
	{
	public:
		std::shared_ptr<bound_global_scope> previous;
		const diagnostic_list& diagnostics;

	};
}