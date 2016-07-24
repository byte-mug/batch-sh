CC := gcc


lua.a:
	cd luaobj; $(CC) -c ../luasrc/*.c
	ar rcs lua.a luaobj/*.o

lib.a:
	cd libobj; $(CC) -c ../libsrc/*.c
	ar rcs lib.a libobj/*.o

%.o: %.c
	$(CC) -c $< -o $@

main: main.o tokens.o compile.o lib.a
	$(CC) main.o tokens.o compile.o lib.a -o main
