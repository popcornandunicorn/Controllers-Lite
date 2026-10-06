# Controllers-Lite
A lightweight, zero-dependency C utility for macOS designed to inspect, monitor, and calibrate RC transmitters  and USB gamepads in real time.
Built directly on top of Apple's **IOKit HID Framework**

## Key Features

- **Zero External Dependencies:** Native C using Apple's `IOKit` and `CoreFoundation` frameworks.
- **Auto-Calibration Engine:** Automatically tracks axis bounds (`min`/`max`) on the fly to output accurate PWM microsecond values (`1000µs–2000µs`).
- **High Channel Support:** Maps both `GenericDesktop` HID axes (Sticks/Pots) and `Button` usage pages (Multi-position switches) up to 16+ channels.
- **Low Latency Terminal UI:** Direct event-driven event loop rendering with zero lag.

## Quick Start

### Prerequisites
- macOS (Apple Silicon or Intel)
- Xcode Command Line Tools (`xcode-select --install`)

### Build and Run
**Clone the repository:**
Build and launch using the Makefile:
make run

<img width="382" height="169" alt="image" src="https://github.com/user-attachments/assets/3eacbb5c-9000-4b96-924d-a05a9ee5d02d" />
