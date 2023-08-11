module;

#include <wdm.h>
#include <ntdef.h>
#include <ntstatus.h>

export module runtime.main;

import std;

extern "C" NTSTATUS DriverEntry(DRIVER_OBJECT * DriverObject, PUNICODE_STRING [[maybe_unused]] ) noexcept {
	DriverObject->DriverUnload = [](DRIVER_OBJECT*) {};
	return STATUS_SUCCESS;
}