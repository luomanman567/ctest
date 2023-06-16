all:build
build:
	gcc -o build main.c
clean:
	rm -rf build