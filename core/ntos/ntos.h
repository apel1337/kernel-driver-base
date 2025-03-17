#pragma once
#include <ntifs.h>
#include "ia32.h"

namespace ntos
{
    template< class type_t >

    type_t find_export(
        const char* export_name
    );

    nt_status_t ps_lookup_process_by_process_id(
        HANDLE pid,
        PEPROCESS* process
    );

    nt_status_t mm_copy_memory(
        void* target_address,
        MM_COPY_ADDRESS source_address,
        SIZE_T number_of_bytes,
        ULONG flags,
        PSIZE_T number_of_bytes_transferred
    );

    list_entry_t* ps_active_process_head();

    void* map_io_space_ex(
        PHYSICAL_ADDRESS physical_address,
        SIZE_T number_of_bytes,
        ULONG protect
    );

    void mm_unmap_io_space(
        void* base_address,
        SIZE_T number_of_bytes
    );

    void mm_unmap_io_space(
        void* base_address,
        SIZE_T number_of_bytes
    );


    void rtl_init_unicode_string(
        PUNICODE_STRING destination_string,
        PCWSTR source_string
    );

    bool mm_is_address_valid(
        void* VirtualAddress
    );

    uintptr_t ps_initial_system_process();

    uint32_t ps_get_process_id(
        uint64_t Process
    );
}
