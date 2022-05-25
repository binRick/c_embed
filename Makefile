
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
##############################################################
DIR=$(shell $(PWD))
LOADER_DIR=$(DIR)/loader
EMBED_DIR=$(DIR)/embed
EMBEDS_DIR=$(DIR)/embeds
PROJECT_DIR=$(DIR)
##############################################################
TIDIED_FILES = $(LOADER_DIR)/src/*.c $(LOADER_DIR)/include/*.h $(EMBED_DIR)/src/*.c $(EMBED_DIR)/include/*.h
##############################################################
CD_LOADER = cd $(LOADER_DIR)
CD_EMBED = cd $(EMBED_DIR)
CD_PROJECT = cd $(PROJECT_DIR)
##############################################################
TBL1_EMBED_FILE = $(EMBEDS_DIR)/tbl1.embed
TBL1_EMBEDDED_FILES = Makefile
##############################################################

all: ensure dirs do-embed do-loader
do-build: do-embed-test do-loader-test

clean: 
	@cd $(EMBED_DIR) && rm -rf deps submodules vendor build meson .cache
	@cd $(LOADER_DIR) && rm -rf deps submodules vendor build meson .cache
	@rm -rf $(EMBEDS_DIR)

ensure: dirs-embeds

setup:
	@clib i

loader-deps:
	@rsync -ar $(PROJECT_DIR)/deps $(LOADER_DIR)/.
	@rsync -ar $(PROJECT_DIR)/submodules $(LOADER_DIR)/.
	@rsync -ar $(PROJECT_DIR)/vendor $(LOADER_DIR)/.
	@rsync -ar $(PROJECT_DIR)/meson $(LOADER_DIR)/.

embed-deps:
	@rsync -ar $(PROJECT_DIR)/deps $(EMBED_DIR)/.
	@rsync -ar $(PROJECT_DIR)/submodules $(EMBED_DIR)/.
	@rsync -ar $(PROJECT_DIR)/vendor $(EMBED_DIR)/.
	@rsync -ar $(PROJECT_DIR)/meson $(EMBED_DIR)/.

deps: embed-deps loader-deps
dirs: ensure dirs-embeds deps

dirs-embeds:
	@mkdir -p $(EMBEDS_DIR)

do-embed: ensure do-embed-test

do-loader: ensure do-embed-tbl1 do-loader-test

do-embed-meson: deps
	@eval $(CD_EMBED) && { meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }

do-loader-meson: deps
	@eval $(CD_LOADER) && { meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }

do-embed-build: do-embed-meson
	@eval $(CD_EMBED) && { ninja -C build; }

do-loader-build: do-loader-meson
	@eval $(CD_LOADER) && { ninja -C build; }

do-loader-test: do-loader-build
	@eval $(CD_LOADER) && { ninja test -C build -v; }

do-embed-test: do-embed-build
	@eval $(CD_EMBED) && { ninja test -C build -v; }

do-embed-tbl1: dirs do-embed-test
	@$(EMBED_DIR)/build/embed -t tbl -z -o $(TBL1_EMBED_FILE) $(TBL1_EMBEDDED_FILES)
	@\cat $(TBL1_EMBED_FILE)

do-embed: do-embed-test

install:
	@cp $(EMBED_DIR)/build/embed /usr/local/bin

test: do-embed-test do-loader-test

uncrustify:
	@$(UNCRUSTIFY) -c etc/uncrustify.cfg --replace $(TIDIED_FILES)

uncrustify-clean:
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

fix-dbg:
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)

tidy: uncrustify uncrustify-clean fix-dbg

dev-all: all

dev: clean tidy nodemon

nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) -w meson.build --delay 1 -I -V -w 'include/*.h' -w meson.build -w src -w Makefile -w loader/meson.build -w loader/src -w loader/include -i '*/embeds/*' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make dev-all||true'


#test install embed build-loader test-loader info-loader
