#ifndef Entry_H
#define Entry_H
#include<string>
#include<optional>
#include<include/crypto/hash.hpp>
#include<include/crypto/encryption.hpp>
#include<include/crypto/sha256.hpp>
#include<include/crypto/salt.hpp>
class Entry
{
    public:
        std::string getServiceName();
        std::string getLogin();
        std::string getPassword();
        std::string getSalt();
        void setServiceName(std::string& serviceName);
        void setLogin(std::string& loginName);
        void setPassword(std::string& password);
        void setSalt(std::string& salt);
        std::string to_string();
        Entry(std::string salt);
    private:
        std::string serviceName = "";
        std::string login = "";
        std::string password = "";
        std::string entryHash = "";
        std::string salt = "";
};
#endif