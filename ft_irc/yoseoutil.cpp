#include "yoseoutil.h"
#include <iostream>

//",,,,#channel,,,,#channel2,"
void splitString(const std::string& param, char del, std::vector<std::string>* const out)
{
    std::string token;
    token.reserve(100);

    for (size_t i = 0; i < param.length(); ++i)
    {
        if (param[i] == del)
        {
            if (!token.empty())
            {
                out->push_back(token);
                token.clear();
            }            
        }
        else
        {
            token.push_back(param[i]);
        }                
    }

    if (!token.empty())
    {
        out->push_back(token);
    }
}

int _isspecial(char c)
{
    const std::string special("-[]{}\\`^");
    for (size_t i = 0; i < special.length(); ++i)
	{
        if (special[i] == c)
        {
            return 4;     
        }    	
    }

    return 0;
}

bool _isValidNickname(const std::string& selectName)
{    
    if (selectName.length() == 0)
    {
        return false;
    }

    if (std::isalpha(selectName[0]) == 0)    
    {
        return false;
    }

    for (size_t i = 0; i < selectName.length(); ++i)
	{
        const char c = selectName[i];

        if (std::isdigit(c) == 0 && std::isalpha(c) ==0 && _isspecial(c) == 0)
        {
            return false;            
        }
	}
	
	return true;
}

