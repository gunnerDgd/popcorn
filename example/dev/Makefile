ifndef KERNELDIR
	KERNELDIR  := /lib/modules/$(shell uname -r)/build
endif

ccflags-y += -I=$(PWD)/../../include

obj-m := po_dev.o

all:
	$(MAKE) KCPPFLAGS="-DPO_PRESET_LINUX -I$(PWD)/../../include" -C $(KERNELDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install