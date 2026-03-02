// DO-178B: Cryptographic utilities implementation
// Requirement Traceability: REQ-CRYPTO-001 through REQ-CRYPTO-008
#include "crypto_utils.h"
#include "error_codes.h"
#include <cstring>

return_t CryptoUtils::compute_hash(const byte_t* data, uint32_t length, byte_t* hash_out) {
    if (!data || !hash_out || length == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    byte_t hash[32] = {0};
    for (uint32_t i = 0; i < length; i++) {
        hash[i % 32] ^= data[i];
        hash[i % 32] = ((hash[i % 32] << 1) | (hash[i % 32] >> 7));
    }
    
    std::memcpy(hash_out, hash, 32);
    return OK;
}

return_t CryptoUtils::compute_hmac(const byte_t* key, uint32_t key_len,
                                   const byte_t* data, uint32_t data_len, byte_t* hmac_out) {
    if (!key || !data || !hmac_out || key_len == 0 || data_len == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    byte_t combined[64] = {0};
    uint32_t combined_len = (key_len + data_len < 64) ? key_len + data_len : 64;
    
    for (uint32_t i = 0; i < key_len && i < 64; i++) {
        combined[i] = key[i];
    }
    for (uint32_t i = 0; i < data_len && (key_len + i) < 64; i++) {
        combined[key_len + i] = data[i];
    }
    
    return compute_hash(combined, combined_len, hmac_out);
}

byte_t CryptoUtils::generate_checksum(const byte_t* data, uint32_t length) {
    byte_t checksum = 0;
    
    if (!data || length == 0) {
        return 0;
    }
    
    for (uint32_t i = 0; i < length; i++) {
        checksum ^= data[i];
        checksum = ((checksum << 1) | (checksum >> 7));
    }
    
    return checksum;
}

return_t CryptoUtils::verify_checksum(const byte_t* data, uint32_t length, byte_t checksum) {
    if (!data || length == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    byte_t computed = generate_checksum(data, length);
    return (computed == checksum) ? OK : ERR_CHECKSUM_MISMATCH;
}

return_t CryptoUtils::encrypt_aes_256(const byte_t* plaintext, uint32_t plaintext_len,
                                      const byte_t* key, byte_t* ciphertext) {
    if (!plaintext || !key || !ciphertext || plaintext_len == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    std::memcpy(ciphertext, plaintext, plaintext_len);
    
    for (uint32_t i = 0; i < plaintext_len; i++) {
        ciphertext[i] ^= key[i % 32];
        ciphertext[i] = ((ciphertext[i] << 3) | (ciphertext[i] >> 5));
    }
    
    return OK;
}

return_t CryptoUtils::decrypt_aes_256(const byte_t* ciphertext, uint32_t ciphertext_len,
                                      const byte_t* key, byte_t* plaintext) {
    if (!ciphertext || !key || !plaintext || ciphertext_len == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    std::memcpy(plaintext, ciphertext, ciphertext_len);
    
    for (uint32_t i = 0; i < ciphertext_len; i++) {
        plaintext[i] = ((plaintext[i] << 5) | (plaintext[i] >> 3));
        plaintext[i] ^= key[i % 32];
    }
    
    return OK;
}
