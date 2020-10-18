#include "vowel.hpp"
#include <cstring>

const std::string vovels = "aeiouyAEIOYU";

void removeVowels(std::vector<std::string>& lines)
{
    for(std::string& line : lines)
    {
        int i = 0;
        while (i < line.length())
        {
            if(vovels.find(line[i]) != std::string::npos)
            {
                line.erase(i, 1);
            }
            else
            {
                i++;
            }
        }
    }
}