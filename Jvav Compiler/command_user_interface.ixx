export module compiler.command_user_interface;

import std;

import compiler.lexical_analyzer;
import compiler.pretty_print;
import compiler.syntax_tree;
import compiler.source_text;
import compiler.zero_copy;
import compiler.command;
import compiler.parser;
import compiler.print;

#ifdef _WIN32
export import :windows;
#endif // _WIN32

namespace compiler
{
	std::vector<std::string_view> split_input(std::string& input) noexcept
	{
		auto split_input = std::vector<std::string_view>();
		for (const auto& value : input | std::views::split(' '))
		{
			split_input.emplace_back(zero_copy{[&]() { return std::string_view(value.begin(), value.end()); }});
		}
		return split_input;
	}

	export class command_user_interface final
	{
	private:
		command_user_interface() = delete;

	public:
		static void launch() noexcept
		{
			std::cin.sync_with_stdio(false);
			std::cout.sync_with_stdio(false);
			// println("");

			while (true)
			{
				// print("> ");
				auto input = std::string();
				std::getline(std::cin, input);

				auto split_input = compiler::split_input(input);
				if (split_input.empty())
				{
					continue;
				}

				const auto& command_name = split_input.front();
				const auto iterator = commands.find(command_name);
				if (iterator == commands.end())
				{
					// perrln("Command not found");
					// perrln("");
					continue;
				}

				split_input.erase(split_input.begin());
				iterator->second(split_input);
			}
		}
	};
}
