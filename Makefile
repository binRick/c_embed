default: all
##############################################################
include submodules/c_deps/etc/includes.mk
EMBED_BINARY=$(shell command -v embed)
TBL1_EMBEDDED_FILES = \
					  Makefile
##############################################################
EMBED_DIR=$(BUILD_DIR)/embed
##############################################################
TIDIED_FILES = \
			   embed/*.h embed/*.c \
			   embed-utils/*.h embed-utils/*.c \
			   embed-test/*.h embed-test/*.c
TBL1_EMBED_FILE=tbl1.c
##############################################################
embed-tbl1: setup
	@$(EMBED_DIR)/embed -t tbl -z -o $(EMBEDS_DIR)/$(TBL1_EMBED_FILE) $(TBL1_EMBEDDED_FILES)
embed: embed-tbl1
