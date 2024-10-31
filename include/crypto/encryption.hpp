#ifndef Encryption_HPP
#define Encryption_HPP

#include<string>
#include<include/crypto/keyderive.hpp>
#include<include/formating/hex.hpp>

class Encryption{
public:
    virtual std::string encryptData(const std::string& data,const std::string& password,const std::string& salt) const= 0 ;
    virtual std::string decryptData(const std::string& data,const std::string& password,const std::string& salt) const = 0;

    virtual std::string getName() const = 0;
    virtual KeyDerive* getKDF() const = 0;
    virtual hexFormating* getHex() const = 0;

    virtual void setKDF(KeyDerive* keyDeriveFunction) = 0 ;
    virtual void setHex(hexFormating* hexFunction) = 0;
    
protected:
    KeyDerive* key_derive_function_;
    hexFormating* hex_function_;
};

#endif
