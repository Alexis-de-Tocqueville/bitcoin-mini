/*****************************************************************************************************
 * Copyright (c) 2013, 2014, 2017, 2021 Pieter Wuille, Andrew Poelstra, Jonas Nick, Russell O'Connor *
 * Distributed under the MIT software license, see the accompanying                                  *
 * file COPYING or https://www.opensource.org/licenses/mit-license.php.                              *
 *****************************************************************************************************/

#include <inttypes.h>
#include <stdio.h>

/* Autotools creates libsecp256k1-config.h, of which ECMULT_WINDOW_SIZE is needed.
   ifndef guard so downstream users can define their own if they do not use autotools. */
#if !defined(ECMULT_WINDOW_SIZE)
#include "libsecp256k1-config.h"
#endif

#include "../include/secp256k1.h"
#include "assumptions.h"
#include "util.h"
#include "field_impl.h"
#include "group_impl.h"
#include "ecmult.h"

static void precompute_ecmult_print_table(FILE *fp, const char *name, int window_g, const secp256k1_gej *gen, int with_conditionals) {
    secp256k1_gej gj;
    secp256k1_ge ge, dgen;
    secp256k1_ge_storage ges;
    int j;
    int i;

    gj = *gen;
    secp256k1_ge_set_gej_var(&ge, &gj);
    secp256k1_ge_to_storage(&ges, &ge);

    fprintf(fp, "static const secp256k1_ge_storage %s[ECMULT_TABLE_SIZE(WINDOW_G)] = {\n", name);
    fprintf(fp, " S(%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32
                  ",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32")\n",
                SECP256K1_GE_STORAGE_CONST_GET(ges));

    secp256k1_gej_double_var(&gj, gen, NULL);
    secp256k1_ge_set_gej_var(&dgen, &gj);

    j = 1;
    for(i = 3; i <= window_g; ++i) {
        if (with_conditionals) {
            fprintf(fp, "#if ECMULT_TABLE_SIZE(WINDOW_G) > %ld\n", ECMULT_TABLE_SIZE(i-1));
        }
        for(;j < ECMULT_TABLE_SIZE(i); ++j) {
            secp256k1_gej_set_ge(&gj, &ge);
            secp256k1_gej_add_ge_var(&gj, &gj, &dgen, NULL);
            secp256k1_ge_set_gej_var(&ge, &gj);
            secp256k1_ge_to_storage(&ges, &ge);

            fprintf(fp, ",S(%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32
                          ",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32")\n",
                        SECP256K1_GE_STORAGE_CONST_GET(ges));
        }
        if (with_conditionals) {
            fprintf(fp, "#endif\n");
        }
    }
    fprintf(fp, "};\n");
}

static void precompute_ecmult_print_two_tables(FILE *fp, int window_g, const secp256k1_ge *g, int with_conditionals) {
    secp256k1_gej gj;
    int i;

    secp256k1_gej_set_ge(&gj, g);
    precompute_ecmult_print_table(fp, "secp256k1_pre_g", window_g, &gj, with_conditionals);
    for (i = 0; i < 128; ++i) {
        secp256k1_gej_double_var(&gj, &gj, NULL);
    }
    precompute_ecmult_print_table(fp, "secp256k1_pre_g_128", window_g, &gj, with_conditionals);
}

static int precompute_ecmult(void) {
    const secp256k1_ge g = SECP256K1_G;
    const secp256k1_ge g_13 = SECP256K1_G_ORDER_13;
    const secp256k1_ge g_199 = SECP256K1_G_ORDER_199;
    const int window_g_13 = 4;
    const int window_g_199 = 8;
    FILE* fp;

    fp = fopen("src/ecmult_static_pre_g.h","w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open src/ecmult_static_pre_g.h for writing!\n");
        return -1;
    }

    fprintf(fp, "/* This file was automatically generated by gen_ecmult_static_pre_g. */\n");
    fprintf(fp, "/* This file contains an array secp256k1_pre_g with odd multiples of the base point G and\n");
    fprintf(fp, " * an array secp256k1_pre_g_128 with odd multiples of 2^128*G for accelerating the computation of a*P + b*G.\n");
    fprintf(fp, " */\n");
    fprintf(fp, "#ifndef SECP256K1_ECMULT_STATIC_PRE_G_H\n");
    fprintf(fp, "#define SECP256K1_ECMULT_STATIC_PRE_G_H\n");
    fprintf(fp, "#include \"group.h\"\n");
    fprintf(fp, "#ifdef S\n");
    fprintf(fp, "   #error macro identifier S already in use.\n");
    fprintf(fp, "#endif\n");
    fprintf(fp, "#define S(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) "
                "SECP256K1_GE_STORAGE_CONST(0x##a##u,0x##b##u,0x##c##u,0x##d##u,0x##e##u,0x##f##u,0x##g##u,"
                "0x##h##u,0x##i##u,0x##j##u,0x##k##u,0x##l##u,0x##m##u,0x##n##u,0x##o##u,0x##p##u)\n");
    fprintf(fp, "#if ECMULT_TABLE_SIZE(ECMULT_WINDOW_SIZE) > %ld\n", ECMULT_TABLE_SIZE(ECMULT_WINDOW_SIZE));
    fprintf(fp, "   #error configuration mismatch, invalid ECMULT_WINDOW_SIZE. Try deleting ecmult_static_pre_g.h before the build.\n");
    fprintf(fp, "#endif\n");
    fprintf(fp, "#if defined(EXHAUSTIVE_TEST_ORDER)\n");
    fprintf(fp, "#if EXHAUSTIVE_TEST_ORDER == 13\n");
    fprintf(fp, "#define WINDOW_G %d\n", window_g_13);

    precompute_ecmult_print_two_tables(fp, window_g_13, &g_13, 0);

    fprintf(fp, "#elif EXHAUSTIVE_TEST_ORDER == 199\n");
    fprintf(fp, "#define WINDOW_G %d\n", window_g_199);

    precompute_ecmult_print_two_tables(fp, window_g_199, &g_199, 0);

    fprintf(fp, "#else\n");
    fprintf(fp, "   #error No known generator for the specified exhaustive test group order.\n");
    fprintf(fp, "#endif\n");
    fprintf(fp, "#else /* !defined(EXHAUSTIVE_TEST_ORDER) */\n");
    fprintf(fp, "#define WINDOW_G ECMULT_WINDOW_SIZE\n");

    precompute_ecmult_print_two_tables(fp, ECMULT_WINDOW_SIZE, &g, 1);

    fprintf(fp, "#endif\n");
    fprintf(fp, "#undef S\n");
    fprintf(fp, "#endif\n");
    fclose(fp);
    return 0;
}

int main(void) {
    return precompute_ecmult();
}
