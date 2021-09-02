# obj-m specifie we're a kernel module.
obj-m += babel.o

# Set the path to the Kernel build utils.
KBUILD=/lib/modules/$(shell uname -r)/build/

default:
	$(MAKE) -C $(KBUILD) M=$(PWD) modules
	cc babel_client.c -o babel_client

clean:
	$(MAKE) -C $(KBUILD) M=$(PWD) clean

menuconfig:
	$(MAKE) -C $(KBUILD) M=$(PWD) menuconfig

test:
	# We put a — in front of the rmmod command to tell make to ignore
	# an error in case the module isn’t loaded.
	-sudo rmmod babel
	# Clear the kernel log without echo
	sudo dmesg -C
	# Insert the module
	sudo insmod babel.ko
	# Display the kernel log
	dmesg