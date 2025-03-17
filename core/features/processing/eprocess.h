#pragma once
#include <ntifs.h>
#include <stdint.h>
#include <intrin.h>

namespace process
{
	inline uintptr_t safe_attach(uintptr_t e_process);
	inline uintptr_t get_eprocess(uint32_t process_id);
}