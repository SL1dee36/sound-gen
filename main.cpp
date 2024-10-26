#include "SoundGenerator.h"
#include <fstream>
#include <iostream>
#include <vector>

std::vector<double> generateNote(double frequency, double duration, int sampleRate, std::string waveType = "sin") {
    SoundParameters params;
    params.frequency = frequency;
    params.duration = duration;
    params.sampleRate = sampleRate;
    params.waveType = waveType;
    return SoundGenerator::generateWave(params);
}

int main(int argc, char* argv[]) {
    SoundParameters params = SoundGenerator::parseParameters(argc, argv);

    std::vector<double> wave;

    if (params.waveType == "mix") {
        SoundParameters params1 = params;
        params1.frequency = 220;
        params1.waveType = "sin";
        params1.duration = 2.0;
        std::vector<double> sound1 = SoundGenerator::generateWave(params1);

        SoundParameters params2 = params;
        params2.frequency = 440;
        params2.waveType = "triangle";
        params2.duration = 1.0;
        std::vector<double> sound2 = SoundGenerator::generateWave(params2);

        std::vector<std::vector<double>> sounds = { sound1, sound2 };
        wave = SoundGenerator::mixSounds(sounds);
        params.outputFilename = "mix1.raw";

    }
    else if (params.waveType == "mix2") {
        SoundParameters params1 = params;
        params1.frequency = 110;
        params1.waveType = "sin";
        params1.duration = 4.0;

        SoundParameters params2 = params;
        params2.frequency = 220;
        params2.waveType = "square";
        params2.duration = 2.0;

        SoundParameters params3 = params;
        params3.frequency = 880;
        params3.waveType = "sawtooth";
        params3.duration = 1.0;

        std::vector<double> sound1 = SoundGenerator::generateWave(params1);
        std::vector<double> sound2 = SoundGenerator::generateWave(params2);
        std::vector<double> sound3 = SoundGenerator::generateWave(params3);

        std::vector<std::vector<double>> sounds = { sound1, sound2 , sound3 };
        wave = SoundGenerator::mixSounds(sounds);
        params.outputFilename = "mix2.raw";

    }
    else if (params.waveType == "pulse_mix") {
        SoundParameters params1 = params;
        params1.frequency = 200;
        params1.waveType = "pulse";
        params1.pulseWidth = 0.25;

        SoundParameters params2 = params;
        params2.amplitude = 0.2;
        params2.waveType = "noise";

        std::vector<double> sound1 = SoundGenerator::generateWave(params1);
        std::vector<double> sound2 = SoundGenerator::generateWave(params2);

        std::vector<std::vector<double>> sounds = { sound1, sound2 };
        wave = SoundGenerator::mixSounds(sounds);
        params.outputFilename = "pulse_mix.raw";

    }
    else if (params.waveType == "grasshopper") {
        int sampleRate = params.sampleRate;
        double wholeNote = 0.5;

        double C4 = 261.63;
        double D4 = 293.66;
        double E4 = 329.63;
        double F4 = 349.23;
        double G4 = 392.00;

        std::vector<std::vector<double>> notes;

        notes.push_back(generateNote(G4, wholeNote * 0.5, sampleRate));
        notes.push_back(generateNote(E4, wholeNote * 0.5, sampleRate));
        notes.push_back(generateNote(C4, wholeNote, sampleRate));
        notes.push_back(generateNote(D4, wholeNote, sampleRate));
        notes.push_back(generateNote(E4, wholeNote * 2, sampleRate));

        notes.push_back(generateNote(F4, wholeNote * 0.5, sampleRate));
        notes.push_back(generateNote(D4, wholeNote * 0.5, sampleRate));
        notes.push_back(generateNote(C4, wholeNote, sampleRate));
        notes.push_back(generateNote(E4, wholeNote, sampleRate));
        notes.push_back(generateNote(D4, wholeNote * 2, sampleRate));

        wave = SoundGenerator::mixSounds(notes);
        params.outputFilename = "grasshopper.raw";

    }
    else {
        wave = SoundGenerator::generateWave(params);
    }

    std::ofstream outputFile(params.outputFilename, std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.write(reinterpret_cast<char*>(wave.data()), wave.size() * sizeof(double));
        outputFile.close();
        std::cout << "Sound saved to " << params.outputFilename << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << params.outputFilename << std::endl;
        return 1;
    }

    return 0;
}