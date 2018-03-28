/*
 * Copyright (C) 2015 Inria
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
 * @brief       Basic ccn-lite relay example (produce and consumer via shell)
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 *
 * @}
 */

#include <stdio.h>

#include "msg.h"
#include "shell.h"

extern int lua_main(int argc, char **argv);
extern int lua_run_main_script(int argc, char **argv);

static const shell_command_t shell_commands[] = {
    { "lua", "Start a Lua prompt, with usual Lua arguments available. Press Ctrl-D to exit back to RIOT.", lua_main}, 
    { "run_lua_script", "Run main.lua, parsed at compile time from your example directory", lua_run_main_script},
    { NULL, NULL, NULL }
};

int main(void)
{
    
    puts("Lua RIOT build");

//  char *input_string = "lua\0";

//    char **input_pp = &input_string;
//    lua_main(1, input_pp);

//    handle_buffer(main_lua, main_lua_len);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
