#include "eprocess.h"
#include "..\..\ntos\ntos.h"

inline uintptr_t process::safe_attach(uintptr_t e_process)
{
	auto current_thread = __readgsqword((0x188));
	if (!current_thread)
		return 0;

	auto apc_state = *(uintptr_t*)(current_thread + (0x98));
	auto old_process = *(uintptr_t*)(apc_state + (0x20));
	*(uintptr_t*)(apc_state + (0x20)) = e_process;

	auto dir_table_base = *(uintptr_t*)(e_process + (0x28));
	__writecr3(dir_table_base);

	return old_process;
}

inline uintptr_t process::get_eprocess(uint32_t process_id)
{
	auto process_list_head = ntos::ps_active_process_head();
	if (!process_list_head) {
		return 0;
	}

	const auto link_va =
		reinterpret_cast<addr_t>(process_list_head) -
		ntos::ps_initial_system_process();
	if (!link_va) {
		return 0;
	}

	for (auto flink = process_list_head->m_flink; flink; flink = flink->m_flink)
	{
		const auto next_eprocess = reinterpret_cast<addr_t>(flink) - link_va;
		if (!next_eprocess) {
			continue;
		}

		const auto next_process_id = ntos::ps_get_process_id(next_eprocess);
		if (next_process_id == process_id) {
			return next_eprocess;
		}
	}

	return 0;
}