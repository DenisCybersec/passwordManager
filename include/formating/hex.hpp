#ifndef HEX_HPP
#define HEX_HPP

#include<string>
#include<vector>
#include<iomanip>

class hexFormating{
    public:
        std::string unsignedCharToHex(const std::vector<unsigned char>& input) const;
        std::vector<unsigned char> hexToUnsignedChar(const std::string& input) const;
};
#endif