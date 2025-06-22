#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/dmaengine.h>
#include <linux/list.h>
#include <linux/mutex.h>



#define VENDOR_ID 0x1af4
#define DEVICE_ID 0x1001
static int __init echo_init(void)
{
	struct pci_dev *dev = NULL;
	u8 val;
	while (dev = pci_get_device(VENDOR_ID, DEVICE_ID, dev))
			printk("device class: %d\n", dev->class >> 8);
			/* The PCI standardized 64 bytes of the configuration space */
			unsigned i;
			for (i = 0; i < 64u; ++i) {
				pci_read_config_byte(dev, i, &val);
				pr_info("config %x %x\n", i, val);
			}
	return 0;
}

static void __exit echo_exit(void)
{
	printk(KERN_INFO "Goodbye, cruel world\n");
}

module_init(echo_init);
module_exit(echo_exit);

MODULE_LICENSE("GPL");
