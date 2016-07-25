CC := gcc

all: bts
	true

lua.a:
	cd luaobj; $(CC) -c ../luasrc/*.c
	ar rcs lua.a luaobj/*.o

lib.a:
	cd libobj; $(CC) -c ../libsrc/*.c
	ar rcs lib.a libobj/*.o

%.o: %.c
	$(CC) -c $< -o $@

main += main.o tokens.o compile.o functions.o pipelib.o
main += lib.a lua.a

bts: $(main)
	$(CC) $(main) lua.a -lm -o bts

main: $(main)
	$(CC) $(main) lua.a -lm -o main

clean:
	rm luaobj/*.o
	rm libobj/*.o
	rm *.o
	rm *.a
