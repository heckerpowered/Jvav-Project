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
			if (variables.contains(variable.name))
			[[unlikely]]
			{
				return false;
			}

			variables.emplace(variable.name, std::ref(variable));
			return true;
		}

#ifdef __INTELLISENSE__
		auto
#else
		std::optional<std::reference_wrapper<const variable_symbol>>
#endif // __INTELLISENSE__
		try_lookup(const std::string& name) noexcept
		{
			const auto iterator = variables.find(name);
			if (iterator != variables.end())
			{
				return iterator->second;
			}

			if (!parent)
			{
#ifndef __INTELLISENSE__
				return std::nullopt;
#endif // __INTELLISENSE__
			}

			return parent->try_lookup(name);
		}

		auto declared_variables() noexcept
		{
			return variables | std::views::values;
		}
	};
}
