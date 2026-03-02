// DO-178B: Communication module interface
// Requirement Traceability: REQ-COMM-001 through REQ-COMM-008
// Compliance Level: Level A (secure transmission)
#pragma once

#include "types.h"
#include "error_codes.h"
#include "config.h"

class Communication {
private:
    byte_t send_buffer[BUFFER_SIZE];
    byte_t receive_buffer[BUFFER_SIZE];
    byte_t encryption_key[CRYPTO_KEY_SIZE];
    bool initialized;
    uint32_t packet_counter;
    
public:
    Communication();
    ~Communication();
    
    return_t initialize(const byte_t* key);
    return_t shutdown();
    return_t send_packet(const LogEntry& entry);
    return_t receive_packet(CommunicationPacket& packet);
    return_t encrypt_payload(const byte_t* plaintext, uint32_t plaintext_len, 
                            byte_t* ciphertext, uint32_t& ciphertext_len);
    return_t decrypt_payload(const byte_t* ciphertext, uint32_t ciphertext_len,
                            byte_t* plaintext, uint32_t& plaintext_len);
};
