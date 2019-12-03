/* Linker script to configure memory regions. */

/*SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{*/
  /* Programme seul */
  /*FLASH (rx) : ORIGIN = 0x0, LENGTH = 512K
  RAM (rwx) :  ORIGIN = 0x20000000, LENGTH = 64K*/

  /* Programme utilisant SoftDevice s112 */
  /*FLASH (rx) : ORIGIN = 0x19000, LENGTH = 0x17000
  RAM (rwx) :  ORIGIN = 0x20001258, LENGTH = 0x4da8*/

  /* Programme utilisant SoftDevice s132 */
/*  FLASH (rx) : ORIGIN = 0x23000, LENGTH = 0x5d000*/
  /*RAM (rwx) :  ORIGIN = 0x200014b8, LENGTH = 0xeb48*/
/*  RAM (rwx) :  ORIGIN = 0x200020e0, LENGTH = 0xdf20*/

  /* Programme utilisant SoftDevice s140 */
  /*FLASH (rx) : ORIGIN = 0x25000, LENGTH = 0x64000
  RAM (rwx) :  ORIGIN = 0x20002080, LENGTH = 0xdf80*/

  /* Programme utilisant SoftDevice s212 */
  /*FLASH (rx) : ORIGIN = 0x12000, LENGTH = 0x6e000
  RAM (rwx) :  ORIGIN = 0x20000b80, LENGTH = 0xf480*/

  /* Programme utilisant SoftDevice s332 */
  /*FLASH (rx) : ORIGIN = 0x2d000, LENGTH = 0x53000
  RAM (rwx) :  ORIGIN = 0x20001f30, LENGTH = 0xe0d0*/
/*}

SECTIONS
{
  . = ALIGN(4);
  .mem_section_dummy_ram :
  {
  }
  .log_dynamic_data :
  {
    PROVIDE(__start_log_dynamic_data = .);
    KEEP(*(.log_dynamic_data))
    PROVIDE(__stop_log_dynamic_data = .);
  } > RAM
  .cli_sorted_cmd_ptrs :
  {
    PROVIDE(__start_cli_sorted_cmd_ptrs = .);
    KEEP(*(.cli_sorted_cmd_ptrs))
    PROVIDE(__stop_cli_sorted_cmd_ptrs = .);
  } > RAM
  .fs_data :
  {
    PROVIDE(__start_fs_data = .);
    KEEP(*(.fs_data))
    PROVIDE(__stop_fs_data = .);
  } > RAM
} INSERT AFTER .data;

SECTIONS
{
  .sdh_ble_observers :
  {
    PROVIDE(__start_sdh_ble_observers = .);
    KEEP(*(SORT(.sdh_ble_observers*)))
    PROVIDE(__stop_sdh_ble_observers = .);
  } > FLASH
  .log_const_data :
  {
    PROVIDE(__start_log_const_data = .);
    KEEP(*(.log_const_data))
    PROVIDE(__stop_log_const_data = .);
  } > FLASH
  .sdh_state_observers :
  {
    PROVIDE(__start_sdh_state_observers = .);
    KEEP(*(SORT(.sdh_state_observers*)))
    PROVIDE(__stop_sdh_state_observers = .);
  } > FLASH
  .sdh_stack_observers :
  {
    PROVIDE(__start_sdh_stack_observers = .);
    KEEP(*(SORT(.sdh_stack_observers*)))
    PROVIDE(__stop_sdh_stack_observers = .);
  } > FLASH
  .sdh_req_observers :
  {
    PROVIDE(__start_sdh_req_observers = .);
    KEEP(*(SORT(.sdh_req_observers*)))
    PROVIDE(__stop_sdh_req_observers = .);
  } > FLASH
} INSERT AFTER .text

INCLUDE "nrf5x_common.ld"
*/


/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)
/*// soft device s132 */
MEMORY 
{
  FLASH (rx) : ORIGIN = 0x23000, LENGTH = 0x5d000
  RAM (rwx) :  ORIGIN = 0x200020e0, LENGTH = 0xdf20
  
}

SECTIONS
{
}

SECTIONS
{
  . = ALIGN(4);
  .mem_section_dummy_ram :
  {
  }
  .log_dynamic_data :
  {
    PROVIDE(__start_log_dynamic_data = .);
    KEEP(*(.log_dynamic_data))
    PROVIDE(__stop_log_dynamic_data = .);
  } > RAM
  .fs_data :
  {
    PROVIDE(__start_fs_data = .);
    KEEP(*(.fs_data))
    PROVIDE(__stop_fs_data = .);
  } > RAM
  .cli_sorted_cmd_ptrs :
  {
    PROVIDE(__start_cli_sorted_cmd_ptrs = .);
    KEEP(*(.cli_sorted_cmd_ptrs))
    PROVIDE(__stop_cli_sorted_cmd_ptrs = .);
  } > RAM

} INSERT AFTER .data;

SECTIONS
{
  .mem_section_dummy_rom :
  {
  }
  .sdh_soc_observers :
  {
    PROVIDE(__start_sdh_soc_observers = .);
    KEEP(*(SORT(.sdh_soc_observers*)))
    PROVIDE(__stop_sdh_soc_observers = .);
  } > FLASH
  .pwr_mgmt_data :
  {
    PROVIDE(__start_pwr_mgmt_data = .);
    KEEP(*(SORT(.pwr_mgmt_data*)))
    PROVIDE(__stop_pwr_mgmt_data = .);
  } > FLASH
  .sdh_ble_observers :
  {
    PROVIDE(__start_sdh_ble_observers = .);
    KEEP(*(SORT(.sdh_ble_observers*)))
    PROVIDE(__stop_sdh_ble_observers = .);
  } > FLASH
    .log_const_data :
  {
    PROVIDE(__start_log_const_data = .);
    KEEP(*(.log_const_data))
    PROVIDE(__stop_log_const_data = .);
  } > FLASH
  .sdh_state_observers :
  {
    PROVIDE(__start_sdh_state_observers = .);
    KEEP(*(SORT(.sdh_state_observers*)))
    PROVIDE(__stop_sdh_state_observers = .);
  } > FLASH
  .sdh_stack_observers :
  {
    PROVIDE(__start_sdh_stack_observers = .);
    KEEP(*(SORT(.sdh_stack_observers*)))
    PROVIDE(__stop_sdh_stack_observers = .);
  } > FLASH
  .sdh_req_observers :
  {
    PROVIDE(__start_sdh_req_observers = .);
    KEEP(*(SORT(.sdh_req_observers*)))
    PROVIDE(__stop_sdh_req_observers = .);
  } > FLASH
    .cli_command :
  {
    PROVIDE(__start_cli_command = .);
    KEEP(*(.cli_command))
    PROVIDE(__stop_cli_command = .);
  } > FLASH
  

} INSERT AFTER .text

INCLUDE "nrf5x_common.ld"
