/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.83
	GENERATOR: ed-c
	http://www.Dafocus.it/
**************************************************************************/

#include "ed_c.h"
#include "ed_lib.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_ED_C_C
/*lint -e961*/
/*lint -e958*/
/*lint -e830*/
/*lint -e525*/
/*lint -e445*/


/* SETITEMS commands for type 'c_IncSkipOfARFCN'. Existing items are not changed. */
void SETITEMS_c_IncSkipOfARFCN (c_IncSkipOfARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_GrpChannelMA'. Existing items are not changed. */
void SETITEMS_c_GrpChannelMA (c_GrpChannelMA* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_MeasurementResultsList'. Existing items are not changed. */
void SETITEMS_c_MeasurementResultsList (c_MeasurementResultsList* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			INIT_c_MeasurementSingleResult (&(sequence->data[i]));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_MeasurementSingleResult (&(sequence->data[i]));
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_TRXLEVCarriers'. Existing items are not changed. */
void SETITEMS_c_TRXLEVCarriers (c_TRXLEVCarriers* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_MobileAllocation'. Existing items are not changed. */
void SETITEMS_c_MobileAllocation (c_MobileAllocation* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_BaRange'. Existing items are not changed. */
void SETITEMS_c_BaRange (c_BaRange* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Lower) = 0;
			(sequence->data[i].Higher) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Access_Reject_message_content_Additional_Reject'. Existing items are not changed. */
void SETITEMS_c_Packet_Access_Reject_message_content_Additional_Reject (c_Packet_Access_Reject_message_content_Additional_Reject* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Global_TFI_Present) {
					if (sequence->data[i].Global_TFI.DOWNLINK_TFI_Present) {
					}
					if (sequence->data[i].Global_TFI.UPLINK_TFI_Present) {
					}
				}
				if (sequence->data[i].Ignore_Present) {
					sequence->data[i].Ignore.usedBits = 0;
				}
				if (sequence->data[i].Packet_Request_Reference_Present) {
				}
				if (sequence->data[i].TLLI_Present) {
				}
				if (sequence->data[i].WAIT_INDICATION_Present) {
				}
				if (sequence->data[i].WAIT__INDICATION_SIZE_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_BSIC_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_BSIC_N (c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_BSIC_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].BSIC_N_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_FREQUENCY_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_FREQUENCY_N (c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_FREQUENCY_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_RXLEV_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_RXLEV_N (c_Packet_Cell_Change_Notification_message_content_CCN_Measurement_Report_RXLEV_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_CELL_IDENTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_CELL_IDENTITY (c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_CELL_IDENTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX (c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_REPORTING_QUANTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_REPORTING_QUANTITY (c_Packet_Cell_Change_Notification_message_content_Target_Cell_and_E_UTRAN_CCN_Measurement_Report_Rel8_E_UTRAN_CCN_Measurement_Report_REPORTING_QUANTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content__3G_BA_CCN_Measurement_Report__3G_CCN_Measurement_Report_REPORTING_QUANTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content__3G_BA_CCN_Measurement_Report__3G_CCN_Measurement_Report_REPORTING_QUANTITY (c_Packet_Cell_Change_Notification_message_content__3G_BA_CCN_Measurement_Report__3G_CCN_Measurement_Report_REPORTING_QUANTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Notification_message_content__3G_BA_CCN_Measurement_Report__3G_CCN_Measurement_Report__3G_CELL_LIST_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Notification_message_content__3G_BA_CCN_Measurement_Report__3G_CCN_Measurement_Report__3G_CELL_LIST_INDEX (c_Packet_Cell_Change_Notification_message_content__3G_BA_CCN_Measurement_Report__3G_CCN_Measurement_Report__3G_CELL_LIST_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_CCN_Support_Description_CCN_SUPPORTED'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_CCN_Support_Description_CCN_SUPPORTED (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_CCN_Support_Description_CCN_SUPPORTED* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters_GPRS_REP_PRIORITY_Description_REP_PRIORITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters_GPRS_REP_PRIORITY_Description_REP_PRIORITY (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters_GPRS_REP_PRIORITY_Description_REP_PRIORITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_N2'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_N2 (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_N2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_REMOVED_3GCELL_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_REMOVED_3GCELL_INDEX (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_REMOVED_3GCELL_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3GCELL_DIFF'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3GCELL_DIFF (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3GCELL_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3G_CELL_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3G_CELL_DIFF_LENGTH (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3G_CELL_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].FDD_ARFCN) = 0;
			sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].FDD_Indic0) = 0;
			(sequence->data[i].NR_OF_FDD_CELLS) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_ENH_Measurement_parameters__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].NR_OF_TDD_CELLS) = 0;
			(sequence->data[i].TDD_ARFCN) = 0;
			sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].TDD_Indic0) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].FREQ_DIFF_LENGTH) = 0;
			(sequence->data[i].NR_OF_FREQUENCIES) = 0;
			sequence->data[i].REMAIN_FREQ_DATA.items = 0;
			(sequence->data[i].START_FREQUENCY) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Cell_selection_params_Present) {
					if (sequence->data[i].Cell_selection_params.GPRS_MS_TXPWR_MAX_CCH_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_PENALTY_TIME_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RESELECT_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RXLEV_ACCESS_MIN_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_TEMPORARY_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.HCS_params_Present) {
					}
					if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION_Present) {
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
						}
					}
				}
				for (i0=0; i0<sequence->data[i].REMAIN_FREQ_DATA.items; i0++) {
					if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params_Present) {
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_MS_TXPWR_MAX_CCH_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_PENALTY_TIME_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_RESELECT_OFFSET_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_RXLEV_ACCESS_MIN_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_TEMPORARY_OFFSET_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.HCS_params_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION_Present) {
							if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
							}
							if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
							}
							if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
							}
						}
					}
					sequence->data[i].REMAIN_FREQ_DATA.data[i0].FREQUENCY_DIFF.usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency_data_REMAIN_FREQ_DATA'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency_data_REMAIN_FREQ_DATA (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency_data_REMAIN_FREQ_DATA* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			sequence->data[i].FREQUENCY_DIFF.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Cell_selection_params_Present) {
					if (sequence->data[i].Cell_selection_params.GPRS_MS_TXPWR_MAX_CCH_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_PENALTY_TIME_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RESELECT_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RXLEV_ACCESS_MIN_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_TEMPORARY_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.HCS_params_Present) {
					}
					if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION_Present) {
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
						}
					}
				}
				sequence->data[i].FREQUENCY_DIFF.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_REMOVED_FREQ_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_REMOVED_FREQ_INDEX (c_Packet_Cell_Change_Order_message_content_GSM_target_cell_NC_Measurement_Parameters_NC_FREQUENCY_LIST_REMOVED_FREQ_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters (c_Packet_Cell_Change_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].EARFCN.items = 0;
			(sequence->data[i].E_UTRAN_PRIORITY) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN (c_Packet_Cell_Change_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters (c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].FDD_ARFCN.items = 0;
			sequence->data[i].TDD_ARFCN.items = 0;
			(sequence->data[i].UTRAN_PRIORITY) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN (c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN (c_Packet_Cell_Change_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Downlink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Downlink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_Packet_Downlink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Downlink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_Packet_Downlink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_Packet_Downlink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Downlink_Assignment_message_content_PERSISTENCE_LEVEL_P_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Packet_Downlink_Assignment_message_content_PERSISTENCE_LEVEL_P_LEVEL (c_Packet_Downlink_Assignment_message_content_PERSISTENCE_LEVEL_P_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Downlink_Dummy_Control_Block_message_content_PERSISTENCE_LEVEL_P_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Packet_Downlink_Dummy_Control_Block_message_content_PERSISTENCE_LEVEL_P_LEVEL (c_Packet_Downlink_Dummy_Control_Block_message_content_PERSISTENCE_LEVEL_P_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_BSIC_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_BSIC_N (c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_BSIC_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].BSIC_N_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_FREQUENCY_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_FREQUENCY_N (c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_FREQUENCY_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_RXLEV_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_RXLEV_N (c_Packet_Measurement_Report_message_content_EXT_Measurement_Report_RXLEV_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_CELL_IDENTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_CELL_IDENTITY (c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_CELL_IDENTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_REPORTING_QUANTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_REPORTING_QUANTITY (c_Packet_Measurement_Report_message_content_E_UTRAN_Measurement_Report_REPORTING_QUANTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_NC_Measurement_Report_BSIC_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_NC_Measurement_Report_BSIC_N (c_Packet_Measurement_Report_message_content_NC_Measurement_Report_BSIC_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].BSIC_N_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_NC_Measurement_Report_FREQUENCY_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_NC_Measurement_Report_FREQUENCY_N (c_Packet_Measurement_Report_message_content_NC_Measurement_Report_FREQUENCY_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content_NC_Measurement_Report_RXLEV_N'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content_NC_Measurement_Report_RXLEV_N (c_Packet_Measurement_Report_message_content_NC_Measurement_Report_RXLEV_N* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content__3G_Measurement_Report_REPORTING_QUANTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content__3G_Measurement_Report_REPORTING_QUANTITY (c_Packet_Measurement_Report_message_content__3G_Measurement_Report_REPORTING_QUANTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Report_message_content__3G_Measurement_Report__3G_CELL_LIST_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Report_message_content__3G_Measurement_Report__3G_CELL_LIST_INDEX (c_Packet_Measurement_Report_message_content__3G_Measurement_Report__3G_CELL_LIST_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_CCN_Support_Description_CCN_SUPPORTED'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_CCN_Support_Description_CCN_SUPPORTED (c_Packet_Measurement_Order_message_content_CCN_Support_Description_CCN_SUPPORTED* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters_GPRS_REP_PRIORITY_Description_REP_PRIORITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters_GPRS_REP_PRIORITY_Description_REP_PRIORITY (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters_GPRS_REP_PRIORITY_Description_REP_PRIORITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH1'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH1 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH2'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH2 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_POWER_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_POWER_LEVEL (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_POWER_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_WALSH'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_WALSH (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_WALSH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_WALSH_LEN'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_WALSH_LEN (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_WALSH_LEN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_Pilot_PN_offset'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_Pilot_PN_offset (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_Pilot_PN_offset* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF1'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF1 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF2'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF2 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER1'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER1 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER2'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER2 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PRIM_PILOT'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PRIM_PILOT (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PRIM_PILOT* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_MODE'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_MODE (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_MODE* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_POWER_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_POWER_LEVEL (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_POWER_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH1'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH1 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH2'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH2 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_A'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_A (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_A* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_B'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_B (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_B* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_C'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_C (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_C* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_N2'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_N2 (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_N2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_REMOVED_3GCELL_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_REMOVED_3GCELL_INDEX (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description_REMOVED_3GCELL_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3GCELL_DIFF'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3GCELL_DIFF (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3GCELL_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3G_CELL_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3G_CELL_DIFF_LENGTH (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_REMOVED_3GCELL_Description__3G_CELL_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].FDD_ARFCN) = 0;
			sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].FDD_Indic0) = 0;
			(sequence->data[i].NR_OF_FDD_CELLS) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells (c_Packet_Measurement_Order_message_content_ENH_Measurement_Parameters__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].NR_OF_TDD_CELLS) = 0;
			(sequence->data[i].TDD_ARFCN) = 0;
			sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].TDD_Indic0) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQUENCY_DIFF'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQUENCY_DIFF (c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQUENCY_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQ_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQ_DIFF_LENGTH (c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQ_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_NR_OF_FREQUENCIES'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_NR_OF_FREQUENCIES (c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_NR_OF_FREQUENCIES* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_START_FREQUENCY'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_START_FREQUENCY (c_Packet_Measurement_Order_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_START_FREQUENCY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT (c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].PCID.items = 0;
			sequence->data[i].PCID_Pattern.items = 0;
			sequence->data[i].PCID_Pattern_length.items = 0;
			sequence->data[i].PCID_pattern_sense.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].PCID_Pattern.items; i0++) {
					sequence->data[i].PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID (c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern (c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length (c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense (c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters (c_Packet_Measurement_Order_message_content_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].E_UTRAN_QQUALMIN_Present) {
				}
				if (sequence->data[i].E_UTRAN_Qmin_Present) {
				}
				if (sequence->data[i].E_UTRAN_RSRPmin_Present) {
				}
				if (sequence->data[i].THRESH_E_UTRAN_high_Q_Present) {
				}
				if (sequence->data[i].THRESH_E_UTRAN_low_Q_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_data_E_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters (c_Packet_Measurement_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].EARFCN.items = 0;
			(sequence->data[i].E_UTRAN_PRIORITY) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN (c_Packet_Measurement_Order_message_content_Individual_Priorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters (c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].FDD_ARFCN.items = 0;
			sequence->data[i].TDD_ARFCN.items = 0;
			(sequence->data[i].UTRAN_PRIORITY) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN (c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN (c_Packet_Measurement_Order_message_content_Individual_Priorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information (c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].LSA_ID.items = 0;
			sequence->data[i].ShortLSA_ID.items = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID (c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID (c_Packet_Measurement_Order_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Measurement_Control_Parameters_Description_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Measurement_Control_Parameters_Description_E_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content_Measurement_Control_Parameters_Description_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Measurement_Control_Parameters_Description_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Measurement_Control_Parameters_Description_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content_Measurement_Control_Parameters_Description_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency (c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].FREQ_DIFF_LENGTH) = 0;
			(sequence->data[i].NR_OF_FREQUENCIES) = 0;
			sequence->data[i].REMAIN_FREQ_DATA.items = 0;
			(sequence->data[i].START_FREQUENCY) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Cell_selection_params_Present) {
					if (sequence->data[i].Cell_selection_params.GPRS_MS_TXPWR_MAX_CCH_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_PENALTY_TIME_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RESELECT_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RXLEV_ACCESS_MIN_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_TEMPORARY_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.HCS_params_Present) {
					}
					if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION_Present) {
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
						}
					}
				}
				for (i0=0; i0<sequence->data[i].REMAIN_FREQ_DATA.items; i0++) {
					if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params_Present) {
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_MS_TXPWR_MAX_CCH_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_PENALTY_TIME_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_RESELECT_OFFSET_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_RXLEV_ACCESS_MIN_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.GPRS_TEMPORARY_OFFSET_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.HCS_params_Present) {
						}
						if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION_Present) {
							if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
							}
							if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
							}
							if (sequence->data[i].REMAIN_FREQ_DATA.data[i0].Cell_selection_params.SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
							}
						}
					}
					sequence->data[i].REMAIN_FREQ_DATA.data[i0].FREQUENCY_DIFF.usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency_data_REMAIN_FREQ_DATA'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency_data_REMAIN_FREQ_DATA (c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_List_of_added_Frequency_data_REMAIN_FREQ_DATA* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			sequence->data[i].FREQUENCY_DIFF.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Cell_selection_params_Present) {
					if (sequence->data[i].Cell_selection_params.GPRS_MS_TXPWR_MAX_CCH_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_PENALTY_TIME_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RESELECT_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_RXLEV_ACCESS_MIN_Present) {
					}
					if (sequence->data[i].Cell_selection_params.GPRS_TEMPORARY_OFFSET_Present) {
					}
					if (sequence->data[i].Cell_selection_params.HCS_params_Present) {
					}
					if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION_Present) {
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
						}
						if (sequence->data[i].Cell_selection_params.SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
						}
					}
				}
				sequence->data[i].FREQUENCY_DIFF.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_REMOVED_FREQ_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_REMOVED_FREQ_INDEX (c_Packet_Measurement_Order_message_content_NC_Measurement_Parameters_NC_FREQUENCY_LIST_REMOVED_FREQ_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].Repeated_EARFCN.items = 0;
			(sequence->data[i].THRESH_E_UTRAN_high) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].E_UTRAN_PRIORITY_Present) {
				}
				if (sequence->data[i].E_UTRAN_QRXLEVMIN_Present) {
				}
				for (i0=0; i0<sequence->data[i].Repeated_EARFCN.items; i0++) {
					if (sequence->data[i].Repeated_EARFCN.data[i0].Measurement_Bandwidth_Present) {
					}
				}
				if (sequence->data[i].THRESH_E_UTRAN_low_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_Repeated_EARFCN'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_Repeated_EARFCN (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_Repeated_EARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].EARFCN) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Measurement_Bandwidth_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_Pattern.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_Pattern_length.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_pattern_sense.items = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Not_Allowed_Cells.PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].Not_Allowed_Cells.PCID_Pattern.items; i0++) {
					sequence->data[i].Not_Allowed_Cells.PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
			sequence->data[i].PCID_to_TA_mapping.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i].PCID_to_TA_mapping.items; i0++) {
					if (sequence->data[i].PCID_to_TA_mapping.data[i0].PCID_BITMAP_GROUP_Present) {
					}
					for (i0=0; i0<sequence->data[i].PCID_to_TA_mapping.data[i0].PCID_Pattern.items; i0++) {
						sequence->data[i].PCID_to_TA_mapping.data[i0].PCID_Pattern.data[i0].usedBits = 0;
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_E_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].PCID.items = 0;
			sequence->data[i].PCID_Pattern.items = 0;
			sequence->data[i].PCID_Pattern_length.items = 0;
			sequence->data[i].PCID_pattern_sense.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].PCID_Pattern.items; i0++) {
					sequence->data[i].PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern_length (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_pattern_sense (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].THRESH_UTRAN_high) = 0;
			sequence->data[i].UTRAN_FREQUENCY_INDEX.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].THRESH_UTRAN_low_Present) {
				}
				if (sequence->data[i].UTRAN_PRIORITY_Present) {
				}
				if (sequence->data[i].UTRAN_QRXLEVMIN_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters_data_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters_data_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters_data_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT (c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].PSC.items = 0;
			sequence->data[i].PSC_Pattern.items = 0;
			sequence->data[i].PSC_Pattern_length.items = 0;
			sequence->data[i].PSC_pattern_sense.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i].PSC_Pattern.items; i0++) {
					sequence->data[i].PSC_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC (c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern (c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern_length (c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_pattern_sense (c_Packet_Measurement_Order_message_content__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Measurement_Order_message_content__3G_CSG_Description_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Measurement_Order_message_content__3G_CSG_Description_UTRAN_FREQUENCY_INDEX (c_Packet_Measurement_Order_message_content__3G_CSG_Description_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_CELL_IDENTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_CELL_IDENTITY (c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_CELL_IDENTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX (c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_REPORTING_QUANTITY'. Existing items are not changed. */
void SETITEMS_c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_REPORTING_QUANTITY (c_Packet_Enhanced_Measurement_Report_message_content_E_UTRAN_Measurement_Report_REPORTING_QUANTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Enhanced_Measurement_Report_message_content_NC_Measurement_Report_Repeated_Invalid_BSIC_Information'. Existing items are not changed. */
void SETITEMS_c_Packet_Enhanced_Measurement_Report_message_content_NC_Measurement_Report_Repeated_Invalid_BSIC_Information (c_Packet_Enhanced_Measurement_Report_message_content_NC_Measurement_Report_Repeated_Invalid_BSIC_Information* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BCCH_FREQ_NCELL) = 0;
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].RXLEV_NCELL) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Enhanced_Measurement_Report_message_content_NC_Measurement_Report_Reporting_Quantity_Info_Reporting_Quantity'. Existing items are not changed. */
void SETITEMS_c_Packet_Enhanced_Measurement_Report_message_content_NC_Measurement_Report_Reporting_Quantity_Info_Reporting_Quantity (c_Packet_Enhanced_Measurement_Report_message_content_NC_Measurement_Report_Reporting_Quantity_Info_Reporting_Quantity* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].REPORTING_QUANTITY_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Enhanced_Measurement_Report_message_content_REPORTING_QUANTITY_R8'. Existing items are not changed. */
void SETITEMS_c_Packet_Enhanced_Measurement_Report_message_content_REPORTING_QUANTITY_R8 (c_Packet_Enhanced_Measurement_Report_message_content_REPORTING_QUANTITY_R8* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].REPORTING_QUANTITY_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_CD_LENGTH'. Existing items are not changed. */
void SETITEMS_c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_CD_LENGTH (c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_CD_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_CONTAINER_DATA'. Existing items are not changed. */
void SETITEMS_c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_CONTAINER_DATA (c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_CONTAINER_DATA* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_PD'. Existing items are not changed. */
void SETITEMS_c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_PD (c_Packet_Neighbour_Cell_Data_message_content_CONTAINER_PD* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Paging_Request_message_content_PERSISTENCE_LEVEL_P_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Packet_Paging_Request_message_content_PERSISTENCE_LEVEL_P_LEVEL (c_Packet_Paging_Request_message_content_PERSISTENCE_LEVEL_P_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Paging_Request_message_content_Repeated_Page_info'. Existing items are not changed. */
void SETITEMS_c_Packet_Paging_Request_message_content_Repeated_Page_info (c_Packet_Paging_Request_message_content_Repeated_Page_info* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].CHANNEL_NEEDED_Present) {
				}
				if (sequence->data[i].Ignore_Present) {
					sequence->data[i].Ignore.usedBits = 0;
				}
				if (sequence->data[i].Length_of_Mobile_Identity_contents_Present) {
				}
				if (sequence->data[i].Mobile_Identity_Present) {
					sequence->data[i].Mobile_Identity.usedBits = 0;
				}
				if (sequence->data[i].PTMSI_Present) {
				}
				if (sequence->data[i].TMSI_Present) {
				}
				if (sequence->data[i].eMLPP_PRIORITY_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_PRACH_Parameters_message_content_PRACH_Control_Parameters_MAX_RETRANS'. Existing items are not changed. */
void SETITEMS_c_Packet_PRACH_Parameters_message_content_PRACH_Control_Parameters_MAX_RETRANS (c_Packet_PRACH_Parameters_message_content_PRACH_Control_Parameters_MAX_RETRANS* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_PRACH_Parameters_message_content_PRACH_Control_Parameters_PERSISTENCE_LEVEL_P_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Packet_PRACH_Parameters_message_content_PRACH_Control_Parameters_PERSISTENCE_LEVEL_P_LEVEL (c_Packet_PRACH_Parameters_message_content_PRACH_Control_Parameters_PERSISTENCE_LEVEL_P_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type'. Existing items are not changed. */
void SETITEMS_c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type (c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities'. Existing items are not changed. */
void SETITEMS_c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities (c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Access_capabilities.CDMA_2000_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.COMPACT_Interference_Measurement_Capability) = 0;
			(sequence->data[i].Access_capabilities.ES_IND) = 0;
			(sequence->data[i].Access_capabilities.PS) = 0;
			(sequence->data[i].Access_capabilities.RF_Power_Capability) = 0;
			(sequence->data[i].Access_capabilities.Revision_Level_Indicator) = 0;
			(sequence->data[i].Access_capabilities.UMTS_3_84_Mcps_TDD_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.UMTS_FDD_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.VBS) = 0;
			(sequence->data[i].Access_capabilities.VGCS) = 0;
			
			(sequence->data[i].Length) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Access_capabilities.A5_bits_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_EGPRS_High_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_Enhancements_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_GPRS_High_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_Advanced_Receiver_Performance_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_Dual_Carrier_for_DTM_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_EGPRS2_Present) {
				}
				if (sequence->data[i].Access_capabilities.E_UTRA_FDD_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.E_UTRA_TDD_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_DTM_EGPRS_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_DTM_GPRS_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_RLC_MAC_Control_Message_Segmentation_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.FLO_Iu_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Flexible_Timeslot_Assignment_Present) {
				}
				if (sequence->data[i].Access_capabilities.GAN_PS_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.GERAN_Feature_Package_1_Present) {
				}
				if (sequence->data[i].Access_capabilities.GERAN_to_E_UTRA_support_in_GERAN_packet_transfer_mode_Present) {
				}
				if (sequence->data[i].Access_capabilities.GMSK_Multislot_Power_Profile_Present) {
				}
				if (sequence->data[i].Access_capabilities.High_Multislot_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Length_Present) {
				}
				if (sequence->data[i].Access_capabilities.Modulation_based_multislot_class_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multiple_TBF_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multislot_Capability_Reduction_for_Downlink_Dual_Carrier_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multislot_capability_Present) {
					if (sequence->data[i].Access_capabilities.Multislot_capability.DTM_EGPRS_Multi_Slot_Sub_Class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.DTM_GPRS_Multi_Slot_Sub_Class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.ECSD_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.EGPRS_Extended_Dynamic_Allocation_Capability_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.EGPRS_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.GPRS_Extended_Dynamic_Allocation_Capability_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.GPRS_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.HSCSD_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.SMS_VALUE_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.SM_VALUE_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.Single_Slot_DTM_Present) {
					}
				}
				if (sequence->data[i].Access_capabilities.PS_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Priority_based_reselection_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.RLC_Non_persistent_Mode_Present) {
				}
				if (sequence->data[i].Access_capabilities.Reduced_Latency_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.UMTS_1_28_Mcps_TDD_Radio_Access_Technology_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Uplink_EGPRS2_Present) {
				}
				if (sequence->data[i].Access_capabilities._8_PSK_Multislot_Power_Profile_Present) {
				}
				if (sequence->data[i].Access_capabilities.m8PSK_Power_Capability_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access'. Existing items are not changed. */
void SETITEMS_c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access (c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].Additional_access_technologies.items = 0;
			(sequence->data[i].Length) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies'. Existing items are not changed. */
void SETITEMS_c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies (c_Packet_Resource_Request_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Access_Technology_Type) = 0;
			(sequence->data[i].GMSK_Power_Class) = 0;
			(sequence->data[i]._8PSK_Power_Class) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_PSI_Status_message_content_Received_PSI_Message_List_PSI_Message_struct'. Existing items are not changed. */
void SETITEMS_c_Packet_PSI_Status_message_content_Received_PSI_Message_List_PSI_Message_struct (c_Packet_PSI_Status_message_content_Received_PSI_Message_List_PSI_Message_struct* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].MESSAGE_TYPE) = 0;
			(sequence->data[i].PSIX_CHANGE_MARK) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Instance_bitmap_Present) {
					sequence->data[i].Instance_bitmap.usedBits = 0;
				}
				if (sequence->data[i].PSIX_COUNT_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_PSI_Status_message_content_Received_Unknown_PSI_Message_List_MESSAGE_TYPE'. Existing items are not changed. */
void SETITEMS_c_Packet_PSI_Status_message_content_Received_Unknown_PSI_Message_List_MESSAGE_TYPE (c_Packet_PSI_Status_message_content_Received_Unknown_PSI_Message_List_MESSAGE_TYPE* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Serving_Cell_Data_message_content_CONTAINER_CD_LENGTH'. Existing items are not changed. */
void SETITEMS_c_Packet_Serving_Cell_Data_message_content_CONTAINER_CD_LENGTH (c_Packet_Serving_Cell_Data_message_content_CONTAINER_CD_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Serving_Cell_Data_message_content_CONTAINER_CONTAINER_DATA'. Existing items are not changed. */
void SETITEMS_c_Packet_Serving_Cell_Data_message_content_CONTAINER_CONTAINER_DATA (c_Packet_Serving_Cell_Data_message_content_CONTAINER_CONTAINER_DATA* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Serving_Cell_Data_message_content_CONTAINER_PD'. Existing items are not changed. */
void SETITEMS_c_Packet_Serving_Cell_Data_message_content_CONTAINER_PD (c_Packet_Serving_Cell_Data_message_content_CONTAINER_PD* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_SI_Status_message_content_Received_SI_Message_List_Instance_bitmap'. Existing items are not changed. */
void SETITEMS_c_Packet_SI_Status_message_content_Received_SI_Message_List_Instance_bitmap (c_Packet_SI_Status_message_content_Received_SI_Message_List_Instance_bitmap* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_SI_Status_message_content_Received_SI_Message_List_MESS_REC'. Existing items are not changed. */
void SETITEMS_c_Packet_SI_Status_message_content_Received_SI_Message_List_MESS_REC (c_Packet_SI_Status_message_content_Received_SI_Message_List_MESS_REC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_SI_Status_message_content_Received_SI_Message_List_SIX_CHANGE_MARK'. Existing items are not changed. */
void SETITEMS_c_Packet_SI_Status_message_content_Received_SI_Message_List_SIX_CHANGE_MARK (c_Packet_SI_Status_message_content_Received_SI_Message_List_SIX_CHANGE_MARK* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_SI_Status_message_content_Received_SI_Message_List_SIX_COUNT'. Existing items are not changed. */
void SETITEMS_c_Packet_SI_Status_message_content_Received_SI_Message_List_SIX_COUNT (c_Packet_SI_Status_message_content_Received_SI_Message_List_SIX_COUNT* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_SI_Status_message_content_Received_SI_Message_List_SI_MESSAGE_TYPE'. Existing items are not changed. */
void SETITEMS_c_Packet_SI_Status_message_content_Received_SI_Message_List_SI_MESSAGE_TYPE (c_Packet_SI_Status_message_content_Received_SI_Message_List_SI_MESSAGE_TYPE* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_SI_Status_message_content_Received_Unknown_SI_Message_List_SI_MESSAGE_TYPE'. Existing items are not changed. */
void SETITEMS_c_Packet_SI_Status_message_content_Received_Unknown_SI_Message_List_SI_MESSAGE_TYPE (c_Packet_SI_Status_message_content_Received_Unknown_SI_Message_List_SI_MESSAGE_TYPE* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI1_message_content_PRACH_Control_Parameters_MAX_RETRANS'. Existing items are not changed. */
void SETITEMS_c_PSI1_message_content_PRACH_Control_Parameters_MAX_RETRANS (c_PSI1_message_content_PRACH_Control_Parameters_MAX_RETRANS* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI1_message_content_PRACH_Control_Parameters_PERSISTENCE_LEVEL_P_LEVEL'. Existing items are not changed. */
void SETITEMS_c_PSI1_message_content_PRACH_Control_Parameters_PERSISTENCE_LEVEL_P_LEVEL (c_PSI1_message_content_PRACH_Control_Parameters_PERSISTENCE_LEVEL_P_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_Cell_Allocation_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_Cell_Allocation_RFL_NUMBER (c_PSI2_message_content_Cell_Allocation_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation (c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].HSN) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].ARFCN_index_list_Present) {
				}
				if (sequence->data[i].MA_BITMAP_Present) {
					sequence->data[i].MA_BITMAP.usedBits = 0;
				}
				if (sequence->data[i].MA_LENGTH_Present) {
				}
				if (sequence->data[i].RFL_number_list_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation_data_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation_data_ARFCN_index_list_ARFCN_INDEX (c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation_data_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation_data_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation_data_RFL_number_list_RFL_NUMBER (c_PSI2_message_content_GPRS_Mobile_Allocations_GPRS_Mobile_Allocation_data_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_GPRS_Mobile_Allocations_MA_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_GPRS_Mobile_Allocations_MA_NUMBER (c_PSI2_message_content_GPRS_Mobile_Allocations_MA_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct (c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].TSC) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Hopping_PCCCH_carriers_Present) {
				}
				if (sequence->data[i].MA_NUMBER_Present) {
				}
				if (sequence->data[i].Non_hopping_PCCCH_carriers_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Hopping_PCCCH_carriers_MAIO'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Hopping_PCCCH_carriers_MAIO (c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Hopping_PCCCH_carriers_MAIO* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Hopping_PCCCH_carriers_TIMESLOT_ALLOCATION'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Hopping_PCCCH_carriers_TIMESLOT_ALLOCATION (c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Hopping_PCCCH_carriers_TIMESLOT_ALLOCATION* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Non_hopping_PCCCH_carriers_ARFCN'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Non_hopping_PCCCH_carriers_ARFCN (c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Non_hopping_PCCCH_carriers_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Non_hopping_PCCCH_carriers_TIMESLOT_ALLOCATION'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Non_hopping_PCCCH_carriers_TIMESLOT_ALLOCATION (c_PSI2_message_content_PCCCH_Description_PCCCH_Description_struct_data_Non_hopping_PCCCH_carriers_TIMESLOT_ALLOCATION* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_Reference_Frequency_Lists_Length_of_RFL_contents'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_Reference_Frequency_Lists_Length_of_RFL_contents (c_PSI2_message_content_Reference_Frequency_Lists_Length_of_RFL_contents* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_Reference_Frequency_Lists_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_Reference_Frequency_Lists_RFL_NUMBER (c_PSI2_message_content_Reference_Frequency_Lists_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI2_message_content_Reference_Frequency_Lists_RFL_contents'. Existing items are not changed. */
void SETITEMS_c_PSI2_message_content_Reference_Frequency_Lists_RFL_contents (c_PSI2_message_content_Reference_Frequency_Lists_RFL_contents* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_CCN_Support_Description_CCN_SUPPORTED'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_CCN_Support_Description_CCN_SUPPORTED (c_PSI3_message_content_CCN_Support_Description_CCN_SUPPORTED* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_COMPACT_Information_COMPACT_Cell_selection_params'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_COMPACT_Information_COMPACT_Cell_selection_params (c_PSI3_message_content_COMPACT_Information_COMPACT_Cell_selection_params* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].CELL_BAR_ACCESS_2) = 0;
			(sequence->data[i].EXC_ACC) = 0;
			(sequence->data[i].SAME_RA_AS_SERVING_CELL) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].GPRS_MS_TXPWR_MAX_CCH_Present) {
				}
				if (sequence->data[i].GPRS_PENALTY_TIME_Present) {
				}
				if (sequence->data[i].GPRS_RESELECT_OFFSET_Present) {
				}
				if (sequence->data[i].GPRS_RXLEV_ACCESS_MIN_Present) {
				}
				if (sequence->data[i].GPRS_TEMPORARY_OFFSET_Present) {
				}
				if (sequence->data[i].GUAR_CONSTANT_PWR_BLKS_Present) {
				}
				if (sequence->data[i].HCS_params_Present) {
				}
				if (sequence->data[i].TIME_GROUP_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_COMPACT_Information_FREQUENCY_DIFF'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_COMPACT_Information_FREQUENCY_DIFF (c_PSI3_message_content_COMPACT_Information_FREQUENCY_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_COMPACT_Information_FREQ_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_COMPACT_Information_FREQ_DIFF_LENGTH (c_PSI3_message_content_COMPACT_Information_FREQ_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_COMPACT_Information_NR_OF_REMAINING_CELLS'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_COMPACT_Information_NR_OF_REMAINING_CELLS (c_PSI3_message_content_COMPACT_Information_NR_OF_REMAINING_CELLS* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_COMPACT_Information_START_FREQUENCY'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_COMPACT_Information_START_FREQUENCY (c_PSI3_message_content_COMPACT_Information_START_FREQUENCY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_LSA_Parameters_LSA_ID_information'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_LSA_Parameters_LSA_ID_information (c_PSI3_message_content_LSA_Parameters_LSA_ID_information* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].LSA_ID.items = 0;
			sequence->data[i].ShortLSA_ID.items = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID (c_PSI3_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID (c_PSI3_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Neighbour_Cell_parameters_Cell_Selection_Params'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Neighbour_Cell_parameters_Cell_Selection_Params (c_PSI3_message_content_Neighbour_Cell_parameters_Cell_Selection_Params* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].CELL_BAR_ACCESS_2) = 0;
			(sequence->data[i].EXC_ACC) = 0;
			(sequence->data[i].SAME_RA_AS_SERVING_CELL) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].GPRS_MS_TXPWR_MAX_CCH_Present) {
				}
				if (sequence->data[i].GPRS_PENALTY_TIME_Present) {
				}
				if (sequence->data[i].GPRS_RESELECT_OFFSET_Present) {
				}
				if (sequence->data[i].GPRS_RXLEV_ACCESS_MIN_Present) {
				}
				if (sequence->data[i].GPRS_TEMPORARY_OFFSET_Present) {
				}
				if (sequence->data[i].HCS_params_Present) {
				}
				if (sequence->data[i].SI13_PBCCH_LOCATION_Present) {
					if (sequence->data[i].SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Neighbour_Cell_parameters_Cell_selection_params'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Neighbour_Cell_parameters_Cell_selection_params (c_PSI3_message_content_Neighbour_Cell_parameters_Cell_selection_params* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].CELL_BAR_ACCESS_2) = 0;
			(sequence->data[i].EXC_ACC) = 0;
			(sequence->data[i].SAME_RA_AS_SERVING_CELL) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].GPRS_MS_TXPWR_MAX_CCH_Present) {
				}
				if (sequence->data[i].GPRS_PENALTY_TIME_Present) {
				}
				if (sequence->data[i].GPRS_RESELECT_OFFSET_Present) {
				}
				if (sequence->data[i].GPRS_RXLEV_ACCESS_MIN_Present) {
				}
				if (sequence->data[i].GPRS_TEMPORARY_OFFSET_Present) {
				}
				if (sequence->data[i].HCS_params_Present) {
				}
				if (sequence->data[i].SI13_PBCCH_LOCATION_Present) {
					if (sequence->data[i].SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Neighbour_Cell_parameters_FREQUENCY_DIFF'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Neighbour_Cell_parameters_FREQUENCY_DIFF (c_PSI3_message_content_Neighbour_Cell_parameters_FREQUENCY_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Neighbour_Cell_parameters_FREQ_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Neighbour_Cell_parameters_FREQ_DIFF_LENGTH (c_PSI3_message_content_Neighbour_Cell_parameters_FREQ_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Neighbour_Cell_parameters_NR_OF_REMAINING_CELLS'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Neighbour_Cell_parameters_NR_OF_REMAINING_CELLS (c_PSI3_message_content_Neighbour_Cell_parameters_NR_OF_REMAINING_CELLS* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Neighbour_Cell_parameters_START_FREQUENCY'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Neighbour_Cell_parameters_START_FREQUENCY (c_PSI3_message_content_Neighbour_Cell_parameters_START_FREQUENCY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Serving_Cell_LSA_ID_information_LSA_ID'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Serving_Cell_LSA_ID_information_LSA_ID (c_PSI3_message_content_Serving_Cell_LSA_ID_information_LSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_message_content_Serving_Cell_LSA_ID_information_ShortLSA_ID'. Existing items are not changed. */
void SETITEMS_c_PSI3_message_content_Serving_Cell_LSA_ID_information_ShortLSA_ID (c_PSI3_message_content_Serving_Cell_LSA_ID_information_ShortLSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_CCN_Support_Description_CCN_SUPPORTED'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_CCN_Support_Description_CCN_SUPPORTED (c_PSI3_bis_message_content_CCN_Support_Description_CCN_SUPPORTED* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_BCC'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_BCC (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_BCC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_CELL_BAR_ACCESS_2'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_CELL_BAR_ACCESS_2 (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_CELL_BAR_ACCESS_2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_CELL_PARAMS_POINTER'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_CELL_PARAMS_POINTER (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_CELL_PARAMS_POINTER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_COMPACT_Neighbour_parameter_set'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_COMPACT_Neighbour_parameter_set (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_COMPACT_Neighbour_parameter_set* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].EXC_ACC) = 0;
			(sequence->data[i].GPRS_PENALTY_TIME) = 0;
			(sequence->data[i].GPRS_RESELECT_OFFSET) = 0;
			(sequence->data[i].GPRS_TEMPORARY_OFFSET) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].GPRS_HCS_THR_Present) {
				}
				if (sequence->data[i].GPRS_MS_TXPWR_MAX_CCH_Present) {
				}
				if (sequence->data[i].GPRS_PRIORITY_CLASS_Present) {
				}
				if (sequence->data[i].GPRS_RXLEV_ACCESS_MIN_Present) {
				}
				if (sequence->data[i].GUAR_CONSTANT_PWR_BLKS_Present) {
				}
				if (sequence->data[i].NCC_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_FREQUENCY_DIFF'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_FREQUENCY_DIFF (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_FREQUENCY_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_FREQ_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_FREQ_DIFF_LENGTH (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_FREQ_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_Message_escape'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_Message_escape (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_Message_escape* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_NR_OF_REMAINING_CELLS'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_NR_OF_REMAINING_CELLS (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_NR_OF_REMAINING_CELLS* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_SAME_RA_AS_SERVING_CELL'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_SAME_RA_AS_SERVING_CELL (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_SAME_RA_AS_SERVING_CELL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_START_FREQUENCY'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_START_FREQUENCY (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_START_FREQUENCY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_TIME_GROUP'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_TIME_GROUP (c_PSI3_bis_message_content_COMPACT_Neighbour_Cell_Parameters_TIME_GROUP* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information (c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].LSA_ID.items = 0;
			sequence->data[i].ShortLSA_ID.items = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID (c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information_data_LSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID (c_PSI3_bis_message_content_LSA_Parameters_LSA_ID_information_data_ShortLSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_Message_escape'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_Message_escape (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_Message_escape* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2 (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].NCellParam2Element.items = 0;
			sequence->data[i].Neighbour_parameter_set.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i].NCellParam2Element.items; i0++) {
					for (i0=0; i0<sequence->data[i].NCellParam2Element.data[i0].NCP2Element.items; i0++) {
						for (i0=0; i0<sequence->data[i].NCellParam2Element.data[i0].NCP2Element.data[i0].FREQUENCY_DIFF.items; i0++) {
							sequence->data[i].NCellParam2Element.data[i0].NCP2Element.data[i0].FREQUENCY_DIFF.data[i0].usedBits = 0;
						}
						if (sequence->data[i].NCellParam2Element.data[i0].NCP2Element.data[i0].FREQ_DIFF_LENGTH_Present) {
						}
						if (sequence->data[i].NCellParam2Element.data[i0].NCP2Element.data[i0].NR_OF_REMAINING_CELLS_Present) {
						}
					}
				}
				for (i0=0; i0<sequence->data[i].Neighbour_parameter_set.items; i0++) {
					if (sequence->data[i].Neighbour_parameter_set.data[i0].GPRS_MS_TXPWR_MAX_CCH_Present) {
					}
					if (sequence->data[i].Neighbour_parameter_set.data[i0].GPRS_RXLEV_ACCESS_MIN_Present) {
					}
					if (sequence->data[i].Neighbour_parameter_set.data[i0].HCS_THR_Present) {
					}
					if (sequence->data[i].Neighbour_parameter_set.data[i0].NCC_Present) {
					}
					if (sequence->data[i].Neighbour_parameter_set.data[i0].PRIORITY_CLASS_Present) {
					}
					if (sequence->data[i].Neighbour_parameter_set.data[i0].SI13_PBCCH_LOCATION_Present) {
						if (sequence->data[i].Neighbour_parameter_set.data[i0].SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
						}
						if (sequence->data[i].Neighbour_parameter_set.data[i0].SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
						}
						if (sequence->data[i].Neighbour_parameter_set.data[i0].SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
						}
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].CELL_PARAMS_POINTER) = 0;
			sequence->data[i].NCP2Element.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i].NCP2Element.items; i0++) {
					for (i0=0; i0<sequence->data[i].NCP2Element.data[i0].FREQUENCY_DIFF.items; i0++) {
						sequence->data[i].NCP2Element.data[i0].FREQUENCY_DIFF.data[i0].usedBits = 0;
					}
					if (sequence->data[i].NCP2Element.data[i0].FREQ_DIFF_LENGTH_Present) {
					}
					if (sequence->data[i].NCP2Element.data[i0].NR_OF_REMAINING_CELLS_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].BCC.items = 0;
			sequence->data[i].CELL_BAR_ACCESS_2.items = 0;
			sequence->data[i].FREQUENCY_DIFF.items = 0;
			(sequence->data[i].NCP2_Property.BCC) = 0;
			(sequence->data[i].NCP2_Property.CELL_BAR_ACCESS_2) = 0;
			(sequence->data[i].NCP2_Property.SAME_RA_AS_SERVING_CELL) = 0;
			
			sequence->data[i].SAME_RA_AS_SERVING_CELL.items = 0;
			(sequence->data[i].START_FREQUENCY) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i].FREQUENCY_DIFF.items; i0++) {
					sequence->data[i].FREQUENCY_DIFF.data[i0].usedBits = 0;
				}
				if (sequence->data[i].FREQ_DIFF_LENGTH_Present) {
				}
				if (sequence->data[i].NR_OF_REMAINING_CELLS_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_BCC'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_BCC (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_BCC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_CELL_BAR_ACCESS_2'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_CELL_BAR_ACCESS_2 (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_CELL_BAR_ACCESS_2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_FREQUENCY_DIFF'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_FREQUENCY_DIFF (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_FREQUENCY_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_SAME_RA_AS_SERVING_CELL'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_SAME_RA_AS_SERVING_CELL (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_NCellParam2Element_data_NCP2Element_data_SAME_RA_AS_SERVING_CELL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_Neighbour_parameter_set'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_Neighbour_parameter_set (c_PSI3_bis_message_content_Neighbour_Cell_parameters_2_NCellParam2_data_Neighbour_parameter_set* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].EXC_ACC) = 0;
			(sequence->data[i].GPRS_PENALTY_TIME) = 0;
			(sequence->data[i].GPRS_RESELECT_OFFSET) = 0;
			(sequence->data[i].GPRS_TEMPORARY_OFFSET) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].GPRS_MS_TXPWR_MAX_CCH_Present) {
				}
				if (sequence->data[i].GPRS_RXLEV_ACCESS_MIN_Present) {
				}
				if (sequence->data[i].HCS_THR_Present) {
				}
				if (sequence->data[i].NCC_Present) {
				}
				if (sequence->data[i].PRIORITY_CLASS_Present) {
				}
				if (sequence->data[i].SI13_PBCCH_LOCATION_Present) {
					if (sequence->data[i].SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_cell_parameters_Cell_Selection_Params'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_cell_parameters_Cell_Selection_Params (c_PSI3_bis_message_content_Neighbour_cell_parameters_Cell_Selection_Params* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].CELL_BAR_ACCESS_2) = 0;
			(sequence->data[i].EXC_ACC) = 0;
			(sequence->data[i].SAME_RA_AS_SERVING_CELL) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].GPRS_MS_TXPWR_MAX_CCH_Present) {
				}
				if (sequence->data[i].GPRS_PENALTY_TIME_Present) {
				}
				if (sequence->data[i].GPRS_RESELECT_OFFSET_Present) {
				}
				if (sequence->data[i].GPRS_RXLEV_ACCESS_MIN_Present) {
				}
				if (sequence->data[i].GPRS_TEMPORARY_OFFSET_Present) {
				}
				if (sequence->data[i].HCS_params_Present) {
				}
				if (sequence->data[i].SI13_PBCCH_LOCATION_Present) {
					if (sequence->data[i].SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_cell_parameters_Cell_selection_params'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_cell_parameters_Cell_selection_params (c_PSI3_bis_message_content_Neighbour_cell_parameters_Cell_selection_params* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].CELL_BAR_ACCESS_2) = 0;
			(sequence->data[i].EXC_ACC) = 0;
			(sequence->data[i].SAME_RA_AS_SERVING_CELL) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].GPRS_MS_TXPWR_MAX_CCH_Present) {
				}
				if (sequence->data[i].GPRS_PENALTY_TIME_Present) {
				}
				if (sequence->data[i].GPRS_RESELECT_OFFSET_Present) {
				}
				if (sequence->data[i].GPRS_RXLEV_ACCESS_MIN_Present) {
				}
				if (sequence->data[i].GPRS_TEMPORARY_OFFSET_Present) {
				}
				if (sequence->data[i].HCS_params_Present) {
				}
				if (sequence->data[i].SI13_PBCCH_LOCATION_Present) {
					if (sequence->data[i].SI13_PBCCH_LOCATION.PBCCH_LOCATION_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.PSI1_REPEAT_PERIOD_Present) {
					}
					if (sequence->data[i].SI13_PBCCH_LOCATION.SI13_LOCATION_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_cell_parameters_FREQUENCY_DIFF'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_cell_parameters_FREQUENCY_DIFF (c_PSI3_bis_message_content_Neighbour_cell_parameters_FREQUENCY_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_cell_parameters_FREQ_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_cell_parameters_FREQ_DIFF_LENGTH (c_PSI3_bis_message_content_Neighbour_cell_parameters_FREQ_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_cell_parameters_NR_OF_REMAINING_CELLS'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_cell_parameters_NR_OF_REMAINING_CELLS (c_PSI3_bis_message_content_Neighbour_cell_parameters_NR_OF_REMAINING_CELLS* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_bis_message_content_Neighbour_cell_parameters_START_FREQUENCY'. Existing items are not changed. */
void SETITEMS_c_PSI3_bis_message_content_Neighbour_cell_parameters_START_FREQUENCY (c_PSI3_bis_message_content_Neighbour_cell_parameters_START_FREQUENCY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_ter_message_content_GPRS_REP_PRIORITY_Description_REP_PRIORITY'. Existing items are not changed. */
void SETITEMS_c_PSI3_ter_message_content_GPRS_REP_PRIORITY_Description_REP_PRIORITY (c_PSI3_ter_message_content_GPRS_REP_PRIORITY_Description_REP_PRIORITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_ter_message_content_Real_Time_Difference_Description_Cell_Index_Start_RTD'. Existing items are not changed. */
void SETITEMS_c_PSI3_ter_message_content_Real_Time_Difference_Description_Cell_Index_Start_RTD (c_PSI3_ter_message_content_Real_Time_Difference_Description_Cell_Index_Start_RTD* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_ter_message_content_Real_Time_Difference_Description_RTD_Struct'. Existing items are not changed. */
void SETITEMS_c_PSI3_ter_message_content_Real_Time_Difference_Description_RTD_Struct (c_PSI3_ter_message_content_Real_Time_Difference_Description_RTD_Struct* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].RTD_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_quater_message_content_GPRS_REP_PRIORITY_Description_REP_PRIORITY'. Existing items are not changed. */
void SETITEMS_c_PSI3_quater_message_content_GPRS_REP_PRIORITY_Description_REP_PRIORITY (c_PSI3_quater_message_content_GPRS_REP_PRIORITY_Description_REP_PRIORITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_quater_message_content__3G_Neighbour_Cells_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_PSI3_quater_message_content__3G_Neighbour_Cells_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells (c_PSI3_quater_message_content__3G_Neighbour_Cells_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].FDD_ARFCN) = 0;
			sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].FDD_Indic0) = 0;
			(sequence->data[i].NR_OF_FDD_CELLS) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI3_quater_message_content__3G_Neighbour_Cells_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_PSI3_quater_message_content__3G_Neighbour_Cells_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells (c_PSI3_quater_message_content__3G_Neighbour_Cells_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].NR_OF_TDD_CELLS) = 0;
			(sequence->data[i].TDD_ARFCN) = 0;
			sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].TDD_Indic0) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI4_message_content_INT_MEAS_CHANNEL_LIST_Channel_Group'. Existing items are not changed. */
void SETITEMS_c_PSI4_message_content_INT_MEAS_CHANNEL_LIST_Channel_Group (c_PSI4_message_content_INT_MEAS_CHANNEL_LIST_Channel_Group* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].TIMESLOT_ALLOCATION) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].ARFCN_Present) {
				}
				if (sequence->data[i].MAIO_Present) {
				}
				if (sequence->data[i].MA_NUMBER_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQUENCY_DIFF'. Existing items are not changed. */
void SETITEMS_c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQUENCY_DIFF (c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQUENCY_DIFF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQ_DIFF_LENGTH'. Existing items are not changed. */
void SETITEMS_c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQ_DIFF_LENGTH (c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_FREQ_DIFF_LENGTH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_NR_OF_FREQUENCIES'. Existing items are not changed. */
void SETITEMS_c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_NR_OF_FREQUENCIES (c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_NR_OF_FREQUENCIES* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_START_FREQUENCY'. Existing items are not changed. */
void SETITEMS_c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_START_FREQUENCY (c_PSI5_message_content_EXT_Measurement_Parameters_EXT_FREQUENCY_LIST_START_FREQUENCY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI13_message_content_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_PSI13_message_content_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_PSI13_message_content_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI13_message_content_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PSI13_message_content_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_PSI13_message_content_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI14_message_content_CCCH_Access_Information_SI13_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_PSI14_message_content_CCCH_Access_Information_SI13_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_PSI14_message_content_CCCH_Access_Information_SI13_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI14_message_content_CCCH_Access_Information_SI13_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PSI14_message_content_CCCH_Access_Information_SI13_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_PSI14_message_content_CCCH_Access_Information_SI13_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI14_message_content_PBCCH_Description_PBCCH_Frequency_Description_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_PSI14_message_content_PBCCH_Description_PBCCH_Frequency_Description_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_PSI14_message_content_PBCCH_Description_PBCCH_Frequency_Description_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI14_message_content_PBCCH_Description_PBCCH_Frequency_Description_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PSI14_message_content_PBCCH_Description_PBCCH_Frequency_Description_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_PSI14_message_content_PBCCH_Description_PBCCH_Frequency_Description_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Uplink_Assignment_message_content_Access_Technologies_Request_Access_Technology_Type'. Existing items are not changed. */
void SETITEMS_c_Packet_Uplink_Assignment_message_content_Access_Technologies_Request_Access_Technology_Type (c_Packet_Uplink_Assignment_message_content_Access_Technologies_Request_Access_Technology_Type* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Uplink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Uplink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_Packet_Uplink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Uplink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_Packet_Uplink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_Packet_Uplink_Assignment_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Uplink_Assignment_message_content_PERSISTENCE_LEVEL_P_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Packet_Uplink_Assignment_message_content_PERSISTENCE_LEVEL_P_LEVEL (c_Packet_Uplink_Assignment_message_content_PERSISTENCE_LEVEL_P_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Timeslot_Reconfigure_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_Packet_Timeslot_Reconfigure_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_Packet_Timeslot_Reconfigure_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Packet_Timeslot_Reconfigure_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_Packet_Timeslot_Reconfigure_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_Packet_Timeslot_Reconfigure_message_content_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type'. Existing items are not changed. */
void SETITEMS_c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type (c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities'. Existing items are not changed. */
void SETITEMS_c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities (c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Access_capabilities.CDMA_2000_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.COMPACT_Interference_Measurement_Capability) = 0;
			(sequence->data[i].Access_capabilities.ES_IND) = 0;
			(sequence->data[i].Access_capabilities.PS) = 0;
			(sequence->data[i].Access_capabilities.RF_Power_Capability) = 0;
			(sequence->data[i].Access_capabilities.Revision_Level_Indicator) = 0;
			(sequence->data[i].Access_capabilities.UMTS_3_84_Mcps_TDD_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.UMTS_FDD_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.VBS) = 0;
			(sequence->data[i].Access_capabilities.VGCS) = 0;
			
			(sequence->data[i].Length) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Access_capabilities.A5_bits_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_EGPRS_High_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_Enhancements_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_GPRS_High_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_Advanced_Receiver_Performance_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_Dual_Carrier_for_DTM_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_EGPRS2_Present) {
				}
				if (sequence->data[i].Access_capabilities.E_UTRA_FDD_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.E_UTRA_TDD_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_DTM_EGPRS_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_DTM_GPRS_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_RLC_MAC_Control_Message_Segmentation_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.FLO_Iu_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Flexible_Timeslot_Assignment_Present) {
				}
				if (sequence->data[i].Access_capabilities.GAN_PS_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.GERAN_Feature_Package_1_Present) {
				}
				if (sequence->data[i].Access_capabilities.GERAN_to_E_UTRA_support_in_GERAN_packet_transfer_mode_Present) {
				}
				if (sequence->data[i].Access_capabilities.GMSK_Multislot_Power_Profile_Present) {
				}
				if (sequence->data[i].Access_capabilities.High_Multislot_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Length_Present) {
				}
				if (sequence->data[i].Access_capabilities.Modulation_based_multislot_class_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multiple_TBF_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multislot_Capability_Reduction_for_Downlink_Dual_Carrier_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multislot_capability_Present) {
					if (sequence->data[i].Access_capabilities.Multislot_capability.DTM_EGPRS_Multi_Slot_Sub_Class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.DTM_GPRS_Multi_Slot_Sub_Class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.ECSD_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.EGPRS_Extended_Dynamic_Allocation_Capability_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.EGPRS_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.GPRS_Extended_Dynamic_Allocation_Capability_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.GPRS_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.HSCSD_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.SMS_VALUE_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.SM_VALUE_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.Single_Slot_DTM_Present) {
					}
				}
				if (sequence->data[i].Access_capabilities.PS_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Priority_based_reselection_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.RLC_Non_persistent_Mode_Present) {
				}
				if (sequence->data[i].Access_capabilities.Reduced_Latency_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.UMTS_1_28_Mcps_TDD_Radio_Access_Technology_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Uplink_EGPRS2_Present) {
				}
				if (sequence->data[i].Access_capabilities._8_PSK_Multislot_Power_Profile_Present) {
				}
				if (sequence->data[i].Access_capabilities.m8PSK_Power_Capability_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access'. Existing items are not changed. */
void SETITEMS_c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access (c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].Additional_access_technologies.items = 0;
			(sequence->data[i].Length) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies'. Existing items are not changed. */
void SETITEMS_c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies (c_Additional_MS_Radio_Access_Capabilities_message_content_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Access_Technology_Type) = 0;
			(sequence->data[i].GMSK_Power_Class) = 0;
			(sequence->data[i]._8PSK_Power_Class) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_Measurement_Control_Parameters_Description_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_Measurement_Control_Parameters_Description_E_UTRAN_FREQUENCY_INDEX (c_PS_Handover_Command_message_content_Measurement_Control_Parameters_Description_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_Measurement_Control_Parameters_Description_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_Measurement_Control_Parameters_Description_UTRAN_FREQUENCY_INDEX (c_PS_Handover_Command_message_content_Measurement_Control_Parameters_Description_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_CCN_Support_Description_CCN_SUPPORTED'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_CCN_Support_Description_CCN_SUPPORTED (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_CCN_Support_Description_CCN_SUPPORTED* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Downlink_TBFs_Downlink_Assignment'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Downlink_TBFs_Downlink_Assignment (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Downlink_TBFs_Downlink_Assignment* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Downlink_TBF_assignment.CONTROL_ACK) = 0;
			(sequence->data[i].Downlink_TBF_assignment.RLC_MODE) = 0;
			(sequence->data[i].Downlink_TBF_assignment.TFI_Assignment) = 0;
			
			(sequence->data[i].TIMESLOT_ALLOCATION) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Downlink_TBF_assignment.EGPRS_Window_Size_Present) {
				}
				if (sequence->data[i].Downlink_TBF_assignment.PFI_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Uplink_TBFs_Uplink_Assignment'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Uplink_TBFs_Uplink_Assignment (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Uplink_TBFs_Uplink_Assignment* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].RLC_MODE) = 0;
			(sequence->data[i].TFI_Assignment) = 0;
			sequence->data[i].USF_ALLOCATION_INFO.items = 0;
			(sequence->data[i].USF_GRANULARITY) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].CHANNEL_CODING_COMMAND_Present) {
				}
				if (sequence->data[i].EGPRS_Channel_Coding_Command_Present) {
				}
				if (sequence->data[i].EGPRS_Window_Size_Present) {
				}
				if (sequence->data[i].PFI_Present) {
				}
				if (sequence->data[i].TBF_TIMESLOT_ALLOCATION_Present) {
					sequence->data[i].TBF_TIMESLOT_ALLOCATION.usedBits = 0;
				}
				if (sequence->data[i].USF_ALLOCATION_Present) {
				}
				if (sequence->data[i].USF_ALLOCATION_ALL_TIMESLOTS_Present) {
				}
				for (i0=0; i0<sequence->data[i].USF_ALLOCATION_INFO.items; i0++) {
					if (sequence->data[i].USF_ALLOCATION_INFO.data[i0].USF_ALLOCATION_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Uplink_TBFs_Uplink_Assignment_data_USF_ALLOCATION_INFO'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Uplink_TBFs_Uplink_Assignment_data_USF_ALLOCATION_INFO (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_EGPRS_mode_EGPRS_mode_Uplink_TBFs_Uplink_Assignment_data_USF_ALLOCATION_INFO* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].USF_ALLOCATION_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_Frequency_Parameters_Direct_encoding_1_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Downlink_TBFs_Downlink_Assignment'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Downlink_TBFs_Downlink_Assignment (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Downlink_TBFs_Downlink_Assignment* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Downlink_TBF_assignment.CONTROL_ACK) = 0;
			(sequence->data[i].Downlink_TBF_assignment.RLC_MODE) = 0;
			(sequence->data[i].Downlink_TBF_assignment.TFI_Assignment) = 0;
			
			(sequence->data[i].TIMESLOT_ALLOCATION) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Downlink_TBF_assignment.EGPRS_Window_Size_Present) {
				}
				if (sequence->data[i].Downlink_TBF_assignment.PFI_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Uplink_TBFs_Uplink_Assignment'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Uplink_TBFs_Uplink_Assignment (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Uplink_TBFs_Uplink_Assignment* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].RLC_MODE) = 0;
			(sequence->data[i].TFI_Assignment) = 0;
			sequence->data[i].USF_ALLOCATION_INFO.items = 0;
			(sequence->data[i].USF_GRANULARITY) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].CHANNEL_CODING_COMMAND_Present) {
				}
				if (sequence->data[i].EGPRS_Channel_Coding_Command_Present) {
				}
				if (sequence->data[i].EGPRS_Window_Size_Present) {
				}
				if (sequence->data[i].PFI_Present) {
				}
				if (sequence->data[i].TBF_TIMESLOT_ALLOCATION_Present) {
					sequence->data[i].TBF_TIMESLOT_ALLOCATION.usedBits = 0;
				}
				if (sequence->data[i].USF_ALLOCATION_Present) {
				}
				if (sequence->data[i].USF_ALLOCATION_ALL_TIMESLOTS_Present) {
				}
				for (i0=0; i0<sequence->data[i].USF_ALLOCATION_INFO.items; i0++) {
					if (sequence->data[i].USF_ALLOCATION_INFO.data[i0].USF_ALLOCATION_Present) {
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Uplink_TBFs_Uplink_Assignment_data_USF_ALLOCATION_INFO'. Existing items are not changed. */
void SETITEMS_c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Uplink_TBFs_Uplink_Assignment_data_USF_ALLOCATION_INFO (c_PS_Handover_Command_message_content_PS_Handover_to_A_Gb_Mode_Payload_PS_Handover_RR_Info_GPRS_mode_GPRS_mode_Uplink_TBFs_Uplink_Assignment_data_USF_ALLOCATION_INFO* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].USF_ALLOCATION_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_UTRANFreqList_FDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_UTRANFreqList_FDD_ARFCN (c_UTRANFreqList_FDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_UTRANFreqList_TDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_UTRANFreqList_TDD_ARFCN (c_UTRANFreqList_TDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_BA_List_Pref_BA_FREQ'. Existing items are not changed. */
void SETITEMS_c_BA_List_Pref_BA_FREQ (c_BA_List_Pref_BA_FREQ* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_BA_List_Pref_Range'. Existing items are not changed. */
void SETITEMS_c_BA_List_Pref_Range (c_BA_List_Pref_Range* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].RANGE_LOWER) = 0;
			(sequence->data[i].RANGE_UPPER) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_E_UTRAN_Description'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_E_UTRAN_Description (c_CellSelectionIndicator_E_UTRAN_Description* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].EARFCN) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Measurement_Bandwidth_Present) {
				}
				if (sequence->data[i].Not_Allowed_Cells_Present) {
					if (sequence->data[i].Not_Allowed_Cells.PCID_BITMAP_GROUP_Present) {
					}
					for (i0=0; i0<sequence->data[i].Not_Allowed_Cells.PCID_Pattern.items; i0++) {
						sequence->data[i].Not_Allowed_Cells.PCID_Pattern.data[i0].usedBits = 0;
					}
				}
				if (sequence->data[i].TARGET_PCID_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID (c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_Pattern (c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_Pattern_length (c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_pattern_sense (c_CellSelectionIndicator_E_UTRAN_Description_data_Not_Allowed_Cells_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_GSM_Description'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_GSM_Description (c_CellSelectionIndicator_GSM_Description* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].ARFCN) = 0;
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].Band_Indicator) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_UTRAN_FDD_Description'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_UTRAN_FDD_Description (c_CellSelectionIndicator_UTRAN_FDD_Description* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].FDD_ARFCN) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Bandwidth_FDD_Present) {
				}
				if (sequence->data[i].FDD_CELL_INFORMATION_Field_Present) {
					sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
				}
				if (sequence->data[i].FDD_Indic0_Present) {
				}
				if (sequence->data[i].NR_OF_FDD_CELLS_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellSelectionIndicator_UTRAN_TDD_Description'. Existing items are not changed. */
void SETITEMS_c_CellSelectionIndicator_UTRAN_TDD_Description (c_CellSelectionIndicator_UTRAN_TDD_Description* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].TDD_ARFCN) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Bandwidth_TDD_Present) {
				}
				if (sequence->data[i].NR_OF_TDD_CELLS_Present) {
				}
				if (sequence->data[i].TDD_CELL_INFORMATION_Field_Present) {
					sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
				}
				if (sequence->data[i].TDD_Indic0_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_ARFCN_FIRST'. Existing items are not changed. */
void SETITEMS_c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_ARFCN_FIRST (c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_ARFCN_FIRST* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_ARFCN_RANGE'. Existing items are not changed. */
void SETITEMS_c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_ARFCN_RANGE (c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_ARFCN_RANGE* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_BAND_OFFSET'. Existing items are not changed. */
void SETITEMS_c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_BAND_OFFSET (c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_BAND_OFFSET* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_GSM_Band'. Existing items are not changed. */
void SETITEMS_c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_GSM_Band (c_Dynamic_ARFCN_Mapping_X_DYNAMIC_ARFCN_MAPPING_Description_GSM_Band* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_IARestOctets_Access_Technologies_Request_Access_Technology_Type'. Existing items are not changed. */
void SETITEMS_c_IARestOctets_Access_Technologies_Request_Access_Technology_Type (c_IARestOctets_Access_Technologies_Request_Access_Technology_Type* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_CCN_Support_Description_CCN_SUPPORTED'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_CCN_Support_Description_CCN_SUPPORTED (c_SI2quaterRestOctets_CCN_Support_Description_CCN_SUPPORTED* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_EARFCN'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_EARFCN (c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_EARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT (c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].PCID.items = 0;
			sequence->data[i].PCID_Pattern.items = 0;
			sequence->data[i].PCID_Pattern_length.items = 0;
			sequence->data[i].PCID_pattern_sense.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].PCID_Pattern.items; i0++) {
					sequence->data[i].PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID (c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern (c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length (c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense (c_SI2quaterRestOctets_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX (c_SI2quaterRestOctets_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters (c_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].E_UTRAN_QQUALMIN_Present) {
				}
				if (sequence->data[i].E_UTRAN_Qmin_Present) {
				}
				if (sequence->data[i].E_UTRAN_RSRPmin_Present) {
				}
				if (sequence->data[i].THRESH_E_UTRAN_high_Q_Present) {
				}
				if (sequence->data[i].THRESH_E_UTRAN_low_Q_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_data_E_UTRAN_FREQUENCY_INDEX (c_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_GPRS_BSIC_Description_BSIC'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_GPRS_BSIC_Description_BSIC (c_SI2quaterRestOctets_GPRS_BSIC_Description_BSIC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_GPRS_BSIC_Description_Frequency_Scrolling'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_GPRS_BSIC_Description_Frequency_Scrolling (c_SI2quaterRestOctets_GPRS_BSIC_Description_Frequency_Scrolling* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD12'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD12 (c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD12* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].RTD.items = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD12_data_RTD'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD12_data_RTD (c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD12_data_RTD* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD6'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD6 (c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD6* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].RTD.items = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD6_data_RTD'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD6_data_RTD (c_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_RTD6_data_RTD* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].Repeated_EARFCN.items = 0;
			(sequence->data[i].THRESH_E_UTRAN_high) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].E_UTRAN_PRIORITY_Present) {
				}
				if (sequence->data[i].E_UTRAN_QRXLEVMIN_Present) {
				}
				for (i0=0; i0<sequence->data[i].Repeated_EARFCN.items; i0++) {
					if (sequence->data[i].Repeated_EARFCN.data[i0].Measurement_Bandwidth_Present) {
					}
				}
				if (sequence->data[i].THRESH_E_UTRAN_low_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_Repeated_EARFCN'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_Repeated_EARFCN (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_Repeated_EARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].EARFCN) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Measurement_Bandwidth_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_Pattern.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_Pattern_length.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_pattern_sense.items = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Not_Allowed_Cells.PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].Not_Allowed_Cells.PCID_Pattern.items; i0++) {
					sequence->data[i].Not_Allowed_Cells.PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
			sequence->data[i].PCID_to_TA_mapping.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i].PCID_to_TA_mapping.items; i0++) {
					if (sequence->data[i].PCID_to_TA_mapping.data[i0].PCID_BITMAP_GROUP_Present) {
					}
					for (i0=0; i0<sequence->data[i].PCID_to_TA_mapping.data[i0].PCID_Pattern.items; i0++) {
						sequence->data[i].PCID_to_TA_mapping.data[i0].PCID_Pattern.data[i0].usedBits = 0;
					}
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_E_UTRAN_FREQUENCY_INDEX (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].PCID.items = 0;
			sequence->data[i].PCID_Pattern.items = 0;
			sequence->data[i].PCID_Pattern_length.items = 0;
			sequence->data[i].PCID_pattern_sense.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].PCID_Pattern.items; i0++) {
					sequence->data[i].PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern_length (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_pattern_sense (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_PCID_to_TA_mapping_data_PCID_to_TA_mapping_data_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].THRESH_UTRAN_high) = 0;
			sequence->data[i].UTRAN_FREQUENCY_INDEX.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].THRESH_UTRAN_low_Present) {
				}
				if (sequence->data[i].UTRAN_PRIORITY_Present) {
				}
				if (sequence->data[i].UTRAN_QRXLEVMIN_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters_data_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters_data_UTRAN_FREQUENCY_INDEX (c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description__3G_Priority_Parameters_Description_Repeated_UTRAN_Priority_Parameters_data_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_CSG_FDD_UARFCN'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_CSG_FDD_UARFCN (c_SI2quaterRestOctets__3G_CSG_Description_CSG_FDD_UARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT (c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].PSC.items = 0;
			sequence->data[i].PSC_Pattern.items = 0;
			sequence->data[i].PSC_Pattern_length.items = 0;
			sequence->data[i].PSC_pattern_sense.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i].PSC_Pattern.items; i0++) {
					sequence->data[i].PSC_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC (c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern (c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern_length (c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_pattern_sense (c_SI2quaterRestOctets__3G_CSG_Description_CSG_PSC_SPLIT_data_PSC_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_CSG_TDD_UARFCN'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_CSG_TDD_UARFCN (c_SI2quaterRestOctets__3G_CSG_Description_CSG_TDD_UARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets__3G_CSG_Description_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets__3G_CSG_Description_UTRAN_FREQUENCY_INDEX (c_SI2quaterRestOctets__3G_CSG_Description_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells (c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].FDD_ARFCN) = 0;
			sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].FDD_Indic0) = 0;
			(sequence->data[i].NR_OF_FDD_CELLS) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells (c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].NR_OF_TDD_CELLS) = 0;
			(sequence->data[i].TDD_ARFCN) = 0;
			sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].TDD_Indic0) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_BSIC'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_BSIC (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_BSIC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CBQ'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CBQ (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CBQ* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CELL_BAR_ACCESS'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CELL_BAR_ACCESS (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CELL_BAR_ACCESS* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CELL_RESELECT_OFFSET'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CELL_RESELECT_OFFSET (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_CELL_RESELECT_OFFSET* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_GPRS_Support_Indicator'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_GPRS_Support_Indicator (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_GPRS_Support_Indicator* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].SAME_RA_AS_SERVING_CELL_Present) {
				}
				if (sequence->data[i].SI13_POSITION_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_MS_TXPWR_MAX_CCH'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_MS_TXPWR_MAX_CCH (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_MS_TXPWR_MAX_CCH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_NCELL_LIST_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_NCELL_LIST_INDEX (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_NCELL_LIST_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_PENALTY_TIME'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_PENALTY_TIME (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_PENALTY_TIME* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_POWER_OFFSET'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_POWER_OFFSET (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_POWER_OFFSET* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_RXLEV_ACCESS_MIN'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_RXLEV_ACCESS_MIN (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_RXLEV_ACCESS_MIN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_SAME_LA_AS_SERVING_CELL'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_SAME_LA_AS_SERVING_CELL (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_SAME_LA_AS_SERVING_CELL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_TEMPORARY_OFFSET'. Existing items are not changed. */
void SETITEMS_c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_TEMPORARY_OFFSET (c_SI2nRestOctets_GSM_Neighbour_Cell_Selection_parameters_TEMPORARY_OFFSET* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI4RestOctet_LSA_ID'. Existing items are not changed. */
void SETITEMS_c_SI4RestOctet_LSA_ID (c_SI4RestOctet_LSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI4RestOctet_ShortLSA_ID'. Existing items are not changed. */
void SETITEMS_c_SI4RestOctet_ShortLSA_ID (c_SI4RestOctet_ShortLSA_ID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI9RestOctet_Scheduling_info_Info_type'. Existing items are not changed. */
void SETITEMS_c_SI9RestOctet_Scheduling_info_Info_type (c_SI9RestOctet_Scheduling_info_Info_type* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Info_type_4_Present) {
				}
				if (sequence->data[i].Info_type_5_Present) {
				}
				if (sequence->data[i].Info_type_6_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI9RestOctet_Scheduling_info_Positions'. Existing items are not changed. */
void SETITEMS_c_SI9RestOctet_Scheduling_info_Positions (c_SI9RestOctet_Scheduling_info_Positions* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Position.bcch_type) = 0;
			(sequence->data[i].Position.modulus) = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Position.relative_position_Present) {
					sequence->data[i].Position.relative_position.usedBits = 0;
				}
				if (sequence->data[i].bcch_type_Present) {
				}
				if (sequence->data[i].modulus_Present) {
				}
				if (sequence->data[i].relative_position_Present) {
					sequence->data[i].relative_position.usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI13RestOctets_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX'. Existing items are not changed. */
void SETITEMS_c_SI13RestOctets_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX (c_SI13RestOctets_GPRS_Mobile_Allocation_ARFCN_index_list_ARFCN_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_SI13RestOctets_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER'. Existing items are not changed. */
void SETITEMS_c_SI13RestOctets_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER (c_SI13RestOctets_GPRS_Mobile_Allocation_RFL_number_list_RFL_NUMBER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Individualpriorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_Individualpriorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters (c_Individualpriorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].EARFCN.items = 0;
			(sequence->data[i].E_UTRAN_PRIORITY) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Individualpriorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN'. Existing items are not changed. */
void SETITEMS_c_Individualpriorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN (c_Individualpriorities_E_UTRAN_Individual_Priority_Parameters_Description_Repeated_Individual_E_UTRAN_Priority_Parameters_data_EARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters'. Existing items are not changed. */
void SETITEMS_c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters (c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].FDD_ARFCN.items = 0;
			sequence->data[i].TDD_ARFCN.items = 0;
			(sequence->data[i].UTRAN_PRIORITY) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN (c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_FDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN'. Existing items are not changed. */
void SETITEMS_c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN (c_Individualpriorities__3G_Individual_Priority_Parameters_Description_Repeated_Individual_UTRAN_Priority_Parameters_data_TDD_ARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_MobileId_IdentityDigit'. Existing items are not changed. */
void SETITEMS_c_MobileId_IdentityDigit (c_MobileId_IdentityDigit* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellChannel_BitMap0'. Existing items are not changed. */
void SETITEMS_c_CellChannel_BitMap0 (c_CellChannel_BitMap0* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellChannel_Range1024_W'. Existing items are not changed. */
void SETITEMS_c_CellChannel_Range1024_W (c_CellChannel_Range1024_W* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellChannel_Range512_W'. Existing items are not changed. */
void SETITEMS_c_CellChannel_Range512_W (c_CellChannel_Range512_W* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellChannel_Range256_W'. Existing items are not changed. */
void SETITEMS_c_CellChannel_Range256_W (c_CellChannel_Range256_W* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellChannel_Range128_W'. Existing items are not changed. */
void SETITEMS_c_CellChannel_Range128_W (c_CellChannel_Range128_W* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_CellChannel_Variable_RRFCN'. Existing items are not changed. */
void SETITEMS_c_CellChannel_Variable_RRFCN (c_CellChannel_Variable_RRFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI6_message_content_NonGSM_Message'. Existing items are not changed. */
void SETITEMS_c_PSI6_message_content_NonGSM_Message (c_PSI6_message_content_NonGSM_Message* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].CONTAINER.items = 0;
			(sequence->data[i].NR_OF_CONTAINER_OCTETS) = 0;
			(sequence->data[i].NonGSM_Protocol_Discriminator) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_PSI6_message_content_NonGSM_Message_data_CONTAINER'. Existing items are not changed. */
void SETITEMS_c_PSI6_message_content_NonGSM_Message_data_CONTAINER (c_PSI6_message_content_NonGSM_Message_data_CONTAINER* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type'. Existing items are not changed. */
void SETITEMS_c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type (c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Access_Technology_Type* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities'. Existing items are not changed. */
void SETITEMS_c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities (c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Access_capabilities* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Access_capabilities.CDMA_2000_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.COMPACT_Interference_Measurement_Capability) = 0;
			(sequence->data[i].Access_capabilities.ES_IND) = 0;
			(sequence->data[i].Access_capabilities.PS) = 0;
			(sequence->data[i].Access_capabilities.RF_Power_Capability) = 0;
			(sequence->data[i].Access_capabilities.Revision_Level_Indicator) = 0;
			(sequence->data[i].Access_capabilities.UMTS_3_84_Mcps_TDD_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.UMTS_FDD_Radio_Access_Technology_Capability) = 0;
			(sequence->data[i].Access_capabilities.VBS) = 0;
			(sequence->data[i].Access_capabilities.VGCS) = 0;
			
			(sequence->data[i].Length) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Access_capabilities.A5_bits_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_EGPRS_High_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_Enhancements_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_GPRS_High_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.DTM_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_Advanced_Receiver_Performance_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_Dual_Carrier_for_DTM_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Downlink_EGPRS2_Present) {
				}
				if (sequence->data[i].Access_capabilities.E_UTRA_FDD_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.E_UTRA_TDD_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_DTM_EGPRS_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_DTM_GPRS_Multi_Slot_Class_Present) {
				}
				if (sequence->data[i].Access_capabilities.Extended_RLC_MAC_Control_Message_Segmentation_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.FLO_Iu_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Flexible_Timeslot_Assignment_Present) {
				}
				if (sequence->data[i].Access_capabilities.GAN_PS_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.GERAN_Feature_Package_1_Present) {
				}
				if (sequence->data[i].Access_capabilities.GERAN_to_E_UTRA_support_in_GERAN_packet_transfer_mode_Present) {
				}
				if (sequence->data[i].Access_capabilities.GMSK_Multislot_Power_Profile_Present) {
				}
				if (sequence->data[i].Access_capabilities.High_Multislot_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Length_Present) {
				}
				if (sequence->data[i].Access_capabilities.Modulation_based_multislot_class_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multiple_TBF_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multislot_Capability_Reduction_for_Downlink_Dual_Carrier_Present) {
				}
				if (sequence->data[i].Access_capabilities.Multislot_capability_Present) {
					if (sequence->data[i].Access_capabilities.Multislot_capability.DTM_EGPRS_Multi_Slot_Sub_Class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.DTM_GPRS_Multi_Slot_Sub_Class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.ECSD_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.EGPRS_Extended_Dynamic_Allocation_Capability_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.EGPRS_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.GPRS_Extended_Dynamic_Allocation_Capability_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.GPRS_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.HSCSD_multislot_class_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.SMS_VALUE_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.SM_VALUE_Present) {
					}
					if (sequence->data[i].Access_capabilities.Multislot_capability.Single_Slot_DTM_Present) {
					}
				}
				if (sequence->data[i].Access_capabilities.PS_Handover_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Priority_based_reselection_support_Present) {
				}
				if (sequence->data[i].Access_capabilities.RLC_Non_persistent_Mode_Present) {
				}
				if (sequence->data[i].Access_capabilities.Reduced_Latency_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.UMTS_1_28_Mcps_TDD_Radio_Access_Technology_Capability_Present) {
				}
				if (sequence->data[i].Access_capabilities.Uplink_EGPRS2_Present) {
				}
				if (sequence->data[i].Access_capabilities._8_PSK_Multislot_Power_Profile_Present) {
				}
				if (sequence->data[i].Access_capabilities.m8PSK_Power_Capability_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access'. Existing items are not changed. */
void SETITEMS_c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access (c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].Additional_access_technologies.items = 0;
			(sequence->data[i].Length) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies'. Existing items are not changed. */
void SETITEMS_c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies (c_MS_Radio_Access_capability_IE_MS_Radio_Access_Capability_2_MS_RA_capability_Additional_access_data_Additional_access_technologies* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Access_Technology_Type) = 0;
			(sequence->data[i].GMSK_Power_Class) = 0;
			(sequence->data[i]._8PSK_Power_Class) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_BSIC_Description_BSIC'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_BSIC_Description_BSIC (c_Measurement_information_BSIC_Description_BSIC* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_BSIC_Description_Frequency_Scrolling'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_BSIC_Description_Frequency_Scrolling (c_Measurement_information_BSIC_Description_Frequency_Scrolling* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT (c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].PCID.items = 0;
			sequence->data[i].PCID_Pattern.items = 0;
			sequence->data[i].PCID_Pattern_length.items = 0;
			sequence->data[i].PCID_pattern_sense.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].PCID_Pattern.items; i0++) {
					sequence->data[i].PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID (c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern (c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length (c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense (c_Measurement_information_E_UTRAN_CSG_Description_CSG_PCI_SPLIT_data_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX (c_Measurement_information_E_UTRAN_CSG_Description_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_E_UTRAN_Measurement_Control_Parameters_Description_Repeated_E_UTRAN_Measurement_Control_Parameters'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_E_UTRAN_Measurement_Control_Parameters_Description_Repeated_E_UTRAN_Measurement_Control_Parameters (c_Measurement_information_E_UTRAN_Parameters_Description_E_UTRAN_Measurement_Control_Parameters_Description_Repeated_E_UTRAN_Measurement_Control_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
			(sequence->data[i].Measurement_Control_E_UTRAN) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_E_UTRAN_Measurement_Control_Parameters_Description_Repeated_E_UTRAN_Measurement_Control_Parameters_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_E_UTRAN_Measurement_Control_Parameters_Description_Repeated_E_UTRAN_Measurement_Control_Parameters_data_E_UTRAN_FREQUENCY_INDEX (c_Measurement_information_E_UTRAN_Parameters_Description_E_UTRAN_Measurement_Control_Parameters_Description_Repeated_E_UTRAN_Measurement_Control_Parameters_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].EARFCN.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Measurement_Bandwidth_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_EARFCN'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_EARFCN (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Neighbour_Cells_data_EARFCN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells* sequence, int desiredItems)
{
	int i, i0;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].E_UTRAN_FREQUENCY_INDEX.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_Pattern.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_Pattern_length.items = 0;
			sequence->data[i].Not_Allowed_Cells.PCID_pattern_sense.items = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].Not_Allowed_Cells.PCID_BITMAP_GROUP_Present) {
				}
				for (i0=0; i0<sequence->data[i].Not_Allowed_Cells.PCID_Pattern.items; i0++) {
					sequence->data[i].Not_Allowed_Cells.PCID_Pattern.data[i0].usedBits = 0;
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_Pattern_length* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense (c_Measurement_information_E_UTRAN_Parameters_Description_Repeated_E_UTRAN_Not_Allowed_Cells_data_Not_Allowed_Cells_PCID_pattern_sense* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_REPORT_PRIORITY_Description_REP_PRIORITY'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_REPORT_PRIORITY_Description_REP_PRIORITY (c_Measurement_information_REPORT_PRIORITY_Description_REP_PRIORITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_Real_Time_Difference_Description_Cell_Index_Start_RTD'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_Real_Time_Difference_Description_Cell_Index_Start_RTD (c_Measurement_information_Real_Time_Difference_Description_Cell_Index_Start_RTD* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_Real_Time_Difference_Description_RTD_Struct'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_Real_Time_Difference_Description_RTD_Struct (c_Measurement_information_Real_Time_Difference_Description_RTD_Struct* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].RTD.items = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information_Real_Time_Difference_Description_RTD_Struct_data_RTD'. Existing items are not changed. */
void SETITEMS_c_Measurement_information_Real_Time_Difference_Description_RTD_Struct_data_RTD (c_Measurement_information_Real_Time_Difference_Description_RTD_Struct_data_RTD* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH1'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH1 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH2'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH2 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_PILOT_WALSH2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_POWER_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_POWER_LEVEL (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_POWER_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_WALSH'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_WALSH (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_TD_WALSH* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_WALSH_LEN'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_WALSH_LEN (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_AUX_WALSH_LEN* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i].usedBits = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_Pilot_PN_offset'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_Pilot_PN_offset (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_Pilot_PN_offset* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF1'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF1 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF2'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF2 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_QOF2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER1'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER1 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER2'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER2 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PILOT_POWER2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PRIM_PILOT'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PRIM_PILOT (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_SR3_PRIM_PILOT* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_MODE'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_MODE (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_MODE* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_POWER_LEVEL'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_POWER_LEVEL (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_TD_POWER_LEVEL* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH1'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH1 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH1* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH2'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH2 (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LENGTH2* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_A'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_A (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_A* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_B'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_B (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_B* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_C'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_C (c_Measurement_information__3G_Neighbour_Cell_Description_CDMA2000_Description_WALSH_LEN_C* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells (c_Measurement_information__3G_Neighbour_Cell_Description_UTRAN_FDD_Description_Repeated_UTRAN_FDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].FDD_ARFCN) = 0;
			sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].FDD_Indic0) = 0;
			(sequence->data[i].NR_OF_FDD_CELLS) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].FDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells (c_Measurement_information__3G_Neighbour_Cell_Description_UTRAN_TDD_Description_Repeated_UTRAN_TDD_Neighbour_Cells* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].NR_OF_TDD_CELLS) = 0;
			(sequence->data[i].TDD_ARFCN) = 0;
			sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			
			(sequence->data[i].TDD_Indic0) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				sequence->data[i].TDD_CELL_INFORMATION_Field.usedBits = 0;
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Supplementary_Parameters_Description__3G_Measurement_Control_Parameters_Description_Repeated_UTRAN_Measurement_Control_Parameters'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Supplementary_Parameters_Description__3G_Measurement_Control_Parameters_Description_Repeated_UTRAN_Measurement_Control_Parameters (c_Measurement_information__3G_Supplementary_Parameters_Description__3G_Measurement_Control_Parameters_Description_Repeated_UTRAN_Measurement_Control_Parameters* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].Measurement_Control_UTRAN) = 0;
			sequence->data[i].UTRAN_FREQUENCY_INDEX.items = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Measurement_information__3G_Supplementary_Parameters_Description__3G_Measurement_Control_Parameters_Description_Repeated_UTRAN_Measurement_Control_Parameters_data_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Measurement_information__3G_Supplementary_Parameters_Description__3G_Measurement_Control_Parameters_Description_Repeated_UTRAN_Measurement_Control_Parameters_data_UTRAN_FREQUENCY_INDEX (c_Measurement_information__3G_Supplementary_Parameters_Description__3G_Measurement_Control_Parameters_Description_Repeated_UTRAN_Measurement_Control_Parameters_data_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_CELL_IDENTITY'. Existing items are not changed. */
void SETITEMS_c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_CELL_IDENTITY (c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_CELL_IDENTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX'. Existing items are not changed. */
void SETITEMS_c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX (c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_E_UTRAN_FREQUENCY_INDEX* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_REPORTING_QUANTITY'. Existing items are not changed. */
void SETITEMS_c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_REPORTING_QUANTITY (c_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_REPORTING_QUANTITY* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Enhanced_Measurement_report_REPORTING_QUANTITY_R8'. Existing items are not changed. */
void SETITEMS_c_Enhanced_Measurement_report_REPORTING_QUANTITY_R8 (c_Enhanced_Measurement_report_REPORTING_QUANTITY_R8* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].REPORTING_QUANTITY_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Enhanced_Measurement_report_Repeated_Invalid_BSIC_Information'. Existing items are not changed. */
void SETITEMS_c_Enhanced_Measurement_report_Repeated_Invalid_BSIC_Information (c_Enhanced_Measurement_report_Repeated_Invalid_BSIC_Information* sequence, int desiredItems)
{
	int i;
	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i].BCCH_FREQ_NCELL) = 0;
			(sequence->data[i].BSIC) = 0;
			(sequence->data[i].RXLEV_NCELL) = 0;
		}
	}

	sequence->items = desiredItems;
}

/* SETITEMS commands for type 'c_Enhanced_Measurement_report_Reporting_Quantity_Info_Reporting_Quantity'. Existing items are not changed. */
void SETITEMS_c_Enhanced_Measurement_report_Reporting_Quantity_Info_Reporting_Quantity (c_Enhanced_Measurement_report_Reporting_Quantity_Info_Reporting_Quantity* sequence, int desiredItems)
{
	int i;
	if (desiredItems < sequence->items) {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i].REPORTING_QUANTITY_Present) {
				}
			}
	}

	sequence->items = desiredItems;
}

/*lint +e958*/
/*lint +e961*/
/*lint +e830*/
/*lint +e525*/
/*lint +e445*/

