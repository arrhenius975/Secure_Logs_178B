// DO-178B: Type definitions for secure logging system
// Requirement Traceability: REQ-TYPES-001 through REQ-TYPES-010
// Compliance Level: Level A (most critical operations)
#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

typedef uint8_t byte_t;
typedef uint32_t return_t;
typedef uint32_t log_level_t;
typedef uint64_t timestamp_t;

enum LogLevel : log_level_t {
    LOG_DEBUG = 0,
    LOG_INFO = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 3,
    LOG_CRITICAL = 4
};

enum UserRole : uint8_t {
    ROLE_VIEWER = 0,
    ROLE_OPERATOR = 1,
    ROLE_ADMINISTRATOR = 2,
    ROLE_AUDITOR = 3
};

struct LogEntry {
    timestamp_t timestamp;
    log_level_t level;
    uint32_t source_id;
    char message[256];
    byte_t checksum;
};

struct UserCredential {
    uint32_t user_id;
    UserRole role;
    byte_t authentication_token[32];
    timestamp_t token_expiry;
};

struct CommunicationPacket {
    uint32_t packet_id;
    uint16_t payload_size;
    byte_t payload[512];
    byte_t signature[64];
    timestamp_t transmission_time;
};
