/*
 * Copyright (C) 2018 FU Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Basic lua example application
 *
 * @author      Daniel Petry <daniel.petry@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <stdlib.h>
#include "lauxlib.h"
#include "lualib.h"
#include "msg.h"
#include "shell.h"
#include "main.lua.h"

extern int lua_main(int argc, char **argv);

static const shell_command_t shell_commands[] = {
	    { "lua", "Start a Lua prompt", lua_main},
	    { NULL, NULL, NULL }
	};
int lua_run_script (const char *buffer, size_t buffer_len ){

    lua_State *L = luaL_newstate();

    if (L == NULL) {
        puts("cannot create state: not enough memory");
        return EXIT_FAILURE;
    }

    luaL_openlibs(L);

    luaL_loadbuffer(L, buffer, buffer_len, "lua input script");

    if (lua_pcall(L, 0, 0, 0) != LUA_OK){
        puts("Lua script running failed");
        return EXIT_FAILURE;
    }

    lua_close(L);

    return EXIT_SUCCESS;
}

int main(void)
{
    puts("Lua RIOT build");

     char line_buf[SHELL_DEFAULT_BUFSIZE];
     shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
//    lua_run_script(main_lua, main_lua_len);

    return 0;
}
