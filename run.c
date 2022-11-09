//reference http://www.troubleshooters.com/codecorn/lua/lua_c_calls_lua.htm

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdlib.h>
#include <stdio.h>

void bail(lua_State *L, char *msg){
	fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
		msg, lua_tostring(L, -1));
	exit(1);
}

int main(int argc, char *argv[]) {
    lua_State *L;
    if( argc == 2 ) {
        L = luaL_newstate();
        luaL_openlibs(L);

        luaL_loadfile(L, "script.lua");

        //why on earth is that needed (it is needed btw)
        lua_pcall(L,0,0,0);

        lua_getglobal(L,"runScript");
        lua_pushstring(L,argv[1]);
        lua_pcall(L,1,0,0);

        lua_close(L);
    }
    else if( argc > 2 ) {
        printf("Too many arguments supplied.\n");
        return 0;
    }
    else {
        printf("One argument expected.\n");
        return 0;
    }
    
    return 0;
}
