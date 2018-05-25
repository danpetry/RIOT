/*
 * Copyright (C) 2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     lua
 * @{
 *
 * @file
 * @brief       Mineplex font.
 *
 * Lua support for the mineplex font.
 *
 * @author      Juan Carrano <j.carrano@fu-berlin.de>
 *
 * @}
 */

#define LUA_LIB

#include "lprefix.h"

#include <string.h>

#include "mineplex.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define BITMAP_TNAME "mineplex_bmp"

/**
 * Index a bitmap character.
 *
 * @param   c   Bitmap character.
 * @param   x   Bit index in the horizontal dimension (1-based)
 * @param   y   Bit index in the vertical dimension (1-based)
 *
 * @return true if the bit is set, false otherwise.
 */
//static int index_(lua_State *L)
//{
//    /* bmap cannot be NULL */
//    uint8_t *bmap = luaL_checkudata (L, 1, BITMAP_TNAME);
//    lua_Integer x = luaL_checkinteger(L, 2);
//    lua_Integer y = luaL_checkinteger(L, 3);
//
//    if (!((x > 0 && x <= MINEPLEX_CHAR_W)
//        &&(y > 0 && y <= MINEPLEX_CHAR_H))) {
//        luaL_error(L, "Bitmap index out of range");
//    }
//
//    lua_pushboolean(L, (bmap[y-1]>>(x-1)) & 1);
//
//    return 1;
//}
//
//static const luaL_Reg bmp_methods[] = {
//  {"index", index_},
//  {NULL, NULL}
//};

/**
 * Return the bitmap corresponding to a character.
 *
 * @param   c   The character given as an ascii code.
 * @return      mineplex object (full userdata with custom metatable)
 */
static int char_(lua_State *L)
{
    (void)L;
//    lua_Number n = luaL_checknumber(L, 1);
//
//    uint8_t *char_copy = lua_newuserdata(L, MINEPLEX_CHAR_H);
//    memcpy(char_copy, mineplex_char(n), MINEPLEX_CHAR_H);
//
//    luaL_setmetatable(L, BITMAP_TNAME);
    puts("called a function!");

    return 1;
}

static const luaL_Reg funcs[] = {
  {"char", char_},
  /* placeholders */
  {"WIDTH", NULL},
  {"HEIGHT", NULL},
  {NULL, NULL}
};

/**
 * Load the library.
 *
 * @return      Lua table.
 */
int luaopen_saul(lua_State *L)
{
	puts("opening saul lua lib");
//    if (luaL_newmetatable(L, BITMAP_TNAME)) {
//        luaL_newlib(L, bmp_methods);
//        lua_setfield(L, -2, "__index");
//    }

//    luaL_newlib(L, funcs);
//    lua_setglobal(L, "danlib");
    //lua_pushcfunction(L, char_);
    //lua_setglobal(L, "printmsg");
    
	lua_newtable(L);
	luaL_setfuncs(L, funcs, 0);

//    lua_pushinteger(L, MINEPLEX_CHAR_W);
//    lua_setfield(L, -2, "WIDTH");
//
//    lua_pushinteger(L, MINEPLEX_CHAR_H);
//    lua_setfield(L, -2, "HEIGHT");

    return 1;
}
