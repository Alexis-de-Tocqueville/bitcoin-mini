/**********************************************************************
 * Copyright (c) 2014 Pieter Wuille                                   *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef SECP256K1_SCALAR_REPR_IMPL_H
#define SECP256K1_SCALAR_REPR_IMPL_H

/* Limbs of the secp256k1 order. */
#define SECP256K1_N_0 ((uint32_t)0xD0364141UL)
#define SECP256K1_N_1 ((uint32_t)0xBFD25E8CUL)
#define SECP256K1_N_2 ((uint32_t)0xAF48A03BUL)
#define SECP256K1_N_3 ((uint32_t)0xBAAEDCE6UL)
#define SECP256K1_N_4 ((uint32_t)0xFFFFFFFEUL)
#define SECP256K1_N_5 ((uint32_t)0xFFFFFFFFUL)
#define SECP256K1_N_6 ((uint32_t)0xFFFFFFFFUL)
#define SECP256K1_N_7 ((uint32_t)0xFFFFFFFFUL)

/* Limbs of 2^256 minus the secp256k1 order. */
#define SECP256K1_N_C_0 (~SECP256K1_N_0 + 1)
#define SECP256K1_N_C_1 (~SECP256K1_N_1)
#define SECP256K1_N_C_2 (~SECP256K1_N_2)
#define SECP256K1_N_C_3 (~SECP256K1_N_3)
#define SECP256K1_N_C_4 (1)

/* Limbs of half the secp256k1 order. */
#define SECP256K1_N_H_0 ((uint32_t)0x681B20A0UL)
#define SECP256K1_N_H_1 ((uint32_t)0xDFE92F46UL)
#define SECP256K1_N_H_2 ((uint32_t)0x57A4501DUL)
#define SECP256K1_N_H_3 ((uint32_t)0x5D576E73UL)
#define SECP256K1_N_H_4 ((uint32_t)0xFFFFFFFFUL)
#define SECP256K1_N_H_5 ((uint32_t)0xFFFFFFFFUL)
#define SECP256K1_N_H_6 ((uint32_t)0xFFFFFFFFUL)
#define SECP256K1_N_H_7 ((uint32_t)0x7FFFFFFFUL)

SECP256K1_INLINE static void secp256k1_scalar_clear(secp256k1_scalar *r) {
    r->d[0] = 0;
    r->d[1] = 0;
    r->d[2] = 0;
    r->d[3] = 0;
    r->d[4] = 0;
    r->d[5] = 0;
    r->d[6] = 0;
    r->d[7] = 0;
}

SECP256K1_INLINE static void secp256k1_scalar_set_int(secp256k1_scalar *r, unsigned int v) {
    r->d[0] = v;
    r->d[1] = 0;
    r->d[2] = 0;
    r->d[3] = 0;
    r->d[4] = 0;
    r->d[5] = 0;
    r->d[6] = 0;
    r->d[7] = 0;
}

SECP256K1_INLINE static unsigned int secp256k1_scalar_get_bits(const secp256k1_scalar *a, unsigned int offset, unsigned int count) {
    VERIFY_CHECK((offset + count - 1) >> 5 == offset >> 5);
    return (a->d[offset >> 5] >> (offset & 0x1F)) & ((1 << count) - 1);
}

SECP256K1_INLINE static unsigned int secp256k1_scalar_get_bits_var(const secp256k1_scalar *a, unsigned int offset, unsigned int count) {
    VERIFY_CHECK(count < 32);
    VERIFY_CHECK(offset + count <= 256);
    if ((offset + count - 1) >> 5 == offset >> 5) {
        return secp256k1_scalar_get_bits(a, offset, count);
    } else {
        VERIFY_CHECK((offset >> 5) + 1 < 8);
        return ((a->d[offset >> 5] >> (offset & 0x1F)) | (a->d[(offset >> 5) + 1] << (32 - (offset & 0x1F)))) & ((((uint32_t)1) << count) - 1);
    }
}

SECP256K1_INLINE static int secp256k1_scalar_check_overflow(const secp256k1_scalar *a) {
    int yes = 0;
    int no = 0;
    no |= (a->d[7] < SECP256K1_N_7); /* No need for a > check. */
    no |= (a->d[6] < SECP256K1_N_6); /* No need for a > check. */
    no |= (a->d[5] < SECP256K1_N_5); /* No need for a > check. */
    no |= (a->d[4] < SECP256K1_N_4);
    yes |= (a->d[4] > SECP256K1_N_4) & ~no;
    no |= (a->d[3] < SECP256K1_N_3) & ~yes;
    yes |= (a->d[3] > SECP256K1_N_3) & ~no;
    no |= (a->d[2] < SECP256K1_N_2) & ~yes;
    yes |= (a->d[2] > SECP256K1_N_2) & ~no;
    no |= (a->d[1] < SECP256K1_N_1) & ~yes;
    yes |= (a->d[1] > SECP256K1_N_1) & ~no;
    yes |= (a->d[0] >= SECP256K1_N_0) & ~no;
    return yes;
}

SECP256K1_INLINE static int secp256k1_scalar_reduce(secp256k1_scalar *r, uint32_t overflow) {
    uint64_t t;
    VERIFY_CHECK(overflow <= 1);
    t = (uint64_t)r->d[0] + overflow * SECP256K1_N_C_0;
    r->d[0] = t & 0xFFFFFFFFUL; t >>= 32;
    t += (uint64_t)r->d[1] + overflow * SECP256K1_N_C_1;
    r->d[1] = t & 0xFFFFFFFFUL; t >>= 32;
    t += (uint64_t)r->d[2] + overflow * SECP256K1_N_C_2;
    r->d[2] = t & 0xFFFFFFFFUL; t >>= 32;
    t += (uint64_t)r->d[3] + overflow * SECP256K1_N_C_3;
    r->d[3] = t & 0xFFFFFFFFUL; t >>= 32;
    t += (uint64_t)r->d[4] + overflow * SECP256K1_N_C_4;
    r->d[4] = t & 0xFFFFFFFFUL; t >>= 32;
    t += (uint64_t)r->d[5];
    r->d[5] = t & 0xFFFFFFFFUL; t >>= 32;
    t += (uint64_t)r->d[6];
    r->d[6] = t & 0xFFFFFFFFUL; t >>= 32;
    t += (uint64_t)r->d[7];
    r->d[7] = t & 0xFFFFFFFFUL;
    return overflow;
}

static int secp256k1_scalar_add(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b) {
    int overflow;
    uint64_t t = (uint64_t)a->d[0] + b->d[0];
    r->d[0] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[1] + b->d[1];
    r->d[1] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[2] + b->d[2];
    r->d[2] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[3] + b->d[3];
    r->d[3] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[4] + b->d[4];
    r->d[4] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[5] + b->d[5];
    r->d[5] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[6] + b->d[6];
    r->d[6] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)a->d[7] + b->d[7];
    r->d[7] = t & 0xFFFFFFFFULL; t >>= 32;
    overflow = t + secp256k1_scalar_check_overflow(r);
    VERIFY_CHECK(overflow == 0 || overflow == 1);
    secp256k1_scalar_reduce(r, overflow);
    return overflow;
}

static void secp256k1_scalar_cadd_bit(secp256k1_scalar *r, unsigned int bit, int flag) {
    uint64_t t;
    VERIFY_CHECK(bit < 256);
    bit += ((uint32_t) flag - 1) & 0x100;  /* forcing (bit >> 5) > 7 makes this a noop */
    t = (uint64_t)r->d[0] + (((uint32_t)((bit >> 5) == 0)) << (bit & 0x1F));
    r->d[0] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)r->d[1] + (((uint32_t)((bit >> 5) == 1)) << (bit & 0x1F));
    r->d[1] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)r->d[2] + (((uint32_t)((bit >> 5) == 2)) << (bit & 0x1F));
    r->d[2] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)r->d[3] + (((uint32_t)((bit >> 5) == 3)) << (bit & 0x1F));
    r->d[3] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)r->d[4] + (((uint32_t)((bit >> 5) == 4)) << (bit & 0x1F));
    r->d[4] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)r->d[5] + (((uint32_t)((bit >> 5) == 5)) << (bit & 0x1F));
    r->d[5] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)r->d[6] + (((uint32_t)((bit >> 5) == 6)) << (bit & 0x1F));
    r->d[6] = t & 0xFFFFFFFFULL; t >>= 32;
    t += (uint64_t)r->d[7] + (((uint32_t)((bit >> 5) == 7)) << (bit & 0x1F));
    r->d[7] = t & 0xFFFFFFFFULL;
#ifdef VERIFY
    VERIFY_CHECK((t >> 32) == 0);
    VERIFY_CHECK(secp256k1_scalar_check_overflow(r) == 0);
#endif
}

static void secp256k1_scalar_set_b32(secp256k1_scalar *r, const unsigned char *b32, int *overflow) {
    int over;
    r->d[0] = (uint32_t)b32[31] | (uint32_t)b32[30] << 8 | (uint32_t)b32[29] << 16 | (uint32_t)b32[28] << 24;
    r->d[1] = (uint32_t)b32[27] | (uint32_t)b32[26] << 8 | (uint32_t)b32[25] << 16 | (uint32_t)b32[24] << 24;
    r->d[2] = (uint32_t)b32[23] | (uint32_t)b32[22] << 8 | (uint32_t)b32[21] << 16 | (uint32_t)b32[20] << 24;
    r->d[3] = (uint32_t)b32[19] | (uint32_t)b32[18] << 8 | (uint32_t)b32[17] << 16 | (uint32_t)b32[16] << 24;
    r->d[4] = (uint32_t)b32[15] | (uint32_t)b32[14] << 8 | (uint32_t)b32[13] << 16 | (uint32_t)b32[12] << 24;
    r->d[5] = (uint32_t)b32[11] | (uint32_t)b32[10] << 8 | (uint32_t)b32[9] << 16 | (uint32_t)b32[8] << 24;
    r->d[6] = (uint32_t)b32[7] | (uint32_t)b32[6] << 8 | (uint32_t)b32[5] << 16 | (uint32_t)b32[4] << 24;
    r->d[7] = (uint32_t)b32[3] | (uint32_t)b32[2] << 8 | (uint32_t)b32[1] << 16 | (uint32_t)b32[0] << 24;
    over = secp256k1_scalar_reduce(r, secp256k1_scalar_check_overflow(r));
    if (overflow) {
        *overflow = over;
    }
}

static void secp256k1_scalar_get_b32(unsigned char *bin, const secp256k1_scalar* a) {
    bin[0] = a->d[7] >> 24; bin[1] = a->d[7] >> 16; bin[2] = a->d[7] >> 8; bin[3] = a->d[7];
    bin[4] = a->d[6] >> 24; bin[5] = a->d[6] >> 16; bin[6] = a->d[6] >> 8; bin[7] = a->d[6];
    bin[8] = a->d[5] >> 24; bin[9] = a->d[5] >> 16; bin[10] = a->d[5] >> 8; bin[11] = a->d[5];
    bin[12] = a->d[4] >> 24; bin[13] = a->d[4] >> 16; bin[14] = a->d[4] >> 8; bin[15] = a->d[4];
    bin[16] = a->d[3] >> 24; bin[17] = a->d[3] >> 16; bin[18] = a->d[3] >> 8; bin[19] = a->d[3];
    bin[20] = a->d[2] >> 24; bin[21] = a->d[2] >> 16; bin[22] = a->d[2] >> 8; bin[23] = a->d[2];
    bin[24] = a->d[1] >> 24; bin[25] = a->d[1] >> 16; bin[26] = a->d[1] >> 8; bin[27] = a->d[1];
    bin[28] = a->d[0] >> 24; bin[29] = a->d[0] >> 16; bin[30] = a->d[0] >> 8; bin[31] = a->d[0];
}

SECP256K1_INLINE static int secp256k1_scalar_is_zero(const secp256k1_scalar *a) {
    return (a->d[0] | a->d[1] | a->d[2] | a->d[3] | a->d[4] | a->d[5] | a->d[6] | a->d[7]) == 0;
}

static void secp256k1_scalar_negate(secp256k1_scalar *r, const secp256k1_scalar *a) {
    uint32_t nonzero = 0xFFFFFFFFUL * (secp256k1_scalar_is_zero(a) == 0);
    uint64_t t = (uint64_t)(~a->d[0]) + SECP256K1_N_0 + 1;
    r->d[0] = t & nonzero; t >>= 32;
    t += (uint64_t)(~a->d[1]) + SECP256K1_N_1;
    r->d[1] = t & nonzero; t >>= 32;
    t += (uint64_t)(~a->d[2]) + SECP256K1_N_2;
    r->d[2] = t & nonzero; t >>= 32;
    t += (uint64_t)(~a->d[3]) + SECP256K1_N_3;
    r->d[3] = t & nonzero; t >>= 32;
    t += (uint64_t)(~a->d[4]) + SECP256K1_N_4;
    r->d[4] = t & nonzero; t >>= 32;
    t += (uint64_t)(~a->d[5]) + SECP256K1_N_5;
    r->d[5] = t & nonzero; t >>= 32;
    t += (uint64_t)(~a->d[6]) + SECP256K1_N_6;
    r->d[6] = t & nonzero; t >>= 32;
    t += (uint64_t)(~a->d[7]) + SECP256K1_N_7;
    r->d[7] = t & nonzero;
}

SECP256K1_INLINE static int secp256k1_scalar_is_one(const secp256k1_scalar *a) {
    return ((a->d[0] ^ 1) | a->d[1] | a->d[2] | a->d[3] | a->d[4] | a->d[5] | a->d[6] | a->d[7]) == 0;
}

static int secp256k1_scalar_is_high(const secp256k1_scalar *a) {
    int yes = 0;
    int no = 0;
    no |= (a->d[7] < SECP256K1_N_H_7);
    yes |= (a->d[7] > SECP256K1_N_H_7) & ~no;
    no |= (a->d[6] < SECP256K1_N_H_6) & ~yes; /* No need for a > check. */
    no |= (a->d[5] < SECP256K1_N_H_5) & ~yes; /* No need for a > check. */
    no |= (a->d[4] < SECP256K1_N_H_4) & ~yes; /* No need for a > check. */
    no |= (a->d[3] < SECP256K1_N_H_3) & ~yes;
    yes |= (a->d[3] > SECP256K1_N_H_3) & ~no;
    no |= (a->d[2] < SECP256K1_N_H_2) & ~yes;
    yes |= (a->d[2] > SECP256K1_N_H_2) & ~no;
    no |= (a->d[1] < SECP256K1_N_H_1) & ~yes;
    yes |= (a->d[1] > SECP256K1_N_H_1) & ~no;
    yes |= (a->d[0] > SECP256K1_N_H_0) & ~no;
    return yes;
}

static int secp256k1_scalar_cond_negate(secp256k1_scalar *r, int flag) {
    /* If we are flag = 0, mask = 00...00 and this is a no-op;
     * if we are flag = 1, mask = 11...11 and this is identical to secp256k1_scalar_negate */
    uint32_t mask = !flag - 1;
    uint32_t nonzero = 0xFFFFFFFFUL * (secp256k1_scalar_is_zero(r) == 0);
    uint64_t t = (uint64_t)(r->d[0] ^ mask) + ((SECP256K1_N_0 + 1) & mask);
    r->d[0] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[1] ^ mask) + (SECP256K1_N_1 & mask);
    r->d[1] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[2] ^ mask) + (SECP256K1_N_2 & mask);
    r->d[2] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[3] ^ mask) + (SECP256K1_N_3 & mask);
    r->d[3] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[4] ^ mask) + (SECP256K1_N_4 & mask);
    r->d[4] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[5] ^ mask) + (SECP256K1_N_5 & mask);
    r->d[5] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[6] ^ mask) + (SECP256K1_N_6 & mask);
    r->d[6] = t & nonzero; t >>= 32;
    t += (uint64_t)(r->d[7] ^ mask) + (SECP256K1_N_7 & mask);
    r->d[7] = t & nonzero;
    return 2 * (mask == 0) - 1;
}


/* Inspired by the macros in OpenSSL's crypto/bn/asm/x86_64-gcc.c. */

/** Add a*b to the number defined by (c0,c1,c2). c2 must never overflow. */
#define muladd(a,b) { \
    uint32_t tl, th; \
    { \
        uint64_t t = (uint64_t)a * b; \
        th = t >> 32;         /* at most 0xFFFFFFFE */ \
        tl = t; \
    } \
    c0 += tl;                 /* overflow is handled on the next line */ \
    th += (c0 < tl) ? 1 : 0;  /* at most 0xFFFFFFFF */ \
    c1 += th;                 /* overflow is handled on the next line */ \
    c2 += (c1 < th) ? 1 : 0;  /* never overflows by contract (verified in the next line) */ \
    VERIFY_CHECK((c1 >= th) || (c2 != 0)); \
}

/** Add a*b to the number defined by (c0,c1). c1 must never overflow. */
#define muladd_fast(a,b) { \
    uint32_t tl, th; \
    { \
        uint64_t t = (uint64_t)a * b; \
        th = t >> 32;         /* at most 0xFFFFFFFE */ \
        tl = t; \
    } \
    c0 += tl;                 /* overflow is handled on the next line */ \
    th += (c0 < tl) ? 1 : 0;  /* at most 0xFFFFFFFF */ \
    c1 += th;                 /* never overflows by contract (verified in the next line) */ \
    VERIFY_CHECK(c1 >= th); \
}

/** Add 2*a*b to the number defined by (c0,c1,c2). c2 must never overflow. */
#define muladd2(a,b) { \
    uint32_t tl, th, th2, tl2; \
    { \
        uint64_t t = (uint64_t)a * b; \
        th = t >> 32;               /* at most 0xFFFFFFFE */ \
        tl = t; \
    } \
    th2 = th + th;                  /* at most 0xFFFFFFFE (in case th was 0x7FFFFFFF) */ \
    c2 += (th2 < th) ? 1 : 0;       /* never overflows by contract (verified the next line) */ \
    VERIFY_CHECK((th2 >= th) || (c2 != 0)); \
    tl2 = tl + tl;                  /* at most 0xFFFFFFFE (in case the lowest 63 bits of tl were 0x7FFFFFFF) */ \
    th2 += (tl2 < tl) ? 1 : 0;      /* at most 0xFFFFFFFF */ \
    c0 += tl2;                      /* overflow is handled on the next line */ \
    th2 += (c0 < tl2) ? 1 : 0;      /* second overflow is handled on the next line */ \
    c2 += (c0 < tl2) & (th2 == 0);  /* never overflows by contract (verified the next line) */ \
    VERIFY_CHECK((c0 >= tl2) || (th2 != 0) || (c2 != 0)); \
    c1 += th2;                      /* overflow is handled on the next line */ \
    c2 += (c1 < th2) ? 1 : 0;       /* never overflows by contract (verified the next line) */ \
    VERIFY_CHECK((c1 >= th2) || (c2 != 0)); \
}

/** Add a to the number defined by (c0,c1,c2). c2 must never overflow. */
#define sumadd(a) { \
    unsigned int over; \
    c0 += (a);                  /* overflow is handled on the next line */ \
    over = (c0 < (a)) ? 1 : 0; \
    c1 += over;                 /* overflow is handled on the next line */ \
    c2 += (c1 < over) ? 1 : 0;  /* never overflows by contract */ \
}

/** Add a to the number defined by (c0,c1). c1 must never overflow, c2 must be zero. */
#define sumadd_fast(a) { \
    c0 += (a);                 /* overflow is handled on the next line */ \
    c1 += (c0 < (a)) ? 1 : 0;  /* never overflows by contract (verified the next line) */ \
    VERIFY_CHECK((c1 != 0) | (c0 >= (a))); \
    VERIFY_CHECK(c2 == 0); \
}

/** Extract the lowest 32 bits of (c0,c1,c2) into n, and left shift the number 32 bits. */
#define extract(n) { \
    (n) = c0; \
    c0 = c1; \
    c1 = c2; \
    c2 = 0; \
}

/** Extract the lowest 32 bits of (c0,c1,c2) into n, and left shift the number 32 bits. c2 is required to be zero. */
#define extract_fast(n) { \
    (n) = c0; \
    c0 = c1; \
    c1 = 0; \
    VERIFY_CHECK(c2 == 0); \
}

static void secp256k1_scalar_reduce_512(secp256k1_scalar *r, const uint32_t *l) {
    uint64_t c;
    uint32_t n0 = l[8], n1 = l[9], n2 = l[10], n3 = l[11], n4 = l[12], n5 = l[13], n6 = l[14], n7 = l[15];
    uint32_t m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12;
    uint32_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    /* 96 bit accumulator. */
    uint32_t c0, c1, c2;

    /* Reduce 512 bits into 385. */
    /* m[0..12] = l[0..7] + n[0..7] * SECP256K1_N_C. */
    c0 = l[0]; c1 = 0; c2 = 0;
    muladd_fast(n0, SECP256K1_N_C_0);
    extract_fast(m0);
    sumadd_fast(l[1]);
    muladd(n1, SECP256K1_N_C_0);
    muladd(n0, SECP256K1_N_C_1);
    extract(m1);
    sumadd(l[2]);
    muladd(n2, SECP256K1_N_C_0);
    muladd(n1, SECP256K1_N_C_1);
    muladd(n0, SECP256K1_N_C_2);
    extract(m2);
    sumadd(l[3]);
    muladd(n3, SECP256K1_N_C_0);
    muladd(n2, SECP256K1_N_C_1);
    muladd(n1, SECP256K1_N_C_2);
    muladd(n0, SECP256K1_N_C_3);
    extract(m3);
    sumadd(l[4]);
    muladd(n4, SECP256K1_N_C_0);
    muladd(n3, SECP256K1_N_C_1);
    muladd(n2, SECP256K1_N_C_2);
    muladd(n1, SECP256K1_N_C_3);
    sumadd(n0);
    extract(m4);
    sumadd(l[5]);
    muladd(n5, SECP256K1_N_C_0);
    muladd(n4, SECP256K1_N_C_1);
    muladd(n3, SECP256K1_N_C_2);
    muladd(n2, SECP256K1_N_C_3);
    sumadd(n1);
    extract(m5);
    sumadd(l[6]);
    muladd(n6, SECP256K1_N_C_0);
    muladd(n5, SECP256K1_N_C_1);
    muladd(n4, SECP256K1_N_C_2);
    muladd(n3, SECP256K1_N_C_3);
    sumadd(n2);
    extract(m6);
    sumadd(l[7]);
    muladd(n7, SECP256K1_N_C_0);
    muladd(n6, SECP256K1_N_C_1);
    muladd(n5, SECP256K1_N_C_2);
    muladd(n4, SECP256K1_N_C_3);
    sumadd(n3);
    extract(m7);
    muladd(n7, SECP256K1_N_C_1);
    muladd(n6, SECP256K1_N_C_2);
    muladd(n5, SECP256K1_N_C_3);
    sumadd(n4);
    extract(m8);
    muladd(n7, SECP256K1_N_C_2);
    muladd(n6, SECP256K1_N_C_3);
    sumadd(n5);
    extract(m9);
    muladd(n7, SECP256K1_N_C_3);
    sumadd(n6);
    extract(m10);
    sumadd_fast(n7);
    extract_fast(m11);
    VERIFY_CHECK(c0 <= 1);
    m12 = c0;

    /* Reduce 385 bits into 258. */
    /* p[0..8] = m[0..7] + m[8..12] * SECP256K1_N_C. */
    c0 = m0; c1 = 0; c2 = 0;
    muladd_fast(m8, SECP256K1_N_C_0);
    extract_fast(p0);
    sumadd_fast(m1);
    muladd(m9, SECP256K1_N_C_0);
    muladd(m8, SECP256K1_N_C_1);
    extract(p1);
    sumadd(m2);
    muladd(m10, SECP256K1_N_C_0);
    muladd(m9, SECP256K1_N_C_1);
    muladd(m8, SECP256K1_N_C_2);
    extract(p2);
    sumadd(m3);
    muladd(m11, SECP256K1_N_C_0);
    muladd(m10, SECP256K1_N_C_1);
    muladd(m9, SECP256K1_N_C_2);
    muladd(m8, SECP256K1_N_C_3);
    extract(p3);
    sumadd(m4);
    muladd(m12, SECP256K1_N_C_0);
    muladd(m11, SECP256K1_N_C_1);
    muladd(m10, SECP256K1_N_C_2);
    muladd(m9, SECP256K1_N_C_3);
    sumadd(m8);
    extract(p4);
    sumadd(m5);
    muladd(m12, SECP256K1_N_C_1);
    muladd(m11, SECP256K1_N_C_2);
    muladd(m10, SECP256K1_N_C_3);
    sumadd(m9);
    extract(p5);
    sumadd(m6);
    muladd(m12, SECP256K1_N_C_2);
    muladd(m11, SECP256K1_N_C_3);
    sumadd(m10);
    extract(p6);
    sumadd_fast(m7);
    muladd_fast(m12, SECP256K1_N_C_3);
    sumadd_fast(m11);
    extract_fast(p7);
    p8 = c0 + m12;
    VERIFY_CHECK(p8 <= 2);

    /* Reduce 258 bits into 256. */
    /* r[0..7] = p[0..7] + p[8] * SECP256K1_N_C. */
    c = p0 + (uint64_t)SECP256K1_N_C_0 * p8;
    r->d[0] = c & 0xFFFFFFFFUL; c >>= 32;
    c += p1 + (uint64_t)SECP256K1_N_C_1 * p8;
    r->d[1] = c & 0xFFFFFFFFUL; c >>= 32;
    c += p2 + (uint64_t)SECP256K1_N_C_2 * p8;
    r->d[2] = c & 0xFFFFFFFFUL; c >>= 32;
    c += p3 + (uint64_t)SECP256K1_N_C_3 * p8;
    r->d[3] = c & 0xFFFFFFFFUL; c >>= 32;
    c += p4 + (uint64_t)p8;
    r->d[4] = c & 0xFFFFFFFFUL; c >>= 32;
    c += p5;
    r->d[5] = c & 0xFFFFFFFFUL; c >>= 32;
    c += p6;
    r->d[6] = c & 0xFFFFFFFFUL; c >>= 32;
    c += p7;
    r->d[7] = c & 0xFFFFFFFFUL; c >>= 32;

    /* Final reduction of r. */
    secp256k1_scalar_reduce(r, c + secp256k1_scalar_check_overflow(r));
}

static void secp256k1_scalar_mul_512(uint32_t *l, const secp256k1_scalar *a, const secp256k1_scalar *b) {
    /* 96 bit accumulator. */
    uint32_t c0 = 0, c1 = 0, c2 = 0;

    /* l[0..15] = a[0..7] * b[0..7]. */
    muladd_fast(a->d[0], b->d[0]);
    extract_fast(l[0]);
    muladd(a->d[0], b->d[1]);
    muladd(a->d[1], b->d[0]);
    extract(l[1]);
    muladd(a->d[0], b->d[2]);
    muladd(a->d[1], b->d[1]);
    muladd(a->d[2], b->d[0]);
    extract(l[2]);
    muladd(a->d[0], b->d[3]);
    muladd(a->d[1], b->d[2]);
    muladd(a->d[2], b->d[1]);
    muladd(a->d[3], b->d[0]);
    extract(l[3]);
    muladd(a->d[0], b->d[4]);
    muladd(a->d[1], b->d[3]);
    muladd(a->d[2], b->d[2]);
    muladd(a->d[3], b->d[1]);
    muladd(a->d[4], b->d[0]);
    extract(l[4]);
    muladd(a->d[0], b->d[5]);
    muladd(a->d[1], b->d[4]);
    muladd(a->d[2], b->d[3]);
    muladd(a->d[3], b->d[2]);
    muladd(a->d[4], b->d[1]);
    muladd(a->d[5], b->d[0]);
    extract(l[5]);
    muladd(a->d[0], b->d[6]);
    muladd(a->d[1], b->d[5]);
    muladd(a->d[2], b->d[4]);
    muladd(a->d[3], b->d[3]);
    muladd(a->d[4], b->d[2]);
    muladd(a->d[5], b->d[1]);
    muladd(a->d[6], b->d[0]);
    extract(l[6]);
    muladd(a->d[0], b->d[7]);
    muladd(a->d[1], b->d[6]);
    muladd(a->d[2], b->d[5]);
    muladd(a->d[3], b->d[4]);
    muladd(a->d[4], b->d[3]);
    muladd(a->d[5], b->d[2]);
    muladd(a->d[6], b->d[1]);
    muladd(a->d[7], b->d[0]);
    extract(l[7]);
    muladd(a->d[1], b->d[7]);
    muladd(a->d[2], b->d[6]);
    muladd(a->d[3], b->d[5]);
    muladd(a->d[4], b->d[4]);
    muladd(a->d[5], b->d[3]);
    muladd(a->d[6], b->d[2]);
    muladd(a->d[7], b->d[1]);
    extract(l[8]);
    muladd(a->d[2], b->d[7]);
    muladd(a->d[3], b->d[6]);
    muladd(a->d[4], b->d[5]);
    muladd(a->d[5], b->d[4]);
    muladd(a->d[6], b->d[3]);
    muladd(a->d[7], b->d[2]);
    extract(l[9]);
    muladd(a->d[3], b->d[7]);
    muladd(a->d[4], b->d[6]);
    muladd(a->d[5], b->d[5]);
    muladd(a->d[6], b->d[4]);
    muladd(a->d[7], b->d[3]);
    extract(l[10]);
    muladd(a->d[4], b->d[7]);
    muladd(a->d[5], b->d[6]);
    muladd(a->d[6], b->d[5]);
    muladd(a->d[7], b->d[4]);
    extract(l[11]);
    muladd(a->d[5], b->d[7]);
    muladd(a->d[6], b->d[6]);
    muladd(a->d[7], b->d[5]);
    extract(l[12]);
    muladd(a->d[6], b->d[7]);
    muladd(a->d[7], b->d[6]);
    extract(l[13]);
    muladd_fast(a->d[7], b->d[7]);
    extract_fast(l[14]);
    VERIFY_CHECK(c1 == 0);
    l[15] = c0;
}

static void secp256k1_scalar_sqr_512(uint32_t *l, const secp256k1_scalar *a) {
    /* 96 bit accumulator. */
    uint32_t c0 = 0, c1 = 0, c2 = 0;

    /* l[0..15] = a[0..7]^2. */
    muladd_fast(a->d[0], a->d[0]);
    extract_fast(l[0]);
    muladd2(a->d[0], a->d[1]);
    extract(l[1]);
    muladd2(a->d[0], a->d[2]);
    muladd(a->d[1], a->d[1]);
    extract(l[2]);
    muladd2(a->d[0], a->d[3]);
    muladd2(a->d[1], a->d[2]);
    extract(l[3]);
    muladd2(a->d[0], a->d[4]);
    muladd2(a->d[1], a->d[3]);
    muladd(a->d[2], a->d[2]);
    extract(l[4]);
    muladd2(a->d[0], a->d[5]);
    muladd2(a->d[1], a->d[4]);
    muladd2(a->d[2], a->d[3]);
    extract(l[5]);
    muladd2(a->d[0], a->d[6]);
    muladd2(a->d[1], a->d[5]);
    muladd2(a->d[2], a->d[4]);
    muladd(a->d[3], a->d[3]);
    extract(l[6]);
    muladd2(a->d[0], a->d[7]);
    muladd2(a->d[1], a->d[6]);
    muladd2(a->d[2], a->d[5]);
    muladd2(a->d[3], a->d[4]);
    extract(l[7]);
    muladd2(a->d[1], a->d[7]);
    muladd2(a->d[2], a->d[6]);
    muladd2(a->d[3], a->d[5]);
    muladd(a->d[4], a->d[4]);
    extract(l[8]);
    muladd2(a->d[2], a->d[7]);
    muladd2(a->d[3], a->d[6]);
    muladd2(a->d[4], a->d[5]);
    extract(l[9]);
    muladd2(a->d[3], a->d[7]);
    muladd2(a->d[4], a->d[6]);
    muladd(a->d[5], a->d[5]);
    extract(l[10]);
    muladd2(a->d[4], a->d[7]);
    muladd2(a->d[5], a->d[6]);
    extract(l[11]);
    muladd2(a->d[5], a->d[7]);
    muladd(a->d[6], a->d[6]);
    extract(l[12]);
    muladd2(a->d[6], a->d[7]);
    extract(l[13]);
    muladd_fast(a->d[7], a->d[7]);
    extract_fast(l[14]);
    VERIFY_CHECK(c1 == 0);
    l[15] = c0;
}

#undef sumadd
#undef sumadd_fast
#undef muladd
#undef muladd_fast
#undef muladd2
#undef extract
#undef extract_fast

static void secp256k1_scalar_mul(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b) {
    uint32_t l[16];
    secp256k1_scalar_mul_512(l, a, b);
    secp256k1_scalar_reduce_512(r, l);
}

static int secp256k1_scalar_shr_int(secp256k1_scalar *r, int n) {
    int ret;
    VERIFY_CHECK(n > 0);
    VERIFY_CHECK(n < 16);
    ret = r->d[0] & ((1 << n) - 1);
    r->d[0] = (r->d[0] >> n) + (r->d[1] << (32 - n));
    r->d[1] = (r->d[1] >> n) + (r->d[2] << (32 - n));
    r->d[2] = (r->d[2] >> n) + (r->d[3] << (32 - n));
    r->d[3] = (r->d[3] >> n) + (r->d[4] << (32 - n));
    r->d[4] = (r->d[4] >> n) + (r->d[5] << (32 - n));
    r->d[5] = (r->d[5] >> n) + (r->d[6] << (32 - n));
    r->d[6] = (r->d[6] >> n) + (r->d[7] << (32 - n));
    r->d[7] = (r->d[7] >> n);
    return ret;
}

static void secp256k1_scalar_sqr(secp256k1_scalar *r, const secp256k1_scalar *a) {
    uint32_t l[16];
    secp256k1_scalar_sqr_512(l, a);
    secp256k1_scalar_reduce_512(r, l);
}

#ifdef USE_ENDOMORPHISM
static void secp256k1_scalar_split_128(secp256k1_scalar *r1, secp256k1_scalar *r2, const secp256k1_scalar *a) {
    r1->d[0] = a->d[0];
    r1->d[1] = a->d[1];
    r1->d[2] = a->d[2];
    r1->d[3] = a->d[3];
    r1->d[4] = 0;
    r1->d[5] = 0;
    r1->d[6] = 0;
    r1->d[7] = 0;
    r2->d[0] = a->d[4];
    r2->d[1] = a->d[5];
    r2->d[2] = a->d[6];
    r2->d[3] = a->d[7];
    r2->d[4] = 0;
    r2->d[5] = 0;
    r2->d[6] = 0;
    r2->d[7] = 0;
}
#endif

SECP256K1_INLINE static int secp256k1_scalar_eq(const secp256k1_scalar *a, const secp256k1_scalar *b) {
    return ((a->d[0] ^ b->d[0]) | (a->d[1] ^ b->d[1]) | (a->d[2] ^ b->d[2]) | (a->d[3] ^ b->d[3]) | (a->d[4] ^ b->d[4]) | (a->d[5] ^ b->d[5]) | (a->d[6] ^ b->d[6]) | (a->d[7] ^ b->d[7])) == 0;
}

SECP256K1_INLINE static void secp256k1_scalar_mul_shift_var(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b, unsigned int shift) {
    uint32_t l[16];
    unsigned int shiftlimbs;
    unsigned int shiftlow;
    unsigned int shifthigh;
    VERIFY_CHECK(shift >= 256);
    secp256k1_scalar_mul_512(l, a, b);
    shiftlimbs = shift >> 5;
    shiftlow = shift & 0x1F;
    shifthigh = 32 - shiftlow;
    r->d[0] = shift < 512 ? (l[0 + shiftlimbs] >> shiftlow | (shift < 480 && shiftlow ? (l[1 + shiftlimbs] << shifthigh) : 0)) : 0;
    r->d[1] = shift < 480 ? (l[1 + shiftlimbs] >> shiftlow | (shift < 448 && shiftlow ? (l[2 + shiftlimbs] << shifthigh) : 0)) : 0;
    r->d[2] = shift < 448 ? (l[2 + shiftlimbs] >> shiftlow | (shift < 416 && shiftlow ? (l[3 + shiftlimbs] << shifthigh) : 0)) : 0;
    r->d[3] = shift < 416 ? (l[3 + shiftlimbs] >> shiftlow | (shift < 384 && shiftlow ? (l[4 + shiftlimbs] << shifthigh) : 0)) : 0;
    r->d[4] = shift < 384 ? (l[4 + shiftlimbs] >> shiftlow | (shift < 352 && shiftlow ? (l[5 + shiftlimbs] << shifthigh) : 0)) : 0;
    r->d[5] = shift < 352 ? (l[5 + shiftlimbs] >> shiftlow | (shift < 320 && shiftlow ? (l[6 + shiftlimbs] << shifthigh) : 0)) : 0;
    r->d[6] = shift < 320 ? (l[6 + shiftlimbs] >> shiftlow | (shift < 288 && shiftlow ? (l[7 + shiftlimbs] << shifthigh) : 0)) : 0;
    r->d[7] = shift < 288 ? (l[7 + shiftlimbs] >> shiftlow)  : 0;
    secp256k1_scalar_cadd_bit(r, 0, (l[(shift - 1) >> 5] >> ((shift - 1) & 0x1f)) & 1);
}

static SECP256K1_INLINE void secp256k1_scalar_cmov(secp256k1_scalar *r, const secp256k1_scalar *a, int flag) {
    uint32_t mask0, mask1;
    VG_CHECK_VERIFY(r->d, sizeof(r->d));
    mask0 = flag + ~((uint32_t)0);
    mask1 = ~mask0;
    r->d[0] = (r->d[0] & mask0) | (a->d[0] & mask1);
    r->d[1] = (r->d[1] & mask0) | (a->d[1] & mask1);
    r->d[2] = (r->d[2] & mask0) | (a->d[2] & mask1);
    r->d[3] = (r->d[3] & mask0) | (a->d[3] & mask1);
    r->d[4] = (r->d[4] & mask0) | (a->d[4] & mask1);
    r->d[5] = (r->d[5] & mask0) | (a->d[5] & mask1);
    r->d[6] = (r->d[6] & mask0) | (a->d[6] & mask1);
    r->d[7] = (r->d[7] & mask0) | (a->d[7] & mask1);
}

static const secp256k1_scalar SECP256K1_SCALAR_NEG_TWO_POW_256 = SECP256K1_SCALAR_CONST(
    0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFDUL,
    0x755DB9CDUL, 0x5E914077UL, 0x7FA4BD19UL, 0xA06C8282UL
);

static const secp256k1_scalar SECP256K1_SCALAR_TWO_POW_744 = SECP256K1_SCALAR_CONST(
    0x4E165355UL, 0x5D800C18UL, 0xEF116DB1UL, 0xB31347F1UL,
    0x6D77C2DCUL, 0x0E3E8029UL, 0x59BA208FUL, 0xFD01F4F7UL
);

static void secp256k1_scalar_mul_add_2(int32_t a0, int32_t a1, int32_t b0, int32_t b1, int32_t c0, int32_t c1, int32_t d0, int32_t d1, int32_t *t) {

    /*  Each [a0,a1], etc. pair is a ??-bit signed value e.g. a0 + a1 * 2^32.
     *  This method calculates ([a0,a1] * [c0,c1]) + ([b0,b1] * [d0,d1]), and
     *  writes the ???-bit signed result to [t[0],t[1],t[2],t[3]].
     */

    int32_t z0, z1, z2, z3;
    int64_t tt;

    tt  = (int64_t)a0 * b0
        + (int64_t)c0 * d0;
    z0  = (int32_t)tt; tt -= z0; tt >>= 32;

    tt += (int64_t)a0 * b1
        + (int64_t)a1 * b0
        + (int64_t)c0 * d1
        + (int64_t)c1 * d0;
    z1  = (int32_t)tt; tt -= z1; tt >>= 32;

    tt += (int64_t)a1 * b1
        + (int64_t)c1 * d1;
    z2  = (int32_t)tt; tt -= z2; tt >>= 32;

    z3 = (int32_t)tt;

    t[0] = z0; t[1] = z1; t[2] = z2; t[3] = z3;
}

static void secp256k1_scalar_mul_add_4(int32_t* tIn, int xPos, int yPos, int uPos, int vPos, int32_t *tOut, int zzPos) {
    int32_t y0 = tIn[yPos + 0];
    int32_t y1 = tIn[yPos + 1];
    int32_t y2 = tIn[yPos + 2];
    int32_t y3 = tIn[yPos + 3];
    int32_t v0 = tIn[vPos + 0];
    int32_t v1 = tIn[vPos + 1];
    int32_t v2 = tIn[vPos + 2];
    int32_t v3 = tIn[vPos + 3];
    int32_t xVal, uVal;
    int32_t z0, z1, z2, z3, z4, z5, z6, z7;
    int64_t c;

    xVal = tIn[xPos];
    uVal = tIn[uPos];

    c  = (int64_t)xVal * y0 + (int64_t)uVal * v0;
    z0 = (int32_t)c; c -= z0; c >>= 32;

    c += (int64_t)xVal * y1 + (int64_t)uVal * v1;
    z1 = (int32_t)c; c -= z1; c >>= 32;

    c += (int64_t)xVal * y2 + (int64_t)uVal * v2;
    z2 = (int32_t)c; c -= z2; c >>= 32;

    c += (int64_t)xVal * y3 + (int64_t)uVal * v3;
    z3 = (int32_t)c; c -= z3; c >>= 32;
    z4 = (int32_t)c;

    xVal = tIn[xPos + 1];
    uVal = tIn[uPos + 1];

    c  = (int64_t)xVal * y0 + (int64_t)uVal * v0 + z1;
    z1 = (int32_t)c; c -= z1; c >>= 32;

    c += (int64_t)xVal * y1 + (int64_t)uVal * v1 + z2;
    z2 = (int32_t)c; c -= z2; c >>= 32;

    c += (int64_t)xVal * y2 + (int64_t)uVal * v2 + z3;
    z3 = (int32_t)c; c -= z3; c >>= 32;

    c += (int64_t)xVal * y3 + (int64_t)uVal * v3 + z4;
    z4 = (int32_t)c; c -= z4; c >>= 32;
    z5 = (int32_t)c;

    xVal = tIn[xPos + 2];
    uVal = tIn[uPos + 2];

    c  = (int64_t)xVal * y0 + (int64_t)uVal * v0 + z2;
    z2 = (int32_t)c; c -= z2; c >>= 32;

    c += (int64_t)xVal * y1 + (int64_t)uVal * v1 + z3;
    z3 = (int32_t)c; c -= z3; c >>= 32;

    c += (int64_t)xVal * y2 + (int64_t)uVal * v2 + z4;
    z4 = (int32_t)c; c -= z4; c >>= 32;

    c += (int64_t)xVal * y3 + (int64_t)uVal * v3 + z5;
    z5 = (int32_t)c; c -= z5; c >>= 32;
    z6 = (int32_t)c;

    xVal = tIn[xPos + 3];
    uVal = tIn[uPos + 3];

    c  = (int64_t)xVal * y0 + (int64_t)uVal * v0 + z3;
    z3 = (int32_t)c; c -= z3; c >>= 32;

    c += (int64_t)xVal * y1 + (int64_t)uVal * v1 + z4;
    z4 = (int32_t)c; c -= z4; c >>= 32;

    c += (int64_t)xVal * y2 + (int64_t)uVal * v2 + z5;
    z5 = (int32_t)c; c -= z5; c >>= 32;

    c += (int64_t)xVal * y3 + (int64_t)uVal * v3 + z6;
    z6 = (int32_t)c; c -= z6; c >>= 32;
    z7 = (int32_t)c;

    tOut[zzPos + 0] = z0;
    tOut[zzPos + 1] = z1;
    tOut[zzPos + 2] = z2;
    tOut[zzPos + 3] = z3;
    tOut[zzPos + 4] = z4;
    tOut[zzPos + 5] = z5;
    tOut[zzPos + 6] = z6;
    tOut[zzPos + 7] = z7;
}

static void secp256k1_scalar_combine_1s(int32_t *t) {

    int32_t a = t[0], b = t[1], c = t[2], d = t[3],
            e = t[4], f = t[5], g = t[6], h = t[7];
    int64_t I, J, K, L;

    I = (int64_t)e * a + (int64_t)f * c;
    J = (int64_t)e * b + (int64_t)f * d;
    K = (int64_t)g * a + (int64_t)h * c;
    L = (int64_t)g * b + (int64_t)h * d;

    a = (int32_t)I; I -= a; I >>= 32; b = (int32_t)I;
    c = (int32_t)J; J -= c; J >>= 32; d = (int32_t)J;
    e = (int32_t)K; K -= e; K >>= 32; f = (int32_t)K;
    g = (int32_t)L; L -= g; L >>= 32; h = (int32_t)L;

    t[0] = a; t[1] = b; t[2] = c; t[3] = d;
    t[4] = e; t[5] = f; t[6] = g; t[7] = h;
}

static void secp256k1_scalar_combine_2s(int32_t *t) {

    int32_t a0 = t[ 0], a1 = t[ 1];
    int32_t b0 = t[ 2], b1 = t[ 3];
    int32_t c0 = t[ 4], c1 = t[ 5];
    int32_t d0 = t[ 6], d1 = t[ 7];
    int32_t e0 = t[ 8], e1 = t[ 9];
    int32_t f0 = t[10], f1 = t[11];
    int32_t g0 = t[12], g1 = t[13];
    int32_t h0 = t[14], h1 = t[15];

    secp256k1_scalar_mul_add_2(e0, e1, a0, a1, f0, f1, c0, c1, &t[0]);
    secp256k1_scalar_mul_add_2(e0, e1, b0, b1, f0, f1, d0, d1, &t[4]);
    secp256k1_scalar_mul_add_2(g0, g1, a0, a1, h0, h1, c0, c1, &t[8]);
    secp256k1_scalar_mul_add_2(g0, g1, b0, b1, h0, h1, d0, d1, &t[12]);
}

static void secp256k1_scalar_combine_4s(int32_t *t)
{
    int32_t tmp[32];

    int aPos = 0;
    int bPos = 4;
    int cPos = 8;
    int dPos = 12;
    int ePos = 16;
    int fPos = 20;
    int gPos = 24;
    int hPos = 28;

    int IPos = 0;
    int JPos = 8;
    int KPos = 16;
    int LPos = 24;

    secp256k1_scalar_mul_add_4(t, ePos, aPos, fPos, cPos, tmp, IPos);
    secp256k1_scalar_mul_add_4(t, ePos, bPos, fPos, dPos, tmp, JPos);
    secp256k1_scalar_mul_add_4(t, gPos, aPos, hPos, cPos, tmp, KPos);
    secp256k1_scalar_mul_add_4(t, gPos, bPos, hPos, dPos, tmp, LPos);

    memcpy(t, tmp, 32 * sizeof(int32_t));
}

static void secp256k1_scalar_decode_matrix(secp256k1_scalar *r, int32_t *t) {

    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
    int flag;
    secp256k1_scalar u;
    int64_t cc;

    cc  = t[0];
    r0  = (uint32_t)cc; cc >>= 32;
    cc += t[1];
    r1  = (uint32_t)cc; cc >>= 32;
    cc += t[2];
    r2  = (uint32_t)cc; cc >>= 32;
    cc += t[3];
    r3  = (uint32_t)cc; cc >>= 32;
    cc += t[4];
    r4  = (uint32_t)cc; cc >>= 32;
    cc += t[5];
    r5  = (uint32_t)cc; cc >>= 32;
    cc += t[6];
    r6  = (uint32_t)cc; cc >>= 32;
    cc += t[7];
    r7  = (uint32_t)cc; cc >>= 32;

    VERIFY_CHECK(cc == 0 || cc == -1);

    flag = (int)cc & 1;

    r->d[0] = r0;
    r->d[1] = r1;
    r->d[2] = r2;
    r->d[3] = r3;
    r->d[4] = r4;
    r->d[5] = r5;
    r->d[6] = r6;
    r->d[7] = r7;

    secp256k1_scalar_add(&u, r, &SECP256K1_SCALAR_NEG_TWO_POW_256);
    secp256k1_scalar_cmov(r, &u, flag);
}

static void secp256k1_scalar_encode_31(int32_t *r, const secp256k1_scalar *a) {

    const uint32_t M31 = UINT32_MAX >> 1;
    const uint32_t *d = &a->d[0];
    uint32_t a0 = d[0], a1 = d[1], a2 = d[2], a3 = d[3],
             a4 = d[4], a5 = d[5], a6 = d[6], a7 = d[7];

#ifdef VERIFY
    VERIFY_CHECK(secp256k1_scalar_check_overflow(a) == 0);
#endif

    r[0] =  a0                   & M31;
    r[1] = (a0 >> 31 | a1 <<  1) & M31;
    r[2] = (a1 >> 30 | a2 <<  2) & M31;
    r[3] = (a2 >> 29 | a3 <<  3) & M31;
    r[4] = (a3 >> 28 | a4 <<  4) & M31;
    r[5] = (a4 >> 27 | a5 <<  5) & M31;
    r[6] = (a5 >> 26 | a6 <<  6) & M31;
    r[7] = (a6 >> 25 | a7 <<  7) & M31;
    r[8] =  a7 >> 24;

#ifdef VERIFY
    VERIFY_CHECK(secp256k1_scalar_check_overflow(a) == 0);
#endif
}

static int secp256k1_scalar_divsteps_31(uint16_t eta, uint32_t f0, uint32_t g0, int32_t *t) {

    uint32_t u = -(uint32_t)1, v = 0, q = 0, r = -(uint32_t)1;
    uint32_t c1, c2, f = f0, g = g0, x, y, z;
    int i;

    for (i = 0; i < 31; ++i) {

        VERIFY_CHECK((f & 1) == 1);
        VERIFY_CHECK((u * f0 + v * g0) == -f << i);
        VERIFY_CHECK((q * f0 + r * g0) == -g << i);

        c1 = -(g & (eta >> 15));

        x = (f ^ g) & c1;
        f ^= x; g ^= x; g ^= c1; g -= c1;

        y = (u ^ q) & c1;
        u ^= y; q ^= y; q ^= c1; q -= c1;

        z = (v ^ r) & c1;
        v ^= z; r ^= z; r ^= c1; r -= c1;

        eta = (eta ^ (uint16_t)c1) - (uint16_t)c1 - 1;

        c2 = -(g & 1);

        g += (f & c2); g >>= 1;
        q += (u & c2); u <<= 1;
        r += (v & c2); v <<= 1;
    }

    t[0] = (int32_t)u;
    t[1] = (int32_t)v;
    t[2] = (int32_t)q;
    t[3] = (int32_t)r;

    return eta;
}

static void secp256k1_scalar_update_fg(int32_t *f, int32_t *g, int32_t *t) {

    const int32_t M31 = (int32_t)(UINT32_MAX >> 1);
    int32_t u = t[0], v = t[1], q = t[2], r = t[3], fi, gi;
    int64_t cf = 0, cg = 0;
    int i;

    fi = f[0];
    gi = g[0];

    cf -= (int64_t)u * fi + (int64_t)v * gi;
    cg -= (int64_t)q * fi + (int64_t)r * gi;

    VERIFY_CHECK(((int32_t)cf & M31) == 0);
    VERIFY_CHECK(((int32_t)cg & M31) == 0);

    cf >>= 31;
    cg >>= 31;

    for (i = 1; i < 9; ++i) {

        fi = f[i];
        gi = g[i];

        cf -= (int64_t)u * fi + (int64_t)v * gi;
        cg -= (int64_t)q * fi + (int64_t)r * gi;

        f[i - 1] = (int32_t)cf & M31; cf >>= 31;
        g[i - 1] = (int32_t)cg & M31; cg >>= 31;
    }

    f[8] = (int32_t)cf;
    g[8] = (int32_t)cg;
}

static void secp256k1_scalar_inverse(secp256k1_scalar *r, const secp256k1_scalar *x) {
#if defined(EXHAUSTIVE_TEST_ORDER)
    int i;
    *r = 0;
    for (i = 0; i < EXHAUSTIVE_TEST_ORDER; i++)
        if ((i * *x) % EXHAUSTIVE_TEST_ORDER == 1)
            *r = i;
    /* If this VERIFY_CHECK triggers we were given a noninvertible scalar (and thus
     * have a composite group order; fix it in exhaustive_tests.c). */
    VERIFY_CHECK(*r != 0);
}
#elif 1

    /* Modular inversion based on the paper "Fast constant-time gcd computation and
     * modular inversion" by Daniel J. Bernstein and Bo-Yin Yang.
     */

    int32_t t[24 * 4];
    int32_t f[9] = { 0x50364141L, 0x7FA4BD19L, 0x3D2280EEL, 0x5576E735L, 0x7FFFFFEBL,
        0x7FFFFFFFL, 0x7FFFFFFFL, 0x7FFFFFFFL, 0xFFL };
    int32_t g[9];
    secp256k1_scalar b0, d0, a1, b1, c1, d1;
    int i, sign;
    int16_t eta;
#ifdef VERIFY
    int zero_in = secp256k1_scalar_is_zero(x);
#endif

    /* Instead of dividing the output by 2^744, scale the input. */
    secp256k1_scalar_mul(&b0, x, &SECP256K1_SCALAR_TWO_POW_744);
    secp256k1_scalar_encode_31(g, &b0);

    /* The paper uses 'delta'; eta == -delta (a performance tweak). */
    eta = -1;

    for (i = 0; i < 24; ++i) {
        eta = secp256k1_scalar_divsteps_31(eta, f[0], g[0], &t[i * 4]);
        secp256k1_scalar_update_fg(f, g, &t[i * 4]);
    }

    /* At this point sufficient iterations have been performed that g must have reached 0
     * and (if g was not originally 0) f must now equal +/- GCD of the initial f, g
     * values i.e. +/- 1. The matrix outputs from each _divstep_31 are combined to get the
     * Bézout coefficients, and thus the modular inverse. The matrix outputs of
     * _divstep_31 introduce an extra factor of 2^31 each, so there is a total extra
     * factor of 2^744 to account for (by scaling the input and/or output accordingly).
     */

    VERIFY_CHECK(g[0] == 0);

    sign = (f[0] >> 1) & 1;

    for (i = 0; i < 3; ++i) {
        int tOff = i * 32;
        secp256k1_scalar_combine_1s(&t[tOff +  0]);
        secp256k1_scalar_combine_1s(&t[tOff +  8]);
        secp256k1_scalar_combine_1s(&t[tOff + 16]);
        secp256k1_scalar_combine_1s(&t[tOff + 24]);
        secp256k1_scalar_combine_2s(&t[tOff +  0]);
        secp256k1_scalar_combine_2s(&t[tOff + 16]);
        secp256k1_scalar_combine_4s(&t[tOff +  0]);
    }

    /* secp256k1_scalar_decode_matrix(&a0, &t[0]); */
    secp256k1_scalar_decode_matrix(&b0, &t[8]);
    /* secp256k1_scalar_decode_matrix(&c0, &t[16]); */
    secp256k1_scalar_decode_matrix(&d0, &t[24]);

    secp256k1_scalar_decode_matrix(&a1, &t[32]);
    secp256k1_scalar_decode_matrix(&b1, &t[40]);
    secp256k1_scalar_decode_matrix(&c1, &t[48]);
    secp256k1_scalar_decode_matrix(&d1, &t[56]);

    secp256k1_scalar_mul(&a1, &a1, &b0);
    secp256k1_scalar_mul(&b1, &b1, &d0);
    secp256k1_scalar_mul(&c1, &c1, &b0);
    secp256k1_scalar_mul(&d1, &d1, &d0);

    secp256k1_scalar_add(&b0, &a1, &b1);
    secp256k1_scalar_add(&d0, &c1, &d1);

    secp256k1_scalar_decode_matrix(&a1, &t[64]);
    secp256k1_scalar_decode_matrix(&b1, &t[72]);
    /* secp256k1_scalar_decode_matrix(&c1, &t[80]); */
    /* secp256k1_scalar_decode_matrix(&d1, &t[88]); */

    secp256k1_scalar_mul(&a1, &a1, &b0);
    secp256k1_scalar_mul(&b1, &b1, &d0);
    /* secp256k1_scalar_mul(&c1, &c1, &b0); */
    /* secp256k1_scalar_mul(&d1, &d1, &d0); */

    secp256k1_scalar_add(&b0, &a1, &b1);
    /* secp256k1_scalar_add(&d0, &c1, &d1); */

    secp256k1_scalar_cond_negate(&b0, sign);

#ifdef VERIFY
    VERIFY_CHECK(!secp256k1_scalar_is_zero(&b0) == !zero_in);
#endif

    *r = b0;
}

SECP256K1_INLINE static int secp256k1_scalar_is_even(const secp256k1_scalar *a) {
    return !(a->d[0] & 1);
}
#else
    secp256k1_scalar *t;
    int i;
    /* First compute xN as x ^ (2^N - 1) for some values of N,
     * and uM as x ^ M for some values of M. */
    secp256k1_scalar x2, x3, x6, x8, x14, x28, x56, x112, x126;
    secp256k1_scalar u2, u5, u9, u11, u13;

    secp256k1_scalar_sqr(&u2, x);
    secp256k1_scalar_mul(&x2, &u2,  x);
    secp256k1_scalar_mul(&u5, &u2, &x2);
    secp256k1_scalar_mul(&x3, &u5,  &u2);
    secp256k1_scalar_mul(&u9, &x3, &u2);
    secp256k1_scalar_mul(&u11, &u9, &u2);
    secp256k1_scalar_mul(&u13, &u11, &u2);

    secp256k1_scalar_sqr(&x6, &u13);
    secp256k1_scalar_sqr(&x6, &x6);
    secp256k1_scalar_mul(&x6, &x6, &u11);

    secp256k1_scalar_sqr(&x8, &x6);
    secp256k1_scalar_sqr(&x8, &x8);
    secp256k1_scalar_mul(&x8, &x8,  &x2);

    secp256k1_scalar_sqr(&x14, &x8);
    for (i = 0; i < 5; i++) {
        secp256k1_scalar_sqr(&x14, &x14);
    }
    secp256k1_scalar_mul(&x14, &x14, &x6);

    secp256k1_scalar_sqr(&x28, &x14);
    for (i = 0; i < 13; i++) {
        secp256k1_scalar_sqr(&x28, &x28);
    }
    secp256k1_scalar_mul(&x28, &x28, &x14);

    secp256k1_scalar_sqr(&x56, &x28);
    for (i = 0; i < 27; i++) {
        secp256k1_scalar_sqr(&x56, &x56);
    }
    secp256k1_scalar_mul(&x56, &x56, &x28);

    secp256k1_scalar_sqr(&x112, &x56);
    for (i = 0; i < 55; i++) {
        secp256k1_scalar_sqr(&x112, &x112);
    }
    secp256k1_scalar_mul(&x112, &x112, &x56);

    secp256k1_scalar_sqr(&x126, &x112);
    for (i = 0; i < 13; i++) {
        secp256k1_scalar_sqr(&x126, &x126);
    }
    secp256k1_scalar_mul(&x126, &x126, &x14);

    /* Then accumulate the final result (t starts at x126). */
    t = &x126;
    for (i = 0; i < 3; i++) {
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u5); /* 101 */
    for (i = 0; i < 4; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x3); /* 111 */
    for (i = 0; i < 4; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u5); /* 101 */
    for (i = 0; i < 5; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u11); /* 1011 */
    for (i = 0; i < 4; i++) {
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u11); /* 1011 */
    for (i = 0; i < 4; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x3); /* 111 */
    for (i = 0; i < 5; i++) { /* 00 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x3); /* 111 */
    for (i = 0; i < 6; i++) { /* 00 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u13); /* 1101 */
    for (i = 0; i < 4; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u5); /* 101 */
    for (i = 0; i < 3; i++) {
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x3); /* 111 */
    for (i = 0; i < 5; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u9); /* 1001 */
    for (i = 0; i < 6; i++) { /* 000 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u5); /* 101 */
    for (i = 0; i < 10; i++) { /* 0000000 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x3); /* 111 */
    for (i = 0; i < 4; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x3); /* 111 */
    for (i = 0; i < 9; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x8); /* 11111111 */
    for (i = 0; i < 5; i++) { /* 0 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u9); /* 1001 */
    for (i = 0; i < 6; i++) { /* 00 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u11); /* 1011 */
    for (i = 0; i < 4; i++) {
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u13); /* 1101 */
    for (i = 0; i < 5; i++) {
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &x2); /* 11 */
    for (i = 0; i < 6; i++) { /* 00 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u13); /* 1101 */
    for (i = 0; i < 10; i++) { /* 000000 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u13); /* 1101 */
    for (i = 0; i < 4; i++) {
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, &u9); /* 1001 */
    for (i = 0; i < 6; i++) { /* 00000 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(t, t, x); /* 1 */
    for (i = 0; i < 8; i++) { /* 00 */
        secp256k1_scalar_sqr(t, t);
    }
    secp256k1_scalar_mul(r, t, &x6); /* 111111 */
}

SECP256K1_INLINE static int secp256k1_scalar_is_even(const secp256k1_scalar *a) {
    return !(a->d[0] & 1);
}
#endif

#endif /* SECP256K1_SCALAR_REPR_IMPL_H */
