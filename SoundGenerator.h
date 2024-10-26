#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm> // для std::max
#include <random>


#ifndef M_PI
#define M_PI 3.14159265358979323846
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
    double pulseWidth = 0.5; // Для pulse wave
};

class SoundGenerator {
public:
    static std::vector<double> generateWave(const SoundParameters& params);
    static std::vector<double> mixSounds(const std::vector<std::vector<double>>& sounds);
    static SoundParameters parseParameters(int argc, char* argv[]);

private:
    static std::vector<double> generateSineWave(const SoundParameters& params);
    static std::vector<double> generateCosineWave(const SoundParameters& params);
    static std::vector<double> generateTriangleWave(const SoundParameters& params);
    static std::vector<double> generateSquareWave(const SoundParameters& params);
    static std::vector<double> generateSawtoothWave(const SoundParameters& params);
    static std::vector<double> generatePulseWave(const SoundParameters& params);
    static std::vector<double> generateWhiteNoise(const SoundParameters& params);
};


std::vector<double> SoundGenerator::generateWave(const SoundParameters& params) {
    if (params.waveType == "cos") {
        return generateCosineWave(params);
    }
    else if (params.waveType == "triangle") {
        return generateTriangleWave(params);
    }
    else if (params.waveType == "square") {
        return generateSquareWave(params);
    }
    else if (params.waveType == "sawtooth") {
        return generateSawtoothWave(params);
    }
    else if (params.waveType == "pulse") {
        return generatePulseWave(params);
    }
    else if (params.waveType == "noise") {
        return generateWhiteNoise(params);
    }
    else {
        return generateSineWave(params); // Default
    }
}


// Реализация функций генерации (полный код):


std::vector<double> SoundGenerator::generateSineWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        samples[i] = params.amplitude * sin(2 * M_PI * params.frequency * time);
    }
    return samples;
}

std::vector<double> SoundGenerator::generateCosineWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        samples[i] = params.amplitude * cos(2 * M_PI * params.frequency * time + params.phaseShift);
    }
    return samples;
}

std::vector<double> SoundGenerator::generateTriangleWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        double period = 1.0 / params.frequency;
        double cyclePos = fmod(time, period);
        samples[i] = params.amplitude * (2.0 * std::abs(2.0 * (cyclePos / period) - 1.0) - 1.0);
    }
    return samples;
}

std::vector<double> SoundGenerator::generateSquareWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        samples[i] = params.amplitude * (sin(2 * M_PI * params.frequency * time) >= 0 ? 1.0 : -1.0);
    }
    return samples;
}


std::vector<double> SoundGenerator::generateSawtoothWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        double period = 1.0 / params.frequency;
        samples[i] = params.amplitude * (2 * fmod(time * params.frequency, 1.0) - 1.0);

    }
    return samples;
}

std::vector<double> SoundGenerator::generatePulseWave(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);
    std::vector<double> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / params.sampleRate;
        double period = 1.0 / params.frequency;
        double cyclePos = fmod(time, period);
        samples[i] = params.amplitude * (cyclePos < params.pulseWidth * period ? 1.0 : -1.0);
    }
    return samples;
}

std::vector<double> SoundGenerator::generateWhiteNoise(const SoundParameters& params) {
    size_t numSamples = static_cast<size_t>(params.sampleRate * params.duration);
    std::vector<double> samples(numSamples);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0); // Диапазон от -1.0 до 1.0
    for (size_t i = 0; i < numSamples; ++i) {
        samples[i] = params.amplitude * dis(gen);
    }
    return samples;
}

// В SoundGenerator.h

std::vector<double> SoundGenerator::mixSounds(const std::vector<std::vector<double>>& sounds) {
    if (sounds.empty()) {
        return {};
    }

    size_t maxLength = 0;
    for (const auto& sound : sounds) {
        maxLength = std::max(maxLength, sound.size());
    }

    std::vector<double> mixedSound(maxLength, 0.0);

    for (const auto& sound : sounds) {
        for (size_t i = 0; i < sound.size(); ++i) {
            mixedSound[i] += sound[i];
        }
    }

    // Нормализация (опционально, чтобы избежать клиппинга)
    double maxAmplitude = 0.0;
    for (double sample : mixedSound) {
        maxAmplitude = std::max(maxAmplitude, std::abs(sample));
    }
    if (maxAmplitude > 1.0) {
        for (double& sample : mixedSound) {
            sample /= maxAmplitude;
        }
    }

    return mixedSound;
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
        else if (arg == "-W" && i + 1 < argc) {  // Для pulse width
            params.pulseWidth = std::stod(argv[++i]);
        }
        else if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [options]\n"
                << "Options:\n"
                << "  -f <frequency>          Frequency in Hz (default 440.0)\n"
                << "  -a <amplitude>          Amplitude (0.0 - 1.0, default 0.8)\n"
                << "  -d <duration>           Duration in seconds (default 1.0)\n"
                << "  -r <sample_rate>        Sample rate (default 44100)\n"
                << "  -p <phase_shift>        Phase shift in radians (default 0.0)\n"
                << "  -o <output_file>        Output file name (default output.raw)\n"
                << "  -w <wave_type>          Wave type (sin, cos, triangle, square, sawtooth, pulse, noise) (default sin)\n"
                << "  -W <pulse_width>        Pulse width (0.0 - 1.0, default 0.5) (only for pulse wave)\n"
                << "  -h, --help              Show this help\n";
            exit(0);
        }
    }
    return params;
}