export module compiler.diagnostic_list;

import std;

import compiler.syntax_kind;
import compiler.diagnostic;
import compiler.text_span;
import compiler.zero_copy;

namespace compiler
{
	export class diagnostic_list final
	{
		std::vector<diagnostic> diagnostic;

		void add_range(const std::vector<compiler::diagnostic>& range) noexcept
		{
			// cannot use insert, diagnostic& operator=(diagnostic const&) is implicitly removed by the compiler.
			for (auto&& value : range)
			{
				diagnostic.emplace_back(value);
			}
		}

		void report(const text_span& span, const std::string& message) noexcept
		{
			diagnostic.emplace_back(span, message);
			std::cout << message << std::endl;
		}

	public:
		[[nodiscard]] constexpr auto begin() noexcept
		{
			return diagnostic.begin();
		}

		[[nodiscard]] constexpr auto end() noexcept
		{
			return diagnostic.end();
		}

		[[nodiscard]] constexpr auto empty() const noexcept
		{
			return diagnostic.empty();
		}

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
