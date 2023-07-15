export module compiler.bound_binary_operator_kind;

namespace compiler
{
	export enum class bound_binary_operator_kind
	{
		addition,
		subtration,
		multiplication,
		division,
		logical_and,
		logical_or,
		equals,
		not_equals,
		less,
		less_or_equals,
		greater,
		greater_or_equals,
		bitwise_and,
		bitwise_xor,
		bitwise_or
	};
}
