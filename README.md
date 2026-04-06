# Pong Pico

An embedded Raspberry Pi Pico 2 project that is growing from a Pong game
into a multi-mode device. The current codebase includes a working display
driver, custom text rendering, and the first app mode for Pong.

## Current Layout

```text
apps/
  home/
  mp3_remote/
  pong/

core/

drivers/
  display/

UI/
  fonts/
  text/

external/
  pico-sdk/
```

## What Lives Where

- `apps/` contains user-facing modes such as Pong and future device screens.
- `core/` is reserved for shared app-state and mode-switching logic.
- `drivers/` contains hardware-facing modules.
- `UI/` contains reusable rendering helpers like fonts and text drawing.
- `external/` contains vendored third-party code such as the Pico SDK.

## Build

```bash
mkdir -p build
cd build
cmake ..
make
```

The generated `.uf2` file can be copied to the Pico while it is in
BOOTSEL mode.

## Notes

- `apps/pong/main.c` is still the current firmware entry point.
- The commented Pong loop is preserved while the project is being
  reorganized into a cleaner multi-app structure.
- `apps/home/` and `apps/mp3_remote/` are placeholders for the next phase
  of the device.
