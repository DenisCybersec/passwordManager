#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <string>
#include <optional>
#include <include/crypto/hash.hpp>
#include <include/crypto/encryption.hpp>
#include <include/crypto/sha256.hpp>
#include <include/crypto/salt.hpp>

class Entry{
public:
    std::string getServiceName() const;
    std::string getLogin() const;
    std::string getPassword() const;
    std::string getSalt() const;
    void setServiceName(std::string &serviceName);
    void setLogin(std::string &loginName);
    void setPassword(std::string &password);
    void setSalt(std::string &salt);
    std::string to_string();
    Entry(std::string salt);

private:
    std::string service_name_ = "";
    std::string login_ = "";
    std::string password_ = "";
    std::string entry_hash_ = "";
    std::string salt_ = "";
};
#endif