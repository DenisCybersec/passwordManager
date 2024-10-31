#include<include/structure/entry.hpp>
std::string Entry::getServiceName() const
{
    return this->service_name_;
}
std::string Entry::getPassword() const
{
    return this->password_;
}
std::string Entry::getLogin() const
{
    return this->login_;
}
void Entry::setPassword(std::string& password)
{
    this->password_ = password;
}
void Entry::setLogin(std::string& login)
{
    this->login_ = login;
}
void Entry::setServiceName(std::string& serviceName)
{
    this->service_name_ = serviceName;
}
std::string Entry::getSalt() const
{
    return this->salt_;
}
void Entry::setSalt(std::string& salt)
{
    this->salt_ = salt;
}
std::string Entry::to_string()
{
    std::string str = "ServiceName: ";
    str.append(this->service_name_);
    str.append(" Login: ");
    str.append(this->login_);
    str.append(" Password: ");
    str.append(this->password_);
    str.append(" Salt: ");
    str.append(this->salt_);
    return str;
}
Entry::Entry(std::string salt)
{
    this->salt_ = salt;
}