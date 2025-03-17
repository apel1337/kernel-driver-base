#pragma once
#include <ntifs.h>
#include "..\..\..\ntos\ntos.h"

namespace rwx
{
	EXTERN_C bool read_address(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_read);

	EXTERN_C bool write_address(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_written);

	EXTERN_C bool discover_next_executable_section(uint64_t image_base, uint64_t* executable_section_base, uint64_t* executable_section_size);
}