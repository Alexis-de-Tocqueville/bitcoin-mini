/**
 * Automatically generated by tools/test_vectors_musig2_generate.py.
 *
 * The test vectors for the KeySort function are included in this file. They can
 * be found in src/modules/extrakeys/tests_impl.h. */

enum MUSIG_ERROR {
    MUSIG_PUBKEY,
    MUSIG_TWEAK,
    MUSIG_PUBNONCE,
    MUSIG_AGGNONCE,
    MUSIG_SECNONCE,
    MUSIG_SIG,
    MUSIG_SIG_VERIFY,
    MUSIG_OTHER
};

struct musig_key_agg_valid_test_case {
    size_t key_indices_len;
    size_t key_indices[4];
    unsigned char expected[32];
};

struct musig_key_agg_error_test_case {
    size_t key_indices_len;
    size_t key_indices[4];
    size_t tweak_indices_len;
    size_t tweak_indices[1];
    int is_xonly[1];
    enum MUSIG_ERROR error;
};

struct musig_key_agg_vector {
    unsigned char pubkeys[7][33];
    unsigned char tweaks[2][32];
    struct musig_key_agg_valid_test_case valid_case[4];
    struct musig_key_agg_error_test_case error_case[5];
};

static const struct musig_key_agg_vector musig_key_agg_vector = {
    {
        { 0x02, 0xF9, 0x30, 0x8A, 0x01, 0x92, 0x58, 0xC3, 0x10, 0x49, 0x34, 0x4F, 0x85, 0xF8, 0x9D, 0x52, 0x29, 0xB5, 0x31, 0xC8, 0x45, 0x83, 0x6F, 0x99, 0xB0, 0x86, 0x01, 0xF1, 0x13, 0xBC, 0xE0, 0x36, 0xF9 },
        { 0x03, 0xDF, 0xF1, 0xD7, 0x7F, 0x2A, 0x67, 0x1C, 0x5F, 0x36, 0x18, 0x37, 0x26, 0xDB, 0x23, 0x41, 0xBE, 0x58, 0xFE, 0xAE, 0x1D, 0xA2, 0xDE, 0xCE, 0xD8, 0x43, 0x24, 0x0F, 0x7B, 0x50, 0x2B, 0xA6, 0x59 },
        { 0x02, 0x35, 0x90, 0xA9, 0x4E, 0x76, 0x8F, 0x8E, 0x18, 0x15, 0xC2, 0xF2, 0x4B, 0x4D, 0x80, 0xA8, 0xE3, 0x14, 0x93, 0x16, 0xC3, 0x51, 0x8C, 0xE7, 0xB7, 0xAD, 0x33, 0x83, 0x68, 0xD0, 0x38, 0xCA, 0x66 },
        { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05 },
        { 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x30 },
        { 0x04, 0xF9, 0x30, 0x8A, 0x01, 0x92, 0x58, 0xC3, 0x10, 0x49, 0x34, 0x4F, 0x85, 0xF8, 0x9D, 0x52, 0x29, 0xB5, 0x31, 0xC8, 0x45, 0x83, 0x6F, 0x99, 0xB0, 0x86, 0x01, 0xF1, 0x13, 0xBC, 0xE0, 0x36, 0xF9 },
        { 0x03, 0x93, 0x5F, 0x97, 0x2D, 0xA0, 0x13, 0xF8, 0x0A, 0xE0, 0x11, 0x89, 0x0F, 0xA8, 0x9B, 0x67, 0xA2, 0x7B, 0x7B, 0xE6, 0xCC, 0xB2, 0x4D, 0x32, 0x74, 0xD1, 0x8B, 0x2D, 0x40, 0x67, 0xF2, 0x61, 0xA9 }
    },
    {
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B, 0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41 },
        { 0x25, 0x2E, 0x4B, 0xD6, 0x74, 0x10, 0xA7, 0x6C, 0xDF, 0x93, 0x3D, 0x30, 0xEA, 0xA1, 0x60, 0x82, 0x14, 0x03, 0x7F, 0x1B, 0x10, 0x5A, 0x01, 0x3E, 0xCC, 0xD3, 0xC5, 0xC1, 0x84, 0xA6, 0x11, 0x0B }
    },
    {
        {  3, { 0, 1, 2 }, { 0x90, 0x53, 0x9E, 0xED, 0xE5, 0x65, 0xF5, 0xD0, 0x54, 0xF3, 0x2C, 0xC0, 0xC2, 0x20, 0x12, 0x68, 0x89, 0xED, 0x1E, 0x5D, 0x19, 0x3B, 0xAF, 0x15, 0xAE, 0xF3, 0x44, 0xFE, 0x59, 0xD4, 0x61, 0x0C }},
        {  3, { 2, 1, 0 }, { 0x62, 0x04, 0xDE, 0x8B, 0x08, 0x34, 0x26, 0xDC, 0x6E, 0xAF, 0x95, 0x02, 0xD2, 0x70, 0x24, 0xD5, 0x3F, 0xC8, 0x26, 0xBF, 0x7D, 0x20, 0x12, 0x14, 0x8A, 0x05, 0x75, 0x43, 0x5D, 0xF5, 0x4B, 0x2B }},
        {  3, { 0, 0, 0 }, { 0xB4, 0x36, 0xE3, 0xBA, 0xD6, 0x2B, 0x8C, 0xD4, 0x09, 0x96, 0x9A, 0x22, 0x47, 0x31, 0xC1, 0x93, 0xD0, 0x51, 0x16, 0x2D, 0x8C, 0x5A, 0xE8, 0xB1, 0x09, 0x30, 0x61, 0x27, 0xDA, 0x3A, 0xA9, 0x35 }},
        {  4, { 0, 0, 1, 1 }, { 0x69, 0xBC, 0x22, 0xBF, 0xA5, 0xD1, 0x06, 0x30, 0x6E, 0x48, 0xA2, 0x06, 0x79, 0xDE, 0x1D, 0x73, 0x89, 0x38, 0x61, 0x24, 0xD0, 0x75, 0x71, 0xD0, 0xD8, 0x72, 0x68, 0x60, 0x28, 0xC2, 0x6A, 0x3E }},
    },
    {
        {  2, { 0, 3 },  0, { 0 }, { 0 }, MUSIG_PUBKEY },
        {  2, { 0, 4 },  0, { 0 }, { 0 }, MUSIG_PUBKEY },
        {  2, { 5, 0 },  0, { 0 }, { 0 }, MUSIG_PUBKEY },
        {  2, { 0, 1 },  1, { 0 }, { 1 }, MUSIG_TWEAK },
        {  1, { 6 },  1, { 1 }, { 0 }, MUSIG_TWEAK },
    },
};

struct musig_nonce_gen_test_case {
    unsigned char rand_[32];
    int has_sk;
    unsigned char sk[32];
    unsigned char pk[33];
    int has_aggpk;
    unsigned char aggpk[32];
    int has_msg;
    unsigned char msg[32];
    int has_extra_in;
    unsigned char extra_in[32];
    unsigned char expected_secnonce[97];
    unsigned char expected_pubnonce[66];
};

struct musig_nonce_gen_vector {
    struct musig_nonce_gen_test_case test_case[2];
};

static const struct musig_nonce_gen_vector musig_nonce_gen_vector = {
    {
        { { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F },  1 , { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }, { 0x02, 0x4D, 0x4B, 0x6C, 0xD1, 0x36, 0x10, 0x32, 0xCA, 0x9B, 0xD2, 0xAE, 0xB9, 0xD9, 0x00, 0xAA, 0x4D, 0x45, 0xD9, 0xEA, 0xD8, 0x0A, 0xC9, 0x42, 0x33, 0x74, 0xC4, 0x51, 0xA7, 0x25, 0x4D, 0x07, 0x66 }, 1 , { 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07 }, 1 , { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, 1 , { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 }, { 0xB1, 0x14, 0xE5, 0x02, 0xBE, 0xAA, 0x4E, 0x30, 0x1D, 0xD0, 0x8A, 0x50, 0x26, 0x41, 0x72, 0xC8, 0x4E, 0x41, 0x65, 0x0E, 0x6C, 0xB7, 0x26, 0xB4, 0x10, 0xC0, 0x69, 0x4D, 0x59, 0xEF, 0xFB, 0x64, 0x95, 0xB5, 0xCA, 0xF2, 0x8D, 0x04, 0x5B, 0x97, 0x3D, 0x63, 0xE3, 0xC9, 0x9A, 0x44, 0xB8, 0x07, 0xBD, 0xE3, 0x75, 0xFD, 0x6C, 0xB3, 0x9E, 0x46, 0xDC, 0x4A, 0x51, 0x17, 0x08, 0xD0, 0xE9, 0xD2, 0x02, 0x4D, 0x4B, 0x6C, 0xD1, 0x36, 0x10, 0x32, 0xCA, 0x9B, 0xD2, 0xAE, 0xB9, 0xD9, 0x00, 0xAA, 0x4D, 0x45, 0xD9, 0xEA, 0xD8, 0x0A, 0xC9, 0x42, 0x33, 0x74, 0xC4, 0x51, 0xA7, 0x25, 0x4D, 0x07, 0x66 }, { 0x02, 0xF7, 0xBE, 0x70, 0x89, 0xE8, 0x37, 0x6E, 0xB3, 0x55, 0x27, 0x23, 0x68, 0x76, 0x6B, 0x17, 0xE8, 0x8E, 0x7D, 0xB7, 0x20, 0x47, 0xD0, 0x5E, 0x56, 0xAA, 0x88, 0x1E, 0xA5, 0x2B, 0x3B, 0x35, 0xDF, 0x02, 0xC2, 0x9C, 0x80, 0x46, 0xFD, 0xD0, 0xDE, 0xD4, 0xC7, 0xE5, 0x58, 0x69, 0x13, 0x72, 0x00, 0xFB, 0xDB, 0xFE, 0x2E, 0xB6, 0x54, 0x26, 0x7B, 0x6D, 0x70, 0x13, 0x60, 0x2C, 0xAE, 0xD3, 0x11, 0x5A } },
        { { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F },  0 , { 0 }, { 0x02, 0xF9, 0x30, 0x8A, 0x01, 0x92, 0x58, 0xC3, 0x10, 0x49, 0x34, 0x4F, 0x85, 0xF8, 0x9D, 0x52, 0x29, 0xB5, 0x31, 0xC8, 0x45, 0x83, 0x6F, 0x99, 0xB0, 0x86, 0x01, 0xF1, 0x13, 0xBC, 0xE0, 0x36, 0xF9 }, 0 , { 0 }, 0 , { 0 }, 0 , { 0 }, { 0x89, 0xBD, 0xD7, 0x87, 0xD0, 0x28, 0x4E, 0x5E, 0x4D, 0x5F, 0xC5, 0x72, 0xE4, 0x9E, 0x31, 0x6B, 0xAB, 0x7E, 0x21, 0xE3, 0xB1, 0x83, 0x0D, 0xE3, 0x7D, 0xFE, 0x80, 0x15, 0x6F, 0xA4, 0x1A, 0x6D, 0x0B, 0x17, 0xAE, 0x8D, 0x02, 0x4C, 0x53, 0x67, 0x96, 0x99, 0xA6, 0xFD, 0x79, 0x44, 0xD9, 0xC4, 0xA3, 0x66, 0xB5, 0x14, 0xBA, 0xF4, 0x30, 0x88, 0xE0, 0x70, 0x8B, 0x10, 0x23, 0xDD, 0x28, 0x97, 0x02, 0xF9, 0x30, 0x8A, 0x01, 0x92, 0x58, 0xC3, 0x10, 0x49, 0x34, 0x4F, 0x85, 0xF8, 0x9D, 0x52, 0x29, 0xB5, 0x31, 0xC8, 0x45, 0x83, 0x6F, 0x99, 0xB0, 0x86, 0x01, 0xF1, 0x13, 0xBC, 0xE0, 0x36, 0xF9 }, { 0x02, 0xC9, 0x6E, 0x7C, 0xB1, 0xE8, 0xAA, 0x5D, 0xAC, 0x64, 0xD8, 0x72, 0x94, 0x79, 0x14, 0x19, 0x8F, 0x60, 0x7D, 0x90, 0xEC, 0xDE, 0x52, 0x00, 0xDE, 0x52, 0x97, 0x8A, 0xD5, 0xDE, 0xD6, 0x3C, 0x00, 0x02, 0x99, 0xEC, 0x51, 0x17, 0xC2, 0xD2, 0x9E, 0xDE, 0xE8, 0xA2, 0x09, 0x25, 0x87, 0xC3, 0x90, 0x9B, 0xE6, 0x94, 0xD5, 0xCF, 0xF0, 0x66, 0x7D, 0x6C, 0x02, 0xEA, 0x40, 0x59, 0xF7, 0xCD, 0x97, 0x86 } },
    },
};

struct musig_nonce_agg_test_case {
    size_t pnonce_indices[2];
    /* if valid case */
    unsigned char expected[66];
    /* if error case */
    int invalid_nonce_idx;
};

struct musig_nonce_agg_vector {
    unsigned char pnonces[7][66];
    struct musig_nonce_agg_test_case valid_case[2];
    struct musig_nonce_agg_test_case error_case[3];
};

static const struct musig_nonce_agg_vector musig_nonce_agg_vector = {
    {
        { 0x02, 0x01, 0x51, 0xC8, 0x0F, 0x43, 0x56, 0x48, 0xDF, 0x67, 0xA2, 0x2B, 0x74, 0x9C, 0xD7, 0x98, 0xCE, 0x54, 0xE0, 0x32, 0x1D, 0x03, 0x4B, 0x92, 0xB7, 0x09, 0xB5, 0x67, 0xD6, 0x0A, 0x42, 0xE6, 0x66, 0x03, 0xBA, 0x47, 0xFB, 0xC1, 0x83, 0x44, 0x37, 0xB3, 0x21, 0x2E, 0x89, 0xA8, 0x4D, 0x84, 0x25, 0xE7, 0xBF, 0x12, 0xE0, 0x24, 0x5D, 0x98, 0x26, 0x22, 0x68, 0xEB, 0xDC, 0xB3, 0x85, 0xD5, 0x06, 0x41 },
        { 0x03, 0xFF, 0x40, 0x6F, 0xFD, 0x8A, 0xDB, 0x9C, 0xD2, 0x98, 0x77, 0xE4, 0x98, 0x50, 0x14, 0xF6, 0x6A, 0x59, 0xF6, 0xCD, 0x01, 0xC0, 0xE8, 0x8C, 0xAA, 0x8E, 0x5F, 0x31, 0x66, 0xB1, 0xF6, 0x76, 0xA6, 0x02, 0x48, 0xC2, 0x64, 0xCD, 0xD5, 0x7D, 0x3C, 0x24, 0xD7, 0x99, 0x90, 0xB0, 0xF8, 0x65, 0x67, 0x4E, 0xB6, 0x2A, 0x0F, 0x90, 0x18, 0x27, 0x7A, 0x95, 0x01, 0x1B, 0x41, 0xBF, 0xC1, 0x93, 0xB8, 0x33 },
        { 0x02, 0x01, 0x51, 0xC8, 0x0F, 0x43, 0x56, 0x48, 0xDF, 0x67, 0xA2, 0x2B, 0x74, 0x9C, 0xD7, 0x98, 0xCE, 0x54, 0xE0, 0x32, 0x1D, 0x03, 0x4B, 0x92, 0xB7, 0x09, 0xB5, 0x67, 0xD6, 0x0A, 0x42, 0xE6, 0x66, 0x02, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98 },
        { 0x03, 0xFF, 0x40, 0x6F, 0xFD, 0x8A, 0xDB, 0x9C, 0xD2, 0x98, 0x77, 0xE4, 0x98, 0x50, 0x14, 0xF6, 0x6A, 0x59, 0xF6, 0xCD, 0x01, 0xC0, 0xE8, 0x8C, 0xAA, 0x8E, 0x5F, 0x31, 0x66, 0xB1, 0xF6, 0x76, 0xA6, 0x03, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98 },
        { 0x04, 0xFF, 0x40, 0x6F, 0xFD, 0x8A, 0xDB, 0x9C, 0xD2, 0x98, 0x77, 0xE4, 0x98, 0x50, 0x14, 0xF6, 0x6A, 0x59, 0xF6, 0xCD, 0x01, 0xC0, 0xE8, 0x8C, 0xAA, 0x8E, 0x5F, 0x31, 0x66, 0xB1, 0xF6, 0x76, 0xA6, 0x02, 0x48, 0xC2, 0x64, 0xCD, 0xD5, 0x7D, 0x3C, 0x24, 0xD7, 0x99, 0x90, 0xB0, 0xF8, 0x65, 0x67, 0x4E, 0xB6, 0x2A, 0x0F, 0x90, 0x18, 0x27, 0x7A, 0x95, 0x01, 0x1B, 0x41, 0xBF, 0xC1, 0x93, 0xB8, 0x33 },
        { 0x03, 0xFF, 0x40, 0x6F, 0xFD, 0x8A, 0xDB, 0x9C, 0xD2, 0x98, 0x77, 0xE4, 0x98, 0x50, 0x14, 0xF6, 0x6A, 0x59, 0xF6, 0xCD, 0x01, 0xC0, 0xE8, 0x8C, 0xAA, 0x8E, 0x5F, 0x31, 0x66, 0xB1, 0xF6, 0x76, 0xA6, 0x02, 0x48, 0xC2, 0x64, 0xCD, 0xD5, 0x7D, 0x3C, 0x24, 0xD7, 0x99, 0x90, 0xB0, 0xF8, 0x65, 0x67, 0x4E, 0xB6, 0x2A, 0x0F, 0x90, 0x18, 0x27, 0x7A, 0x95, 0x01, 0x1B, 0x41, 0xBF, 0xC1, 0x93, 0xB8, 0x31 },
        { 0x03, 0xFF, 0x40, 0x6F, 0xFD, 0x8A, 0xDB, 0x9C, 0xD2, 0x98, 0x77, 0xE4, 0x98, 0x50, 0x14, 0xF6, 0x6A, 0x59, 0xF6, 0xCD, 0x01, 0xC0, 0xE8, 0x8C, 0xAA, 0x8E, 0x5F, 0x31, 0x66, 0xB1, 0xF6, 0x76, 0xA6, 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x30 }
    },
    {
        { { 0, 1 }, { 0x03, 0x5F, 0xE1, 0x87, 0x3B, 0x4F, 0x29, 0x67, 0xF5, 0x2F, 0xEA, 0x4A, 0x06, 0xAD, 0x5A, 0x8E, 0xCC, 0xBE, 0x9D, 0x0F, 0xD7, 0x30, 0x68, 0x01, 0x2C, 0x89, 0x4E, 0x2E, 0x87, 0xCC, 0xB5, 0x80, 0x4B, 0x02, 0x47, 0x25, 0x37, 0x73, 0x45, 0xBD, 0xE0, 0xE9, 0xC3, 0x3A, 0xF3, 0xC4, 0x3C, 0x0A, 0x29, 0xA9, 0x24, 0x9F, 0x2F, 0x29, 0x56, 0xFA, 0x8C, 0xFE, 0xB5, 0x5C, 0x85, 0x73, 0xD0, 0x26, 0x2D, 0xC8 }, 0 },
        { { 2, 3 }, { 0x03, 0x5F, 0xE1, 0x87, 0x3B, 0x4F, 0x29, 0x67, 0xF5, 0x2F, 0xEA, 0x4A, 0x06, 0xAD, 0x5A, 0x8E, 0xCC, 0xBE, 0x9D, 0x0F, 0xD7, 0x30, 0x68, 0x01, 0x2C, 0x89, 0x4E, 0x2E, 0x87, 0xCC, 0xB5, 0x80, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 0 },
    },
    {
        { { 0, 4 }, { 0 }, 1 },
        { { 5, 1 }, { 0 }, 0 },
        { { 6, 1 }, { 0 }, 0 },
    },
};

/* Omit pubnonces in the test vectors because our partial signature verification
 * implementation is able to accept the aggnonce directly. */
struct musig_valid_case {
    size_t key_indices_len;
    size_t key_indices[3];
    size_t aggnonce_index;
    size_t msg_index;
    size_t signer_index;
    unsigned char expected[32];
};

struct musig_sign_error_case {
    size_t key_indices_len;
    size_t key_indices[3];
    size_t aggnonce_index;
    size_t msg_index;
    size_t secnonce_index;
    enum MUSIG_ERROR error;
};

struct musig_verify_fail_error_case {
    unsigned char sig[32];
    size_t key_indices_len;
    size_t key_indices[3];
    size_t nonce_indices_len;
    size_t nonce_indices[3];
    size_t msg_index;
    size_t signer_index;
    enum MUSIG_ERROR error;
};

struct musig_sign_verify_vector {
    unsigned char sk[32];
    unsigned char pubkeys[4][33];
    unsigned char secnonces[2][194];
    unsigned char pubnonces[5][194];
    unsigned char aggnonces[5][66];
    unsigned char msgs[1][32];
    struct musig_valid_case valid_case[4];
    struct musig_sign_error_case sign_error_case[6];
    struct musig_verify_fail_error_case verify_fail_case[3];
    struct musig_verify_fail_error_case verify_error_case[2];
};

static const struct musig_sign_verify_vector musig_sign_verify_vector = {
    { 0x7F, 0xB9, 0xE0, 0xE6, 0x87, 0xAD, 0xA1, 0xEE, 0xBF, 0x7E, 0xCF, 0xE2, 0xF2, 0x1E, 0x73, 0xEB, 0xDB, 0x51, 0xA7, 0xD4, 0x50, 0x94, 0x8D, 0xFE, 0x8D, 0x76, 0xD7, 0xF2, 0xD1, 0x00, 0x76, 0x71 },
    {
        { 0x03, 0x93, 0x5F, 0x97, 0x2D, 0xA0, 0x13, 0xF8, 0x0A, 0xE0, 0x11, 0x89, 0x0F, 0xA8, 0x9B, 0x67, 0xA2, 0x7B, 0x7B, 0xE6, 0xCC, 0xB2, 0x4D, 0x32, 0x74, 0xD1, 0x8B, 0x2D, 0x40, 0x67, 0xF2, 0x61, 0xA9 },
        { 0x02, 0xF9, 0x30, 0x8A, 0x01, 0x92, 0x58, 0xC3, 0x10, 0x49, 0x34, 0x4F, 0x85, 0xF8, 0x9D, 0x52, 0x29, 0xB5, 0x31, 0xC8, 0x45, 0x83, 0x6F, 0x99, 0xB0, 0x86, 0x01, 0xF1, 0x13, 0xBC, 0xE0, 0x36, 0xF9 },
        { 0x02, 0xDF, 0xF1, 0xD7, 0x7F, 0x2A, 0x67, 0x1C, 0x5F, 0x36, 0x18, 0x37, 0x26, 0xDB, 0x23, 0x41, 0xBE, 0x58, 0xFE, 0xAE, 0x1D, 0xA2, 0xDE, 0xCE, 0xD8, 0x43, 0x24, 0x0F, 0x7B, 0x50, 0x2B, 0xA6, 0x61 },
        { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07 }
    },
    {
        { 0x50, 0x8B, 0x81, 0xA6, 0x11, 0xF1, 0x00, 0xA6, 0xB2, 0xB6, 0xB2, 0x96, 0x56, 0x59, 0x08, 0x98, 0xAF, 0x48, 0x8B, 0xCF, 0x2E, 0x1F, 0x55, 0xCF, 0x22, 0xE5, 0xCF, 0xB8, 0x44, 0x21, 0xFE, 0x61, 0xFA, 0x27, 0xFD, 0x49, 0xB1, 0xD5, 0x00, 0x85, 0xB4, 0x81, 0x28, 0x5E, 0x1C, 0xA2, 0x05, 0xD5, 0x5C, 0x82, 0xCC, 0x1B, 0x31, 0xFF, 0x5C, 0xD5, 0x4A, 0x48, 0x98, 0x29, 0x35, 0x59, 0x01, 0xF7, 0x03, 0x93, 0x5F, 0x97, 0x2D, 0xA0, 0x13, 0xF8, 0x0A, 0xE0, 0x11, 0x89, 0x0F, 0xA8, 0x9B, 0x67, 0xA2, 0x7B, 0x7B, 0xE6, 0xCC, 0xB2, 0x4D, 0x32, 0x74, 0xD1, 0x8B, 0x2D, 0x40, 0x67, 0xF2, 0x61, 0xA9 },
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x93, 0x5F, 0x97, 0x2D, 0xA0, 0x13, 0xF8, 0x0A, 0xE0, 0x11, 0x89, 0x0F, 0xA8, 0x9B, 0x67, 0xA2, 0x7B, 0x7B, 0xE6, 0xCC, 0xB2, 0x4D, 0x32, 0x74, 0xD1, 0x8B, 0x2D, 0x40, 0x67, 0xF2, 0x61, 0xA9 }
    },
    {
        { 0x03, 0x37, 0xC8, 0x78, 0x21, 0xAF, 0xD5, 0x0A, 0x86, 0x44, 0xD8, 0x20, 0xA8, 0xF3, 0xE0, 0x2E, 0x49, 0x9C, 0x93, 0x18, 0x65, 0xC2, 0x36, 0x0F, 0xB4, 0x3D, 0x0A, 0x0D, 0x20, 0xDA, 0xFE, 0x07, 0xEA, 0x02, 0x87, 0xBF, 0x89, 0x1D, 0x2A, 0x6D, 0xEA, 0xEB, 0xAD, 0xC9, 0x09, 0x35, 0x2A, 0xA9, 0x40, 0x5D, 0x14, 0x28, 0xC1, 0x5F, 0x4B, 0x75, 0xF0, 0x4D, 0xAE, 0x64, 0x2A, 0x95, 0xC2, 0x54, 0x84, 0x80 },
        { 0x02, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98, 0x02, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98 },
        { 0x03, 0x2D, 0xE2, 0x66, 0x26, 0x28, 0xC9, 0x0B, 0x03, 0xF5, 0xE7, 0x20, 0x28, 0x4E, 0xB5, 0x2F, 0xF7, 0xD7, 0x1F, 0x42, 0x84, 0xF6, 0x27, 0xB6, 0x8A, 0x85, 0x3D, 0x78, 0xC7, 0x8E, 0x1F, 0xFE, 0x93, 0x03, 0xE4, 0xC5, 0x52, 0x4E, 0x83, 0xFF, 0xE1, 0x49, 0x3B, 0x90, 0x77, 0xCF, 0x1C, 0xA6, 0xBE, 0xB2, 0x09, 0x0C, 0x93, 0xD9, 0x30, 0x32, 0x10, 0x71, 0xAD, 0x40, 0xB2, 0xF4, 0x4E, 0x59, 0x90, 0x46 },
        { 0x02, 0x37, 0xC8, 0x78, 0x21, 0xAF, 0xD5, 0x0A, 0x86, 0x44, 0xD8, 0x20, 0xA8, 0xF3, 0xE0, 0x2E, 0x49, 0x9C, 0x93, 0x18, 0x65, 0xC2, 0x36, 0x0F, 0xB4, 0x3D, 0x0A, 0x0D, 0x20, 0xDA, 0xFE, 0x07, 0xEA, 0x03, 0x87, 0xBF, 0x89, 0x1D, 0x2A, 0x6D, 0xEA, 0xEB, 0xAD, 0xC9, 0x09, 0x35, 0x2A, 0xA9, 0x40, 0x5D, 0x14, 0x28, 0xC1, 0x5F, 0x4B, 0x75, 0xF0, 0x4D, 0xAE, 0x64, 0x2A, 0x95, 0xC2, 0x54, 0x84, 0x80 },
        { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x02, 0x87, 0xBF, 0x89, 0x1D, 0x2A, 0x6D, 0xEA, 0xEB, 0xAD, 0xC9, 0x09, 0x35, 0x2A, 0xA9, 0x40, 0x5D, 0x14, 0x28, 0xC1, 0x5F, 0x4B, 0x75, 0xF0, 0x4D, 0xAE, 0x64, 0x2A, 0x95, 0xC2, 0x54, 0x84, 0x80 }
    },
    {
        { 0x02, 0x84, 0x65, 0xFC, 0xF0, 0xBB, 0xDB, 0xCF, 0x44, 0x3A, 0xAB, 0xCC, 0xE5, 0x33, 0xD4, 0x2B, 0x4B, 0x5A, 0x10, 0x96, 0x6A, 0xC0, 0x9A, 0x49, 0x65, 0x5E, 0x8C, 0x42, 0xDA, 0xAB, 0x8F, 0xCD, 0x61, 0x03, 0x74, 0x96, 0xA3, 0xCC, 0x86, 0x92, 0x6D, 0x45, 0x2C, 0xAF, 0xCF, 0xD5, 0x5D, 0x25, 0x97, 0x2C, 0xA1, 0x67, 0x5D, 0x54, 0x93, 0x10, 0xDE, 0x29, 0x6B, 0xFF, 0x42, 0xF7, 0x2E, 0xEE, 0xA8, 0xC9 },
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x04, 0x84, 0x65, 0xFC, 0xF0, 0xBB, 0xDB, 0xCF, 0x44, 0x3A, 0xAB, 0xCC, 0xE5, 0x33, 0xD4, 0x2B, 0x4B, 0x5A, 0x10, 0x96, 0x6A, 0xC0, 0x9A, 0x49, 0x65, 0x5E, 0x8C, 0x42, 0xDA, 0xAB, 0x8F, 0xCD, 0x61, 0x03, 0x74, 0x96, 0xA3, 0xCC, 0x86, 0x92, 0x6D, 0x45, 0x2C, 0xAF, 0xCF, 0xD5, 0x5D, 0x25, 0x97, 0x2C, 0xA1, 0x67, 0x5D, 0x54, 0x93, 0x10, 0xDE, 0x29, 0x6B, 0xFF, 0x42, 0xF7, 0x2E, 0xEE, 0xA8, 0xC9 },
        { 0x02, 0x84, 0x65, 0xFC, 0xF0, 0xBB, 0xDB, 0xCF, 0x44, 0x3A, 0xAB, 0xCC, 0xE5, 0x33, 0xD4, 0x2B, 0x4B, 0x5A, 0x10, 0x96, 0x6A, 0xC0, 0x9A, 0x49, 0x65, 0x5E, 0x8C, 0x42, 0xDA, 0xAB, 0x8F, 0xCD, 0x61, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09 },
        { 0x02, 0x84, 0x65, 0xFC, 0xF0, 0xBB, 0xDB, 0xCF, 0x44, 0x3A, 0xAB, 0xCC, 0xE5, 0x33, 0xD4, 0x2B, 0x4B, 0x5A, 0x10, 0x96, 0x6A, 0xC0, 0x9A, 0x49, 0x65, 0x5E, 0x8C, 0x42, 0xDA, 0xAB, 0x8F, 0xCD, 0x61, 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x30 }
    },
    {
        { 0xF9, 0x54, 0x66, 0xD0, 0x86, 0x77, 0x0E, 0x68, 0x99, 0x64, 0x66, 0x42, 0x19, 0x26, 0x6F, 0xE5, 0xED, 0x21, 0x5C, 0x92, 0xAE, 0x20, 0xBA, 0xB5, 0xC9, 0xD7, 0x9A, 0xDD, 0xDD, 0xF3, 0xC0, 0xCF }
    },
    {
        {  3, { 0, 1, 2 }, 0, 0, 0, { 0x01, 0x2A, 0xBB, 0xCB, 0x52, 0xB3, 0x01, 0x6A, 0xC0, 0x3A, 0xD8, 0x23, 0x95, 0xA1, 0xA4, 0x15, 0xC4, 0x8B, 0x93, 0xDE, 0xF7, 0x87, 0x18, 0xE6, 0x2A, 0x7A, 0x90, 0x05, 0x2F, 0xE2, 0x24, 0xFB }},
        {  3, { 1, 0, 2 }, 0, 0, 1, { 0x9F, 0xF2, 0xF7, 0xAA, 0xA8, 0x56, 0x15, 0x0C, 0xC8, 0x81, 0x92, 0x54, 0x21, 0x8D, 0x3A, 0xDE, 0xEB, 0x05, 0x35, 0x26, 0x90, 0x51, 0x89, 0x77, 0x24, 0xF9, 0xDB, 0x37, 0x89, 0x51, 0x3A, 0x52 }},
        {  3, { 1, 2, 0 }, 0, 0, 2, { 0xFA, 0x23, 0xC3, 0x59, 0xF6, 0xFA, 0xC4, 0xE7, 0x79, 0x6B, 0xB9, 0x3B, 0xC9, 0xF0, 0x53, 0x2A, 0x95, 0x46, 0x8C, 0x53, 0x9B, 0xA2, 0x0F, 0xF8, 0x6D, 0x7C, 0x76, 0xED, 0x92, 0x22, 0x79, 0x00 }},
        {  2, { 0, 1 }, 1, 0, 0, { 0xAE, 0x38, 0x60, 0x64, 0xB2, 0x61, 0x05, 0x40, 0x47, 0x98, 0xF7, 0x5D, 0xE2, 0xEB, 0x9A, 0xF5, 0xED, 0xA5, 0x38, 0x7B, 0x06, 0x4B, 0x83, 0xD0, 0x49, 0xCB, 0x7C, 0x5E, 0x08, 0x87, 0x95, 0x31 }},
    },
    {
        {  2, { 1, 2 }, 0, 0, 0, MUSIG_PUBKEY },
        {  3, { 1, 0, 3 }, 0, 0, 0, MUSIG_PUBKEY },
        {  3, { 1, 2, 0 }, 2, 0, 0, MUSIG_AGGNONCE },
        {  3, { 1, 2, 0 }, 3, 0, 0, MUSIG_AGGNONCE },
        {  3, { 1, 2, 0 }, 4, 0, 0, MUSIG_AGGNONCE },
        {  3, { 0, 1, 2 }, 0, 0, 1, MUSIG_SECNONCE },
    },
    {
        { { 0x97, 0xAC, 0x83, 0x3A, 0xDC, 0xB1, 0xAF, 0xA4, 0x2E, 0xBF, 0x9E, 0x07, 0x25, 0x61, 0x6F, 0x3C, 0x9A, 0x0D, 0x5B, 0x61, 0x4F, 0x6F, 0xE2, 0x83, 0xCE, 0xAA, 0xA3, 0x7A, 0x8F, 0xFA, 0xF4, 0x06 },  3, { 0, 1, 2 },  3, { 0, 1, 2 }, 0, 0, MUSIG_SIG_VERIFY },
        { { 0x68, 0x53, 0x7C, 0xC5, 0x23, 0x4E, 0x50, 0x5B, 0xD1, 0x40, 0x61, 0xF8, 0xDA, 0x9E, 0x90, 0xC2, 0x20, 0xA1, 0x81, 0x85, 0x5F, 0xD8, 0xBD, 0xB7, 0xF1, 0x27, 0xBB, 0x12, 0x40, 0x3B, 0x4D, 0x3B },  3, { 0, 1, 2 },  3, { 0, 1, 2 }, 0, 1, MUSIG_SIG_VERIFY },
        { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B, 0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41 },  3, { 0, 1, 2 },  3, { 0, 1, 2 }, 0, 0, MUSIG_SIG },
    },
    {
        { { 0x68, 0x53, 0x7C, 0xC5, 0x23, 0x4E, 0x50, 0x5B, 0xD1, 0x40, 0x61, 0xF8, 0xDA, 0x9E, 0x90, 0xC2, 0x20, 0xA1, 0x81, 0x85, 0x5F, 0xD8, 0xBD, 0xB7, 0xF1, 0x27, 0xBB, 0x12, 0x40, 0x3B, 0x4D, 0x3B },  3, { 0, 1, 2 },  3, { 4, 1, 2 }, 0, 0, MUSIG_PUBNONCE },
        { { 0x68, 0x53, 0x7C, 0xC5, 0x23, 0x4E, 0x50, 0x5B, 0xD1, 0x40, 0x61, 0xF8, 0xDA, 0x9E, 0x90, 0xC2, 0x20, 0xA1, 0x81, 0x85, 0x5F, 0xD8, 0xBD, 0xB7, 0xF1, 0x27, 0xBB, 0x12, 0x40, 0x3B, 0x4D, 0x3B },  3, { 3, 1, 2 },  3, { 0, 1, 2 }, 0, 0, MUSIG_PUBKEY },
    },
};

struct musig_tweak_case {
    size_t key_indices_len;
    size_t key_indices[3];
    size_t nonce_indices_len;
    size_t nonce_indices[3];
    size_t tweak_indices_len;
    size_t tweak_indices[4];
    int is_xonly[4];
    size_t signer_index;
    unsigned char expected[32];
};

struct musig_tweak_vector {
    unsigned char sk[32];
    unsigned char secnonce[97];
    unsigned char aggnonce[66];
    unsigned char msg[32];
    unsigned char pubkeys[3][33];
    unsigned char pubnonces[3][194];
    unsigned char tweaks[5][32];
    struct musig_tweak_case valid_case[5];
    struct musig_tweak_case error_case[1];
};

static const struct musig_tweak_vector musig_tweak_vector = {
    { 0x7F, 0xB9, 0xE0, 0xE6, 0x87, 0xAD, 0xA1, 0xEE, 0xBF, 0x7E, 0xCF, 0xE2, 0xF2, 0x1E, 0x73, 0xEB, 0xDB, 0x51, 0xA7, 0xD4, 0x50, 0x94, 0x8D, 0xFE, 0x8D, 0x76, 0xD7, 0xF2, 0xD1, 0x00, 0x76, 0x71 },
    { 0x50, 0x8B, 0x81, 0xA6, 0x11, 0xF1, 0x00, 0xA6, 0xB2, 0xB6, 0xB2, 0x96, 0x56, 0x59, 0x08, 0x98, 0xAF, 0x48, 0x8B, 0xCF, 0x2E, 0x1F, 0x55, 0xCF, 0x22, 0xE5, 0xCF, 0xB8, 0x44, 0x21, 0xFE, 0x61, 0xFA, 0x27, 0xFD, 0x49, 0xB1, 0xD5, 0x00, 0x85, 0xB4, 0x81, 0x28, 0x5E, 0x1C, 0xA2, 0x05, 0xD5, 0x5C, 0x82, 0xCC, 0x1B, 0x31, 0xFF, 0x5C, 0xD5, 0x4A, 0x48, 0x98, 0x29, 0x35, 0x59, 0x01, 0xF7, 0x03, 0x93, 0x5F, 0x97, 0x2D, 0xA0, 0x13, 0xF8, 0x0A, 0xE0, 0x11, 0x89, 0x0F, 0xA8, 0x9B, 0x67, 0xA2, 0x7B, 0x7B, 0xE6, 0xCC, 0xB2, 0x4D, 0x32, 0x74, 0xD1, 0x8B, 0x2D, 0x40, 0x67, 0xF2, 0x61, 0xA9 },
    { 0x02, 0x84, 0x65, 0xFC, 0xF0, 0xBB, 0xDB, 0xCF, 0x44, 0x3A, 0xAB, 0xCC, 0xE5, 0x33, 0xD4, 0x2B, 0x4B, 0x5A, 0x10, 0x96, 0x6A, 0xC0, 0x9A, 0x49, 0x65, 0x5E, 0x8C, 0x42, 0xDA, 0xAB, 0x8F, 0xCD, 0x61, 0x03, 0x74, 0x96, 0xA3, 0xCC, 0x86, 0x92, 0x6D, 0x45, 0x2C, 0xAF, 0xCF, 0xD5, 0x5D, 0x25, 0x97, 0x2C, 0xA1, 0x67, 0x5D, 0x54, 0x93, 0x10, 0xDE, 0x29, 0x6B, 0xFF, 0x42, 0xF7, 0x2E, 0xEE, 0xA8, 0xC9 },
    { 0xF9, 0x54, 0x66, 0xD0, 0x86, 0x77, 0x0E, 0x68, 0x99, 0x64, 0x66, 0x42, 0x19, 0x26, 0x6F, 0xE5, 0xED, 0x21, 0x5C, 0x92, 0xAE, 0x20, 0xBA, 0xB5, 0xC9, 0xD7, 0x9A, 0xDD, 0xDD, 0xF3, 0xC0, 0xCF },
    {
        { 0x03, 0x93, 0x5F, 0x97, 0x2D, 0xA0, 0x13, 0xF8, 0x0A, 0xE0, 0x11, 0x89, 0x0F, 0xA8, 0x9B, 0x67, 0xA2, 0x7B, 0x7B, 0xE6, 0xCC, 0xB2, 0x4D, 0x32, 0x74, 0xD1, 0x8B, 0x2D, 0x40, 0x67, 0xF2, 0x61, 0xA9 },
        { 0x02, 0xF9, 0x30, 0x8A, 0x01, 0x92, 0x58, 0xC3, 0x10, 0x49, 0x34, 0x4F, 0x85, 0xF8, 0x9D, 0x52, 0x29, 0xB5, 0x31, 0xC8, 0x45, 0x83, 0x6F, 0x99, 0xB0, 0x86, 0x01, 0xF1, 0x13, 0xBC, 0xE0, 0x36, 0xF9 },
        { 0x02, 0xDF, 0xF1, 0xD7, 0x7F, 0x2A, 0x67, 0x1C, 0x5F, 0x36, 0x18, 0x37, 0x26, 0xDB, 0x23, 0x41, 0xBE, 0x58, 0xFE, 0xAE, 0x1D, 0xA2, 0xDE, 0xCE, 0xD8, 0x43, 0x24, 0x0F, 0x7B, 0x50, 0x2B, 0xA6, 0x59 }
    },
    {
        { 0x03, 0x37, 0xC8, 0x78, 0x21, 0xAF, 0xD5, 0x0A, 0x86, 0x44, 0xD8, 0x20, 0xA8, 0xF3, 0xE0, 0x2E, 0x49, 0x9C, 0x93, 0x18, 0x65, 0xC2, 0x36, 0x0F, 0xB4, 0x3D, 0x0A, 0x0D, 0x20, 0xDA, 0xFE, 0x07, 0xEA, 0x02, 0x87, 0xBF, 0x89, 0x1D, 0x2A, 0x6D, 0xEA, 0xEB, 0xAD, 0xC9, 0x09, 0x35, 0x2A, 0xA9, 0x40, 0x5D, 0x14, 0x28, 0xC1, 0x5F, 0x4B, 0x75, 0xF0, 0x4D, 0xAE, 0x64, 0x2A, 0x95, 0xC2, 0x54, 0x84, 0x80 },
        { 0x02, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98, 0x02, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98 },
        { 0x03, 0x2D, 0xE2, 0x66, 0x26, 0x28, 0xC9, 0x0B, 0x03, 0xF5, 0xE7, 0x20, 0x28, 0x4E, 0xB5, 0x2F, 0xF7, 0xD7, 0x1F, 0x42, 0x84, 0xF6, 0x27, 0xB6, 0x8A, 0x85, 0x3D, 0x78, 0xC7, 0x8E, 0x1F, 0xFE, 0x93, 0x03, 0xE4, 0xC5, 0x52, 0x4E, 0x83, 0xFF, 0xE1, 0x49, 0x3B, 0x90, 0x77, 0xCF, 0x1C, 0xA6, 0xBE, 0xB2, 0x09, 0x0C, 0x93, 0xD9, 0x30, 0x32, 0x10, 0x71, 0xAD, 0x40, 0xB2, 0xF4, 0x4E, 0x59, 0x90, 0x46 }
    },
    {
        { 0xE8, 0xF7, 0x91, 0xFF, 0x92, 0x25, 0xA2, 0xAF, 0x01, 0x02, 0xAF, 0xFF, 0x4A, 0x9A, 0x72, 0x3D, 0x96, 0x12, 0xA6, 0x82, 0xA2, 0x5E, 0xBE, 0x79, 0x80, 0x2B, 0x26, 0x3C, 0xDF, 0xCD, 0x83, 0xBB },
        { 0xAE, 0x2E, 0xA7, 0x97, 0xCC, 0x0F, 0xE7, 0x2A, 0xC5, 0xB9, 0x7B, 0x97, 0xF3, 0xC6, 0x95, 0x7D, 0x7E, 0x41, 0x99, 0xA1, 0x67, 0xA5, 0x8E, 0xB0, 0x8B, 0xCA, 0xFF, 0xDA, 0x70, 0xAC, 0x04, 0x55 },
        { 0xF5, 0x2E, 0xCB, 0xC5, 0x65, 0xB3, 0xD8, 0xBE, 0xA2, 0xDF, 0xD5, 0xB7, 0x5A, 0x4F, 0x45, 0x7E, 0x54, 0x36, 0x98, 0x09, 0x32, 0x2E, 0x41, 0x20, 0x83, 0x16, 0x26, 0xF2, 0x90, 0xFA, 0x87, 0xE0 },
        { 0x19, 0x69, 0xAD, 0x73, 0xCC, 0x17, 0x7F, 0xA0, 0xB4, 0xFC, 0xED, 0x6D, 0xF1, 0xF7, 0xBF, 0x99, 0x07, 0xE6, 0x65, 0xFD, 0xE9, 0xBA, 0x19, 0x6A, 0x74, 0xFE, 0xD0, 0xA3, 0xCF, 0x5A, 0xEF, 0x9D },
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B, 0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41 }
    },
    {
        {  3, { 1, 2, 0 },  3, { 1, 2, 0 },  1, { 0 }, { 1 }, 2, { 0xE2, 0x8A, 0x5C, 0x66, 0xE6, 0x1E, 0x17, 0x8C, 0x2B, 0xA1, 0x9D, 0xB7, 0x7B, 0x6C, 0xF9, 0xF7, 0xE2, 0xF0, 0xF5, 0x6C, 0x17, 0x91, 0x8C, 0xD1, 0x31, 0x35, 0xE6, 0x0C, 0xC8, 0x48, 0xFE, 0x91 }},
        {  3, { 1, 2, 0 },  3, { 1, 2, 0 },  1, { 0 }, { 0 }, 2, { 0x38, 0xB0, 0x76, 0x77, 0x98, 0x25, 0x2F, 0x21, 0xBF, 0x57, 0x02, 0xC4, 0x80, 0x28, 0xB0, 0x95, 0x42, 0x83, 0x20, 0xF7, 0x3A, 0x4B, 0x14, 0xDB, 0x1E, 0x25, 0xDE, 0x58, 0x54, 0x3D, 0x2D, 0x2D }},
        {  3, { 1, 2, 0 },  3, { 1, 2, 0 },  2, { 0, 1 }, { 0, 1 }, 2, { 0x40, 0x8A, 0x0A, 0x21, 0xC4, 0xA0, 0xF5, 0xDA, 0xCA, 0xF9, 0x64, 0x6A, 0xD6, 0xEB, 0x6F, 0xEC, 0xD7, 0xF7, 0xA1, 0x1F, 0x03, 0xED, 0x1F, 0x48, 0xDF, 0xFF, 0x21, 0x85, 0xBC, 0x2C, 0x24, 0x08 }},
        {  3, { 1, 2, 0 },  3, { 1, 2, 0 },  4, { 0, 1, 2, 3 }, { 0, 0, 1, 1 }, 2, { 0x45, 0xAB, 0xD2, 0x06, 0xE6, 0x1E, 0x3D, 0xF2, 0xEC, 0x9E, 0x26, 0x4A, 0x6F, 0xEC, 0x82, 0x92, 0x14, 0x1A, 0x63, 0x3C, 0x28, 0x58, 0x63, 0x88, 0x23, 0x55, 0x41, 0xF9, 0xAD, 0xE7, 0x54, 0x35 }},
        {  3, { 1, 2, 0 },  3, { 1, 2, 0 },  4, { 0, 1, 2, 3 }, { 1, 0, 1, 0 }, 2, { 0xB2, 0x55, 0xFD, 0xCA, 0xC2, 0x7B, 0x40, 0xC7, 0xCE, 0x78, 0x48, 0xE2, 0xD3, 0xB7, 0xBF, 0x5E, 0xA0, 0xED, 0x75, 0x6D, 0xA8, 0x15, 0x65, 0xAC, 0x80, 0x4C, 0xCC, 0xA3, 0xE1, 0xD5, 0xD2, 0x39 }},
    },
    {
        {  3, { 1, 2, 0 },  3, { 1, 2, 0 },  1, { 4 }, { 0 }, 2, { 0 }},
    },
};

/* Omit pubnonces in the test vectors because they're only needed for
 * implementations that do not directly accept an aggnonce. */
struct musig_sig_agg_case {
    size_t key_indices_len;
    size_t key_indices[2];
    size_t tweak_indices_len;
    size_t tweak_indices[3];
    int is_xonly[3];
    unsigned char aggnonce[66];
    size_t psig_indices_len;
    size_t psig_indices[2];
    /* if valid case */
    unsigned char expected[64];
    /* if error case */
    int invalid_sig_idx;
};

struct musig_sig_agg_vector {
    unsigned char pubkeys[4][33];
    unsigned char tweaks[3][32];
    unsigned char psigs[9][32];
    unsigned char msg[32];
    struct musig_sig_agg_case valid_case[4];
    struct musig_sig_agg_case error_case[1];
};

static const struct musig_sig_agg_vector musig_sig_agg_vector = {
    {
        { 0x03, 0x93, 0x5F, 0x97, 0x2D, 0xA0, 0x13, 0xF8, 0x0A, 0xE0, 0x11, 0x89, 0x0F, 0xA8, 0x9B, 0x67, 0xA2, 0x7B, 0x7B, 0xE6, 0xCC, 0xB2, 0x4D, 0x32, 0x74, 0xD1, 0x8B, 0x2D, 0x40, 0x67, 0xF2, 0x61, 0xA9 },
        { 0x02, 0xD2, 0xDC, 0x6F, 0x5D, 0xF7, 0xC5, 0x6A, 0xCF, 0x38, 0xC7, 0xFA, 0x0A, 0xE7, 0xA7, 0x59, 0xAE, 0x30, 0xE1, 0x9B, 0x37, 0x35, 0x9D, 0xFD, 0xE0, 0x15, 0x87, 0x23, 0x24, 0xC7, 0xEF, 0x6E, 0x05 },
        { 0x03, 0xC7, 0xFB, 0x10, 0x1D, 0x97, 0xFF, 0x93, 0x0A, 0xCD, 0x0C, 0x67, 0x60, 0x85, 0x2E, 0xF6, 0x4E, 0x69, 0x08, 0x3D, 0xE0, 0xB0, 0x6A, 0xC6, 0x33, 0x57, 0x24, 0x75, 0x4B, 0xB4, 0xB0, 0x52, 0x2C },
        { 0x02, 0x35, 0x24, 0x33, 0xB2, 0x1E, 0x7E, 0x05, 0xD3, 0xB4, 0x52, 0xB8, 0x1C, 0xAE, 0x56, 0x6E, 0x06, 0xD2, 0xE0, 0x03, 0xEC, 0xE1, 0x6D, 0x10, 0x74, 0xAA, 0xBA, 0x42, 0x89, 0xE0, 0xE3, 0xD5, 0x81 }
    },
    {
        { 0xB5, 0x11, 0xDA, 0x49, 0x21, 0x82, 0xA9, 0x1B, 0x0F, 0xFB, 0x9A, 0x98, 0x02, 0x0D, 0x55, 0xF2, 0x60, 0xAE, 0x86, 0xD7, 0xEC, 0xBD, 0x03, 0x99, 0xC7, 0x38, 0x3D, 0x59, 0xA5, 0xF2, 0xAF, 0x7C },
        { 0xA8, 0x15, 0xFE, 0x04, 0x9E, 0xE3, 0xC5, 0xAA, 0xB6, 0x63, 0x10, 0x47, 0x7F, 0xBC, 0x8B, 0xCC, 0xCA, 0xC2, 0xF3, 0x39, 0x5F, 0x59, 0xF9, 0x21, 0xC3, 0x64, 0xAC, 0xD7, 0x8A, 0x2F, 0x48, 0xDC },
        { 0x75, 0x44, 0x8A, 0x87, 0x27, 0x4B, 0x05, 0x64, 0x68, 0xB9, 0x77, 0xBE, 0x06, 0xEB, 0x1E, 0x9F, 0x65, 0x75, 0x77, 0xB7, 0x32, 0x0B, 0x0A, 0x33, 0x76, 0xEA, 0x51, 0xFD, 0x42, 0x0D, 0x18, 0xA8 }
    },
    {
        { 0xB1, 0x5D, 0x2C, 0xD3, 0xC3, 0xD2, 0x2B, 0x04, 0xDA, 0xE4, 0x38, 0xCE, 0x65, 0x3F, 0x6B, 0x4E, 0xCF, 0x04, 0x2F, 0x42, 0xCF, 0xDE, 0xD7, 0xC4, 0x1B, 0x64, 0xAA, 0xF9, 0xB4, 0xAF, 0x53, 0xFB },
        { 0x61, 0x93, 0xD6, 0xAC, 0x61, 0xB3, 0x54, 0xE9, 0x10, 0x5B, 0xBD, 0xC8, 0x93, 0x7A, 0x34, 0x54, 0xA6, 0xD7, 0x05, 0xB6, 0xD5, 0x73, 0x22, 0xA5, 0xA4, 0x72, 0xA0, 0x2C, 0xE9, 0x9F, 0xCB, 0x64 },
        { 0x9A, 0x87, 0xD3, 0xB7, 0x9E, 0xC6, 0x72, 0x28, 0xCB, 0x97, 0x87, 0x8B, 0x76, 0x04, 0x9B, 0x15, 0xDB, 0xD0, 0x5B, 0x81, 0x58, 0xD1, 0x7B, 0x5B, 0x91, 0x14, 0xD3, 0xC2, 0x26, 0x88, 0x75, 0x05 },
        { 0x66, 0xF8, 0x2E, 0xA9, 0x09, 0x23, 0x68, 0x9B, 0x85, 0x5D, 0x36, 0xC6, 0xB7, 0xE0, 0x32, 0xFB, 0x99, 0x70, 0x30, 0x14, 0x81, 0xB9, 0x9E, 0x01, 0xCD, 0xB4, 0xD6, 0xAC, 0x7C, 0x34, 0x7A, 0x15 },
        { 0x4F, 0x5A, 0xEE, 0x41, 0x51, 0x08, 0x48, 0xA6, 0x44, 0x7D, 0xCD, 0x1B, 0xBC, 0x78, 0x45, 0x7E, 0xF6, 0x90, 0x24, 0x94, 0x4C, 0x87, 0xF4, 0x02, 0x50, 0xD3, 0xEF, 0x2C, 0x25, 0xD3, 0x3E, 0xFE },
        { 0xDD, 0xEF, 0x42, 0x7B, 0xBB, 0x84, 0x7C, 0xC0, 0x27, 0xBE, 0xFF, 0x4E, 0xDB, 0x01, 0x03, 0x81, 0x48, 0x91, 0x78, 0x32, 0x25, 0x3E, 0xBC, 0x35, 0x5F, 0xC3, 0x3F, 0x4A, 0x8E, 0x2F, 0xCC, 0xE4 },
        { 0x97, 0xB8, 0x90, 0xA2, 0x6C, 0x98, 0x1D, 0xA8, 0x10, 0x2D, 0x3B, 0xC2, 0x94, 0x15, 0x9D, 0x17, 0x1D, 0x72, 0x81, 0x0F, 0xDF, 0x7C, 0x6A, 0x69, 0x1D, 0xEF, 0x02, 0xF0, 0xF7, 0xAF, 0x3F, 0xDC },
        { 0x53, 0xFA, 0x9E, 0x08, 0xBA, 0x52, 0x43, 0xCB, 0xCB, 0x0D, 0x79, 0x7C, 0x5E, 0xE8, 0x3B, 0xC6, 0x72, 0x8E, 0x53, 0x9E, 0xB7, 0x6C, 0x2D, 0x0B, 0xF0, 0xF9, 0x71, 0xEE, 0x4E, 0x90, 0x99, 0x71 },
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B, 0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41 }
    },
    { 0x59, 0x9C, 0x67, 0xEA, 0x41, 0x0D, 0x00, 0x5B, 0x9D, 0xA9, 0x08, 0x17, 0xCF, 0x03, 0xED, 0x3B, 0x1C, 0x86, 0x8E, 0x4D, 0xA4, 0xED, 0xF0, 0x0A, 0x58, 0x80, 0xB0, 0x08, 0x2C, 0x23, 0x78, 0x69 },
    {
        {  2, { 0, 1 },  0, { 0 }, { 0 }, { 0x03, 0x41, 0x43, 0x27, 0x22, 0xC5, 0xCD, 0x02, 0x68, 0xD8, 0x29, 0xC7, 0x02, 0xCF, 0x0D, 0x1C, 0xBC, 0xE5, 0x70, 0x33, 0xEE, 0xD2, 0x01, 0xFD, 0x33, 0x51, 0x91, 0x38, 0x52, 0x27, 0xC3, 0x21, 0x0C, 0x03, 0xD3, 0x77, 0xF2, 0xD2, 0x58, 0xB6, 0x4A, 0xAD, 0xC0, 0xE1, 0x6F, 0x26, 0x46, 0x23, 0x23, 0xD7, 0x01, 0xD2, 0x86, 0x04, 0x6A, 0x2E, 0xA9, 0x33, 0x65, 0x65, 0x6A, 0xFD, 0x98, 0x75, 0x98, 0x2B },  2, { 0, 1 }, { 0x04, 0x1D, 0xA2, 0x22, 0x23, 0xCE, 0x65, 0xC9, 0x2C, 0x9A, 0x0D, 0x6C, 0x2C, 0xAC, 0x82, 0x8A, 0xAF, 0x1E, 0xEE, 0x56, 0x30, 0x4F, 0xEC, 0x37, 0x1D, 0xDF, 0x91, 0xEB, 0xB2, 0xB9, 0xEF, 0x09, 0x12, 0xF1, 0x03, 0x80, 0x25, 0x85, 0x7F, 0xED, 0xEB, 0x3F, 0xF6, 0x96, 0xF8, 0xB9, 0x9F, 0xA4, 0xBB, 0x2C, 0x58, 0x12, 0xF6, 0x09, 0x5A, 0x2E, 0x00, 0x04, 0xEC, 0x99, 0xCE, 0x18, 0xDE, 0x1E }, 0 },
        {  2, { 0, 2 },  0, { 0 }, { 0 }, { 0x02, 0x24, 0xAF, 0xD3, 0x6C, 0x90, 0x20, 0x84, 0x05, 0x8B, 0x51, 0xB5, 0xD3, 0x66, 0x76, 0xBB, 0xA4, 0xDC, 0x97, 0xC7, 0x75, 0x87, 0x37, 0x68, 0xE5, 0x88, 0x22, 0xF8, 0x7F, 0xE4, 0x37, 0xD7, 0x92, 0x02, 0x8C, 0xB1, 0x59, 0x29, 0x09, 0x9E, 0xEE, 0x2F, 0x5D, 0xAE, 0x40, 0x4C, 0xD3, 0x93, 0x57, 0x59, 0x1B, 0xA3, 0x2E, 0x9A, 0xF4, 0xE1, 0x62, 0xB8, 0xD3, 0xE7, 0xCB, 0x5E, 0xFE, 0x31, 0xCB, 0x20 },  2, { 2, 3 }, { 0x10, 0x69, 0xB6, 0x7E, 0xC3, 0xD2, 0xF3, 0xC7, 0xC0, 0x82, 0x91, 0xAC, 0xCB, 0x17, 0xA9, 0xC9, 0xB8, 0xF2, 0x81, 0x9A, 0x52, 0xEB, 0x5D, 0xF8, 0x72, 0x6E, 0x17, 0xE7, 0xD6, 0xB5, 0x2E, 0x9F, 0x01, 0x80, 0x02, 0x60, 0xA7, 0xE9, 0xDA, 0xC4, 0x50, 0xF4, 0xBE, 0x52, 0x2D, 0xE4, 0xCE, 0x12, 0xBA, 0x91, 0xAE, 0xAF, 0x2B, 0x42, 0x79, 0x21, 0x9E, 0xF7, 0x4B, 0xE1, 0xD2, 0x86, 0xAD, 0xD9 }, 0 },
        {  2, { 0, 2 },  1, { 0 }, { 0 }, { 0x02, 0x08, 0xC5, 0xC4, 0x38, 0xC7, 0x10, 0xF4, 0xF9, 0x6A, 0x61, 0xE9, 0xFF, 0x3C, 0x37, 0x75, 0x88, 0x14, 0xB8, 0xC3, 0xAE, 0x12, 0xBF, 0xEA, 0x0E, 0xD2, 0xC8, 0x7F, 0xF6, 0x95, 0x4F, 0xF1, 0x86, 0x02, 0x0B, 0x18, 0x16, 0xEA, 0x10, 0x4B, 0x4F, 0xCA, 0x2D, 0x30, 0x4D, 0x73, 0x3E, 0x0E, 0x19, 0xCE, 0xAD, 0x51, 0x30, 0x3F, 0xF6, 0x42, 0x0B, 0xFD, 0x22, 0x23, 0x35, 0xCA, 0xA4, 0x02, 0x91, 0x6D },  2, { 4, 5 }, { 0x5C, 0x55, 0x8E, 0x1D, 0xCA, 0xDE, 0x86, 0xDA, 0x0B, 0x2F, 0x02, 0x62, 0x6A, 0x51, 0x2E, 0x30, 0xA2, 0x2C, 0xF5, 0x25, 0x5C, 0xAE, 0xA7, 0xEE, 0x32, 0xC3, 0x8E, 0x9A, 0x71, 0xA0, 0xE9, 0x14, 0x8B, 0xA6, 0xC0, 0xE6, 0xEC, 0x76, 0x83, 0xB6, 0x42, 0x20, 0xF0, 0x29, 0x86, 0x96, 0xF1, 0xB8, 0x78, 0xCD, 0x47, 0xB1, 0x07, 0xB8, 0x1F, 0x71, 0x88, 0x81, 0x2D, 0x59, 0x39, 0x71, 0xE0, 0xCC }, 0 },
        {  2, { 0, 3 },  3, { 0, 1, 2 }, { 1, 0, 1 }, { 0x02, 0xB5, 0xAD, 0x07, 0xAF, 0xCD, 0x99, 0xB6, 0xD9, 0x2C, 0xB4, 0x33, 0xFB, 0xD2, 0xA2, 0x8F, 0xDE, 0xB9, 0x8E, 0xAE, 0x2E, 0xB0, 0x9B, 0x60, 0x14, 0xEF, 0x0F, 0x81, 0x97, 0xCD, 0x58, 0x40, 0x33, 0x02, 0xE8, 0x61, 0x69, 0x10, 0xF9, 0x29, 0x3C, 0xF6, 0x92, 0xC4, 0x9F, 0x35, 0x1D, 0xB8, 0x6B, 0x25, 0xE3, 0x52, 0x90, 0x1F, 0x0E, 0x23, 0x7B, 0xAF, 0xDA, 0x11, 0xF1, 0xC1, 0xCE, 0xF2, 0x9F, 0xFD },  2, { 6, 7 }, { 0x83, 0x9B, 0x08, 0x82, 0x0B, 0x68, 0x1D, 0xBA, 0x8D, 0xAF, 0x4C, 0xC7, 0xB1, 0x04, 0xE8, 0xF2, 0x63, 0x8F, 0x93, 0x88, 0xF8, 0xD7, 0xA5, 0x55, 0xDC, 0x17, 0xB6, 0xE6, 0x97, 0x1D, 0x74, 0x26, 0xCE, 0x07, 0xBF, 0x6A, 0xB0, 0x1F, 0x1D, 0xB5, 0x0E, 0x4E, 0x33, 0x71, 0x92, 0x95, 0xF4, 0x09, 0x45, 0x72, 0xB7, 0x98, 0x68, 0xE4, 0x40, 0xFB, 0x3D, 0xEF, 0xD3, 0xFA, 0xC1, 0xDB, 0x58, 0x9E }, 0 },
    },
    {
        {  2, { 0, 3 },  3, { 0, 1, 2 }, { 1, 0, 1 }, { 0x02, 0xB5, 0xAD, 0x07, 0xAF, 0xCD, 0x99, 0xB6, 0xD9, 0x2C, 0xB4, 0x33, 0xFB, 0xD2, 0xA2, 0x8F, 0xDE, 0xB9, 0x8E, 0xAE, 0x2E, 0xB0, 0x9B, 0x60, 0x14, 0xEF, 0x0F, 0x81, 0x97, 0xCD, 0x58, 0x40, 0x33, 0x02, 0xE8, 0x61, 0x69, 0x10, 0xF9, 0x29, 0x3C, 0xF6, 0x92, 0xC4, 0x9F, 0x35, 0x1D, 0xB8, 0x6B, 0x25, 0xE3, 0x52, 0x90, 0x1F, 0x0E, 0x23, 0x7B, 0xAF, 0xDA, 0x11, 0xF1, 0xC1, 0xCE, 0xF2, 0x9F, 0xFD },  2, { 7, 8 }, { 0 }, 1 },
    },
};
enum { MUSIG_VECTORS_MAX_PUBKEYS = 7 };
