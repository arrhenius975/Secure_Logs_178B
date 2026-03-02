// DO-178B: Access control module interface
// Requirement Traceability: REQ-AC-001 through REQ-AC-010
// Compliance Level: Level A (authorization-critical)
#pragma once

#include "types.h"
#include "error_codes.h"
#include "config.h"

class AccessControl {
private:
    UserCredential users[MAX_USERS];
    uint32_t user_count;
    bool initialized;
    
public:
    AccessControl();
    ~AccessControl();
    
    return_t initialize();
    return_t shutdown();
    return_t authenticate_user(uint32_t user_id, const byte_t* token, uint32_t token_len);
    return_t authorize_action(uint32_t user_id, UserRole required_role);
    return_t register_user(uint32_t user_id, UserRole role, const byte_t* token);
    return_t revoke_user(uint32_t user_id);
    return_t validate_token(const byte_t* token, uint32_t token_len);
};
