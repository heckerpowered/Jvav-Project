export module compiler.bound_node_kind;

import std;

namespace compiler
{
	export enum class bound_node_kind
	{
		unary_expression,
		literal_expression,
		variable_expression,
		assignment_expression,
		block_statement,
		expression_statement,
		variable_declaration,
		if_statement,
		while_statement,
		for_statement
	};

	export [[nodiscard]] constexpr std::string_view to_string(const bound_node_kind kind) noexcept
	{
		switch (kind)
		{
		case bound_node_kind::unary_expression:
			return "UnaryExpression";
		case bound_node_kind::literal_expression:
			return "LiteralExpression";
		case bound_node_kind::variable_expression:
			return "VariableExpression";
		case bound_node_kind::assignment_expression:
			return "AssignmentExpression";
		case bound_node_kind::block_statement:
			return "BlockStatement";
		case bound_node_kind::expression_statement:
			return "ExpressionStatement";
		case bound_node_kind::variable_declaration:
			return "VariableDeclaration";
		case bound_node_kind::if_statement:
			return "IfStatement";
		case bound_node_kind::while_statement:
			return "WhileStatement";
		case bound_node_kind::for_statement:
			return "ForStatement";
		default:
			return "Unknown";
		}
	}
}
