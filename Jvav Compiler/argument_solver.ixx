export module compiler.argument_solver;

import std;

namespace compiler {
    export std::map<std::string_view, std::vector<std::string_view>> 
        solve_arguments(std::vector<std::string_view> const& arguments) noexcept {
        auto solved_arguments = std::map<std::string_view, std::vector<std::string_view>>();
        
        for (auto&& argument : arguments) {
            auto const position = argument.find('=');
            if (position == std::string_view::npos) {
                solved_arguments.try_emplace(argument);
            }
            else {
                auto name = argument.substr(0, position);
                auto value = argument.substr(position + 1);
                solved_arguments[name].push_back(value);
            }
        }

        return solved_arguments;
    }
}