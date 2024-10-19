#ifndef Hex_H
#define Hex_H
#include<string>
#include<vector>
#include<iomanip>
class hexFormating
{
    public:
        std::string unsignedCharToHex(std::vector<unsigned char> input);
        std::vector<unsigned char> hexToUnsignedChar(std::string input);
};
#endif