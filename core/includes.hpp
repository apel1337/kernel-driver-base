#pragma once
// basic wdk includes
#include <ntifs.h>
#include <wdm.h>
#include <intrin.h>









#define null 0

enum ntstatus
{
	success = STATUS_SUCCESS,
	fail = STATUS_UNSUCCESSFUL,
	failed_entry = STATUS_FAILED_DRIVER_ENTRY,
	access_denied = STATUS_ACCESS_DENIED,
};