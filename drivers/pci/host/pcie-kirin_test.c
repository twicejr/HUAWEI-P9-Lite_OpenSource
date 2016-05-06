


#define WIFI_POWER_GPIO 31

void test_access_phy(void)
{
	unsigned int index = 0;
	unsigned int pos = 0;
	PCIE_PR_INFO("List PCIePHY Register: \n");
	writel((0x1<<21), my_test_pcie->apb_base+0x0);
	writel((0x1<<21), my_test_pcie->apb_base+0x4);
	for(index = 0; index++; index <10) {
		PCIE_PR_INFO("Register[0x%x]----Value[0x%x] \n", pos, readl(my_test_pcie->phy_base+pos));
		pos += 4;
	}
}

void test_access_core(void)
{
	unsigned int index = 0;
	unsigned int pos = 0;
	PCIE_PR_INFO("List PCIePHY Register: \n");
	writel((0x1<<21), my_test_pcie->apb_base+0x0);
	writel((0x1<<21), my_test_pcie->apb_base+0x4);
	for(index = 0; index++; index <10) {
		PCIE_PR_INFO("Register[0x%x]----Value[0x%x] \n", pos, readl(my_test_pcie->apb_base+pos));
		pos += 4;
	}
}

void test_set_ep_aspm(void)
{
	unsigned int val = 0;
	val = readl(my_test_pcie->pp->dbi_base + 0x1000000 + 0x710);
	val |= 0x3;
	writel(val, my_test_pcie->pp->dbi_base + 0x1000000 + 0x710);
	udelay(5);
	val = readl(my_test_pcie->pp->dbi_base + 0x1000000 + 0x710);
	PCIE_PR_ERR("EP ASPM status [0x%x]", val);
}
void test_link_emumerate()
{
	int ret = 0;
	int index = 0;
	struct pcie_port *pp = &my_test_pcie->pp;
	
	ret = gpio_request(31, "BCM WL");
	if(ret != 0) {
		PCIE_PR_ERR("Failed to request BCM WL GPIO");
		return;
	}

	gpio_direction_output(31, 0);
	mdelay(20);
	if(kirin_pcie_link_up(pp)==0) {
		PCIE_PR_INFO("Link break Successed");
	}
	else {
		PCIE_PR_ERR("[deliwa]: Failed to break link");
	}

	gpio_direction_output(31, 1);
	mdelay(200);
	if(kirin_pcie_link_up(pp)==1) {
		PCIE_PR_INFO("Linkup Successed");
		power_on_pcie();
	}
	else {
		PCIE_PR_ERR("[deliwa]: Failed to establish link");
	}

	
	gpio_free(31);
	return 0;
}

void test_access_apb_register(void)
{
	int ret = 0;
	unsigned int bak_val = 0;
	/*PCIePHY apb*/
	PCIE_PR_INFO("PCIePHY apb Read and Write testcase\n");
	bak_val = readl(my_test_pcie->phy_base + 0x0);
	ret = bak_val | (0x1 < 21);
	writel(ret, my_test_pcie->phy_base + 0x0);
	PCIE_PR_ERR("Success");
	
	writel(bak_val, my_test_pcie->phy_base + 0x0);
	
	/*PCIeCORE apb*/
	PCIE_PR_INFO("PCIeCORE apb Read and Write testcase\n");
	bak_val = kirin_elb_readl(my_test_pcie, SOC_PCIECTRL_CTRL12_ADDR);
	ret = bak_val | 0x3;
	kirin_elb_writel(my_test_pcie, ret, SOC_PCIECTRL_CTRL12_ADDR);
	ret = kirin_elb_readl(my_test_pcie, SOC_PCIECTRL_CTRL12_ADDR);
	if( (ret & 0x3) != 0x3){
		PCIE_PR_ERR("Failed to read and write CORE register");
	}
	else {
		PCIE_PR_ERR("Success");
	}
}


