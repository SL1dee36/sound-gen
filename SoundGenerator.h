#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14
#endif

// Структура для хранения параметров звука
struct SoundParameters {
    double frequency = 440.0;
    double amplitude = 0.8;
    double duration = 1.0;
    int sampleRate = 44100;
    double phaseShift = 0.0;
    std::string outputFilename = "output.raw";
    std::string waveType = "sin";
};

class SoundGenerator {
public:
    static std::vector<double> generateWave(const SoundParameters& params);
    static SoundParameters parseParameters(int argc, char* argv[]);

private:
    static std::vector<double> generateSineWave(const SoundParameters& params);
    static std::vector<double> generateCosineWave(const SoundParameters& params);
};

std::vector<double> SoundGenerator::generateWave(const SoundParameters& params) {
    if (params.waveType == "cos") {
        return generateCosineWave(params);
    }
    else {
        return generateSineWave(params);
    }
}

std::vector<double> SoundGenerator::generateSineWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration); // Явное преобразование
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        samples[i] = params.amplitude * sin(2 * M_PI * params.frequency * time);
    }
    return samples;
}

std::vector<double> SoundGenerator::generateCosineWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);  // Явное преобразование
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        samples[i] = params.amplitude * cos(2 * M_PI * params.frequency * time + params.phaseShift);
    }
    return samples;
}

SoundParameters SoundGenerator::parseParameters(int argc, char* argv[]) {
    SoundParameters params;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-f" && i + 1 < argc) {
            params.frequency = std::stod(argv[++i]);
        }
        else if (arg == "-a" && i + 1 < argc) {
            params.amplitude = std::stod(argv[++i]);
        }
        else if (arg == "-d" && i + 1 < argc) {
            params.duration = std::stod(argv[++i]);
        }
        else if (arg == "-r" && i + 1 < argc) {
            params.sampleRate = std::stoi(argv[++i]);
        }
        else if (arg == "-p" && i + 1 < argc) {
            params.phaseShift = std::stod(argv[++i]);
        }
        else if (arg == "-o" && i + 1 < argc) {
            params.outputFilename = argv[++i];
        }
        else if (arg == "-w" && i + 1 < argc) {
            params.waveType = argv[++i];
        }
        else if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [options]\n"
                << "Options:\n"
                << "  -f <frequency>          Frequency in Hz (default 440.0)\n"
                << "  -a <amplitude>        Amplitude (0.0 - 1.0, default 0.8)\n"
                << "  -d <duration>         Duration in seconds (default 1.0)\n"
                << "  -r <sample_rate>       Sample rate (default 44100)\n"
                << "  -p <phase_shift>       Phase shift in radians (default 0.0)\n"
                << "  -o <output_file>        Output file name (default output.raw)\n"
                << "  -w <wave_type>        Wave type (sin or cos, default sin)\n"
                << "  -h, --help             Show this help\n";
            exit(0);
        }
    }
    return params;
}