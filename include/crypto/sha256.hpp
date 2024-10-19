#ifndef SHA256_H
#define SHA256_H
#include <include/crypto/hash.hpp>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <iostream>
#include <iomanip>
class Sha256: public Hash
{
    public:
        std::string getHash(std::string& input) override;
        inline std::string getName() override {return "SHA256";}; 
        ~Sha256() override;
};
#endif