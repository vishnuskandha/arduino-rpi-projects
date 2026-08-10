# Security Policy

## Reporting a Vulnerability

If you find a security issue in this repository, do not open a public issue. Report it privately by emailing the repository owner at **vishnuskandha@gmail.com** with a description of the problem and, if possible, a minimal reproduction.

You can expect an acknowledgment within a few days and a proposed fix as soon as the issue is understood. Please do not disclose the issue publicly until a fix is released.

## Security Notice: SSH Key Removal (2026)

This repository previously tracked a private SSH key (`key`) and its public counterpart (`key.pub`) at the root. These files were publicly accessible and are treated as **compromised**. They have been removed from the working tree and from git tracking, and `key*`, `*.pem`, and `*.ppk` are now ignored via `.gitignore`.

If you used this key pair anywhere (e.g., GitHub, a server), assume it is exposed:

1. **Revoke/rotate the key immediately.** Generate a new key pair with `ssh-keygen` and deploy the new public key to the services you use.
2. Remove the old key from the remote servers where it was authorized.
3. Never commit private keys. Add key material to `.gitignore` before adding files.

## Scope

The MIT license under which this project is distributed comes with no warranty. Issues in third-party libraries and board support packages (e.g., Arduino cores, ESP32 SDK, OpenCV) should be reported to their respective maintainers.
