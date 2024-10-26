#include "SoundGenerator.h"

int main(int argc, char* argv[]) {
    SoundParameters params = SoundGenerator::parseParameters(argc, argv);
    std::vector<double> wave = SoundGenerator::generateWave(params);

    std::ofstream outputFile(params.outputFilename, std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.write(reinterpret_cast<char*>(wave.data()), wave.size() * sizeof(double));
        outputFile.close();
        std::cout << "Sound saved to a file " << params.outputFilename << std::endl;
    }
    else {
        std::cerr << "Error when opening a file " << params.outputFilename << std::endl;
        return 1;
    }

    return 0;
}