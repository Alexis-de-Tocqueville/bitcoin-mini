/**********************************************************************
 * Copyright (c) 2017 Andrew Poelstra                                 *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef _SECP256K1_SCRATCH_IMPL_H_
#define _SECP256K1_SCRATCH_IMPL_H_

#include "scratch.h"

#define ALIGNMENT 16

static secp256k1_scratch* secp256k1_scratch_create(const secp256k1_callback* error_callback, size_t init_size, size_t max_size) {
    secp256k1_scratch* ret = (secp256k1_scratch*)checked_malloc(error_callback, sizeof(*ret));
    if (ret != NULL) {
        ret->data = checked_malloc(error_callback, init_size);
        if (ret->data == NULL) {
            free (ret);
            return NULL;
        }
        ret->offset = 0;
        ret->init_size = init_size;
        ret->max_size = max_size;
    }
    return ret;
}

static void secp256k1_scratch_destroy(secp256k1_scratch* scratch) {
    if (scratch != NULL) {
        free(scratch->data);
        free(scratch);
    }
}

static size_t secp256k1_scratch_max_allocation(const secp256k1_scratch* scratch, size_t objects) {
    return scratch->max_size - objects * ALIGNMENT;
}

static int secp256k1_scratch_resize(secp256k1_scratch* scratch, const secp256k1_callback* error_callback, size_t n, size_t objects) {
    n += objects * ALIGNMENT;
    if (n > scratch->init_size && n <= scratch->max_size) {
        void *tmp = checked_realloc(error_callback, scratch->data, n);
        if (tmp == NULL) {
            return 0;
        }
        scratch->init_size = n;
        scratch->data = tmp;
    }
    return n <= scratch->max_size;
}

static void *secp256k1_scratch_alloc(secp256k1_scratch* scratch, size_t size) {
    void *ret;
    size = ((size + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT;
    if (size + scratch->offset > scratch->init_size) {
        return NULL;
    }
    ret = (void *) ((unsigned char *) scratch->data + scratch->offset);
    memset(ret, 0, size);
    scratch->offset += size;
    return ret;
}

static void secp256k1_scratch_reset(secp256k1_scratch* scratch) {
    scratch->offset = 0;
}

#endif