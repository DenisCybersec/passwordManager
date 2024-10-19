#ifndef BASE_H
#define BASE_H
#include<QWidget>
class Base : QWidget
{
    public:
        void addEntry(std::string serviceName,std::string login, std::string password);
};
#endif