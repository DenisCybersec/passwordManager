#include<include/formating/hex.hpp>
std::string hexFormating::unsignedCharToHex(std::vector<unsigned char> input)
{
    std::stringstream stream;
    for (int i = 0; i < input.size(); ++i){
        stream << std::hex << std::setw(2) << std::setfill('0') << (int)input[i];
    }
    return stream.str();
}
std::vector<unsigned char> hexFormating::hexToUnsignedChar(std::string input)
{
    std::vector<unsigned char> hex(input.length() / 2);
    for (int i = 0; i < input.length(); i += 2) {
        std::string byteString = input.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(strtol(byteString.c_str(), nullptr, 16));
        hex[i / 2] = byte;
    }
    return hex;
}