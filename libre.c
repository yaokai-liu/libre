/**
 * Project Name: libre
 * Module Name:
 * Filename: libre.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "libre.h"
#include <nmmintrin.h>

bool INLINE matchSeqX(const char *string, const char *pattern) {
    __m128i_u a, b;
    a = _mm_loadu_si128((__m128i_u *) string);
    b = _mm_loadu_si128((__m128i_u *) pattern);
    return _mm_testc_si128(a, b);
}

bool INLINE matchSeq8(const char *string, const char *pattern) {
    __m128i_u a, b;
    a = _mm_loadu_si64(string);
    b = _mm_loadu_si64(pattern);
    return _mm_testc_si128(a, b);
}

bool INLINE matchSeq4(const char *string, const char *pattern) {
    __m128i_u a, b;
    a = _mm_loadu_si32(string);
    b = _mm_loadu_si32(pattern);
    return _mm_testc_si128(a, b);
}

bool INLINE matchChar(const char *string, const char *pattern) {
    return *string == *pattern;
}

bool matchSequence(const char *string, const char *pattern, uint32_t len_pa) {
    while (len_pa >= 16) {
        if (matchSeqX(string, pattern)) {
            string += 16; pattern += 16; len_pa -= 16;
        } else { return false; }
    }
    while (len_pa >= 8) {
        if (matchSeq8(string, pattern)) {
            string += 8; pattern += 8; len_pa -= 8;
        } else { return false; }
    }
    while (len_pa >= 4) {
        if (matchSeq4(string, pattern)) {
            string += 4; pattern += 4; len_pa -= 4;
        } else { return false; }
    }
    while (len_pa >= 1) {
        if (matchChar(string, pattern)) {
            string ++; pattern ++; len_pa --;
        } else { return false; }
    }
    return true;
}


bool INLINE matchPlainX(const char *string, const char *pattern) {
    __m128i_u a, b, c;
    a = _mm_set1_epi8(*string);
    b = _mm_loadu_si128((__m128i_u *) pattern);
    c = _mm_cmpeq_epi8(a, b);
    return !_mm_testz_si128(c, c);
}

bool INLINE matchPlain8(const char *string, const char *pattern) {
    __m128i_u a, b, c;
    a = _mm_set1_epi16(*string);
    b = _mm_loadu_si16(pattern);
    c = _mm_cmpeq_epi16(a, b);
    return !_mm_testz_si128(c, c);
}

bool INLINE matchPlain4(const char *string, const char *pattern) {
    __m128i_u a, b, c;
    a = _mm_set1_epi32(*string);
    b = _mm_loadu_si32(pattern);
    c = _mm_cmpeq_epi16(a, b);
    return !_mm_testz_si128(c, c);
}

bool matchPlains(const char *string, const char *pattern, uint32_t len_pl) {
    while (len_pl >= 16) {
        if (!matchPlainX(string, pattern)) {
            pattern += 16; len_pl -= 16;
        } else { return true; }
    }
    while (len_pl >= 8) {
        if (!matchPlain8(string, pattern)) {
            pattern += 8; len_pl -= 8;
        } else { return true; }
    }
    while (len_pl >= 4) {
        if (!matchPlain4(string, pattern)) {
            pattern += 4; len_pl -= 4;
        } else { return true; }
    }
    while (len_pl >= 1) {
        if (!matchChar(string, pattern)) {
            pattern++; len_pl--;
        } else { return true; }
    }
    return false;
}

bool INLINE matchRangeX(const char * string, const char * lower_bounds, const char * upper_bounds) {
    __m128i_u a, b, c, d, l, u;
    a = _mm_set1_epi8(*string);
    l = _mm_loadu_si128((__m128i_u *) lower_bounds);
    u = _mm_loadu_si128((__m128i_u *) upper_bounds);
    b = _mm_cmplt_epi8(a, l);
    c = _mm_cmpgt_epi8(a, u);
    d = _mm_or_si128(b, c);
    return !_mm_test_all_ones(d);
}

bool INLINE matchRange8(const char *string, const char *lower_bounds, const char *upper_bounds) {
    __m128i_u a, b, c, d, l, u;
    a = _mm_set1_epi16(*string);
    l = _mm_loadu_si16((__m128i_u *) lower_bounds);
    u = _mm_loadu_si16((__m128i_u *) upper_bounds);
    b = _mm_cmplt_epi16(a, l);
    c = _mm_cmpgt_epi16(a, u);
    d = _mm_or_si128(b, c);
    return !_mm_test_all_ones(d);
}

bool INLINE matchRange4(const char *string, const char *lower_bounds, const char *upper_bounds) {
    __m128i_u a, b, c, d, l, u;
    a = _mm_set1_epi32(*string);
    l = _mm_loadu_si32((__m128i_u *) lower_bounds);
    u = _mm_loadu_si32((__m128i_u *) upper_bounds);
    b = _mm_cmplt_epi32(a, l);
    c = _mm_cmpgt_epi32(a, u);
    d = _mm_or_si128(b, c);
    return !_mm_test_all_ones(d);
}

bool INLINE matchRange(const char *string, const char *lower_bounds, const char *upper_bounds) {
    return *lower_bounds <= *string && *string <= *upper_bounds;
}

bool matchRanges(const char *string, const char *lower_bounds, const char *upper_bounds, uint32_t len_rn) {
    while (len_rn >= 16) {
        if (!matchRangeX(string, lower_bounds, upper_bounds)) {
            lower_bounds += 16; upper_bounds += 16; len_rn -= 16;
        } else { return true; }
    }
    while (len_rn >= 8) {
        if (!matchRange8(string, lower_bounds, upper_bounds)) {
            lower_bounds += 8; upper_bounds += 8; len_rn -= 8;
        } else { return true; }
    }
    while (len_rn >= 4) {
        if (!matchRange4(string, lower_bounds, upper_bounds)) {
            lower_bounds += 4; upper_bounds += 4; len_rn -= 4;
        } else { return true; }
    }
    while (len_rn >= 1) {
        if (!matchRange(string, lower_bounds, upper_bounds)) {
            lower_bounds ++; upper_bounds ++; len_rn --;
        } else { return true; }
    }
    return false;
}
