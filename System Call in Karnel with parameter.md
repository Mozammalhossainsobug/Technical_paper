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

Create system call's source code:
````
vim kernel/my_syscall.c
````
Source Code:
````
#include <linux/syscalls.h>
#include <linux/kernel.h>

SYSCALL_DEFINE0(my_syscall_0)
{
    printk("my_syscall_0\n");
    return 0;
}

SYSCALL_DEFINE1(my_syscall_1, int, a)
{
    printk("my_syscall_1 : %d\n", a);
    return 0;
}

SYSCALL_DEFINE2(my_syscall_2, int, a, int, b)
{
    printk("my_syscall_2 : %d, %d\n", a, b);
    return b;
}
````
## Connect our System Call to the Kernel: 
Open Makefile of Kernel:
````
vim kernel/Makefile
````
Code in Makefile search for "obj-y = " 
Add like :
````
obj-y = fork.o exec_domain.o panic.o \
        cpu.o exit.o softirq.o resource.o \
        sysctl.o sysctl_binary.o capability.o ptrace.o user.o \
        signal.o sys.o umh.o workqueue.o pid.o task_work.o \
        extable.o params.o \
        kthread.o sys_ni.o nsproxy.o \
        notifier.o ksysfs.o cred.o reboot.o \
        async.o range.o smpboot.o ucount.o \
       my_syscall.o
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
335     common     my_syscall_0     __x64_sys_my_syscall_0
336     common     my_syscall_1     __x64_sys_my_syscall_1
337     common     my_syscall_2     __x64_sys_my_syscall_2
````
modify include/linux/syscalls.h : add those lines below:
```
asmlinkage long sys_my_syscall_0(void);
asmlinkage long sys_my_syscall_1(int);
asmlinkage long sys_my_syscall_2(int, int);
```
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
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{
    printf("1 : %d\n", syscall(335));
    printf("2 : %d\n", syscall(336, 1));
    printf("3 : %d\n", syscall(337, 2, 3));
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
