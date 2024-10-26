# SoundGenerator

A simple C++ library for generating sine and cosine waves and saving them to raw audio files.

## Features

* Generate sine and cosine waves.
* Control frequency, amplitude, duration, sample rate, and phase shift.
* Command-line interface for easy generation.
* C++ API for programmatic use.
* Cross-platform compatibility (using CMake).

## Build Instructions

1. Clone the repository: `git clone https://github.com/sl1dee36/sound-gen.git` (replace with your repository URL)
2. Create a build directory: `mkdir build && cd build`
3. Configure the project with CMake: `cmake ..`
4. Build the project: `cmake --build .`

This will generate the `SoundGenerator` executable in the `build` directory.


## Usage

### Command Line

```
Usage: SoundGenerator [options]
Options:
  -f <frequency>          Frequency in Hz (default 440.0)
  -a <amplitude>          Amplitude (0.0 - 1.0, default 0.8)
  -d <duration>           Duration in seconds (default 1.0)
  -r <sample_rate>        Sample rate (default 44100)
  -p <phase_shift>        Phase shift in radians (default 0.0) (only for cosine)
  -o <output_file>        Output file name (default output.raw)
  -w <wave_type>          Wave type (sin or cos, default sin)
  -h, --help              Show this help
```

**Examples:**

```bash
# Generate a sine wave with 880 Hz frequency, 0.5 amplitude, 2 seconds duration
SoundGenerator -f 880 -a 0.5 -d 2 -w sin -o sine_880.raw

# Generate a cosine wave with 220 Hz frequency and pi/2 phase shift
SoundGenerator -f 220 -p 1.5708 -w cos -o cosine_220.raw

# Generate a default sine wave
SoundGenerator
```

### C++ Code

See the [documentation](docs/index.md) for detailed instructions and examples on using the `SoundGenerator` class in your C++ code.


## Documentation
For more detailed information and examples, please refer to the [documentation](docs/index.md).


## Contributing
Contributions are welcome! Please feel free to open issues and submit pull requests.

## License
This project is licensed under the [MIT License](LICENSE).
