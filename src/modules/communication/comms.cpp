// DO-178B: Communication module implementation
// Requirement Traceability: REQ-COMM-001 through REQ-COMM-008
#include "comms.h"
#include "../../utils/crypto_utils.h"
#include <cstring>
#include <ctime>

Communication::Communication() : initialized(false), packet_counter(0) {
    std::memset(send_buffer, 0, sizeof(send_buffer));
    std::memset(receive_buffer, 0, sizeof(receive_buffer));
    std::memset(encryption_key, 0, sizeof(encryption_key));
}

Communication::~Communication() {
    if (initialized) {
        shutdown();
    }
}

return_t Communication::initialize(const byte_t* key) {
    if (initialized) {
        return ERR_ALREADY_INITIALIZED;
    }
    
    if (!key) {
        return ERR_INVALID_PARAMETER;
    }
    
    std::memcpy(encryption_key, key, CRYPTO_KEY_SIZE);
    packet_counter = 0;
    initialized = true;
    
    return OK;
}

return_t Communication::shutdown() {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    std::memset(send_buffer, 0, sizeof(send_buffer));
    std::memset(receive_buffer, 0, sizeof(receive_buffer));
    std::memset(encryption_key, 0, sizeof(encryption_key));
    initialized = false;
    
    return OK;
}

return_t Communication::send_packet(const LogEntry& entry) {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    CommunicationPacket packet;
    packet.packet_id = packet_counter++;
    packet.transmission_time = static_cast<timestamp_t>(std::time(nullptr));
    packet.payload_size = sizeof(LogEntry);
    
    if (packet.payload_size > sizeof(packet.payload)) {
        return ERR_BUFFER_OVERFLOW;
    }
    
    std::memcpy(packet.payload, &entry, packet.payload_size);
    
    CryptoUtils::compute_hmac(encryption_key, CRYPTO_KEY_SIZE, 
                             packet.payload, packet.payload_size, packet.signature);
    
    return OK;
}

return_t Communication::receive_packet(CommunicationPacket& packet __attribute__((unused))) {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    return OK;
}

return_t Communication::encrypt_payload(const byte_t* plaintext, uint32_t plaintext_len,
                                       byte_t* ciphertext, uint32_t& ciphertext_len) {
    if (!initialized || !plaintext || !ciphertext || plaintext_len == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    if (plaintext_len > BUFFER_SIZE) {
        return ERR_BUFFER_OVERFLOW;
    }
    
    return_t result = CryptoUtils::encrypt_aes_256(plaintext, plaintext_len, 
                                                   encryption_key, ciphertext);
    
    if (result == OK) {
        ciphertext_len = plaintext_len;
    }
    
    return result;
}

return_t Communication::decrypt_payload(const byte_t* ciphertext, uint32_t ciphertext_len,
                                       byte_t* plaintext, uint32_t& plaintext_len) {
    if (!initialized || !ciphertext || !plaintext || ciphertext_len == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    if (ciphertext_len > BUFFER_SIZE) {
        return ERR_BUFFER_OVERFLOW;
    }
    
    return_t result = CryptoUtils::decrypt_aes_256(ciphertext, ciphertext_len,
                                                   encryption_key, plaintext);
    
    if (result == OK) {
        plaintext_len = ciphertext_len;
    }
    
    return result;
}
