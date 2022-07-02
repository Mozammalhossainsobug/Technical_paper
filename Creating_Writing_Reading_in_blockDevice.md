### first get into super user
```
sudo su
```
### Creating block_devices
```
dd if=/dev/zero of=myfile bs=1M count=32
```
> dd = copy , if =source , of=destination, bs=block_size(unit), count=ammount
### finding out the address of created block device
```
losetup --show -f myfile
```
> location for my pc
> 
> ![location for my_pc](https://github.com/Mozammalhossainsobug/Technical_paper/blob/main/Screenshot%20from%202022-07-02%2022-57-21.png)
### geting details about block device
```
ls -al /dev/loop29
```
> Details will look like
> 
> ![Details](https://github.com/Mozammalhossainsobug/Technical_paper/blob/main/Screenshot%20from%202022-07-02%2023-02-57.png)

### Writing in a block device
```
echo Welcome_to_virtual_block_device >/dev/loop0
```
>![message writing](https://github.com/Mozammalhossainsobug/Technical_paper/blob/main/Screenshot%20from%202022-07-02%2023-00-27.png)
### Reading from a block device
```
dd if=/dev/loop29
```
>![Reading](https://github.com/Mozammalhossainsobug/Technical_paper/blob/main/Screenshot%20from%202022-07-02%2023-05-43.png)
### Deleting block device
```
losetup -d /dev/loop29
```


