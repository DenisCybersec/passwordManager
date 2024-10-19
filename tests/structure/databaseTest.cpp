#include<gtest/gtest.h>
#include<include/structure/database.hpp>
#include<include/crypto/salt.hpp>
#include<include/crypto/sha256.hpp>
#include<include/crypto/aes.hpp>
#include<include/crypto/pbkdf2.hpp>
#include<include/formating/hex.hpp>
TEST(dbTest,dbTest)
{
    Sha256* sha256 = new Sha256();
    hexFormating* hex = new hexFormating();
    Salt* saltGenerator = new Salt();
    PBKDF2* pbkdf2 = new PBKDF2(1000,32,hex);
    AES* aes = new AES(pbkdf2,hex);
    std::map<std::string, void*> mp = {{"SHA256",sha256},{"AES",aes},{"PBKDF2",pbkdf2}};
    std::string password = "password";
    std::string salt = "1234";
    Database* db = new Database(sha256,aes,pbkdf2,password,salt,"");
    std::string hash = db->getKeyHash();
    std::string key = db->getKey();
    EXPECT_EQ(key,pbkdf2->getKey(password,salt));
    std::string calcHash = sha256->getHash(key);
    EXPECT_EQ(hash,calcHash);
    Entry* entry = new Entry("1234");
    std::string login = "login";
    std::string serviceName = "serviceName";
    entry->setLogin(login);
    entry->setPassword(password);
    entry->setServiceName(serviceName);
    db->addEntry(entry);
    nlohmann::json j = db->exportToJson();
    Database* restoredBase = new Database(j,"password",mp,""); 
    EXPECT_EQ(db->getKey(),restoredBase->getKey());
    std::cout << db->noEncryptionToJson();
    EXPECT_EQ(db->noEncryptionToJson().dump(1),restoredBase->noEncryptionToJson().dump(1));
    EXPECT_ANY_THROW(Database* restoredBase = new Database(j,"pass",mp,""));
}