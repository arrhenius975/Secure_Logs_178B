// DO-178B: Access control module implementation
// Requirement Traceability: REQ-AC-001 through REQ-AC-010
#include "access_control.h"
#include "../../utils/crypto_utils.h"
#include <cstring>
#include <ctime>

AccessControl::AccessControl() : user_count(0), initialized(false) {
    std::memset(users, 0, sizeof(users));
}

AccessControl::~AccessControl() {
    if (initialized) {
        shutdown();
    }
}

return_t AccessControl::initialize() {
    if (initialized) {
        return ERR_ALREADY_INITIALIZED;
    }
    
    std::memset(users, 0, sizeof(users));
    user_count = 0;
    initialized = true;
    
    return OK;
}

return_t AccessControl::shutdown() {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    std::memset(users, 0, sizeof(users));
    user_count = 0;
    initialized = false;
    
    return OK;
}

return_t AccessControl::authenticate_user(uint32_t user_id, const byte_t* token, uint32_t token_len) {
    if (!initialized || !token || token_len == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    for (uint32_t i = 0; i < user_count; i++) {
        if (users[i].user_id == user_id) {
            if (std::memcmp(users[i].authentication_token, token, 
                           token_len < 32 ? token_len : 32) != 0) {
                return ERR_AUTHENTICATION_FAILED;
            }
            
            timestamp_t now = static_cast<timestamp_t>(std::time(nullptr));
            if (users[i].token_expiry < now) {
                return ERR_INVALID_TOKEN;
            }
            
            return OK;
        }
    }
    
    return ERR_AUTHENTICATION_FAILED;
}

return_t AccessControl::authorize_action(uint32_t user_id, UserRole required_role) {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    for (uint32_t i = 0; i < user_count; i++) {
        if (users[i].user_id == user_id) {
            if (users[i].role < required_role) {
                return ERR_AUTHORIZATION_DENIED;
            }
            return OK;
        }
    }
    
    return ERR_AUTHENTICATION_FAILED;
}

return_t AccessControl::register_user(uint32_t user_id, UserRole role, const byte_t* token) {
    if (!initialized || !token || user_count >= MAX_USERS) {
        return ERR_INVALID_PARAMETER;
    }
    
    for (uint32_t i = 0; i < user_count; i++) {
        if (users[i].user_id == user_id) {
            return ERR_GENERAL_FAILURE;
        }
    }
    
    UserCredential& new_user = users[user_count];
    new_user.user_id = user_id;
    new_user.role = role;
    new_user.token_expiry = static_cast<timestamp_t>(std::time(nullptr)) + AUTHENTICATION_TIMEOUT;
    
    std::memcpy(new_user.authentication_token, token, 32);
    user_count++;
    
    return OK;
}

return_t AccessControl::revoke_user(uint32_t user_id) {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    for (uint32_t i = 0; i < user_count; i++) {
        if (users[i].user_id == user_id) {
            std::memset(&users[i], 0, sizeof(UserCredential));
            
            if (i < user_count - 1) {
                std::memcpy(&users[i], &users[user_count - 1], sizeof(UserCredential));
            }
            
            user_count--;
            return OK;
        }
    }
    
    return ERR_GENERAL_FAILURE;
}

return_t AccessControl::validate_token(const byte_t* token, uint32_t token_len) {
    if (!token || token_len == 0) {
        return ERR_INVALID_PARAMETER;
    }
    
    return CryptoUtils::verify_checksum(token, token_len, token[0]);
}
