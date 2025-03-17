#pragma once
#include <ntifs.h>
#include <stdint.h>

#define image_scn_mem_execute 0x20000000

struct export_directory_t {
    int32_t m_characteristics;
    int32_t m_time_date_stamp;
    int16_t m_major_version;
    int16_t m_minor_version;
    int32_t m_name;
    int32_t m_base;
    int32_t m_number_of_functions;
    int32_t m_number_of_names;
    int32_t m_address_of_functions;
    int32_t m_address_of_names;
    int32_t m_address_of_names_ordinals;
};

struct list_entry_t {
    list_entry_t* m_flink;
    list_entry_t* m_blink;
};

using addr_t = unsigned char*;

enum pe_magic_t {
    dos_header = 0x5a4d,
    nt_headers = 0x4550,
    opt_header = 0x020b
};

enum nt_status_t {
    success,
    alerted = 0x101,
    timeout = 0x102,
    pending = 0x103,
    length_mismatch = 0xc4
};

inline void* fast_memcpy(
    void* dest,
    const void* src,
    size_t len
) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    while (len--)
        *d++ = *s++;
    return dest;
}

struct data_directory_t {
    int32_t m_virtual_address;
    int32_t m_size;

    template< class type_t >

    type_t as_rva(
        addr_t rva
    ) {
        return reinterpret_cast<type_t>(rva + m_virtual_address);
    }
};

struct dos_header_t
{
    int16_t m_magic;
    int16_t m_cblp;
    int16_t m_cp;
    int16_t m_crlc;
    int16_t m_cparhdr;
    int16_t m_minalloc;
    int16_t m_maxalloc;
    int16_t m_ss;
    int16_t m_sp;
    int16_t m_csum;
    int16_t m_ip;
    int16_t m_cs;
    int16_t m_lfarlc;
    int16_t m_ovno;
    int16_t m_res0[0x4];
    int16_t m_oemid;
    int16_t m_oeminfo;
    int16_t m_res1[0xa];
    int32_t m_lfanew;

    constexpr bool is_valid() {
        return m_magic == pe_magic_t::dos_header;
    }
};

struct nt_headers_t {
    int32_t m_signature;
    int16_t m_machine;
    int16_t m_number_of_sections;
    int32_t m_time_date_stamp;
    int32_t m_pointer_to_symbol_table;
    int32_t m_number_of_symbols;
    int16_t m_size_of_optional_header;
    int16_t m_characteristics;

    int16_t m_magic;
    int8_t m_major_linker_version;
    int8_t m_minor_linker_version;
    int32_t m_size_of_code;
    int32_t m_size_of_initialized_data;
    int32_t m_size_of_uninitialized_data;
    int32_t m_address_of_entry_point;
    int32_t m_base_of_code;
    uint64_t m_image_base;
    int32_t m_section_alignment;
    int32_t m_file_alignment;
    int16_t m_major_operating_system_version;
    int16_t m_minor_operating_system_version;
    int16_t m_major_image_version;
    int16_t m_minor_image_version;
    int16_t m_major_subsystem_version;
    int16_t m_minor_subsystem_version;
    int32_t m_win32_version_value;
    int32_t m_size_of_image;
    int32_t m_size_of_headers;
    int32_t m_check_sum;
    int16_t m_subsystem;
    int16_t m_dll_characteristics;
    uint64_t m_size_of_stack_reserve;
    uint64_t m_size_of_stack_commit;
    uint64_t m_size_of_heap_reserve;
    uint64_t m_size_of_heap_commit;
    int32_t m_loader_flags;
    int32_t m_number_of_rva_and_sizes;

    data_directory_t m_export_table;
    data_directory_t m_import_table;
    data_directory_t m_resource_table;
    data_directory_t m_exception_table;
    data_directory_t m_certificate_table;
    data_directory_t m_base_relocation_table;
    data_directory_t m_debug;
    data_directory_t m_architecture;
    data_directory_t m_global_ptr;
    data_directory_t m_tls_table;
    data_directory_t m_load_config_table;
    data_directory_t m_bound_import;
    data_directory_t m_iat;
    data_directory_t m_delay_import_descriptor;
    data_directory_t m_clr_runtime_header;
    data_directory_t m_reserved;

    constexpr bool is_valid() {
        return m_signature == pe_magic_t::nt_headers
            && m_magic == pe_magic_t::opt_header;
    }
};

struct section_header_t {
    char m_name[0x8];
    union {
        int32_t m_physical_address;
        int32_t m_virtual_size;
    };
    int32_t m_virtual_address;
    int32_t m_size_of_raw_data;
    int32_t m_pointer_to_raw_data;
    int32_t m_pointer_to_relocations;
    int32_t m_pointer_to_line_numbers;
    int16_t m_number_of_relocations;
    int16_t m_number_of_line_numbers;
    int32_t m_characteristics;
};