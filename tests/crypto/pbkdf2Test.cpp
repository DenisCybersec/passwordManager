#include<gtest/gtest.h>
#include<include/crypto/pbkdf2.hpp>
#include<include/formating/hex.hpp>
TEST(PBKDF2,PBKDF2EmptySaltTest16)
{
    hexFormating* hex = new hexFormating();
    PBKDF2* keyDer = new PBKDF2(1000,16,hex);
    std::vector<std::string> input = {"123","password","qwerty","321",""};
    std::vector<std::string> expect = {"e09895bd6126911781b7221460c942bc","26939681d19995a2cefb7b90d13e1343","b1444b43fe945ff29561e772401db5a0","7b4fcbd02ace64911943faf398a6906c","4fc58a21c100ce1835b8f9991d738b56"};
    for(int i = 0;i<input.size();i++)
    {
        std::string hash = keyDer->getKey(input.at(i),"");
        EXPECT_EQ(hash,expect.at(i));
    }
}
TEST(PBKDF2,PBKDF2EmptySaltTest32)
{
    hexFormating* hex = new hexFormating();
    PBKDF2* keyDer = new PBKDF2(1000,32,hex);
    std::vector<std::string> input = {"123","password","qwerty","321",""};
    std::vector<std::string> expect = {"e09895bd6126911781b7221460c942bc6d905249b3803779189d7dff58f4ac8a","26939681d19995a2cefb7b90d13e1343f09b30f0abbd07416a23b9bc3c5b3536","b1444b43fe945ff29561e772401db5a00b4c27e4936788b0a717d0b6a99690bc","7b4fcbd02ace64911943faf398a6906c929630001bd3384f7f744fe2b81e72ab","4fc58a21c100ce1835b8f9991d738b56965d14b24e1761fbdffc69ac5e0b667a"};
    for(int i = 0;i<input.size();i++)
    {
        std::string hash = keyDer->getKey(input.at(i),"");
        EXPECT_EQ(hash,expect.at(i));
    }
}
TEST(PBKDF2,PBKDF2SaltTest32)
{
    hexFormating* hex = new hexFormating();
    PBKDF2* keyDer = new PBKDF2(1000,32,hex);
    std::vector<std::string> input = {"123","password","qwerty","321",""};
    std::vector<std::string> expect = {"ccadce19edf58f5f150c314a40ae3676c548736dd64efcbba08b763e9ff9531c","4ccaaedf2e8ba75970c3594300d241bc932be2481ab6d908a622fdb65972a6ca","06ed144da5e1902014a18fc2b4465b3338082053c2ae516d72ba6087d632fd95","24d6f846f30ee16ad8f48477529bd38a13af0e9a160a405d92ef717524ada2bd","aab99aa32b2b5b89601114570d07c254ee9103d38eba6adaa4bf3920f1ff8033"};
    for(int i = 0;i<input.size();i++)
    {
        std::string hash = keyDer->getKey(input.at(i),"saltSALT");
        EXPECT_EQ(hash,expect.at(i));
    }
}