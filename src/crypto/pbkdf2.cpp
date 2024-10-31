#include<include/crypto/pbkdf2.hpp>
std::string PBKDF2::getKey(const std::string& password,const std::string& salt) const
{
    int iterations = this->iterations_;
    int key_length = this->key_length_;
    std::vector<unsigned char> derived_key(this->key_length_);
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                           (const unsigned char*)salt.c_str(), salt.length(),
                           iterations, EVP_sha256(),key_length , derived_key.data())) {
        std::cerr << "Error in key derivation." << std::endl;
        throw std::runtime_error("Key derivation failed.");
    }
    std::string ret = hex_->unsignedCharToHex(derived_key);
    return ret; // returns the derived key as a hex string
}
PBKDF2::PBKDF2(int iterations, int key_length,hexFormating* hex)
{
    this->hex_ = hex;
    this->iterations_ = iterations;
    this->key_length_ = key_length;
}