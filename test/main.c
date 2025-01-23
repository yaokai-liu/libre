/**
 * Project Name: libre
 * Module Name: test
 * Filename: main.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "libre.h"

int main() {
    char * string =  "0123456789abcdefghijklmnopqrstuvwxyz";
    char pattern RE_ALIGN [] = "0123456789abcdefghijklmnopqrstu";
    char lower_bounds RE_ALIGN [] = "0123456789abcdefghijklmnopqrstu";
    char upper_bounds RE_ALIGN [] = "123456789abcdefghijklmnopqrstuv";
//    return matchSequence(string, pattern, 16);
//    return matchPlains(string, pattern, 16);
    return matchRanges(string, lower_bounds, upper_bounds, 16);
}
