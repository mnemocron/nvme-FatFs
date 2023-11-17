# FatFs driver for NVME SSD on MicroBlaze

---

https://scolton.blogspot.com/2019/11/zynq-ultrascale-fatfs-with-bare-metal.html


### AXI to PCIE Bridge

The bridge has three AXI interfaces:
- AXI-Lite Slave for configuration of the PCIe
- AXI4 Slave for writing data to PCIe via BAR0
- AXI4 Master to act as a R/W DMA Master to transfer from/to the SSD

#### AXI-Lite Slave 
> If the NVMe drive has successfully enumerated, its Endpoint PCIe Configuration Space will be mapped to some offset in the AXI-Lite Slave register space. In my case, with no switch involved, it shows up as Bus 1, Device 0, Function 0 at offset 0x1000. Here, it's possible to check the Device ID, Vendor ID, and Class Codes. *Most importantly, the BAR0 register holds the PCIe memory address assigned to the device. The AXI address assigned to BAR0 in the Address Editor in Vivado is mapped to this PCIe address by the bridge.*

#### AXI Slave
> Reads from and writes to the AXI BAR0 address are done through the AXI Slave Interface. This is a full AXI interface supporting burst transactions and a wide data bus. In another class of PCIe device, it might be responsible for transferring large amounts of data to the device through the BAR0 address range. *But for an NVMe drive, BAR0 just provides access to the NVMe Controller Registers*, which are used to set up the drive *and inform it of pending data transfers*.

#### AXI Master
> *The AXI Master Interface is where all NVMe data transfer occurs, for both reads and writes*. One way to look at it is that the drive itself contains the DMA engine, which issues memory reads and writes to the system (AXI) memory space through the bridge. *The host requests that the drive perform these data transfers by submitting them to a queue*, which is also contained in system memory and accessed through this interface.

---

Therefore:
The AXI PCIE bridge IP needs to be connected to DDR4 memory to access the submission (SQ) and completion queues (CQ)
(similar to how ERNIC works).


---


## Bring up sequence (sort of)

1. Init PCIe root complex
2. Enumerate PCIe devices
3. Allocate memory for Admin SQ/CQ, SQ/CQ and IO SQ/CQ in DDR4 memory
4. Request capabilities from drive and configure LB sizes and page sizes??
5. initialize IO SQ/CQ












