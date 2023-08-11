export module compiler.syntax_kind;

import std;

namespace compiler
{
	export enum class syntax_kind
	{
		// Tokens
		floating_point_token,
		double_precision_floating_point_token,
		int8_token,
		int16_token,
		int32_token,
		int64_token,
		whitespace_token,
		slash_token,
		minus_token,
		multiplication_token,
		plus_token,
		open_parenthesis_token,
		close_parenthesis_token,
		bad_token,
		end_token,
		identifier_token,
		bang_token,
		ampersand_ampersand_token,
		pipe_pipe_token,
		equals_equals_token,
		bang_equals_token,
		equals_token,
		close_brace_token,
		open_brace_token,
		less_token,
		less_or_equals_token,
		greater_token,
		greater_or_equals_token,
		ampersand_token,
		pipe_token,
		tilde_token,
		hat_token,
		dot_token,

		// Nodes
		compilation_unit,
		else_clause,

		// Statements
		block_statement,
		expression_statement,
		variable_declaration,
		if_statement,
		while_statement,
		for_statement,

		// Expressions
		binary_expression,
		parenthesized_expression,
		unary_expression,
		number_literal_expression,
		boolean_literal_expression,
		name_expression,
		assignment_expression,

		// Keywords
		true_keyword,
		false_keyword,
		auto_keyword,
		if_keyword,
		else_keyword,
		while_keyword,
		for_keyword,
	};

	export [[nodiscard]] constexpr std::string_view to_string(const syntax_kind kind) noexcept
	{
		switch (kind)
		{
		case syntax_kind::int8_token:
			return "Int8Token";
		case syntax_kind::int16_token:
			return "Int16Token";
		case syntax_kind::int32_token:
			return "Int32Token";
		case syntax_kind::int64_token:
			return "Int64Token";
		case syntax_kind::floating_point_token:
			return "FloatingPointToken";
		case syntax_kind::double_precision_floating_point_token:
			return "DoublePrecisionFloatingPointToken";
		case syntax_kind::whitespace_token:
			return "WhitespaceToken";
		case syntax_kind::slash_token:
			return "SlashToken";
		case syntax_kind::minus_token:
			return "MinusToken";
		case syntax_kind::multiplication_token:
			return "MultiplicationToken";
		case syntax_kind::plus_token:
			return "PlusToken";
		case syntax_kind::open_parenthesis_token:
			return "OpenParenthesisToken";
		case syntax_kind::close_parenthesis_token:
			return "CloseParenthesisToken";
		case syntax_kind::bad_token:
			return "BadToken";
		case syntax_kind::end_token:
			return "EndToken";
		case syntax_kind::identifier_token:
			return "IdentifierToken";
		case syntax_kind::bang_token:
			return "BangToken";
		case syntax_kind::ampersand_ampersand_token:
			return "AmpersandAmpersandToken";
		case syntax_kind::pipe_pipe_token:
			return "PipePipeToken";
		case syntax_kind::equals_equals_token:
			return "EqualsEqualsToken";
		case syntax_kind::bang_equals_token:
			return "BangEqualsToken";
		case syntax_kind::equals_token:
			return "EqualsToken";
		case syntax_kind::close_brace_token:
			return "CloseBraceToken";
		case syntax_kind::open_brace_token:
			return "OpenBraceToken";
		case syntax_kind::less_token:
			return "LessToken";
		case syntax_kind::less_or_equals_token:
			return "LessOrEqualsToken";
		case syntax_kind::greater_token:
			return "GreaterToken";
		case syntax_kind::ampersand_token:
			return "AmpersandToken";
		case syntax_kind::pipe_token:
			return "PipeToken";
		case syntax_kind::tilde_token:
			return "TildeToken";
		case syntax_kind::hat_token:
			return "HatToken";
		case syntax_kind::compilation_unit:
			return "ComplicationUnit";
		case syntax_kind::else_clause:
			return "ElseClause";
		case syntax_kind::block_statement:
			return "BlockStatement";
		case syntax_kind::expression_statement:
			return "ExpressionStatement";
		case syntax_kind::variable_declaration:
			return "VariableDeclaration";
		case syntax_kind::if_statement:
			return "IfStatement";
		case syntax_kind::while_statement:
			return "WhileStatement";
		case syntax_kind::for_statement:
			return "ForStatement";
		case syntax_kind::binary_expression:
			return "BinaryExpression";
		case syntax_kind::parenthesized_expression:
			return "ParenthesizedExpression";
		case syntax_kind::unary_expression:
			return "UnaryExpression";
		case syntax_kind::number_literal_expression:
			return "NumberLiteralExpression";
		case syntax_kind::boolean_literal_expression:
			return "BooleanLiteralExpression";
		case syntax_kind::name_expression:
			return "NameExpression";
		case syntax_kind::assignment_expression:
			return "AssignmentExpression";
		case syntax_kind::true_keyword:
			return "TrueKeyword";
		case syntax_kind::false_keyword:
			return "FalseKeyword";
		case syntax_kind::auto_keyword:
			return "AutoKeyword";
		case syntax_kind::if_keyword:
			return "IfKeyword";
		case syntax_kind::else_keyword:
			return "ElseKeyword";
		case syntax_kind::while_keyword:
			return "WhileKeyword";
		case syntax_kind::for_keyword:
			return "ForKeyword";
		default:
			return "Unknown";
		}
	}
}
