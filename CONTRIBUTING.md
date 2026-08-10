# Contributing

Thanks for wanting to contribute to this collection of Arduino and Raspberry Pi projects.

## Project Conventions

- One folder per project at the repository root, named in `kebab-case` (e.g., `servo-camera`).
- Arduino/ESP32 code goes in `<project>/arduino/` as `.ino` sketches.
- Raspberry Pi code goes in `<project>/raspberry_pi/` as `.py` scripts.
- Every project folder must contain a `README.md` documenting hardware, wiring, libraries, and usage.
- WiFi credentials, MQTT server addresses, and API keys must use placeholders such as `YOUR_WIFI_SSID`. Never commit real credentials or private keys.

## Adding a New Project

1. Create the project folder and subfolders following the conventions above.
2. Write the sketch(es) or script(s) and a README.
3. Add a row to the project table in the root `README.md`.
4. Commit with a conventional message, e.g. `feat: add <project-name>`.

## Before Submitting

- Keep code readable and commented where behavior is non-obvious.
- Verify pin mappings are documented.
- Make sure the root CI workflow still passes on your branch.
- Do not include compiled binaries, build output, or private key material.

## Pull Requests

- Work from your own fork and open a pull request against `main`.
- Keep changes focused; one logical change per PR.
- Respond to review feedback.

## Reporting Issues

Use the GitHub issue tracker for bugs and feature requests. For security issues, see [SECURITY.md](SECURITY.md).
