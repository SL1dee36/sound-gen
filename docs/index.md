# SoundGenerator Library: Documentation and Tutorial

This library provides a flexible and powerful way to generate various audio waveforms, mix sounds, and save the results to raw audio files. It's designed for ease of use, both programmatically in C++ and through a command-line interface. This documentation provides a comprehensive guide to using the library, including detailed explanations of its features, functions, and parameters.

## Table of Contents

* [1. Building the Library](#building-the-library)
* [2. Usage: Command Line](#usage-command-line)
* [3. Usage: C++ Code](#usage-c-code)
* [4. Sound Parameters](#sound-parameters)
* [5. Waveform Generation](#waveform-generation)
    * [5.1 Sine Wave](#sine-wave)
    * [5.2 Cosine Wave](#cosine-wave)
    * [5.3 Triangle Wave](#triangle-wave)
    * [5.4 Square Wave](#square-wave)
    * [5.5 Sawtooth Wave](#sawtooth-wave)
    * [5.6 Pulse Wave](#pulse-wave)
    * [5.7 White Noise](#white-noise)
* [6. Sound Mixing](#sound-mixing)
* [7. Example Melodies](#example-melodies)
* [8. Examples](#examples)


### 1. Building the Library

The library consists of `SoundGenerator.h` and `main.cpp`. Compile these into a library or include them directly in your project.  Building with CMake:

1. **Create `CMakeLists.txt`:**

   ```cmake
   cmake_minimum_required(VERSION 3.8)
   project(SoundGenerator)

   add_executable(SoundGenerator main.cpp SoundGenerator.h)
   ```

2. **Build:** Use your preferred CMake method (command line, IDE).


### 2. Usage: Command Line

The compiled executable takes arguments:

```
Usage: SoundGenerator [options]
Options:
  -f <frequency>          Frequency in Hz (default 440.0)
  -a <amplitude>          Amplitude (0.0 - 1.0, default 0.8)
  -d <duration>           Duration in seconds (default 1.0)
  -r <sample_rate>        Sample rate (default 44100)
  -p <phase_shift>        Phase shift in radians (default 0.0) (cosine only)
  -o <output_file>        Output file name (default output.raw)
  -w <wave_type>          Wave type (sin, cos, triangle, square, sawtooth, pulse, noise, mix, mix2, pulse_mix, grasshopper) (default sin)
  -W <pulse_width>        Pulse width (0.0 - 1.0, default 0.5) (pulse wave only)
  -h, --help              Show this help
```

### 3. Usage: C++ Code

```cpp
#include "SoundGenerator.h"
#include <fstream>

int main() {
    SoundParameters params;
    params.frequency = 1000.0;      // Set frequency to 1000 Hz
    params.amplitude = 0.7;         // Set amplitude to 0.7
    params.duration = 5.0;          // Set duration to 5 seconds
    params.waveType = "cos";        // Generate a cosine wave
    params.phaseShift = M_PI / 4;   // Set phase shift to pi/4
    params.outputFilename = "my_sound.raw";

    std::vector<double> wave = SoundGenerator::generateWave(params);

    std::ofstream outputFile(params.outputFilename, std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.write(reinterpret_cast<char*>(wave.data()), wave.size() * sizeof(double));
        outputFile.close();
        std::cout << "Sound saved to " << params.outputFilename << std::endl;
    } else {
        std::cerr << "Error opening file: " << params.outputFilename << std::endl;
        return 1;
    }

    return 0;
}
```

### 4. Sound Parameters (`SoundParameters` struct)

```cpp
struct SoundParameters {
    double frequency = 440.0;      // Frequency of the wave in Hz
    double amplitude = 0.8;        // Amplitude (0.0 - 1.0).  Represents the loudness.
    double duration = 1.0;         // Duration of the sound in seconds
    int sampleRate = 44100;        // Number of samples per second (affects audio quality)
    double phaseShift = 0.0;       // Phase shift in radians (shifts the wave horizontally). Only applicable to cosine waves.
    std::string outputFilename = "output.raw";  // Name of the output .raw audio file
    std::string waveType = "sin";  // Type of waveform to generate (sin, cos, triangle, etc.)
    double pulseWidth = 0.5;       // Duty cycle of the pulse wave (0.0 - 1.0), representing the "on" time within each cycle.
};
```

### 5. Waveform Generation

* #### 5.1 Sine Wave

    A fundamental waveform representing a smooth oscillation. Formula: *amplitude * sin(2π * frequency * time)*

* #### 5.2 Cosine Wave

    Similar to a sine wave, but shifted by π/2 radians. Formula: *amplitude * cos(2π * frequency * time + phase_shift)*

* #### 5.3 Triangle Wave

    A waveform with a linear ramp up and down. Contains only odd harmonics.

* #### 5.4 Square Wave

    A waveform that alternates between two amplitude values.  Creates a harsh, buzzing sound. Contains only odd harmonics.

* #### 5.5 Sawtooth Wave

    A waveform with a linear ramp up followed by an instant drop. Creates a bright, rich sound often used in synthesizers. Contains both even and odd harmonics.

* #### 5.6 Pulse Wave

    A waveform similar to a square wave but with a controllable duty cycle (`pulseWidth`). Allows for variations in timbre.

* #### 5.7 White Noise

    A random signal with equal energy across all frequencies. Useful for sound effects.

### 6. Sound Mixing (`mixSounds` function)

```cpp
std::vector<double> SoundGenerator::mixSounds(const std::vector<std::vector<double>>& sounds);
```
Combines multiple audio waveforms into a single output. Each input waveform is represented as a `std::vector<double>`.  The function adds the samples of each input waveform at each time point.  The output is then normalized to prevent clipping, ensuring the amplitude stays within the range of -1.0 to 1.0.


### 7. Example Melodies

The "Grasshopper" melody demonstrates how to create basic tunes using the library.  See `main.cpp` for implementation details.

### 8. Examples (Code Examples in `main.cpp`)

The `main.cpp` file provides examples demonstrating single waveform generation, mixing sounds (including "mix", "mix2", and "pulse_mix" presets), and playing the "Grasshopper" melody.  These examples demonstrate how to use the library's functions and configure the `SoundParameters` struct.
