export module compiler.bound_scope;

import std;

import compiler.variable_symbol;

namespace compiler
{
	export class bound_scope final
	{
	private:
		std::unordered_map<std::string, std::reference_wrapper<const variable_symbol>> variables;

	public:
		const std::shared_ptr<bound_scope> parent;

		[[nodiscard]] bound_scope(const std::shared_ptr<bound_scope>& parent)
			noexcept : parent(parent)
		{
		}

		bool try_declare(const variable_symbol& variable) noexcept
		{
			if (variables.contains(variable.logger_name)) [[unlikely]]
			{
				return false;
			}

			variables.emplace(variable.logger_name, std::ref(variable));
			return true;
		}

#ifdef __INTELLISENSE__
		auto
#else
		std::optional<std::reference_wrapper<const variable_symbol>>
#endif // __INTELLISENSE__
		try_lookup(const std::string& logger_name) noexcept
		{
			const auto iterator{ variables.find(logger_name) };
			if (iterator != variables.end()) [[likely]]
			{
				return iterator->second;
			}

			if (!parent) [[unlikely]]
			{
#ifndef __INTELLISENSE__
				return std::nullopt;
#endif // __INTELLISENSE__
			}

			return parent->try_lookup(logger_name);
		}

		auto declared_variables() noexcept
		{
			return variables | std::views::values;
		}
	};
}
