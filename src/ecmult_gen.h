/***********************************************************************
 * Copyright (c) 2013, 2014, 2021 Pieter Wuille, Peter Dettman         *
 * Distributed under the MIT software license, see the accompanying    *
 * file COPYING or https://www.opensource.org/licenses/mit-license.php.*
 ***********************************************************************/

#ifndef SECP256K1_ECMULT_GEN_H
#define SECP256K1_ECMULT_GEN_H

#include "scalar.h"
#include "group.h"

/* Configuration parameters for the signed-digit multi-comb algorithm:
 *
 * - COMB_BLOCKS is the number of lookup tables.
 * - COMB_TEETH is the number of bits covered by one table.
 *
 * The comb's spacing (COMB_SPACING), or the distance between the teeth,
 * is defined as ceil(256 / (COMB_BLOCKS * COMB_TEETH)).
 *
 * The size of the precomputed table is COMB_BLOCKS * (1 << (COMB_TEETH - 1))
 * secp256k1_ge_storages.
 *
 * The number of point additions equals COMB_BLOCKS * COMB_SPACING. Each point
 * addition involves a cmov from (1 << (COMB_TEETH - 1)) table entries and a
 * conditional negation.
 *
 * The number of point doublings is COMB_SPACING - 1. */

#if defined(EXHAUSTIVE_TEST_ORDER)
/* We need to control these values for exhaustive tests because
 * the tables cannot have infinities in them (secp256k1_ge_storage
 * doesn't support infinities) */
#  undef COMB_BLOCKS
#  undef COMB_TEETH
#  if EXHAUSTIVE_TEST_ORDER > 32
#    define COMB_BLOCKS 52
#    define COMB_TEETH 5
#  elif EXHAUSTIVE_TEST_ORDER > 16
#    define COMB_BLOCKS 64
#    define COMB_TEETH 4
#  elif EXHAUSTIVE_TEST_ORDER > 8
#    define COMB_BLOCKS 86
#    define COMB_TEETH 3
#  elif EXHAUSTIVE_TEST_ORDER > 4
#    define COMB_BLOCKS 128
#    define COMB_TEETH 2
#  else
#    define COMB_BLOCKS 256
#    define COMB_TEETH 1
#  endif
#else /* !defined(EXHAUSTIVE_TEST_ORDER) */
/* Use (11, 6) as default configuration, which results in a 22 kB table. */
#  ifndef COMB_BLOCKS
#    define COMB_BLOCKS 11
#  endif
#  ifndef COMB_TEETH
#    define COMB_TEETH 6
#  endif
#endif /* defined(EXHAUSTIVE_TEST_ORDER) */

/* Range checks on the parameters. */
#if !(1 <= COMB_BLOCKS && COMB_BLOCKS <= 256)
#  error "COMB_BLOCKS must be in the range [1, 256]"
#endif
#if !(1 <= COMB_TEETH && COMB_TEETH <= 8)
#  error "COMB_TEETH must be in the range [1, 8]"
#endif

/* The remaining COMB_* parameters are derived values, don't modify these. */
/* - The distance between the teeth of the comb. */
#define COMB_SPACING ((255 + COMB_BLOCKS * COMB_TEETH) / (COMB_BLOCKS * COMB_TEETH))
/* - The number of bits covered by all the combs; must be at least 256. */
#define COMB_BITS (COMB_BLOCKS * COMB_TEETH * COMB_SPACING)
/* - The number of points per table. */
#define COMB_POINTS (1 << (COMB_TEETH - 1))

/* Additional sanity checks. */
#if (COMB_BLOCKS - 1) * COMB_TEETH * COMB_SPACING >= 256
#  error "COMB_BLOCKS can be reduced"
#endif
#if COMB_BLOCKS * (COMB_TEETH - 1) * COMB_SPACING >= 256
#  error "COMB_TEETH can be reduced"
#endif

typedef struct {
    /* Whether the context has been built. */
    int built;

    /* Blinding values used when computing nG as (n-b)G + bG. */
    secp256k1_scalar scalar_offset; /* -b */
    secp256k1_ge final_point_add;  /* bG */
} secp256k1_ecmult_gen_context;

static void secp256k1_ecmult_gen_context_build(secp256k1_ecmult_gen_context* ctx);
static void secp256k1_ecmult_gen_context_clear(secp256k1_ecmult_gen_context* ctx);

/** Multiply with the generator: R = a*G */
static void secp256k1_ecmult_gen(const secp256k1_ecmult_gen_context* ctx, secp256k1_gej *r, const secp256k1_scalar *a);

static void secp256k1_ecmult_gen_blind(secp256k1_ecmult_gen_context *ctx, const unsigned char *seed32);

#endif /* SECP256K1_ECMULT_GEN_H */
