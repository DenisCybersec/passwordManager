#ifndef Database_H
#define Database_H

#include <vector>
#include <include/structure/entry.hpp>
#include <include/crypto/encryption.hpp>
#include <include/crypto/hash.hpp>
#include <include/crypto/pbkdf2.hpp>
#include <include/crypto/aes.hpp>
#include <nlohmann/json.hpp>

class Database{
public:
    std::vector<Entry *> &getEntries();
    void setEntries(std::vector<Entry *> &vector);
    bool checkKey(std::string password);
    void setKey(std::string password);
    void addEntry(Entry *entry);
    nlohmann::json exportToJson();
    nlohmann::json noEncryptionToJson();
    void readDatabaseInfoFromJson(nlohmann::json j);
    void readEntriesFromJson(nlohmann::json j);
    bool checkDatabasePassword();
    std::string getKeyHash();
    std::string getKey();
    std::string getPath();
    Salt *getGen();
    Database(Hash *hashAlgo, Encryption *encryptionAlgo, KeyDerive *keyDeriveAlgo, std::string databasePassword, std::string salt, std::string path); // create new one
    Database(nlohmann::json j, std::string password, std::map<std::string, void *> mp, std::string path);                                             // restore Database from file
    ~Database()
    {
        delete this->gen;
        for (auto i : entries_)
        {
            delete i;
        }
    }

private:
    std::vector<Entry *> entries_ = std::vector<Entry *>();
    std::map<std::string, void *> string_to_function_;
    Salt *gen = new Salt();
    std::string key_hash_;
    std::string key_;
    std::string salt_;
    std::string path_;
    Hash *hash_algorithm_;
    Encryption *encryption_algorithm_;
    KeyDerive *key_derive_algorithm_;
};
#endif