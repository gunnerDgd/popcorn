ifndef KERNELDIR
	KERNELDIR  := /lib/modules/$(shell uname -r)/build
endif

obj-m   += po.o
po-objs := ../../src/core/linux/obj.o	  	 \
		   ../../src/core/linux/mem.o		 \
		   ../../src/core/box.o		  	     \
		   ../../src/core/list.o	 	 	 \
		   ../../src/core/map.o		  	     \
		   ../../src/core/str.o		  	     \
					   						 \
		   ../../src/dev/details/linux_dev.o \
		   ../../src/dev/details/linux_chr.o \
		   ../../src/dev/details/linux_ns.o  \
				 							 \
           ../../src/dev/chr.o 	  		     \
           ../../src/dev/chr_dev.o  		 \
           ../../src/dev/dev.o 	  		     \
           ../../src/dev/ns.o 	      		 \
		 						  		  	 \
		   ../../src/mem/details/linux_ubuf.o\
		   ../../src/mem/details/linux_heap.o\
		   ../../src/mem/details/linux_page.o\
		   po_dev.o

all:
	$(MAKE) KCPPFLAGS="-DPO_PRESET_LINUX -I$(PWD)/../../include" -C $(KERNELDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) 		   clean
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/../../src clean

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install