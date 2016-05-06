#ifndef __OF_PCI_H
#define __OF_PCI_H

#include <linux/pci.h>

struct pci_dev;
struct of_irq;
int of_irq_map_pci(const struct pci_dev *pdev, struct of_irq *out_irq);

struct device_node;
struct device_node *of_pci_find_child_device(struct device_node *parent,
					     unsigned int devfn);

#if defined(CONFIG_OF_ADDRESS)
int of_pci_get_host_bridge_resources(struct device_node *dev,
			unsigned char busno, unsigned char bus_max,
			struct list_head *resources, resource_size_t *io_base);
#endif


#endif

