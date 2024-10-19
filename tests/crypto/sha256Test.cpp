#include<gtest/gtest.h>
#include<include/crypto/sha256.hpp>
#include<string>
TEST(SHA256Test,hashingWork)
{
    Sha256* sha256 = new Sha256();
    std::vector<std::string> strs = {"123","321","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",""};
    std::vector<std::string> hashes (strs.size());
    for(int i = 0;i<strs.size();i++)
    {
        hashes.at(i) = sha256->getHash(strs.at(i)); 
    }
    std::vector<std::string> expects = {
        "a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3",
        "8d23cf6c86e834a7aa6eded54c26ce2bb2e74903538c61bdd5d2197997ab2f72",
        "c094ed2f614ab7a02e7557f8eba6b03b457ce7beacf1d8031088f97a1770e5e6",
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    };
    for(int i = 0;i<expects.size();i++)
    {
        EXPECT_EQ(hashes.at(i),expects.at(i));
    }
}