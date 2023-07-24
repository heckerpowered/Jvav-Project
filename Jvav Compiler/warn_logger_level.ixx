export module compiler.warn_logger_level;

import std;

import compiler.logger_level;

namespace compiler
{
	export class warn_logger_level final : public logger_level
	{
	public:
		using super = logger_level;

	private:
		[[nodiscard]] warn_logger_level() noexcept
		{
		}

		std::string name() const noexcept override
		{
			return "WARN";
		}

	public:
		static warn_logger_level get() noexcept
		{
			static auto instance{ warn_logger_level{} };
			return instance;
		}
	};
}