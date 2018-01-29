BUILD_DIR  ?= $(CURDIR)/riot

CFLAGS += -Wno-error
all: liblua

liblua:
	# running .lua makefile, copied into library directory
	# mkdir -p $(BUILD_DIR)
	# "$(MAKE)" -C $(BUILD_DIR)
# JERRYHEAP  ?= 16
# 
# EXT_CFLAGS :=-D__TARGET_RIOT
# 
# EXT_CFLAGS += $(CFLAGS)

# .PHONY: libjerry riot-jerry flash clean

# all: libjerry riot-jerry

# libjerry:
# 	mkdir -p $(BUILD_DIR)
# 	cmake -B$(BUILD_DIR) -H./ \
# 	 -DCMAKE_SYSTEM_NAME=RIOT \
# 	 -DCMAKE_SYSTEM_PROCESSOR="$(MCPU)" \
# 	 -DCMAKE_C_COMPILER=$(CC) \
# 	 -DCMAKE_C_COMPILER_WORKS=TRUE \
# 	 -DENABLE_LTO=OFF \
# 	 -DFEATURE_VALGRIND=OFF \
# 	 -DENABLE_ALL_IN_ONE=OFF \
# 	 -DJERRY_LIBC=OFF \
# 	 -DJERRY_LIBM=OFF \
# 	 -DJERRY_CMDLINE=OFF \
# 	 -DEXTERNAL_COMPILE_FLAGS="$(EXT_CFLAGS)" \
# 	 -DMEM_HEAP_SIZE_KB=$(JERRYHEAP)
# 
# 	"$(MAKE)" -C $(BUILD_DIR) jerry-core jerry-ext jerry-port-default-minimal
# 	cp $(BUILD_DIR)/lib/libjerry-core.a $(BINDIR)/jerryscript.a
# 	cp $(BUILD_DIR)/lib/libjerry-ext.a $(BINDIR)/jerryscript-ext.a
# 	cp $(BUILD_DIR)/lib/libjerry-port-default-minimal.a $(BINDIR)/jerryport-minimal.a

include $(RIOTBASE)/Makefile.base
