export module compiler.symbol_kind;

namespace compiler
{
	export enum class symbol_kind
	{
		function,
		global_variable,
		local_variable,
		parameter,
		type
	};
}
