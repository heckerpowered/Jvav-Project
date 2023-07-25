export module compiler.diagnostic_list;

import std;

import compiler.syntax_kind;
import compiler.diagnostic;
import compiler.text_span;
import compiler.zero_copy;

namespace compiler
{
	export class diagnostic_list final : public std::vector<diagnostic>
	{
	public:
		using super = std::vector<diagnostic>;

	private:
		void report(const text_span& span, const std::string& message) noexcept
		{
			emplace_back(span, message);
		}

	public:
		void report_unexpected_token(const text_span& span, const syntax_kind actual_kind,
		                             const syntax_kind expected_kind) noexcept
		{
			// Formatting makes IntelliSense crash, Visual Studio 2022 17.7.0 Preview 2
#ifndef __INTELLISENSE__
			const auto message{ std::format("Unexpected token {}, expected {}", compiler::to_string(actual_kind),
											 compiler::to_string(expected_kind)) };
			report(span, message);
#endif // __INTELLISENSE__
		}

		void report_bad_character(const text_span& span, const char character) noexcept
		{
			// Formatting makes IntelliSense crash, Visual Studio 2022 17.7.0 Preview 2
#ifndef __INTELLISENSE__
			const auto message{ std::format("Bad character input {}", character) };
			report(span, message);
#endif // __INTELLISENSE__
		}
	};
}
