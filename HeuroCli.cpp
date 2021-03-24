#include "HeuroCli.hpp"

#include <numeric>

HeuroCli::HeuroCli(const std::string &outputFilename)
    : m_OutputFile(outputFilename, "scp41")
{
}

void HeuroCli::run()
{
    HE_PROFILE_BEGIN_SESSION("Scp", "profiling.txt");
    evaluateFile("scp41");
    evaluateFile("scp42");
    evaluateFile("scpnrg1");
    evaluateFile("scpnrg2");
    evaluateFile("scpnrg3");
    evaluateFile("scpnrg4");
    evaluateFile("scpnrg5");
    evaluateFile("scpnrh1");
    evaluateFile("scpnrh2");
    evaluateFile("scpnrh3");
    evaluateFile("scpnrh4");
    evaluateFile("scpnrh5");
    HE_PROFILE_END_SESSION();
}

void HeuroCli::evaluateFile(const std::string &inputFileName)
{
    if (inputFileName != "scp41")
    {
        m_OutputFile.addSheet(inputFileName);
    }

    Heuro::ScpInput input = Heuro::ScpParser::parseFile("assets/" + inputFileName + ".txt");
    Heuro::Scp solver(input.elementCount, input.subsetCount, input.costs, input.relations);

    Heuro::ScpResult constructiveResult;
    {
        std::string scopeName = inputFileName + "\tconst";
        HE_PROFILE_SCOPE(scopeName.c_str());
        constructiveResult = solver.constructive();
    }
    m_OutputFile.addValues(inputFileName, constructiveResult.toVec());

    int maxIterations = 1000;
    int k = 10; // Heuro::RandomIntGenerator(2, input.subsetCount)();

    Heuro::ScpResult graspResult;
    {
        std::string scopeName = inputFileName + "\tgrasp";
        HE_PROFILE_SCOPE(scopeName.c_str());
        graspResult = solver.grasp(maxIterations, k);
    }
    m_OutputFile.addValues(inputFileName, graspResult.toVec());

    int rho = 5; // static_cast<int>(std::reduce(input.costs.begin(), input.costs.end()) / input.costs.size());

    Heuro::ScpResult noiseResult;
    {
        std::string scopeName = inputFileName + "\tnoise";
        HE_PROFILE_SCOPE(scopeName.c_str());
        noiseResult = solver.graspWithNoise(maxIterations, k, rho);
    }
    m_OutputFile.addValues(inputFileName, noiseResult.toVec());
}
