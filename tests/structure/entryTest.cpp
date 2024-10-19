#include<gtest/gtest.h>
#include<include/structure/entry.hpp>
#include<include/crypto/salt.hpp>
TEST(entryTest,entryTest)
{
    Entry* entry = new Entry("1234");
    Salt* salt = new Salt();
    EXPECT_EQ(entry->getSalt(),"1234");
    for(int i = 0;i<10;i++)
    {
        std::string login = salt->generateSalt(20);
        entry->setLogin(login);
        EXPECT_EQ(login,entry->getLogin());
        std::string password = salt->generateSalt(20);
        entry->setPassword(password);
        EXPECT_EQ(password,entry->getPassword());
        std::string serviceName = salt->generateSalt(20);
        entry->setServiceName(serviceName);
        EXPECT_EQ(serviceName,entry->getServiceName());
        std::string strSalt = salt->generateSalt(20);
        entry->setSalt(strSalt);
        EXPECT_EQ(strSalt,entry->getSalt());
    }
}