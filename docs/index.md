## SoundGenerator Library: Documentation and Tutorial

This library provides a simple way to generate sine and cosine waves and save them to a raw audio file. It's designed to be easy to use, both programmatically and through the command line.

### 1. Building the Library

The library consists of two files: `SoundGenerator.h` and `main.cpp`.  You can compile these into a library or directly include them into your project.  Here's how to build a simple executable using CMake:

1.  **Create a `CMakeLists.txt` file:**

    ```cmake
    cmake_minimum_required(VERSION 3.8)
    project(SoundGenerator)

    add_executable(SoundGenerator main.cpp SoundGenerator.h) # Include both files
    ```

2.  **Build the project:** Use your preferred CMake build process (e.g., from the command line or within an IDE like Visual Studio).

### 2. Usage: Command Line

The compiled executable accepts command-line arguments to control the generated sound:

```
Usage: SoundGenerator [options]
Options:
  -f <frequency>          Frequency in Hz (default 440.0)
  -a <amplitude>        Amplitude (0.0 - 1.0, default 0.8)
  -d <duration>         Duration in seconds (default 1.0)
  -r <sample_rate>       Sample rate (default 44100)
  -p <phase_shift>       Phase shift in radians (default 0.0)  (only for cosine wave)
  -o <output_file>        Output file name (default output.raw)
  -w <wave_type>        Wave type (sin or cos, default sin)
  -h, --help             Show this help
```

**Examples:**

*   Generate a sine wave with a frequency of 880 Hz, amplitude of 0.5, and duration of 2 seconds:

    ```bash
    SoundGenerator -f 880 -a 0.5 -d 2 -w sin -o sine_880.raw
    ```

*   Generate a cosine wave with a frequency of 220 Hz, a phase shift of π/2 radians, and save it to `cosine_220.raw`:

    ```bash
    SoundGenerator -f 220 -p 1.5708 -w cos -o cosine_220.raw
    ```

*  Generate a default sine wave (440Hz, 0.8 amplitude, 1 second duration) to "output.raw"

    ```bash
    SoundGenerator 
    ```


### 3. Usage: C++ Code

You can also use the `SoundGenerator` class directly within your C++ code:

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

This code demonstrates how to configure the `SoundParameters` struct and use the `SoundGenerator::generateWave` function to create a sound wave programmatically.  Remember to handle potential file I/O errors.



This comprehensive documentation covers command-line usage, programmatic usage, and build instructions, providing clear examples for users to get started quickly.  Remember to use an audio player or library that can handle raw audio files to listen to the generated sounds.
