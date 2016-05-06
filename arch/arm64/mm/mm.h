extern void __init bootmem_init(void);
extern void __init arm64_swiotlb_init(void);

void fixup_init(void);

void create_mapping_late(phys_addr_t phys, unsigned long virt,
				  phys_addr_t size, pgprot_t prot);
