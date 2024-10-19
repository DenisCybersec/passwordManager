#include<include/structure/entry.hpp>
std::string Entry::getServiceName()
{
    return this->serviceName;
}
std::string Entry::getPassword()
{
    return this->password;
}
std::string Entry::getLogin()
{
    return this->login;
}
void Entry::setPassword(std::string& password)
{
    this->password = password;
}
void Entry::setLogin(std::string& login)
{
    this->login = login;
}
void Entry::setServiceName(std::string& serviceName)
{
    this->serviceName = serviceName;
}
std::string Entry::getSalt()
{
    return this->salt;
}
void Entry::setSalt(std::string& salt)
{
    this->salt = salt;
}
std::string Entry::to_string()
{
    std::string str = "ServiceName: ";
    str.append(this->serviceName);
    str.append(" Login: ");
    str.append(this->login);
    str.append(" Password: ");
    str.append(this->password);
    str.append(" Salt: ");
    str.append(this->salt);
    return str;
}
Entry::Entry(std::string salt)
{
    this->salt = salt;
}