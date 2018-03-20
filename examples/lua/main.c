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
int main(void)
{
    
    puts("Lua RTOS build");

    char *input_string = "lua\0";

    char **input_pp = &input_string;
    lua_main(1, input_pp);

    return 0;
}
