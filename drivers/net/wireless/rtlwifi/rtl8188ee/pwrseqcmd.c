

#include "pwrseq.h"




bool rtl88_hal_pwrseqcmdparsing(struct rtl_priv *rtlpriv, u8 cut_version,
				u8 fab_version, u8 interface_type,
				struct wlan_pwr_cfg pwrcfgcmd[])
{
	struct wlan_pwr_cfg cmd = {0};
	bool polling_bit = false;
	u32 ary_idx = 0;
	u8 val = 0;
	u32 offset = 0;
	u32 polling_count = 0;
	u32 max_polling_cnt = 5000;

	do {
		cmd = pwrcfgcmd[ary_idx];
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "rtl88_hal_pwrseqcmdparsing(): offset(%#x), cut_msk(%#x), fab_msk(%#x),"
			 "interface_msk(%#x), base(%#x), cmd(%#x), msk(%#x), val(%#x)\n",
			 GET_PWR_CFG_OFFSET(cmd),
			 GET_PWR_CFG_CUT_MASK(cmd),
			 GET_PWR_CFG_FAB_MASK(cmd),
			 GET_PWR_CFG_INTF_MASK(cmd),
			 GET_PWR_CFG_BASE(cmd),
			 GET_PWR_CFG_CMD(cmd),
			 GET_PWR_CFG_MASK(cmd),
			 GET_PWR_CFG_VALUE(cmd));

		if ((GET_PWR_CFG_FAB_MASK(cmd) & fab_version) &&
		    (GET_PWR_CFG_CUT_MASK(cmd) & cut_version) &&
		    (GET_PWR_CFG_INTF_MASK(cmd) & interface_type)) {
			switch (GET_PWR_CFG_CMD(cmd)) {
			case PWR_CMD_READ:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					 "rtl88_hal_pwrseqcmdparsing(): PWR_CMD_READ\n");
				break;
			case PWR_CMD_WRITE: {
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					 "rtl88_hal_pwrseqcmdparsing(): PWR_CMD_WRITE\n");
				offset = GET_PWR_CFG_OFFSET(cmd);

					/*Read the val from system register*/
					val = rtl_read_byte(rtlpriv, offset);
					val &= (~(GET_PWR_CFG_MASK(cmd)));
					val |= (GET_PWR_CFG_VALUE(cmd) &
						GET_PWR_CFG_MASK(cmd));

					/*Write the val back to sytem register*/
					rtl_write_byte(rtlpriv, offset, val);
				}
				break;
			case PWR_CMD_POLLING:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					 "rtl88_hal_pwrseqcmdparsing(): PWR_CMD_POLLING\n");
				polling_bit = false;
				offset = GET_PWR_CFG_OFFSET(cmd);

				do {
					val = rtl_read_byte(rtlpriv, offset);

					val = val & GET_PWR_CFG_MASK(cmd);
					if (val == (GET_PWR_CFG_VALUE(cmd) &
						    GET_PWR_CFG_MASK(cmd)))
						polling_bit = true;
					else
						udelay(10);

					if (polling_count++ > max_polling_cnt) {
						RT_TRACE(rtlpriv, COMP_INIT,
							 DBG_LOUD,
							 "polling fail in pwrseqcmd\n");
						return false;
					}
				} while (!polling_bit);

				break;
			case PWR_CMD_DELAY:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					 "rtl88_hal_pwrseqcmdparsing(): PWR_CMD_DELAY\n");
				if (GET_PWR_CFG_VALUE(cmd) == PWRSEQ_DELAY_US)
					udelay(GET_PWR_CFG_OFFSET(cmd));
				else
					mdelay(GET_PWR_CFG_OFFSET(cmd));
				break;
			case PWR_CMD_END:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					 "rtl88_hal_pwrseqcmdparsing(): PWR_CMD_END\n");
				return true;
				break;
			default:
				RT_ASSERT(false,
					  "rtl88_hal_pwrseqcmdparsing(): Unknown CMD!!\n");
				break;
			}
		}

		ary_idx++;
	} while (1);

	return true;
}
