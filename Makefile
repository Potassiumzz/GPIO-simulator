compile:
	mkdir -p bin
	gcc -Iinclude src/*.c -o bin/GPIO-simulator

run:compile
	bin/GPIO-simulator
