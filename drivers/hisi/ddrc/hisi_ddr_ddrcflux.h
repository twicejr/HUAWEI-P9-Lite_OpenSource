#ifndef HISI_DDR_DMCFLUX_H
#define HISI_DDR_DMCFLUX_H

/*usr para*/
enum ddrc_flux_para
{
	sta_id = 0,
	sta_id_mask,
	interval,
	sum_time,
	irq_affinity,
	ddrc_unsec_pass,
	dmss_enable,
	qosbuf_enable,
	dmc_enable,
	dmccmd_enable,
	dmcdata_enable,
	dmclatency_enable,
	ddrc_flux_max,
};

typedef struct
{
	char name[6];
}slice_info;

extern  slice_info  slice;

#endif
