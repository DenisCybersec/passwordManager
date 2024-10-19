#ifndef AES_H
#define AES_H
#include<include/crypto/encryption.hpp>
#include<openssl/aes.h>
#include<vector>
#include<iomanip>
#include<memory>
class AES : public Encryption
{
    public:
        std::string encryptData(std::string& data, std::string& password, std::string& salt) override;
        std::string decryptData(std::string& data, std::string& password, std::string& salt) override;
        void setKDF(KeyDerive* keyDeriveFunction) override;
        void setHex(hexFormating* hexFunctions) override;
        KeyDerive* getKDF();
        hexFormating* getHex();
        inline std::string getName() override{return "AES";}
        AES(KeyDerive* keyDeriveFunction,hexFormating* hexFunctions);
};
#endif