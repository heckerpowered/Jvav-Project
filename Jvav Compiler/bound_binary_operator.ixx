export module compiler.bound_binary_operator;

import std;

import compiler.bound_binary_operator_kind;
import compiler.syntax_kind;
import compiler.type_symbol;

namespace compiler
{
	export class bound_binary_operator final
	{
	private:
		[[nodiscard]] bound_binary_operator(const syntax_kind syntax_kind, const bound_binary_operator_kind kind,
											const type_symbol& type) noexcept :
			bound_binary_operator(syntax_kind, kind, type, type)
		{
		}

		[[nodiscard]] bound_binary_operator(const syntax_kind syntax_kind, const bound_binary_operator_kind kind,
											const type_symbol& operand_type, const type_symbol& result_type) noexcept :
			bound_binary_operator(syntax_kind, kind, operand_type, operand_type, result_type)
		{
		}

		[[nodiscard]] bound_binary_operator(const syntax_kind syntax_kind, const bound_binary_operator_kind kind,
											const type_symbol& left_type, const type_symbol& right_type,
											const type_symbol& result_type) noexcept :
			syntax_kind(syntax_kind), kind(kind), left_type(left_type), right_type(right_type), result_type(result_type)
		{
		}

	public:
		const syntax_kind syntax_kind;
		const bound_binary_operator_kind kind;
		const type_symbol left_type;
		const type_symbol right_type;
		const type_symbol result_type;

		static std::array<bound_binary_operator, 20> operators;

		static std::shared_ptr<bound_binary_operator> bind()
		{
		}
	};

	std::array<bound_binary_operator, 20> bound_binary_operator::operators = {
		bound_binary_operator(syntax_kind::plus_token, bound_binary_operator_kind::addition, int_type),
		bound_binary_operator(syntax_kind::minus_token, bound_binary_operator_kind::subtraction, int_type),
		bound_binary_operator(syntax_kind::multiplication_token, bound_binary_operator_kind::multiplication, int_type),
		bound_binary_operator(syntax_kind::slash_token, bound_binary_operator_kind::division, int_type),
		bound_binary_operator(syntax_kind::equals_equals_token, bound_binary_operator_kind::equals, int_type,
							  bool_type),
		bound_binary_operator(syntax_kind::bang_equals_token, bound_binary_operator_kind::not_equals, int_type,
							  bool_type),
		bound_binary_operator(syntax_kind::ampersand_token, bound_binary_operator_kind::bitwise_and, int_type),
		bound_binary_operator(syntax_kind::pipe_token, bound_binary_operator_kind::bitwise_or, int_type),
		bound_binary_operator(syntax_kind::hat_token, bound_binary_operator_kind::bitwise_xor, int_type),
		bound_binary_operator(syntax_kind::less_token, bound_binary_operator_kind::less, int_type, bool_type),
		bound_binary_operator(syntax_kind::less_or_equals_token, bound_binary_operator_kind::less_or_equals, int_type,
							  bool_type),
		bound_binary_operator(syntax_kind::greater_token, bound_binary_operator_kind::greater, int_type, bool_type),
		bound_binary_operator(syntax_kind::greater_or_equals_token, bound_binary_operator_kind::greater_or_equals,
							  int_type, bool_type),

		bound_binary_operator(syntax_kind::ampersand_token, bound_binary_operator_kind::bitwise_and, bool_type),
		bound_binary_operator(syntax_kind::ampersand_ampersand_token, bound_binary_operator_kind::logical_and,
							  bool_type),
		bound_binary_operator(syntax_kind::pipe_token, bound_binary_operator_kind::bitwise_or, bool_type),
		bound_binary_operator(syntax_kind::pipe_pipe_token, bound_binary_operator_kind::logical_or, bool_type),
		bound_binary_operator(syntax_kind::hat_token, bound_binary_operator_kind::bitwise_xor, bool_type),
		bound_binary_operator(syntax_kind::equals_equals_token, bound_binary_operator_kind::equals, bool_type),
		bound_binary_operator(syntax_kind::bang_equals_token, bound_binary_operator_kind::not_equals, bool_type)
	};
}
