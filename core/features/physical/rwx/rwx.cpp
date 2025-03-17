#include "rwx.h"

bool rwx::read_address(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_read)
{
	if (!target_address || !buffer || !bytes_read) {
		return false;
	}

	if (size == 0) {
		*bytes_read = 0;
		return false;
	}

	MM_COPY_ADDRESS to_read = { 0 };

	to_read.PhysicalAddress.QuadPart = (LONGLONG)target_address;

	ntos::mm_copy_memory(buffer, to_read, size, 0x1, bytes_read); // pg safe / eac safe

	return true;
}

bool rwx::write_address(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_written)
{
	if (!target_address || !buffer || !bytes_written)
		return false;

	if (size == 0) {
		*bytes_written = 0;
		return false;
	}

	PHYSICAL_ADDRESS to_write = { 0 };

	to_write.QuadPart = reinterpret_cast<LONGLONG>(target_address);

	PVOID mapped_page = ntos::map_io_space_ex(to_write, size, 0x04);
	if (!mapped_page)
		return false;

	memcpy(mapped_page, buffer, size); // find your own way to safely copy memory / pg safe / ac unsafe

	*bytes_written = size;

	ntos::mm_unmap_io_space(mapped_page, size);
	return true;
}

bool rwx::discover_next_executable_section(uint64_t image_base, uint64_t* executable_section_base, uint64_t* executable_section_size)
{
	return true;
}