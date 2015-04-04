

example : src/lista.c src/lista.h example.c
	mkdir -p build && gcc -o build/example src/lista.c example.c


.PHONY: clean test

clean:
	rm -rf build

test:
	gcc -o build/test test/test.c src/lista.c && build/test
