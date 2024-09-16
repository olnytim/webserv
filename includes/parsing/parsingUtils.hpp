//
// Created by ashot on 9/7/2024.
//

#ifndef PARSINGUTILS_HPP
#define PARSINGUTILS_HPP

#include "../Headers.hpp"


class parsingUtils {
public:
    static int ft_stoi(const std::string &str) {
        int res = 0;
        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] < '0' || str[i] > '9')
                throw std::exception();
            res = res * 10 + str[i] - '0';
        }
        return res;
    }

    // Finds the corresponding bracket for the opening bracket at start_bracket_pos
    // Returns the position of the closing bracket or std::string::npos if the closing bracket is not found
    // Arguments: str - string to search in, start_bracket_pos - position of the opening bracket
    static size_t findEndingBracket(const std::string &str, size_t start_bracket_pos) {
        size_t openBracketPos = str.find('{', start_bracket_pos + 1);
        size_t closeBracketPos = str.find('}', start_bracket_pos + 1);
        if (closeBracketPos == std::string::npos)
            return std::string::npos;
        if (openBracketPos == std::string::npos || openBracketPos > closeBracketPos)
            return closeBracketPos;
        while (true) {
            closeBracketPos = findEndingBracket(str, openBracketPos);
            if (closeBracketPos == std::string::npos)
                return std::string::npos;
            openBracketPos = str.find('{', closeBracketPos + 1);
            closeBracketPos = str.find('}', closeBracketPos + 1);
            if (openBracketPos == std::string::npos || openBracketPos > closeBracketPos)
                return closeBracketPos;
        }
    }

    static std::vector<std::string> splitParams(const std::string &content, const std::string &delim) {
        std::vector<std::string>	str;
        std::string::size_type		start, end;
        start = end = 0;
        while (start != std::string::npos)
        {
            end = content.find_first_of(delim, start);
            if (end == std::string::npos) {
                std::string tmp1 = content.substr(start);
                if (!tmp1.empty() || tmp1.length() > 0)
                    str.push_back(tmp1);
                break;
            }
            std::string tmp = content.substr(start, end - start);
            if (!tmp.empty() || tmp.length() > 0)
                str.push_back(tmp);
            start = content.find_first_not_of(delim, end);
        }
        return (str);
    }

    static std::string trimWhitespace(std::string &str) {
        size_t start = str.find_first_not_of(" \t\n\r\f\v");
        if (start == std::string::npos)
            return "";
        size_t end = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(start, end - start + 1);
    }
};

#endif //PARSINGUTILS_HPP