#ifndef PBKDF2_HPP
#define PBKDF2_HPP

#include<include/crypto/keyderive.hpp>
#include<include/formating/hex.hpp>
#include<iomanip>

class PBKDF2 : public KeyDerive{
public:
    std::string getKey(const std::string& password,const std::string& salt) const override;
    inline std::string getName() const override {return "PBKDF2";};
    PBKDF2(int iterations,int key_length,hexFormating* hex);
private:
    hexFormating* hex_;
    int iterations_;
    int key_length_;
};
#endif