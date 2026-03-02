// DO-178B: Error code definitions for secure logging system
// Requirement Traceability: REQ-ERR-001 through REQ-ERR-020
// Compliance Level: Level A (critical for safety analysis)
#pragma once

#define OK                              0x00000000
#define ERR_GENERAL_FAILURE             0x00000001
#define ERR_MEMORY_ALLOCATION           0x00000002
#define ERR_INVALID_PARAMETER           0x00000003
#define ERR_AUTHENTICATION_FAILED       0x00000004
#define ERR_AUTHORIZATION_DENIED        0x00000005
#define ERR_LOG_BUFFER_FULL             0x00000006
#define ERR_COMMUNICATION_FAILED        0x00000007
#define ERR_ENCRYPTION_FAILED           0x00000008
#define ERR_DECRYPTION_FAILED           0x00000009
#define ERR_CHECKSUM_MISMATCH           0x0000000A
#define ERR_INVALID_LOG_ENTRY           0x0000000B
#define ERR_FILE_OPERATION_FAILED       0x0000000C
#define ERR_CONFIG_LOAD_FAILED          0x0000000D
#define ERR_TIMEOUT                     0x0000000E
#define ERR_BUFFER_OVERFLOW             0x0000000F
#define ERR_INVALID_TOKEN               0x00000010
#define ERR_PERMISSION_DENIED           0x00000011
#define ERR_NOT_INITIALIZED             0x00000012
#define ERR_ALREADY_INITIALIZED         0x00000013
