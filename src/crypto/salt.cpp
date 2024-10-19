#include<include/crypto/salt.hpp>
#include<include/formating/hex.hpp>
std::string Salt::generateSalt(int saltLength)
{
    std::vector<unsigned char> salt(saltLength/2);
    RAND_bytes(salt.data(), saltLength/2);
    hexFormating* hex = new hexFormating();
    std::string str = hex->unsignedCharToHex(salt);
    return str;
}