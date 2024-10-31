#ifndef SHA256_HPP
#define SHA256_HPP

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
        std::string getHash(const std::string& input) const override;
        inline std::string getName() const override {return "SHA256";}; 
        ~Sha256() override;
};
#endif