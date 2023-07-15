#include <ntddk.h>
#include <wdm.h>
#include <ntdef.h>

extern "C" NTSTATUS DriverEntry(DRIVER_OBJECT * DriverObject, PUNICODE_STRING [[maybe_unused]] ) noexcept {
	DriverObject->DriverUnload = [](DRIVER_OBJECT* DriverObject [[maybe_unused]] ) {};

	return STATUS_SUCCESS;
}