// DO-178B: Logger module implementation
// Requirement Traceability: REQ-LOG-001 through REQ-LOG-012
#include "logger.h"
#include "../../utils/crypto_utils.h"
#include <ctime>
#include <cstring>
#include <fstream>

Logger::Logger() : current_index(0), total_entries(0), initialized(false) {
    std::memset(log_buffer, 0, sizeof(log_buffer));
}

Logger::~Logger() {
    if (initialized) {
        shutdown();
    }
}

return_t Logger::initialize() {
    if (initialized) {
        return ERR_ALREADY_INITIALIZED;
    }
    
    std::memset(log_buffer, 0, sizeof(log_buffer));
    current_index = 0;
    total_entries = 0;
    initialized = true;
    
    return OK;
}

return_t Logger::shutdown() {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    initialized = false;
    return OK;
}

return_t Logger::log_message(log_level_t level, uint32_t source_id, const char* message) {
    if (!initialized || !message) {
        return ERR_INVALID_PARAMETER;
    }
    
    if (total_entries >= MAX_LOG_ENTRIES) {
        return ERR_LOG_BUFFER_FULL;
    }
    
    LogEntry& entry = log_buffer[current_index];
    entry.timestamp = static_cast<timestamp_t>(std::time(nullptr));
    entry.level = level;
    entry.source_id = source_id;
    
    std::strncpy(entry.message, message, MAX_MESSAGE_LENGTH - 1);
    entry.message[MAX_MESSAGE_LENGTH - 1] = '\0';
    
    entry.checksum = CryptoUtils::generate_checksum(
        reinterpret_cast<byte_t*>(entry.message),
        std::strlen(entry.message)
    );
    
    current_index = (current_index + 1) % MAX_LOG_ENTRIES;
    total_entries++;
    
    return OK;
}

return_t Logger::get_log_entry(uint32_t index, LogEntry& entry) {
    if (!initialized || index >= total_entries || index >= MAX_LOG_ENTRIES) {
        return ERR_INVALID_PARAMETER;
    }
    
    entry = log_buffer[index];
    return OK;
}

uint32_t Logger::get_total_entries() const {
    return total_entries;
}

return_t Logger::clear_logs() {
    if (!initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    std::memset(log_buffer, 0, sizeof(log_buffer));
    current_index = 0;
    total_entries = 0;
    
    return OK;
}

return_t Logger::export_logs(const char* filename) {
    if (!initialized || !filename) {
        return ERR_INVALID_PARAMETER;
    }
    
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return ERR_FILE_OPERATION_FAILED;
    }
    
    for (uint32_t i = 0; i < total_entries && i < MAX_LOG_ENTRIES; i++) {
        file.write(reinterpret_cast<char*>(&log_buffer[i]), sizeof(LogEntry));
    }
    
    file.close();
    return OK;
}
