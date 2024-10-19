#include<include/crypto/pbkdf2.hpp>
std::string PBKDF2::getKey(std::string password,std::string salt)
{
    int& iterations = this->iterations;
    int& key_length = this->key_length;
    std::vector<unsigned char> derived_key(this->key_length);
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                           (const unsigned char*)salt.c_str(), salt.length(),
                           iterations, EVP_sha256(),key_length , derived_key.data())) {
        std::cerr << "Error in key derivation." << std::endl;
        throw std::runtime_error("Key derivation failed.");
    }
    std::string ret = hex->unsignedCharToHex(derived_key);
    return ret; // returns the derived key as a hex string
}
PBKDF2::PBKDF2(int iterations, int key_length,hexFormating* hex)
{
    this->hex = hex;
    this->iterations = iterations;
    this->key_length = key_length;
}