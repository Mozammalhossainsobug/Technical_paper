#### To see PCI devices
```
lspci | cut -d: -f1-2
```
#### To see only hexa_value
```
cat /proc/bus/pci/devices | cut -f1
```
### Directory to find out devices list
```
cd /sys/bus/pci/devices
ls
```
>first_value = domain, second_value = bus, third_value = device, fourth_value = function
####  Device's configuration registers can be found by reading 
> /sys/bus/pci/devices/device_address(founded from previous quiery)
```
cd
cd /sys/bus/pci/devices/0000:00:00.0
ls
```
>meta data

