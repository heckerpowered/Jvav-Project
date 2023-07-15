export module compiler.syntax_node;

import std;

import compiler.syntax_kind;
import compiler.text_span;

namespace compiler
{
	export class syntax_node
	{
	public:
		[[nodiscard]] virtual syntax_kind kind() const noexcept = 0;
		[[nodiscard]] virtual std::vector<std::shared_ptr<syntax_node>> children() const noexcept = 0;

		virtual text_span span() const noexcept
		{
			const auto children = this->children();
			const auto first = children.front()->span();
			const auto last = children.back()->span();

			return text_span::from_bounds(first.start, last.start);
		}
	};
}
