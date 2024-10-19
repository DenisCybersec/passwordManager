#include<gtest/gtest.h>
#include<include/crypto/aes.hpp>
#include<include/crypto/pbkdf2.hpp>
#include<include/crypto/salt.hpp>
#include<include/formating/hex.hpp>
TEST(AesTest,EncryptTest)
{
    hexFormating* hex = new hexFormating();
    PBKDF2* keyDerive = new PBKDF2(1000,32,hex);
    AES* aes = new AES(keyDerive,hex);
    std::string str = "textToBeEncrypted";
    std::string password = "password";
    std::string salt = "saltSALT";
    std::string cryptedText = aes->encryptData(str,password,salt);
    EXPECT_EQ(cryptedText,"4804059ce5e4247844d1ef1e47b5f0f140bcb342a86b2559279c858b78dcc064");

}
TEST(AesTest,EncryptDecryptTest)
{
    hexFormating* hex = new hexFormating();
    PBKDF2* keyDerive = new PBKDF2(1000,32,hex);
    AES* aes = new AES(keyDerive,hex);
    Salt* generator = new Salt();
    for(int i = 0;i<50;i++)
    {
        std::string str = generator->generateSalt(32);
        std::string password = generator->generateSalt(32);
        std::string salt = generator->generateSalt(32);
        std::string cryptedText = aes->encryptData(str,password,salt);
        std::string decryptedText = aes->decryptData(cryptedText,password,salt);
        EXPECT_EQ(str,decryptedText) << "Origin: " << str << "Result: " << decryptedText << std::endl;
    }
}