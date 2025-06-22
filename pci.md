

# Enable Device
在PCI驱动程序的probe函数中，在驱动程序可以访问PCI设备的任何资源（I/O区域或中断）之前，驱动程序必须调用pci_enable_device函数：

int pci_enable_device(struct pci_dev *dev);
这个函数实际上启用了设备。它唤醒设备，并在某些情况下还分配其中断线和I/O区域。例如，对于CardBus设备（在驱动程序级别上已经完全等同于PCI），就会发生这种情况。调用pci_enable_device函数是为了确保PCI设备在驱动程序中被正确启用，以便后续可以访问设备的资源和功能。



# 读取配置空间
```
int pci_read_config_byte(struct pci_dev *dev, int where, u8 *val);
int pci_read_config_word(struct pci_dev *dev, int where, u16 *val);
int pci_read_config_dword(struct pci_dev *dev, int where, u32 *val);
```


# 注册驱动
```
int pci_register_driver(struct pci_driver *drv);
```

# 注销驱动
```
void pci_unregister_driver(struct pci_driver *drv);
```


# MODULE_DEVICE_TABLE

```
static struct pci_device_id echo_ids[] = {
	{PCI_DEVICE(VID, DID)},
	{},
};
MODULE_DEVICE_TABLE(pci, echo_ids);
```
pci_device_id 需要被导出到用户空间，使热插拔和模块装载系统知道什么模块针对什么硬件
设备，

```
cat /proc/kallsyms  |grep device_table
ffffffffc06cf180 d __mod_pci__echo_ids_device_table     [echodev]
```

该语句会创建一个 局部变量，指向 pci_device_id 数组。在稍后的内核构建过程中，depmod
程序在所有的模块中搜索符号__mod_pci__echo_ids_device_table.如果找到符号，把数据
从该模块抽出，添加到文件中 /lib/modules/<kernel version>/modules.pcimap 文件中。





# pci_resource 相关函数


include/linux/pci.h



pci_resource_start: 获取 dev 中第 bar 个基址寄存器中记录的资源起始地址.

pci_resource_end:获取 dev 中第 bar 个基址寄存器中记录的资源结束地址。
pci_resource_flags :取 dev 中第 bar 个基址寄存器中记录的资源标志，是内存资源还是 IO 资源。
pci_resource_len:获取 dev 中第 bar 个基址寄存器中记录的资源大小。
pci_request_regions: 申请 PCI 设备 pdev 内的内存资源和I/0 资源，取名为res_name.

pci_dev 结构体中的 resource 记录



# 驱动probe 的堆栈，记录下
```
[  304.029386] Call Trace:
[  304.029401]  dump_stack+0x41/0x60
[  304.029406]  echo_probe+0x38/0x338 [echodev]
[  304.029409]  local_pci_probe+0x4e/0x90
[  304.029414]  pci_device_probe+0x109/0x1c0
[  304.029416]  __driver_probe_device+0x141/0x450
[  304.029420]  driver_probe_device+0x1f/0x90
[  304.029421]  ? __device_attach_driver+0x110/0x110
[  304.029423]  __driver_attach+0x7f/0x170
[  304.029425]  ? __device_attach_driver+0x110/0x110
[  304.029426]  bus_for_each_dev+0x7b/0xd0
[  304.029428]  bus_add_driver+0x148/0x200
[  304.029429]  ? 0xffffffffc0614000
[  304.029430]  driver_register+0x6e/0xc0
[  304.029433]  ? 0xffffffffc0614000
[  304.029433]  echo_init+0x64/0x1000 [echodev]
[  304.029435]  do_one_initcall+0x46/0x1d0
[  304.029439]  ? do_init_module+0x22/0x230
[  304.029441]  ? kmem_cache_alloc_trace+0x142/0x280
[  304.029445]  do_init_module+0x5a/0x230
[  304.029446]  load_module+0x1582/0x18c0
[  304.029448]  ? __do_sys_finit_module+0xb1/0x110
[  304.029449]  __do_sys_finit_module+0xb1/0x110
[  304.029451]  do_syscall_64+0x5b/0x1b0
[  304.029453]  entry_SYSCALL_64_after_hwframe+0x61/0xc6
[  304.029457] RIP: 0033:0x7fc27200e41d

```

# map

pcim_iomap
pci_iomap
ioremap
