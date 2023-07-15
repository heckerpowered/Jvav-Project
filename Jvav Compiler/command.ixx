export module compiler.command;

import std;

import :eval;

namespace compiler
{
	export std::unordered_map<std::string_view, std::function<void(std::vector<std::string_view>& arguments)>> commands{
		{"exit", [](const std::vector<std::string_view>&) noexcept { std::exit(0); }},
		{"eval", eval}
	};
}
