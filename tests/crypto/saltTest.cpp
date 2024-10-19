#include<gtest/gtest.h>
#include<include/crypto/salt.hpp>
TEST(SaltTest,SaltLength)
{
    Salt* generator = new Salt();
    for(int i = 2;i<1000;i+=2)
    {
        std::string salt = generator->generateSalt(i);
        EXPECT_EQ(salt.size(),i) << "Asked length: " << i << "Actual Length: " << salt.size();
    }
}