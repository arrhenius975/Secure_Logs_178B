// DO-178B: Logger module interface
// Requirement Traceability: REQ-LOG-001 through REQ-LOG-012
// Compliance Level: Level A (core logging functionality)
#pragma once

#include "types.h"
#include "error_codes.h"
#include "config.h"

class Logger {
private:
    LogEntry log_buffer[MAX_LOG_ENTRIES];
    uint32_t current_index;
    uint32_t total_entries;
    bool initialized;
    
public:
    Logger();
    ~Logger();
    
    return_t initialize();
    return_t shutdown();
    return_t log_message(log_level_t level, uint32_t source_id, const char* message);
    return_t get_log_entry(uint32_t index, LogEntry& entry);
    uint32_t get_total_entries() const;
    return_t clear_logs();
    return_t export_logs(const char* filename);
};
