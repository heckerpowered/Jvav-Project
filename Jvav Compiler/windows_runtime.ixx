module;

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

export module compiler.runtime:windows;

import std;

namespace compiler
{
#ifdef _WIN32
	struct service_handle_deleter
	{
		void operator()(SC_HANDLE const* handle) const noexcept
		{
			if (handle && *handle)
			{
				CloseServiceHandle(*handle);
			}
		}
	};

	export class runtime_windows_implement final
	{
	private:
		runtime_windows_implement() = delete;

	public:
		std::expected<bool, std::error_code> is_runtime_ready() noexcept
		{
			const auto service_control_manager = std::unique_ptr<SC_HANDLE, service_handle_deleter>(
				new SC_HANDLE(OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS)));
			if (!*service_control_manager)
			{
				return std::unexpected(std::error_code(GetLastError(), std::system_category()));
			}

			constexpr auto service_name = "Jvav Runtime";
			const auto service = std::unique_ptr<SC_HANDLE, service_handle_deleter>(
				new SC_HANDLE(OpenServiceA(*service_control_manager, service_name, SERVICE_ALL_ACCESS)));
			if (!*service)
			{
				return std::unexpected(std::error_code(GetLastError(), std::system_category()));
			}

			auto service_status = SERVICE_STATUS();
			if (!QueryServiceStatus(*service, &service_status))
			{
				return std::unexpected(std::error_code(GetLastError(), std::system_category()));
			}

			return service_status.dwCurrentState == SERVICE_RUNNING;
		}
	};
#endif
}
