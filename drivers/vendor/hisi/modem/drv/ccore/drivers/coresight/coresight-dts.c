/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "osl_malloc.h"
#include "of.h"
#include "securec.h"
#include "coresight-platform.h"

/*lint --e{801, 830, 525, 534, 586, 522}*/

struct coresight_platform_data_s *of_get_coresight_platform_cfg(struct device_node *node)
{
	int i, ret = 0;
	int outports_len = 0;
/*
	struct clk *clk;
*/
	struct device_node *child_node, *cpu;
	struct coresight_platform_data_s *pdata;

	pdata = osl_malloc(sizeof(*pdata));
	if (!pdata)
		return NULL;

    memset_s((void *)pdata, sizeof(*pdata), 0, sizeof(*pdata));

	ret = of_property_read_u32(node, "coresight-id", (u32*)&pdata->id);
	if (ret)
		goto err;

	ret = of_property_read_string(node, "coresight-name", &pdata->name);
	if (ret)
		goto err;

	ret = of_property_read_u32(node, "coresight-nr-inports",
				   (u32*)&pdata->nr_inports);
	if (ret)
		goto err;

	pdata->nr_outports = 0;
	if (of_get_property(node, "coresight-outports", &outports_len))
		pdata->nr_outports = (unsigned int)outports_len/sizeof(uint32_t);

	if (pdata->nr_outports)
    {
        pdata->outports = osl_malloc((unsigned int)pdata->nr_outports*sizeof(*pdata->outports));
		if (!pdata->outports)
            goto err;

        memset_s((void *)pdata->outports, (unsigned int)pdata->nr_outports*sizeof(*pdata->outports), 0,
            (unsigned int)pdata->nr_outports*sizeof(*pdata->outports));

		ret = of_property_read_u32_array(node, "coresight-outports",
						 (u32 *)pdata->outports,
						 pdata->nr_outports);
		if (ret)
			goto err;

        pdata->child_ids = osl_malloc(pdata->nr_outports*sizeof(*pdata->child_ids));
		if (!pdata->child_ids)
			goto err;

        memset_s((void *)pdata->child_ids, pdata->nr_outports*sizeof(*pdata->child_ids), 0,
            pdata->nr_outports*sizeof(*pdata->child_ids));

		for (i = 0; i < (int)pdata->nr_outports; i++) {
			child_node = of_parse_phandle(node,
						      "coresight-child-list",
						      i);
			if (!child_node)
                goto err;

			ret = of_property_read_u32(child_node, "coresight-id",
						   (u32 *)&pdata->child_ids[i]);
			of_node_put(child_node);
			if (ret)
				goto err;
		}

        pdata->child_ports = osl_malloc(pdata->nr_outports*sizeof(*pdata->child_ports));
		if (!pdata->child_ports)
			goto err;

        memset_s((void *)pdata->child_ports,pdata->nr_outports*sizeof(*pdata->child_ports),0,
            pdata->nr_outports*sizeof(*pdata->child_ports));

		ret = of_property_read_u32_array(node, "coresight-child-ports",
						 (u32 *)pdata->child_ports,
						 pdata->nr_outports);
		if (ret)
			goto err;
	}

	pdata->default_sink = of_property_read_bool(node,
						    "coresight-default-sink");

	/* affinity defaults to CPU0 */
	pdata->cpu = 0;
	cpu = of_parse_phandle(node, "cpu", 0);
	if (cpu) {
		const u32 *mpidr;
		int len;

		mpidr = of_get_property(cpu, "reg", &len);
		if (mpidr && (unsigned int)len == 4) {
            pdata->cpu = (int)be32_to_cpup(mpidr);
		}
	}

	/* clock specifics */
/*
	pdata->clk = NULL;
	clk = of_clk_get(node, 0);
	if (!IS_ERR(clk))
		pdata->clk = clk;
*/
   	return pdata;

err:
    if(NULL != pdata->child_ports)
        osl_free((void*)pdata->child_ports);
    if(NULL != pdata->child_ids)
        osl_free((void*)pdata->child_ids);
    if(NULL != pdata->outports)
        osl_free((void*)pdata->outports);
    osl_free(pdata);
    return NULL;
}


