#include "core/includes.hpp"
#include "dependencies/cipher/hash.hpp"

#pragma warning(disable: 4996)

ntstatus entry( uintptr_t driver_base, uintptr_t driver_size )
{
	if ( !driver_base || !driver_size )
	{
		DbgPrint(_(" [exa.pro] -> invalid parameters.\n"));
		return failed_entry;
	}

	DbgPrint(_(" [exa.pro] -> entry.\n"));

	return success;
}

