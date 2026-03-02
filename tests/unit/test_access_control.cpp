// DO-178B: Access control unit tests
// Requirement Traceability: REQ-TEST-AC-001 through REQ-TEST-AC-008
// Compliance Level: Level A (verification of security-critical authentication)

#include "../src/modules/access_control/access_control.h"
#include "../include/error_codes.h"
#include <cassert>
#include <iostream>
#include <cstring>

int main() {
    AccessControl ac;
    
    assert(ac.initialize() == OK);
    assert(ac.initialize() == ERR_ALREADY_INITIALIZED);
    
    byte_t token1[32] = {1, 2, 3};
    byte_t token2[32] = {4, 5, 6};
    
    assert(ac.register_user(1, ROLE_ADMINISTRATOR, token1) == OK);
    assert(ac.register_user(2, ROLE_OPERATOR, token2) == OK);
    
    assert(ac.authenticate_user(1, token1, 32) == OK);
    assert(ac.authenticate_user(1, token2, 32) == ERR_AUTHENTICATION_FAILED);
    
    assert(ac.authorize_action(1, ROLE_VIEWER) == OK);
    assert(ac.authorize_action(2, ROLE_ADMINISTRATOR) == ERR_AUTHORIZATION_DENIED);
    
    assert(ac.revoke_user(1) == OK);
    assert(ac.authenticate_user(1, token1, 32) == ERR_AUTHENTICATION_FAILED);
    
    assert(ac.shutdown() == OK);
    assert(ac.shutdown() == ERR_NOT_INITIALIZED);
    
    std::cout << "All access control tests passed" << std::endl;
    return 0;
}
