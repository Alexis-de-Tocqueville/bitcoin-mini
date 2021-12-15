/******************************************************************************
 * Copyright (c) 2013, 2014, 2015, 2017, 2021 Pieter Wuille, Andrew Poelstra, *
 * Jonas Nick, Russell O'Connor, Thomas Daede, Cory Fields.                   *
 * Distributed under the MIT software license, see the accompanying           *
 * file COPYING or https://www.opensource.org/licenses/mit-license.php.       *
 ******************************************************************************/

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

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
#include "ecmult_gen.h"
#include "ecmult_gen_prec_impl.h"

static void secp256k1_ecmult_create_prec_table(secp256k1_ge_storage* table, int window_g, const secp256k1_gej* gen) {
    secp256k1_gej gj;
    secp256k1_ge ge, dgen;
    int j;

    gj = *gen;
    secp256k1_ge_set_gej_var(&ge, &gj);
    secp256k1_ge_to_storage(&table[0], &ge);

    secp256k1_gej_double_var(&gj, gen, NULL);
    secp256k1_ge_set_gej_var(&dgen, &gj);

    for (j = 1; j < ECMULT_TABLE_SIZE(window_g); ++j) {
        secp256k1_gej_set_ge(&gj, &ge);
        secp256k1_gej_add_ge_var(&gj, &gj, &dgen, NULL);
        secp256k1_ge_set_gej_var(&ge, &gj);
        secp256k1_ge_to_storage(&table[j], &ge);
    }
}

static void secp256k1_ecmult_create_prec_two_tables(secp256k1_ge_storage* table, secp256k1_ge_storage* table_128, int window_g, const secp256k1_ge* gen) {
    secp256k1_gej gj;
    int i;

    secp256k1_gej_set_ge(&gj, gen);
    secp256k1_ecmult_create_prec_table(table, window_g, &gj);
    for (i = 0; i < 128; ++i) {
        secp256k1_gej_double_var(&gj, &gj, NULL);
    }
    secp256k1_ecmult_create_prec_table(table_128, window_g, &gj);
}

static void precompute_ecmult_print_table(FILE *fp, const char *name, int window_g, const secp256k1_ge_storage* table, int with_conditionals) {
    int j;
    int i;

    fprintf(fp, "static const secp256k1_ge_storage %s[ECMULT_TABLE_SIZE(WINDOW_G)] = {\n", name);

    fprintf(fp, " S(%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32
                  ",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32")\n",
                SECP256K1_GE_STORAGE_CONST_GET(table[0]));

    j = 1;
    for(i = 3; i <= window_g; ++i) {
        if (with_conditionals) {
            fprintf(fp, "#if ECMULT_TABLE_SIZE(WINDOW_G) > %ld\n", ECMULT_TABLE_SIZE(i-1));
        }
        for(;j < ECMULT_TABLE_SIZE(i); ++j) {
            fprintf(fp, ",S(%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32
                          ",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32")\n",
                        SECP256K1_GE_STORAGE_CONST_GET(table[j]));
        }
        if (with_conditionals) {
            fprintf(fp, "#endif\n");
        }
    }
    fprintf(fp, "};\n");
}

static void precompute_ecmult_print_two_tables(FILE *fp, int window_g, const secp256k1_ge *g, int with_conditionals) {
    secp256k1_ge_storage* table = malloc(ECMULT_TABLE_SIZE(window_g) * sizeof(secp256k1_ge_storage));
    secp256k1_ge_storage* table_128 = malloc(ECMULT_TABLE_SIZE(window_g) * sizeof(secp256k1_ge_storage));

    secp256k1_ecmult_create_prec_two_tables(table, table_128, window_g, g);

    precompute_ecmult_print_table(fp, "secp256k1_pre_g", window_g, table, with_conditionals);
    precompute_ecmult_print_table(fp, "secp256k1_pre_g_128", window_g, table_128, with_conditionals);

    free(table);
    free(table_128);
}

static int precompute_ecmult(void) {
    const secp256k1_ge g = SECP256K1_G;
    const secp256k1_ge g_13 = SECP256K1_G_ORDER_13;
    const secp256k1_ge g_199 = SECP256K1_G_ORDER_199;
    const int window_g_13 = 4;
    const int window_g_199 = 8;
    FILE* fp;

    fp = fopen("src/precomputed_ecmult.h","w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open src/precomputed_ecmult.h for writing!\n");
        return -1;
    }

    fprintf(fp, "/* This file was automatically generated by precompute. */\n");
    fprintf(fp, "/* This file contains an array secp256k1_pre_g with odd multiples of the base point G and\n");
    fprintf(fp, " * an array secp256k1_pre_g_128 with odd multiples of 2^128*G for accelerating the computation of a*P + b*G.\n");
    fprintf(fp, " */\n");
    fprintf(fp, "#ifndef SECP256K1_PRECOMPUTED_ECMULT_H\n");
    fprintf(fp, "#define SECP256K1_PRECOMPUTED_ECMULT_H\n");
    fprintf(fp, "#include \"group.h\"\n");
    fprintf(fp, "#ifdef S\n");
    fprintf(fp, "   #error macro identifier S already in use.\n");
    fprintf(fp, "#endif\n");
    fprintf(fp, "#define S(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) "
                "SECP256K1_GE_STORAGE_CONST(0x##a##u,0x##b##u,0x##c##u,0x##d##u,0x##e##u,0x##f##u,0x##g##u,"
                "0x##h##u,0x##i##u,0x##j##u,0x##k##u,0x##l##u,0x##m##u,0x##n##u,0x##o##u,0x##p##u)\n");
    fprintf(fp, "#if ECMULT_TABLE_SIZE(ECMULT_WINDOW_SIZE) > %ld\n", ECMULT_TABLE_SIZE(ECMULT_WINDOW_SIZE));
    fprintf(fp, "   #error configuration mismatch, invalid ECMULT_WINDOW_SIZE. Try deleting precomputed_ecmult.h before the build.\n");
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
    fprintf(fp, "#endif /* SECP256K1_PRECOMPUTED_ECMULT_H */\n");
    fclose(fp);
    return 0;
}

static int precompute_ecmult_gen(int h_file) {
    static const char outfile_c[] = "src/precomputed_ecmult_gen.c";
    static const char outfile_h[] = "src/precomputed_ecmult_gen.h";
    const char* outfile = h_file ? outfile_h : outfile_c;
    FILE *fp;
    int bits;

    fp = fopen(outfile, "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open %s for writing!\n", outfile);
        return -1;
    }

    if (h_file) {
        fprintf(fp, "/* This file was automatically generated by precompute. */\n");
        fprintf(fp, "/* See ecmult_gen_impl.h for details about the contents of this file. */\n");
        fprintf(fp, "#ifndef SECP256K1_PRECOMPUTED_ECMULT_GEN_H\n");
        fprintf(fp, "#define SECP256K1_PRECOMPUTED_ECMULT_GEN_H\n");

        fprintf(fp, "#include \"group.h\"\n");
        fprintf(fp, "#include \"ecmult_gen.h\"\n");

        fprintf(fp, "#ifdef EXHAUSTIVE_TEST_ORDER\n");
        fprintf(fp, "static secp256k1_ge_storage secp256k1_ecmult_gen_prec_table[ECMULT_GEN_PREC_N(ECMULT_GEN_PREC_BITS)][ECMULT_GEN_PREC_G(ECMULT_GEN_PREC_BITS)];\n");
        fprintf(fp, "#else\n");
        fprintf(fp, "extern const secp256k1_ge_storage secp256k1_ecmult_gen_prec_table[ECMULT_GEN_PREC_N(ECMULT_GEN_PREC_BITS)][ECMULT_GEN_PREC_G(ECMULT_GEN_PREC_BITS)];\n");
        fprintf(fp, "#endif /* EXHAUSTIVE_TEST_ORDER */\n");
        fprintf(fp, "#endif /* SECP256K1_PRECOMPUTED_ECMULT_GEN_H */\n");
        fclose(fp);
        return 0;
    }

    fprintf(fp, "/* This file was automatically generated by precompute. */\n");
    fprintf(fp, "/* See ecmult_gen_impl.h for details about the contents of this file. */\n");

    fprintf(fp, "#if defined HAVE_CONFIG_H\n");
    fprintf(fp, "#include \"libsecp256k1-config.h\"\n");
    fprintf(fp, "#endif\n");

    fprintf(fp, "#include \"../include/secp256k1.h\"\n");

    fprintf(fp, "#include \"group.h\"\n");
    fprintf(fp, "#include \"ecmult_gen.h\"\n");

    fprintf(fp, "#ifdef EXHAUSTIVE_TEST_ORDER\n");
    fprintf(fp, "#error Cannot compile precomputed_ecmult_gen.c in exhaustive test mode\n");
    fprintf(fp, "#endif /* EXHAUSTIVE_TEST_ORDER */\n");

    fprintf(fp, "#define S(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) "
            "SECP256K1_GE_STORAGE_CONST(0x##a##u,0x##b##u,0x##c##u,0x##d##u,0x##e##u,0x##f##u,0x##g##u,"
            "0x##h##u,0x##i##u,0x##j##u,0x##k##u,0x##l##u,0x##m##u,0x##n##u,0x##o##u,0x##p##u)\n");

    fprintf(fp, "const secp256k1_ge_storage secp256k1_ecmult_gen_prec_table[ECMULT_GEN_PREC_N(ECMULT_GEN_PREC_BITS)][ECMULT_GEN_PREC_G(ECMULT_GEN_PREC_BITS)] = {\n");

    for (bits = 2; bits <= 8; bits *= 2) {
        int g = ECMULT_GEN_PREC_G(bits);
        int n = ECMULT_GEN_PREC_N(bits);
        int inner, outer;

        secp256k1_ge_storage* table = checked_malloc(&default_error_callback, n * g * sizeof(secp256k1_ge_storage));
        secp256k1_ecmult_gen_create_prec_table(table, &secp256k1_ge_const_g, bits);

        fprintf(fp, "#if ECMULT_GEN_PREC_BITS == %d\n", bits);
        for(outer = 0; outer != n; outer++) {
            fprintf(fp,"{");
            for(inner = 0; inner != g; inner++) {
                fprintf(fp, "S(%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32
                            ",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32",%"PRIx32")",
                        SECP256K1_GE_STORAGE_CONST_GET(table[outer * g + inner]));
                if (inner != g - 1) {
                    fprintf(fp,",\n");
                } 
            }
            if (outer != n - 1) {
                fprintf(fp,"},\n");
            } else {
                fprintf(fp,"}\n");
            }
        }
        fprintf(fp, "#endif\n");
        free(table);
    }

    fprintf(fp, "};\n");
    fprintf(fp, "#undef S\n");
    fclose(fp);

    return 0;
}

int main(int argc, char** argv) {
    if (argc == 2 && !strcmp(argv[1], "ecmult")) {
        return precompute_ecmult();
    } else if (argc == 2 && !strcmp(argv[1], "ecmult_gen_c")) {
        return precompute_ecmult_gen(0);
    } else if (argc == 2 && !strcmp(argv[1], "ecmult_gen_h")) {
        return precompute_ecmult_gen(1);
    } else {
        fprintf(stderr, "Usage: ./precompute [ecmult|ecmult_gen_c|ecmult_gen_h]\n");
        return 1;
    }
}
