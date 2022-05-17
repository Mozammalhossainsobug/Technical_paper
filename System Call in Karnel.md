## Prerequisites:
```
sudo apt-get install gcc
sudo apt-get install libncurses5-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt install make
sudo apt-get install libssl-dev
sudo apt-get install libelf-dev
sudo apt-get update
sudo apt-get upgrade
sudo apt install fakeroot
sudo apt install build-essential
sudo apt install ncurses-dev
sudo apt install xz-utils
sudo apt install libssl-dev
sudo apt install flex
```
## Download Kernel Source:
````
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.17.7.tar.xz
````
## Extract Kernel Source:
````
tar xvf linux-5.17.7.tar.xz
````
## Get into Kernel Source Directory:
````
cd linux-5.17.7
````
## Write System Call Source Code:

Create a directory:
````
mkdir helloworld
````
Create system call's source code:
````
vim helloworld/helloworld.c
````
Source Code:
````
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(helloworld) {
	printk("Hello World!!\n");
	return 0;
}
````
Create Makefile into helloworld directory:
````
vim helloworld/Makefile
````
Code in Makefile:
````
obj-y:= helloworld.o
````
## Connect our System Call to the Kernel: 
Open Makefile of Kernel:
````
vim Makefile
````
Search for crypto/

Add helloworld/
After making change:
````
core-y			+= kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ helloworld/
````
Open "include/linux/syscalls.h" file:
````
vim include/linux/syscalls.h
````
Goto bottom of the file
Add:
````
asmlinkage long sys_helloworld(void);
````
Open "arch/x86/entry/syscalls/syscall_64.tbl" file:
````
vim arch/x86/entry/syscalls/syscall_64.tbl
````
Add "335 common helloworld sys_helloworld"
After adding it will look like this:
````
334	common	rseq			sys_rseq
335	common	helloworld		sys_helloworld
````
## Compile The Kernel:
Clean Build Directory:
````
make clean
make mrproper
````
Download 
````
wget https://raw.github.com/xanmod/linux/5.17/CONFIGS/xanmod/gcc/config_x86-64
````
Rename .config
````
mv config_x86-64 .config
````
Make ".config" compatible:
````
scripts/config --disable SYSTEM_REVOCATION_KEYS
scripts/config --disable SYSTEM_TRUSTED_KEYS
scripts/config --disable CONFIG_X86_X32
yes "" | make oldconfig
````
Start the build:
````
make -j$(nproc)
````
## Install Modules:
````
sudo make modules_install -j$(nproc)
````
## Install Kernel:
````
sudo make install -j$(nproc)
````
Reboot to the new kernel:
````
reboot
````
## Test Our System Call:
Create a file named "test.c":
````
vim test.c
````
Source Code:
````
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define __NR_helloworld 335

long helloworld_syscall(void)
{
    return syscall(__NR_helloworld);
}

int main(int argc, char *argv[])
{
    long activity;
    activity = helloworld_syscall();

    if(activity < 0)
    {
        perror("Your system call appears to have failed.");
    }

    else
    {
        printf("Congratulations! Your system call is functional. Run the command dmesg in the terminal and find out more!\n");
    }

    return 0;
}
````
Compile "test":
````
gcc test.c -o test
````
Run "test":
````
./test
````
Examine Output & dmesg : :smiling_face_with_three_hearts:
````
sudo dmesg
````
