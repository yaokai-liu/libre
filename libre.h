/**
 * Project Name: libre
 * Module Name:
 * Filename: libre.h
 * Creator: Yaokai Liu
 * Create Date: 2024-07-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef LIBRE_LIBRE_H
#define LIBRE_LIBRE_H

#include <stdint.h>
#include <stdbool.h>

#define RE_ALIGN [[gnu::aligned(16)]]

// 16 bytes
bool matchSeqX(const char *string, const char *pattern);
// 8 bytes
bool matchSeq8(const char *string, const char *pattern);
// 4 bytes
bool matchSeq4(const char *string, const char *pattern);
// 16 bytes
bool matchPlainX(const char *string, const char *pattern);
// 8 bytes
bool matchPlain8(const char *string, const char *pattern);
// 4 bytes
bool matchPlain4(const char *string, const char *pattern);
// 1 byte
bool matchChar(const char *string, const char *pattern);
// 16 bytes
bool matchRangeX(const char *string, const char *lower_bounds, const char *upper_bounds);
// 8 bytes
bool matchRange8(const char *string, const char *lower_bounds, const char *upper_bounds);
// 4 bytes
bool matchRange4(const char *string, const char *lower_bounds, const char *upper_bounds);
// 1 byte
bool matchRange(const char *string, const char *lower_bounds, const char *upper_bounds);

bool matchSequence(const char * string, const char *pattern, uint32_t len_pa);
bool matchPlains(const char *string, const char *pattern, uint32_t len_pl);
bool matchRanges(const char *string, const char *lower_bounds,
                 const char *upper_bounds, uint32_t len_rn);

#endif //LIBRE_LIBRE_H
