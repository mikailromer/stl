#include <iostream>
#include <algorithm>
#include "palindrom.hpp"

bool is_palindrome(std::string word)
{
    std::string compared_word = "";
    std::for_each(word.begin(), word.end(), 
                [&word](char sign)
                {
                    auto result = forbidden_signs.find(sign);
                    if(result != std::string::npos)
                    {
                        word.erase(word.begin() + result);
                    }
                }
    );

    for(int i = 0; i < word.length()/2; i++)
    {
        if(word[i] != word[word.length() - 1 - i])
        {
            return false;
        }
    }

    return true;
}