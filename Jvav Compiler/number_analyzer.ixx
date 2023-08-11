export module compiler.number_analyzer;

import std;

import compiler.diagnostic_list;

namespace compiler
{
	export class number_analyzer
	{
	private:
		const std::string_view number;
		const std::shared_ptr<diagnostic_list> diagnostics;
		const std::string_view::const_iterator iterator;

	public:
		[[nodiscard]] number_analyzer(const std::string_view& number, const std::shared_ptr<diagnostic_list>& diagnostics) 
			noexcept : number{ number }, diagnostics{ diagnostics }, iterator{ this->number.begin() }
		{
		}
	};
}