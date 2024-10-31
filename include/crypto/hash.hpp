#ifndef HASH_HPP
#define HASH_HPP

#include<string>

class Hash{
public:
    virtual std::string getHash(const std::string& data) const = 0 ;
    virtual std::string getName() const = 0;
    virtual ~Hash() {};
};
#endif