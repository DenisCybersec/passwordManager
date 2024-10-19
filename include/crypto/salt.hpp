#ifndef Salt_H
#define Salt_H
#include<string>
#include<openssl/rand.h>
class Salt
{
    public:
        std::string generateSalt(int saltLength);
};
#endif