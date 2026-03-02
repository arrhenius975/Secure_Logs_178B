// DO-178B: Cryptographic utilities for secure logging
// Requirement Traceability: REQ-CRYPTO-001 through REQ-CRYPTO-008  
// Compliance Level: Level A (security-critical operations)
#pragma once

#include "types.h"

class CryptoUtils {
public:
    static return_t compute_hash(const byte_t* data, uint32_t length, byte_t* hash_out);
    static return_t compute_hmac(const byte_t* key, uint32_t key_len, 
                                 const byte_t* data, uint32_t data_len, byte_t* hmac_out);
    static return_t verify_checksum(const byte_t* data, uint32_t length, byte_t checksum);
    static byte_t generate_checksum(const byte_t* data, uint32_t length);
    static return_t encrypt_aes_256(const byte_t* plaintext, uint32_t plaintext_len,
                                    const byte_t* key, byte_t* ciphertext);
    static return_t decrypt_aes_256(const byte_t* ciphertext, uint32_t ciphertext_len,
                                    const byte_t* key, byte_t* plaintext);
};
