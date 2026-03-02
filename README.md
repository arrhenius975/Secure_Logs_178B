# DO-178B Standard Compliant Secure Logging System

This project is a DO-178B standard compliant Secure logging system implemented in C++. It is designed to provide secure, reliable, and compliant logging mechanisms for use in critical systems that require high standards of software assurance, such as those in the aviation or defense sectors.

## Table of Contents
- [Introduction](#introduction)
- [DO-178B Compliance](#do-178b-compliance)
- [Installation](#installation)
- [Usage](#usage)
- [Technologies & Tools](#technologies--tools)
- [Contributing](#contributing)
- [License](#license)

---

## Introduction

This project implements a DO-178B compliant secure logging system designed for critical systems requiring high assurance. It emphasizes:

- **Modular Architecture:** Four independent, testable modules (Logger, Access Control, Communication, Crypto Utils)
- **Security-First Design:** Encryption, authentication, authorization, and integrity verification
- **Compliance Traceability:** Every function mapped to specific DO-178B requirements (REQ-* identifiers)
- **Defensive Programming:** Comprehensive error handling with 20+ error codes and strict parameter validation
- **Safe Coding Practices:** Use of C++17 standard library, bounds checking, and memory-safe operations
- **Verification & Validation:** Complete unit and integration test coverage for all critical components

## DO-178B Compliance

This implementation adheres to DO-178B guidelines for airborne software development:

### Compliance Features

- **Requirements Traceability (DO-178B 6.4.1)**
  - Every function includes `REQ-*` markers linked to specific requirements
  - Compliance level annotations (Level A for critical components)
  - Complete mapping between code and specifications

- **Safety-Critical Design (DO-178B 6.3)**
  - Defensive programming with strict input validation
  - Comprehensive error codes and return value checking
  - Safe defaults and fail-safe mechanisms
  - No unchecked assumptions or implicit conversions

- **Verification & Validation (DO-178B 6.4.4 & 6.4.5)**
  - Unit tests for individual modules
  - Integration tests for end-to-end functionality
  - Test assertions verify both success and failure paths
  - Requirement coverage traceability

- **Compliance Documentation (DO-178B 6.2)**
  - [requirements.md](docs/requirements/requirements.md) - Functional requirements
  - [traceability_matrix.md](docs/traceability/traceability_matrix.md) - Requirement to code mapping
  - In-code comments for design rationale
  - Error code definitions with requirement links
    
## Installation

To install this project locally, follow these steps:

1. Clone the repository:
  
   ```bash
   git clone https://github.com/arrhenius975/Secure_Logs_178B.git
   cd Secure_Logs_178B
   ```
   
2. Build the project:
   - Ensure you have a compatible C++ compiler (GCC 15.2.0 or later) installed.
   - Create build directory and compile:
    
   ```bash
   mkdir -p build
   cd ..
   g++ -std=c++17 -Wall -Wextra -I./include -I./src -o build/DO178B_CyberSecurity_Logging src/main.cpp src/modules/logging/logger.cpp src/modules/access_control/access_control.cpp src/modules/communication/comms.cpp src/utils/crypto_utils.cpp
   ```
   
3. Build and run tests:
   
   ```bash
   # Logger module unit tests
   g++ -std=c++17 -Wall -Wextra -I./include -I./src -I. -o build/test_logger tests/unit/test_logger.cpp src/modules/logging/logger.cpp src/utils/crypto_utils.cpp
   ./build/test_logger
   
   # Access control module tests
   g++ -std=c++17 -Wall -Wextra -I./include -I./src -I. -o build/test_access_control tests/unit/test_access_control.cpp src/modules/access_control/access_control.cpp src/utils/crypto_utils.cpp
   ./build/test_access_control
   
   # Communication module tests
   g++ -std=c++17 -Wall -Wextra -I./include -I./src -I. -o build/test_comms tests/unit/test_comms.cpp src/modules/communication/comms.cpp src/utils/crypto_utils.cpp
   ./build/test_comms
   
   # Integration tests
   g++ -std=c++17 -Wall -Wextra -I./include -I./src -I. -o build/test_logging_comms tests/integration/test_logging_comms.cpp src/modules/logging/logger.cpp src/modules/communication/comms.cpp src/modules/access_control/access_control.cpp src/utils/crypto_utils.cpp
   ./build/test_logging_comms
   ```
   
## Usage

The system is composed of four core modules:

### Core Modules

1. **Logger Module** (`src/modules/logging/logger.h`)
   - Manages secure log entry creation and storage
   - Supports multiple log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL)
   - Provides log buffer management and export functionality
   - Includes checksum verification for data integrity

2. **Access Control Module** (`src/modules/access_control/access_control.h`)
   - User authentication and token validation
   - Role-based authorization (VIEWER, OPERATOR, ADMINISTRATOR, AUDITOR)
   - User registration and revocation
   - Token expiry management

3. **Communication Module** (`src/modules/communication/comms.h`)
   - Secure packet transmission for log entries
   - Encryption/decryption of payloads using AES-256
   - HMAC signature generation for authentication
   - Packet counter for sequencing

4. **Cryptographic Utilities** (`src/utils/crypto_utils.h`)
   - Hash computation and HMAC generation
   - AES-256 encryption and decryption
   - Checksum generation and verification

### Running the Application

To run the application:

```bash
./build/DO178B_CyberSecurity_Logging
```

The application will:
- Initialize all security modules
- Set up user credentials and authentication
- Create sample log entries
- Export logs to `secure_logs.bin`
- Display system status and entry counts

Refer to the [docs](./docs) folder for detailed design documentation and requirements traceability.

## Technologies & Tools

The project uses the following technologies and tools:

- **Language:** C++17 (ISO/IEC 14882:2017)
- **Compiler:** GCC 15.2.0 or compatible C++ compiler
- **Build:** Direct g++ compilation
- **Version Control:** Git
- **Compliance Standard:** DO-178B (Certification Considerations for Airborne Software)
- **Code Quality:** Wall and Wextra compiler flags for strict error checking
- **Testing:** Custom unit and integration test suites
- **Compliance Documentation:** 
  - Requirement traceability markers in code (REQ-* format)
  - DO-178B compliance levels (Level A for critical components)
  - Error code mapping and definitions
  - Configuration management

### Project Structure

```
Secure_Logs_178B/
├── include/              # Header files for configuration and types
├── src/
│   ├── main.cpp         # Application entry point
│   ├── modules/         # Core functional modules
│   │   ├── logging/     # Logger implementation
│   │   ├── access_control/  # Authentication & authorization
│   │   └── communication/   # Secure communications
│   └── utils/           # Cryptographic utilities
├── tests/               # Unit and integration tests
├── docs/                # Design and compliance documentation
├── configs/             # Configuration files
└── tools/               # Build and analysis scripts
```

## Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a branch for your feature (git checkout -b feature-xyz).
3. Commit your changes (git commit -m "Add feature xyz").
4. Push to your branch (git push origin feature-xyz).
5. Open a pull request.

Please ensure all code adheres to DO-178B guidelines and includes appropriate tests.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
