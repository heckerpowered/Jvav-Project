export module compiler.console_target;

import std;

import compiler.logger_target;

namespace compiler
{
	export class console_target final : public target
	{
	public:
		using super = target;

		void write(std::string_view const string) const noexcept override
		{
			std::cout << string;
		}
	};
}