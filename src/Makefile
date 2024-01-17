ifndef KERNELDIR
	KERNELDIR  := /lib/modules/$(shell uname -r)/build
endif

obj-m 	 	 := popcorn.o
popcorn-objs := ./core/linux/obj.o	  		  \
				./core/mem.o		  		  \
			    ./core/box.o		  		  \
			    ./core/list.o	 	 		  \
			    ./core/map.o		  		  \
			    ./core/str.o		  		  \
			   						  		  \
			    ./dev/linux/details/dev.o 	  \
			    ./dev/linux/details/dev_type.o\
			    ./dev/linux/dev.o		 	  \
			    ./dev/linux/dev_type.o	      \
			   						  		  \
			    ./mem/linux/details/buf.o	  \
			    ./mem/linux/buf.o			  \
			    po_linux.o					  \


all:
	$(MAKE) KCPPFLAGS="-DPO_PRESET_LINUX" -C $(KERNELDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install