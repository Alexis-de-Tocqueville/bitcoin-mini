#ifndef SECP256K1_ECDSA_ADAPTOR_H
#define SECP256K1_ECDSA_ADAPTOR_H

#ifdef __cplusplus
extern "C" {
#endif


/* note: adaptor_proof129 is 129 because 1*R + 1*R' + 1*e + 1*x = 2*32 + 1 + 32 + 32 */

/** Adaptor sign
 *  TODO: add nonce function
 *
 *  Returns: 1 on success, 0 on failure
 *  Args:             ctx: a secp256k1 context object
 *  Out:    adaptor_sig32: pointer to 32-byte to store the returned signature
 *       adaptor_proof129: pointer to 129-byte to store the adaptor proof
 *  In:           adaptor: adaptor point
 *                  msg32: the 32-byte message to sign
 *
 */
SECP256K1_API int secp256k1_ecdsa_adaptor_sign(
    const secp256k1_context* ctx,
    unsigned char *adaptor_sig32,
    unsigned char *adaptor_proof129,
    const secp256k1_pubkey *adaptor,
    const unsigned char *msg32
) SECP256K1_ARG_NONNULL(1) SECP256K1_ARG_NONNULL(2) SECP256K1_ARG_NONNULL(3) SECP256K1_ARG_NONNULL(4);

/** Adaptor verify
 *
 *  Returns: 1 on success, 0 on failure
 *  Args:             ctx: a secp256k1 context object
 *  In:     adaptor_sig32: pointer to 32-byte signature to verify
 *                 pubkey: pubkey
 *                  msg32: 32-byte message
 *                adaptor: adaptor point
 *       adaptor_proof129: pointer to 129-byte adaptor proof
 *
 */
SECP256K1_API int secp256k1_ecdsa_adaptor_sig_verify(
    const secp256k1_context* ctx,
    const unsigned char *adaptor_sig32,
    const secp256k1_pubkey *pubkey,
    const unsigned char *msg32,
    const secp256k1_pubkey *adaptor,
    const unsigned char *adaptor_proof129,
) SECP256K1_ARG_NONNULL(1) SECP256K1_ARG_NONNULL(2) SECP256K1_ARG_NONNULL(3) SECP256K1_ARG_NONNULL(4) SECP256K1_ARG_NONNULL(5) SECP256K1_ARG_NONNULL(6);

/** Adapt aka complete
 *
 *  Returns: 1 on success, 0 on failure
 *  Args:             ctx: a secp256k1 context object
 *  Out:              sig: ecdsa signature
 *  In:  adaptor_secret32: pointer to 32-byte byte adaptor secret of the adaptor point
 *       adaptor_proof129: pointer to 129-byte byte adaptor proof
 *
 */
 SECP256K1_API int secp256k1_ecdsa_adaptor_adapt(
    const secp256k1_context* ctx,
    secp256k1_ecdsa_signature *sig,
    const unsigned char *adaptor_secret32,
    const unsigned char *adaptor_proof129,
) SECP256K1_ARG_NONNULL(1) SECP256K1_ARG_NONNULL(2) SECP256K1_ARG_NONNULL(3) SECP256K1_ARG_NONNULL(4);

/** Adaptor extract
 *
 *  Returns: 1 on success, 0 on failure
 *  Args:             ctx: a secp256k1 context object
 *  Out: adaptor_secret32: pointer to 32-byte adaptor secret of the adaptor point
 *  In:               sig: ecdsa signature to extract the adaptor_secret from
 *            adaptor_sig: adaptor sig to extract the adaptor_secret from
 *                adaptor: adaptor point
 *
 */
SECP256K1_API int secp256k1_ecdsa_adaptor_extract_secret(
    const secp256k1_context* ctx,
    unsigned char *adaptor_secret32,
    const secp256k1_ecdsa_signature *sig,
    const unsigned char *adaptor_sig32,
    const secp256k1_pubkey *adaptor
) SECP256K1_ARG_NONNULL(1) SECP256K1_ARG_NONNULL(2) SECP256K1_ARG_NONNULL(3) SECP256K1_ARG_NONNULL(4) SECP256K1_ARG_NONNULL(5);

#ifdef __cplusplus
}
#endif

#endif /* SECP256K1_ADAPTOR_H */
