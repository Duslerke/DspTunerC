.PHONY: all configure build run clean
all: configure build

# Gerate makefile and instructions for native system's compiler for how to build
configure:
	cmake -S . -B build

# Actually trigger the build
build:
	cmake --build build

run:
	./build/tuner

clean:
	rm -rf build
