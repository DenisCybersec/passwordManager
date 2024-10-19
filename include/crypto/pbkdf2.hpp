#ifndef PBKDF2_H
#define PBKDF2_H
#include<include/crypto/keyderive.hpp>
#include<include/formating/hex.hpp>
#include<iomanip>
class PBKDF2 : public KeyDerive
{
    public:
        std::string getKey(std::string password,std::string salt) override;
        inline std::string getName() {return "PBKDF2";};
        PBKDF2(int iterations, int key_length,hexFormating* hex);
    private:
        hexFormating* hex;
        int iterations;
        int key_length;
};
#endif