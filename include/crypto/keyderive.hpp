#ifndef KEY_HPP
#define KEY_HPP

#include <string>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>

class KeyDerive{
public:
    virtual std::string getKey(const std::string& password,const std::string& salt) const = 0;
    virtual std::string getName() const = 0;
    virtual ~KeyDerive() = default;
};
#endif