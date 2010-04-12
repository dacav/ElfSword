#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <elfsword.h>

#include <stdio.h>

static
int call_new (lua_State *l)
{
	const char *fname;

	fname = luaL_checkstring(l, 1);
	printf("Required file: %s\n", fname);

	// just to test my new skillz
	lua_newtable(l);
	lua_pushinteger(l, 1);
	lua_pushinteger(l, 3.14);
	lua_settable(l, -3);

	//lua_pushlightuserdata(l, (void *)0xDEADBEEF);
	return 1;
}

static
int call_print (lua_State *l)
{
	printf("You called with %p\n", luaL_checkudata(l, 1, "nightelf"));
	return 0;
}

int luaopen_nightelf (lua_State *l)
{
	luaL_reg functions[] = {
		{"new", call_new},
		{"print", call_print},
		{NULL, NULL}
	};
	luaL_openlib(l, "nightelf", functions, 0);
	return 1;
}

