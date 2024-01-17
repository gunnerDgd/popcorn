ifndef KERNELDIR
	KERNELDIR  := /lib/modules/$(shell uname -r)/build
endif

POPCORN_DIR = $(PWD)/../../src
obj-m 	 	 += popcorn.o
obj-m 		 += po_dev.o
popcorn-objs := ../../src/core/linux/obj.o	  		  \
				../../src/core/mem.o		  		  \
			    ../../src/core/box.o		  		  \
			    ../../src/core/list.o	 	 		  \
			    ../../src/core/map.o		  		  \
			    ../../src/core/str.o		  		  \
			   						  				  \
			    ../../src/dev/linux/details/dev.o 	  \
			    ../../src/dev/linux/details/dev_type.o\
			    ../../src/dev/linux/dev.o		 	  \
			    ../../src/dev/linux/dev_type.o	      \
			   						  				  \
			    ../../src/mem/linux/details/buf.o	  \
			    ../../src/mem/linux/buf.o			  \
			    ../../src/po_linux.o				  \

all:
	$(MAKE) KCPPFLAGS="-DPO_PRESET_LINUX -I$(PWD)/../../include" -C $(KERNELDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) 		   clean
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/../../src clean

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install