// DO-178B: Configuration parameters for secure logging system
// Requirement Traceability: REQ-CONFIG-001 through REQ-CONFIG-015
// Compliance Level: Level A (system initialization)
#pragma once

#define MAX_LOG_ENTRIES                 10000
#define MAX_USERS                       100
#define MAX_LOG_FILE_SIZE               10485760
#define MAX_MESSAGE_LENGTH              256
#define CRYPTO_KEY_SIZE                 32
#define AUTHENTICATION_TIMEOUT          3600
#define LOG_ROTATION_INTERVAL           86400
#define BUFFER_SIZE                     4096
#define MAX_RETRIES                     3
#define COMMUNICATION_TIMEOUT           5000
#define HASH_SIZE                       32
#define SIGNATURE_SIZE                  64
#define MAX_CONCURRENT_USERS            50
