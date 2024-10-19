#ifndef KEY_H
#define KEY_H
#include <string>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
class KeyDerive
{
    public:
        virtual std::string getKey(std::string password,std::string salt) = 0;
        virtual std::string getName() = 0;
        virtual ~KeyDerive() = default;
};
#endif