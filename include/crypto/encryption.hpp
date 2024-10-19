#ifndef Encryption_H
#define Encryption_H
#include<string>
#include<include/crypto/keyderive.hpp>
#include<include/formating/hex.hpp>
class Encryption
{
    public:
        virtual std::string encryptData(std::string& data, std::string& password, std::string& salt) = 0;
        virtual std::string decryptData(std::string& data, std::string& password, std::string& salt) = 0;
        virtual std::string getName() = 0;
        virtual void setKDF(KeyDerive* keyDeriveFunction) = 0;
        virtual void setHex(hexFormating* hexFunctions) = 0;
        virtual KeyDerive* getKDF() = 0;
        virtual hexFormating* getHex() = 0;
    protected:
        KeyDerive* keyDeriveFunction;
        hexFormating* hexFunctions;
};
#endif
