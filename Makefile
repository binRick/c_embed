default: all
##########################################################
clean:
	@rm -rf loader/build build loader/c_embed/*.c_embed

meson:
	@meson build ||true
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

embed:
	@./build/c_embed -t tbl -z -o loader/c_embed/tbl1.c_embed Makefile src/c_embed.c loader/src/loader1.c meson.build loader/meson.build


all: clean meson test install embed build-loader test-loader info-loader
