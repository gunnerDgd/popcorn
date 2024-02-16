popcorn-objs :=\
	/src/core/linux/atom.o\
	/src/core/linux/bit.o\
	/src/core/linux/mem.o\
	/src/core/linux/sched.o\
	/src/core/linux/task.o\
	/src/core/linux/thd.o\
	/src/core/linux/mod.o\
	/src/core/fut.o\
	/src/core/mem.o\
	/src/core/node.o\
	/src/core/str.o\
	/src/core/list.o\
	/src/core/obj.o\
	/src/core/box.o\
	/src/core/map.o\
	/src/core/set.o\
	/src/core/endian.o\
	/src/core/ops/arith.o\
	/src/core/ops/cast.o\
	/src/core/ops/bit.o\
	/src/core/ops/cmp.o\
	/src/core/ops/logical.o\
	/src/core/sync/spsc.o\
	/src/core/sync/spmc.o\
	/src/core/sync/mpsc.o\
	/src/core/sync/mpmc.o\

popcorn-dev-objs :=\
	/linux/src/dev/dev.o\
	/linux/src/dev/class.o\
	/linux/src/dev/chr/chr.o\
	/linux/src/dev/chr/dev.o\
	/linux/src/dev/chr/type.o\
-objs :=\

all:
	$(MAKE) KCPPFLAGS="-DPRESET_LINUX -DPRESET_ARCH_X86_64 -DPRESET_ARCH_BIT=64 -DPRESET_ARCH_ENDIAN_LITTLE" -C /lib/modules/6.6.11-200.fc39.x86_64/build M=/mnt/sdd2/code/popcorn modules

clean:
	$(MAKE) -C /lib/modules/6.6.11-200.fc39.x86_64/build M=/mnt/sdd2/code/popcorn clean
