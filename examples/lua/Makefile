APPLICATION = lua

# If no BOARD is found in the environment, use this default:
BOARD ?= native

BOARD_WHITELIST := fox iotlab-m3 msba2 mulle native pba-d-01-kw2x samr21-xpro


# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# CFLAGS += -DUSE_LINKLAYER
# CFLAGS += -DUSE_RONR
# CFLAGS += -DCCNL_UAPI_H_
# CFLAGS += -DUSE_SUITE_NDNTLV
# CFLAGS += -DNEEDS_PREFIX_MATCHING
# CFLAGS += -DNEEDS_PACKET_CRAFTING

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
# USEMODULE += gnrc_netdev_default
# USEMODULE += auto_init_gnrc_netif
# # This application dumps received packets to STDIO using the pktdump module
# USEMODULE += gnrc_pktdump
# USEMODULE += timex
# USEMODULE += xtimer
# USEMODULE += random
# USEMODULE += prng_minstd

# USEPKG += tlsf
# USEPKG += ccn-lite
USEPKG += lua


include $(RIOTBASE)/Makefile.include

LUA_PATH := $(BINDIR)/lua/$(MODULE)
# add directory of generated *.lua.h files to include path
CFLAGS += -I$(LUA_PATH)

# generate .lua.h header files of .lua files
LUA = $(wildcard *.lua)
LUA_H := $(LUA:%.lua=$(LUA_PATH)/%.lua.h)

$(LUA_PATH)/:
	@mkdir -p $@

$(LUA_H): | $(LUA_PATH)/
$(LUA_H): $(LUA_PATH)/%.lua.h: %.lua
	xxd -i $< | sed 's/^unsigned/const/g' > $@

$(RIOTBUILD_CONFIG_HEADER_C): $(LUA_H)
