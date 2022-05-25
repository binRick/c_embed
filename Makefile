default: all
##########################################################
clean:
	@rm -rf build
	@rm -rf loader/build

meson:
	@meson build ||true
	@ninja -C build

install:
	cp build/c_embed /usr/local/bin

test:	
	./build/c_embed --test

build-loader:
	@cd loader && meson build
	@cd loader && ninja -C build

test-loader:
	./loader/build/loader1 --test

info-loader:
	./loader/build/loader1 info

all: meson test install build-loader test-loader info-loader
