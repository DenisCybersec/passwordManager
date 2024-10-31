#ifndef AES_HPP
#define AES_HPP

#include<include/crypto/encryption.hpp>
#include<openssl/aes.h>
#include<vector>
#include<iomanip>
#include<memory>

class AES : public Encryption{
public:
    AES(KeyDerive* keyDeriveFunction, hexFormating* hexFunctions);

    std::string encryptData(const std::string& data, const std::string& password, const std::string& salt) const override;
    std::string decryptData(const std::string& data, const std::string& password, const std::string& salt) const override;

    void setKDF(KeyDerive* keyDeriveFunction) override;
    void setHex(hexFormating* hexFunctions) override;

    KeyDerive* getKDF() const override;
    hexFormating* getHex() const override;
    inline std::string getName() const override{return "AES";}
};

#endif