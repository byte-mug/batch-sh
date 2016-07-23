CC := gcc


lua.a:
	cd luaobj; $(CC) -c ../luasrc/*.c
	ar rcs lua.a luaobj/*.o

