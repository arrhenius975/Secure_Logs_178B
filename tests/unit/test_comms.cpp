// DO-178B: Communication module unit tests
// Requirement Traceability: REQ-TEST-COMM-001 through REQ-TEST-COMM-006
// Compliance Level: Level A (verification of secure transmission)

#include "../src/modules/communication/comms.h"
#include "../include/error_codes.h"
#include <cassert>
#include <iostream>
#include <cstring>

int main() {
    Communication comms;
    
    byte_t key[32] = {0};
    for (int i = 0; i < 32; i++) {
        key[i] = static_cast<byte_t>(i & 0xFF);
    }
    
    assert(comms.initialize(key) == OK);
    assert(comms.initialize(key) == ERR_ALREADY_INITIALIZED);
    
    byte_t plaintext[] = "Hello, World!";
    byte_t ciphertext[256] = {0};
    byte_t decrypted[256] = {0};
    uint32_t cipher_len = 0;
    uint32_t decrypt_len = 0;
    
    assert(comms.encrypt_payload(plaintext, 13, ciphertext, cipher_len) == OK);
    assert(cipher_len == 13);
    
    assert(comms.decrypt_payload(ciphertext, cipher_len, decrypted, decrypt_len) == OK);
    assert(decrypt_len == 13);
    assert(std::memcmp(plaintext, decrypted, 13) == 0);
    
    assert(comms.shutdown() == OK);
    assert(comms.shutdown() == ERR_NOT_INITIALIZED);
    
    std::cout << "All communication tests passed" << std::endl;
    return 0;
}
