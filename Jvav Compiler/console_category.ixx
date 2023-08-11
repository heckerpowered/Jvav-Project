export module compiler.console_category;

import std;

import compiler.console_error;

namespace compiler {
	export class console_category final : public std::error_category
	{
	public:
		using super = std::error_category;

		const char* name() const noexcept override
		{
			return "console";
		}

		std::string message(const int error_code) const override
		{
			switch (static_cast<console_error>(error_code)) {
			case console_error::invalid_console_color:
				return "Invalid console color";
			default:
				return "unknow error";
			}
		}
	};
}