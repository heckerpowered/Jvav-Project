export module compiler.diagnostic;

import std;
import compiler.text_span;

namespace compiler
{
	export class diagnostic final
	{
	public:
		const text_span span;
		const std::string message;

		[[nodiscard]] diagnostic(const text_span& span, const std::string& message)
			noexcept : span(span), message(message)
		{
		}
	};
}
