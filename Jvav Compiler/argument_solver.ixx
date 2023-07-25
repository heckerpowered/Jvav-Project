export module compiler.argument_solver;

import std;

namespace compiler
{
	export std::map<std::string_view, std::vector<std::string_view>>
	solve_arguments(const std::vector<std::string_view>& arguments) noexcept
	{
		auto solved_arguments = std::map<std::string_view, std::vector<std::string_view>>();

		for (const auto& argument : arguments)
		{
			const auto position = argument.find('=');
			if (position == std::string_view::npos)
			{
				solved_arguments.try_emplace(argument);
			}
			else
			{
				auto name = argument.substr(0, position);
				auto value = argument.substr(position + 1);
				solved_arguments[name].push_back(value);
			}
		}

		return solved_arguments;
	}
}
