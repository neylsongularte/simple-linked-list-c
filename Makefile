

main : src/lista.c main.c
	mkdir -p build && gcc -o build/main src/lista.c main.c


.PHONY: clean

clean:
	rm -rf build
