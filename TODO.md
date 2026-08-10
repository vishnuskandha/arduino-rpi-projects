# Todo: Arduino/RPi Mini Projects Implementation

## Selected Project
- Arduino Smart Lock with Keypad + RFID + Pi Logging - DONE

## Implementation Checklist

### 1. Project Setup
- [x] Create project folder: `project-name/`
- [x] Create `arduino/` or `raspberry_pi/` subfolders as needed
- [x] Write `README.md` with overview, hardware list, wiring, software installation, usage, troubleshooting
- [x] Add code files (`.ino` or `.py`)
- [x] Test code syntax (static review)
- [x] Update main `README.md` table with new project row
- [x] Commit with conventional message: `feat: add <project-name>`
- [x] Push to GitHub

### 2. Quality Checks
- [x] Code includes comments
- [x] Pin mappings clearly defined
- [x] Error handling (where appropriate)
- [x] No hardcoded WiFi passwords (use placeholders)
- [x] License: MIT (inherit from repo)

### 3. Repository Hygiene
- [x] Remove private key material (`key`, `key.pub`) from tracking
- [x] Add key patterns to `.gitignore`
- [x] Add CI workflow with repo sanity checks
- [x] Add `SECURITY.md` and `CONTRIBUTING.md`
