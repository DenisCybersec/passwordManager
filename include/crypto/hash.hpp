#ifndef Hash_H
#define Hash_H
#include<string>
class Hash
{
    public:
        virtual std::string getHash(std::string& data) = 0;
        virtual std::string getName() = 0;
        virtual ~Hash() {};
};
#endif