#ifndef SALT_HPP
#define SALT_HPP

#include<string>
#include<openssl/rand.h>

class Salt{
public:
    std::string generateSalt(int saltLength) const;
};
#endif