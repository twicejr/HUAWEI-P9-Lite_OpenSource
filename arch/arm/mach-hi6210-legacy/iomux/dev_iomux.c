#include <mach/platform.h>
#include <mach/io.h>
#include <linux/mux.h>
#include <hsad/config_interface.h>
#include "iomux.h"
#include "hi6210_iomux.h"

extern unsigned int get_boardid(void);

static int __init iomux_dev_init(void)
{
    unsigned int current_board_id = get_boardid();
    struct iomux_config_table *tmp_borad_entry = NULL;

    /* get the target block coresponding the board id */
    tmp_borad_entry = &(block_config_tables[0]);
    while (IOMUX_CONFIG_TBL_END_SYMBOL != tmp_borad_entry->board_id) {
        if (current_board_id == tmp_borad_entry->board_id) {
            break;
        }
        tmp_borad_entry++;
    }
    if (IOMUX_CONFIG_TBL_END_SYMBOL == tmp_borad_entry->board_id){
        pr_err("NO IOMUX BLOCK is matched with board_id %d,%s %d.\r\n",
            tmp_borad_entry->board_id, __func__, __LINE__);
        tmp_borad_entry = &(block_config_tables[0]);
    }
    iomux_register_blocks_table((struct iomux_block_table *)tmp_borad_entry->table_item);

    /* get the target pin coresponding the board id */
    tmp_borad_entry = &(pin_config_tables[0]);
    while (IOMUX_CONFIG_TBL_END_SYMBOL != tmp_borad_entry->board_id) {
        if (current_board_id == tmp_borad_entry->board_id) {
            break;
        }
        tmp_borad_entry++;
    }
    if (IOMUX_CONFIG_TBL_END_SYMBOL == tmp_borad_entry->board_id){
        pr_err("NO IOMUX PIN is matched with board_id %d,%s %d.\r\n",
            tmp_borad_entry->board_id, __func__, __LINE__);
        tmp_borad_entry = &(pin_config_tables[0]);
    }
    iomux_register_pins_table((struct iomux_pin_table *)tmp_borad_entry->table_item);

    return 0;
}
core_initcall(iomux_dev_init);

