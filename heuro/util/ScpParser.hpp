#pragma once

#include "util/Data.hpp"

#include <string>

namespace Heuro
{

    class ScpParser
    {
    public:
        static ScpInput parseFile(const std::string &filename);
    };

}


