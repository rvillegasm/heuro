#include "HeuroCli.hpp"

#include <numeric>

HeuroCli::HeuroCli(const std::string &outputFilename)
    : m_OutputFile(outputFilename, "scp41")
{
}

void HeuroCli::run()
{
    HE_PROFILE_BEGIN_SESSION("Scp", "profiling.txt");
//    evaluateFile("scp41");
//    evaluateFile("scp42");
//    evaluateFile("scpnrg1");
//    evaluateFile("scpnrg2");
//    evaluateFile("scpnrg3");
//    evaluateFile("scpnrg4");
//    evaluateFile("scpnrg5");
//    evaluateFile("scpnrh1");
//    evaluateFile("scpnrh2");
//    evaluateFile("scpnrh3");
//    evaluateFile("scpnrh4");
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

//    // Constructive
//    for (int i = 0; i < 5; ++i)
//    {
//        Heuro::ScpResult constructiveResult;
//        {
//            std::string scopeName = inputFileName + "\tconst__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            constructiveResult = solver.constructive();
//        }
//        m_OutputFile.addValues(inputFileName, constructiveResult.toVec());
//    }
//    // Grasp
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult graspResult;
//        {
//            std::string scopeName = inputFileName + "\tgrasp_iter100_k10__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            graspResult = solver.grasp(100, 10);
//        }
//        m_OutputFile.addValues(inputFileName, graspResult.toVec());
//    }
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult graspResult;
//        {
//            std::string scopeName = inputFileName + "\tgrasp_iter100_k50__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            graspResult = solver.grasp(100, 50);
//        }
//        m_OutputFile.addValues(inputFileName, graspResult.toVec());
//    }
//    // Noise
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult noiseResult;
//        {
//            std::string scopeName = inputFileName + "\tnoise_iter100_k10_rho5__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            noiseResult = solver.graspWithNoise(100, 10, 5);
//        }
//        m_OutputFile.addValues(inputFileName, noiseResult.toVec());
//    }
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult noiseResult;
//        {
//            std::string scopeName = inputFileName + "\tnoise_iter100_k10_rho2__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            noiseResult = solver.graspWithNoise(100, 10, 2);
//        }
//        m_OutputFile.addValues(inputFileName, noiseResult.toVec());
//    }
//    // Sim Annealing
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult simAnnealingResult;
//        {
//            std::string scopeName = inputFileName + "\tsimAnnealing_t10.0_k10_flin0.1__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            simAnnealingResult = solver.simulatedAnnealing(300000, 10.0, 10, [](double t0, int k) { return t0 - 0.1 * k; });
//        }
//        m_OutputFile.addValues(inputFileName, simAnnealingResult.toVec());
//    }
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult simAnnealingResult;
//        {
//            std::string scopeName = inputFileName + "\tsimAnnealing_t10.0_k50_flin0.1__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            simAnnealingResult = solver.simulatedAnnealing(300000, 10.0, 50, [](double t0, int k) { return t0 - 0.1 * k; });
//        }
//        m_OutputFile.addValues(inputFileName, simAnnealingResult.toVec());
//    }
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult simAnnealingResult;
//        {
//            std::string scopeName = inputFileName + "\tsimAnnealing_t5.0_k10_flin0.01__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            simAnnealingResult = solver.simulatedAnnealing(300000, 5.0, 10, [](double t0, int k) { return t0 - 0.01 * k; });
//        }
//        m_OutputFile.addValues(inputFileName, simAnnealingResult.toVec());
//    }
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult simAnnealingResult;
//        {
//            std::string scopeName = inputFileName + "\tsimAnnealing_t10.0_k10_fexp__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            simAnnealingResult = solver.simulatedAnnealing(300000, 10.0, 10, [](double t0, int k) { return t0 * exp(-k); });
//        }
//        m_OutputFile.addValues(inputFileName, simAnnealingResult.toVec());
//    }
//    // VNS
//    for (int i = 0; i < 3; ++i)
//    {
//        Heuro::ScpResult vnsResult;
//        {
//            std::string scopeName = inputFileName + "\tvns__" + std::to_string(i);
//            HE_PROFILE_SCOPE(scopeName.c_str());
//            vnsResult = solver.vns(300000);
//        }
//        m_OutputFile.addValues(inputFileName, vnsResult.toVec());
//    }
    // blga
    for (int i = 0; i < 1; ++i)
    {
        Heuro::ScpResult blgaResult;
        {
            std::string scopeName = inputFileName + "\tblga_ps300_mc10_gcp0.8_rss50__" + std::to_string(i);
            HE_PROFILE_SCOPE(scopeName.c_str());
            blgaResult = solver.blga(300000, 300, 10, 0.8, 50);
        }
        m_OutputFile.addValues(inputFileName, blgaResult.toVec());
    }
    for (int i = 0; i < 2; ++i)
    {
        Heuro::ScpResult blgaResult;
        {
            std::string scopeName = inputFileName + "\tblga_ps300_mc10_gcp0.65_rss50__" + std::to_string(i);
            HE_PROFILE_SCOPE(scopeName.c_str());
            blgaResult = solver.blga(300000, 300, 10, 0.65, 50);
        }
        m_OutputFile.addValues(inputFileName, blgaResult.toVec());
    }
    for (int i = 0; i < 2; ++i)
    {
        Heuro::ScpResult blgaResult;
        {
            std::string scopeName = inputFileName + "\tblga_ps150_mc10_gcp0.8_rss50__" + std::to_string(i);
            HE_PROFILE_SCOPE(scopeName.c_str());
            blgaResult = solver.blga(300000, 150, 10, 0.8, 50);
        }
        m_OutputFile.addValues(inputFileName, blgaResult.toVec());
    }
    for (int i = 0; i < 2; ++i)
    {
        Heuro::ScpResult blgaResult;
        {
            std::string scopeName = inputFileName + "\tblga_ps300_mc5_gcp0.8_rss25__" + std::to_string(i);
            HE_PROFILE_SCOPE(scopeName.c_str());
            blgaResult = solver.blga(300000, 300, 5, 0.8, 25);
        }
        m_OutputFile.addValues(inputFileName, blgaResult.toVec());
    }
    for (int i = 0; i < 2; ++i)
    {
        Heuro::ScpResult blgaResult;
        {
            std::string scopeName = inputFileName + "\tblga_ps300_mc5_gcp0.65_rss25__" + std::to_string(i);
            HE_PROFILE_SCOPE(scopeName.c_str());
            blgaResult = solver.blga(300000, 300, 5, 0.65, 25);
        }
        m_OutputFile.addValues(inputFileName, blgaResult.toVec());
    }
}
