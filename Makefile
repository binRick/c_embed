default: all
##############################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
UNCRUSTIFY=$(shell command -v uncrustify)
PWD=$(shell command -v pwd)
FIND=$(shell command -v find)
EMBED_BINARY=$(shell command -v embed)
JQ_BIN=$(shell command -v jq)
TBL1_EMBEDDED_FILES = \
					  Makefile
##############################################################
DIR=$(shell $(PWD))
M1_DIR=$(DIR)
LOADER_DIR=$(DIR)/loader
EMBEDS_DIR=$(DIR)/embeds
VENDOR_DIR=$(DIR)/vendor
PROJECT_DIR=$(DIR)
MESON_DEPS_DIR=$(DIR)/meson/deps
VENDOR_DIR=$(DIR)/vendor
DEPS_DIR=$(DIR)/deps
BUILD_DIR=$(DIR)/build
ETC_DIR=$(DIR)/etc
MENU_DIR=$(DIR)/menu
DOCKER_DIR=$(DIR)/docker
LIST_DIR=$(DIR)/list
SOURCE_VENV_CMD=$(DIR)/scripts
VENV_DIR=$(DIR)/.venv
SCRIPTS_DIR=$(DIR)/scripts
EMBED_DIR=$(BUILD_DIR)/embed
SOURCE_VENV_CMD = source $(VENV_DIR)/bin/activate
##############################################################
TIDIED_FILES = \
			   embed/*.h embed/*.c \
			   embed-utils/*.h embed-utils/*.c \
			   embed-test/*.h embed-test/*.c
TBL1_EMBED_FILE=tbl1.c
##############################################################
all: setup build test
clean:
	@rm -rf build
install: do-install
do-install: all
	@meson install -C build
	@cp $(BUILD_DIR)/embed/embed /usr/local/bin
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
do-build: do-meson                                                                                       
	@meson compile -C build
do-test:
	@passh meson test -C build -v
build: do-meson do-build	
do-meson:
	@eval cd . && {  meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }
uncrustify:
	@$(UNCRUSTIFY) -c etc/uncrustify.cfg --replace $(TIDIED_FILES) 
	@shfmt -w scripts/*.sh

uncrustify-clean:
	@find  . -type f -name "*unc-back*"|xargs -I % unlink %

fix-dbg:
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)
	tidy: uncrustify uncrustify-clean fix-dbg rm-make-logs
setup:
	@mkdir -p $(EMBEDS_DIR)
dev-all: all
pull:
	@git pull
do-embed-tbl1: setup
	@$(EMBED_DIR)/embed -t tbl -z -o $(EMBEDS_DIR)/$(TBL1_EMBED_FILE) $(TBL1_EMBEDDED_FILES)
	@\cat $(EMBEDS_DIR)/$(TBL1_EMBED_FILE)
do-embed: do-embed-test
install: do-install

test: setup do-test do-embed-tbl1

dev: nodemon
nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) -V -i build -w . -w '*/meson.build' --delay .1 -i '*/subprojects' -I  -w 'include/*.h' -w meson.build -w src -w Makefile -w loader/meson.build -w loader/src -w loader/include -i '*/embeds/*' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make||true'


git-pull:
	@git pull --recurse-submodules
git-submodules-pull-master:
	@git submodule foreach git pull origin master --jobs=10
git-submodules-update:
	@git submodule update --init
