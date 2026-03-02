// DO-178B: Logger unit tests
// Requirement Traceability: REQ-TEST-LOG-001 through REQ-TEST-LOG-010
// Compliance Level: Level A (verification of critical logging functionality)

#include "../src/modules/logging/logger.h"
#include "../include/error_codes.h"
#include <cassert>
#include <iostream>

int main() {
    Logger logger;
    
    assert(logger.initialize() == OK);
    assert(logger.initialize() == ERR_ALREADY_INITIALIZED);
    
    assert(logger.log_message(LOG_INFO, 1, "Test message 1") == OK);
    assert(logger.log_message(LOG_WARNING, 2, "Test warning") == OK);
    assert(logger.log_message(LOG_ERROR, 3, "Test error") == OK);
    
    assert(logger.get_total_entries() == 3);
    
    LogEntry entry;
    assert(logger.get_log_entry(0, entry) == OK);
    assert(entry.level == LOG_INFO);
    assert(entry.source_id == 1);
    
    assert(logger.export_logs("test_logs.bin") == OK);
    
    assert(logger.clear_logs() == OK);
    assert(logger.get_total_entries() == 0);
    
    assert(logger.shutdown() == OK);
    assert(logger.shutdown() == ERR_NOT_INITIALIZED);
    
    std::cout << "All logger tests passed" << std::endl;
    return 0;
}
