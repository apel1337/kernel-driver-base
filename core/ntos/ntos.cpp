#include "ntos.h"
#include "..\..\dependencies\cipher\hash.hpp"

uintptr_t ntoskrnl_image = 0; // find a way to get it

namespace ntos
{
    template< class type_t >
    type_t find_export(
        const char* export_name
    )
    {
        auto dos_header = reinterpret_cast<dos_header_t*>(ntoskrnl_image); // find a way to get it
        if (!dos_header->is_valid()) {
        }

        auto m_nt_header = reinterpret_cast<nt_headers_t*>(reinterpret_cast<uint64_t>(dos_header) + dos_header->m_lfanew);
        if (!m_nt_header->is_valid()) {
        }

        auto library{ reinterpret_cast<int8_t*>(dos_header) };
        auto export_directory =
            reinterpret_cast<export_directory_t*> (ntoskrnl_image + m_nt_header->m_export_table.m_virtual_address); // find a way to get it
        if (!export_directory->m_address_of_functions
            || !export_directory->m_address_of_names
            || !export_directory->m_address_of_names_ordinals)
            return {};

        auto names{ reinterpret_cast<int32_t*>(library + export_directory->m_address_of_names) };
        auto functions{ reinterpret_cast<int32_t*>(library + export_directory->m_address_of_functions) };
        auto ordinals{ reinterpret_cast<int16_t*>(library + export_directory->m_address_of_names_ordinals) };

        for (int32_t i = 0; i < export_directory->m_number_of_names; i++) {
            auto current_name{ library + names[i] };
            auto current_function{ library + functions[ordinals[i]] };

            if (!(strcmp)(export_name, reinterpret_cast<char*>(current_name)))
                return reinterpret_cast<type_t>(current_function);
        }

        return reinterpret_cast<type_t>(0);
    }

    nt_status_t ps_lookup_process_by_process_id(
        HANDLE pid,
        PEPROCESS* process
    )
    {
        auto function_address = find_export<addr_t>(_("PsLookupProcessByProcessId"));
        if (!function_address) {
            return {};
        }

        using function_t = nt_status_t(
            HANDLE pid,
            PEPROCESS* process
        );

        return reinterpret_cast<function_t*>(function_address)(pid,
            process);
    }

    nt_status_t mm_copy_memory(
        void* target_address,
        MM_COPY_ADDRESS source_address,
        SIZE_T number_of_bytes,
        ULONG flags,
        PSIZE_T number_of_bytes_transferred
    )
    {
        auto function_address = find_export<addr_t>(_("MmCopyMemory"));
        if (!function_address) {
            return {};
        }

        using function_t = nt_status_t(
            void* target_address,
            MM_COPY_ADDRESS source_address,
            SIZE_T number_of_bytes,
            ULONG falgs,
            PSIZE_T number_of_bytes_transferred
        );

        return reinterpret_cast<function_t*>(function_address) (
            target_address,
            source_address,
            number_of_bytes,
            flags,
            number_of_bytes_transferred);
    }

    list_entry_t* ps_active_process_head()
    {
        static auto function_address = find_export<addr_t>(("KeCapturePersistentThreadState"));
        if (!function_address) {
            return { };
        }

        while (function_address[0x0] != 0x20
            || function_address[0x1] != 0x48
            || function_address[0x2] != 0x8d)
            function_address++;

        return *reinterpret_cast<list_entry_t**>
            (&function_address[0x8] + *reinterpret_cast<int32_t*>(&function_address[0x4]));
    }

    void* map_io_space_ex(
        PHYSICAL_ADDRESS physical_address,
        SIZE_T number_of_bytes,
        ULONG protect
    )
    {
        auto function_address = find_export<addr_t>(_("MmMapIoSpaceEx"));
        if (!function_address) {
            return {};
        }

        using function_t = void* (
            PHYSICAL_ADDRESS physical_address,
            SIZE_T number_of_bytes,
            ULONG protect
            );

        return reinterpret_cast<function_t*>(function_address) (
            physical_address,
            number_of_bytes,
            protect);
    }

    void mm_unmap_io_space(
        void* base_address,
        SIZE_T number_of_bytes
    )
    {
        auto function_address = find_export<addr_t>(_("MmUnmapIoSpace"));
        if (!function_address) {
            return;
        }

        using function_t = void(
            void* base_address,
            SIZE_T number_of_bytes
            );

        reinterpret_cast<function_t*>(function_address) (
            base_address,
            number_of_bytes);
    }

    void rtl_init_unicode_string(
        PUNICODE_STRING destination_string,
        PCWSTR source_string
    )
    {
        auto function_address = find_export<addr_t>(_("RtlInitUnicodeString"));
        if (!function_address) {
            return;
        }

        using function_t = void* (
            PUNICODE_STRING destination_string,
            PCWSTR source_string
            );

        reinterpret_cast<function_t*>(function_address) (
            destination_string,
            source_string);
    }

    bool mm_is_address_valid(
        void* VirtualAddress
    )
    {
        auto function_address = find_export<addr_t>(_("MmIsAddressValid"));
        if (!function_address) {
            return false;
        }

        using function_t = bool(
            void* VirtualAddress
            );

        return reinterpret_cast<function_t*>(function_address)(VirtualAddress);
    }

    uintptr_t ps_initial_system_process()
    {
        auto function_address = find_export<addr_t>(("PsInitialSystemProcess"));
        if (!function_address) {
            return {};
        }

        return *reinterpret_cast<uintptr_t*>(function_address);
    }

    uint32_t ps_get_process_id(
        uint64_t Process
    )
    {
        auto function_address = find_export<addr_t>(("PsGetProcessId"));
        if (!function_address) {
            return {};
        }

        using function_t = HANDLE(
            PEPROCESS Process
        );

        return reinterpret_cast<uint32_t>(
            reinterpret_cast<function_t*>(function_address)(
                reinterpret_cast<PEPROCESS>(Process))
            );
    }
}