PKG_NAME=lua
# PKG_URL=https://github.com/jerryscript-project/jerryscript.git
# PKG_VERSION=bd574956e3702bc5b0512ad835b1df896cf00626
# PKG_LICENSE=Apache-2.0

.PHONY: all

# CFLAGS += -Wno-implicit-fallthrough

# disable warnings when compiling with LLVM for board native
# ifeq ($(TOOLCHAIN)_$(BOARD),llvm_native)
# export CFLAGS += -Wno-macro-redefined -Wno-gnu-folding-constant
# endif
all: 
	# @mkdir $(PKG_BUILDDIR)/LuaRTOS
	cp -r /home/danielpetry/Sandbox/lua-5.3.4/src/* $(PKG_BUILDDIR)
	# Our build system - comment out to use their one
	@cp Makefile.lua $(PKG_BUILDDIR)/Makefile
	"$(MAKE)" -C $(PKG_BUILDDIR)
#	ar cr $(PKG_BUILDDIR)/lua.a $(PKG_BUILDDIR)/lua.o $(PKG_BUILDDIR)/liblua.a
#	echo $(PKG_BUILDDIR)
#	echo $(BINDIR)
#	cp $(PKG_BUILDDIR)/lua.a $(BINDIR) 

# uncomment this when the package needs to be checked out by git
include $(RIOTBASE)/pkg/pkg.mk
