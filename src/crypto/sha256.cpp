#include<include/crypto/sha256.hpp>
std::string Sha256::getHash(std::string& input){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    std::stringstream stream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i){
        stream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return stream.str();
}
Sha256::~Sha256(){}