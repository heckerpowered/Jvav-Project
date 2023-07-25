export module compiler.bound_scope;

import std;

import compiler.variable_symbol;

namespace compiler
{
	export class bound_scope final
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<variable_symbol>> variables;

	public:
		const std::shared_ptr<bound_scope> parent;

		[[nodiscard]] bound_scope(const std::shared_ptr<bound_scope>& parent)
			noexcept : parent(parent)
		{
		}

		bool try_declare(const std::shared_ptr<variable_symbol>& variable) noexcept
		{
			if (variables.contains(variable->name)) [[unlikely]]
			{
				return false;
			}

			variables.emplace(variable->name, std::ref(variable));
			return true;
		}

		std::shared_ptr<variable_symbol> try_lookup(const std::string& name) noexcept
		{
			const auto iterator{ variables.find(name) };
			if (iterator != variables.end()) [[likely]]
			{
				return iterator->second;
			}

			if (!parent) [[unlikely]]
			{
				return nullptr;
			}

			return parent->try_lookup(name);
		}

		auto declared_variables() noexcept
		{
			return variables | std::views::values;
		}
	};
}
