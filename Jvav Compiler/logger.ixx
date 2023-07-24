export module compiler.logger;

import std;

import compiler.logger_target;
import compiler.logger_level;

#ifdef _MSC_VER
#define novtable __declspec(novtable)
#else
#define novtable
#endif // DEBUG

namespace compiler {
	export class logger_string {
	public:
		template<std::convertible_to<std::string_view> stream_type>
		[[nodiscard]] constexpr logger_string(const stream_type& string) noexcept : string(string)
		{
		}

		[[nodiscard]] constexpr std::string_view get() const noexcept {
			return string;
		}

	private:
		std::string_view string;
	};

	export class logger : public std::unordered_set<std::shared_ptr<target>> {
	public:
		using super = std::unordered_set<std::shared_ptr<target>>;

		[[nodiscard]] logger(std::string_view const& logger_name)
			noexcept : logger_name(logger_name)
		{
		}

	private:
		void write(std::string_view const& message) const noexcept
		{
			for (auto&& target : *this)
			{
				target->write(message);
			}
		}
	public:
		void log(logger_level const& level, std::string_view const& message) const noexcept
		{
			const auto prefix{ get_prefix(level) };
#ifndef __INTELLISENSE__
			write(std::format("{} {}\n", prefix, message));
#endif // !__INTELLISENSE__
		}

		template<typename... format_types>
		void log_format(logger_level const& level, const std::format_string<format_types...>& message, 
						format_types&&... format_arguments) const noexcept
		{
			const auto prefix{ get_prefix(level) };
#ifndef __INTELLISENSE__
			write(std::format("{} {}\n", prefix, std::format(message, std::forward<format_types>(format_arguments)...)));
#endif // !__INTELLISENSE__
		}
	
		template<typename function_type> requires requires(function_type function, std::ostream& output_stream)
		{
			std::invoke(function, output_stream);
		}
		void log_stream(logger_level const& level, function_type&& function) const noexcept
#ifdef LOSER_MODE
			(noexcept(std::invoke(std::declval<function_type>(), std::declval<std::ostream&>())))
#endif // LOSER_MODE
		{
			auto stream{ std::stringstream{} };
			std::invoke(function, stream);
			const auto prefix{ get_prefix(level) };
#ifndef __INTELLISENSE__
			write(std::format("{} {}\n", prefix, stream.str()));
#endif // !__INTELLISENSE__
		}

		std::string const& name() const noexcept
		{
			return logger_name;
		}

		std::string& name() noexcept
		{
			return logger_name;
		}

	protected:
		virtual std::string get_prefix(logger_level const& level) const noexcept
		{
#ifndef __INTELLISENSE__
			const auto current_time = std::chrono::system_clock::now();
			return std::format("[{:%T}] [{}/{}]", current_time, logger_name, level.name());
#endif // !__INTELLISENSE__
		}

	private:
		std::string logger_name;
	};
}