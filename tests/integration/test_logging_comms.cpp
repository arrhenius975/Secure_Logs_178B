// DO-178B: Logging and communication integration tests
// Requirement Traceability: REQ-TEST-INT-001 through REQ-TEST-INT-005
// Compliance Level: Level A (verification of end-to-end functionality)

#include "../src/modules/logging/logger.h"
#include "../src/modules/communication/comms.h"
#include "../src/modules/access_control/access_control.h"
#include "../include/error_codes.h"
#include <cassert>
#include <iostream>
#include <cstring>

int main() {
    Logger logger;
    Communication comms;
    AccessControl ac;
    
    byte_t key[32] = {0};
    for (int i = 0; i < 32; i++) {
        key[i] = static_cast<byte_t>((i * 3 + 7) & 0xFF);
    }
    
    assert(logger.initialize() == OK);
    assert(comms.initialize(key) == OK);
    assert(ac.initialize() == OK);
    
    assert(logger.log_message(LOG_INFO, 1, "Integration test: System initialized") == OK);
    assert(logger.log_message(LOG_INFO, 1, "Integration test: Communication channel open") == OK);
    
    byte_t token[32] = {0};
    for (int i = 0; i < 32; i++) {
        token[i] = static_cast<byte_t>((i * 5 + 2) & 0xFF);
    }
    
    assert(ac.register_user(999, ROLE_ADMINISTRATOR, token) == OK);
    assert(ac.authenticate_user(999, token, 32) == OK);
    
    LogEntry entry;
    assert(logger.get_log_entry(0, entry) == OK);
    assert(comms.send_packet(entry) == OK);
    
    assert(logger.get_total_entries() == 2);
    
    assert(logger.shutdown() == OK);
    assert(comms.shutdown() == OK);
    assert(ac.shutdown() == OK);
    
    std::cout << "All integration tests passed" << std::endl;
    return 0;
}
