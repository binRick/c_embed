default: all
##########################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
UNCRUSTIFY=$(shell command -v uncrustify)
##########################################################
TIDIED_FILES = src/*.c include/*.h loader/src/*.c loader/src/*.c
#loader/include/*.h
##########################################################
clean:
	@rm -rf loader/build build loader/c_embed/*.c_embed
	@touch ./loader/c_embed/tbl1.c_embed

setup:
	@clib i

do-meson:
#	@rm -rf build
	@meson build||true
	@meson build --reconfigure||true
	@meson build --reconfigure||true
	@ninja -C build

install:
	@cp build/c_embed /usr/local/bin

test:	
	@./build/c_embed --test

build-loader:
	@cd loader && meson build
	@cd loader && ninja -C build

test-loader:
	@./loader/build/loader1 --test

info-loader:
	@./loader/build/loader1 info
	@\tail -n 15 ./loader/c_embed/tbl1.c_embed

embed:
	@./build/c_embed -t tbl -z -o loader/c_embed/tbl1.c_embed Makefile src/c_embed.c loader/src/loader1.c meson.build loader/meson.build .direnv
	@\cat ./loader/c_embed/tbl1.c_embed


uncrustify:
	@$(UNCRUSTIFY) -c etc/uncrustify.cfg --replace $(TIDIED_FILES)
#	@shfmt -w scripts/*.sh

uncrustify-clean:
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

fix-dbg:
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)

tidy: uncrustify uncrustify-clean fix-dbg

dev:
	@$(PASSH) -L .nodemon.log $(NODEMON) -w meson.build -I -V -w 'include/*.h' -w meson.build -w src -w Makefile -w loader/meson.build -w loader/src -w loader/include -i 'loader/c_embed/*' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make||true'

all: clean do-meson test install embed build-loader test-loader info-loader
