#include <include/structure/database.hpp>
// Init new database
Database::Database(Hash *hashAlgo, Encryption *encryptionAlgo, KeyDerive *keyDeriveAlgo, std::string databasePassword, std::string salt,std::string path)
{
    this->hashAlgorithm = hashAlgo;
    this->encryptionAlgorithm = encryptionAlgo;
    this->keyDeriveAlgorithm = keyDeriveAlgo;
    std::string key = keyDeriveAlgo->getKey(databasePassword, salt);
    this->key = key;
    this->path = path;
    this->salt = salt;
    this->keyHash = hashAlgo->getHash(key);
}
// Init database from json with password
Database::Database(nlohmann::json j, std::string password, std::map<std::string, void *> mp,std::string path)
{
    this->stringToFunction = mp;
    this->path = path;
    this->readDatabaseInfoFromJson(j.at(0));
    this->key=this->keyDeriveAlgorithm->getKey(password,this->salt);
    nlohmann::json subArr = nlohmann::json::array();
    for(int i = 1;i<j.size();i++)
    {
        subArr.push_back(j.at(i));
    }
    this->checkDatabasePassword();
    this->readEntriesFromJson(subArr);
}
// Get all Entries
std::vector<Entry *> &Database::getEntries()
{
    return this->Entries;
}
// Set vector of Entries
void Database::setEntries(std::vector<Entry *> &vector)
{
    this->Entries.assign(vector.begin(), vector.end());
}
// Get  password after KeyDerive
std::string Database::getKey()
{
    return this->key;
}
// Set password after KeyDerive
void Database::setKey(std::string key)
{
    this->key = key;
}
std::string Database::getPath()
{
    return this->path;
}
// Dump database to json for export
nlohmann::json Database::exportToJson()
{
    nlohmann::json j = nlohmann::json::array();
    nlohmann::json databaseInfo;
    databaseInfo["hash"] = this->keyHash;
    databaseInfo["hashAlgo"] = this->hashAlgorithm->getName();
    databaseInfo["keyDerive"] = this->keyDeriveAlgorithm->getName();
    databaseInfo["encryption"] = this->encryptionAlgorithm->getName();
    databaseInfo["salt"] = this->salt;
    j.push_back(databaseInfo);
    for (auto i : this->Entries)
    {
        std::string serviceName = i->getServiceName();
        std::string login = i->getLogin();
        std::string password = i->getPassword();
        std::string salt = i->getSalt();
        std::string encryptedServiceName = this->encryptionAlgorithm->encryptData(serviceName, this->key, salt);
        std::string encryptedLogin = this->encryptionAlgorithm->encryptData(login, this->key, salt);
        std::string encryptedPassword = this->encryptionAlgorithm->encryptData(password, this->key, salt);
        nlohmann::json entry;
        entry["sN"] = encryptedServiceName;
        entry["L"] = encryptedLogin;
        entry["P"] = encryptedPassword;
        entry["S"] = salt;
        j.push_back(entry);
    }
    return j;
}
// Restore database info from Json
void Database::readDatabaseInfoFromJson(nlohmann::json i)
{
    // restoring database info from database
    if (i.contains("hash") && i.contains("hashAlgo") && i.contains("salt") && i.contains("encryption") && i.contains("keyDerive"))
    {
        this->keyHash = i.value("hash", "");
        this->salt = i.value("salt","");
        std::string encryptionName = i.value("encryption", "");
        std::string hashName = i.value("hashAlgo", "");
        std::string keyDerive = i.value("keyDerive", "");
        if (this->stringToFunction.count(encryptionName) == 0)
        {
            std::cerr << "Unknow encryption algorithm" << std::endl;
        }
        else
        {
            this->encryptionAlgorithm = (Encryption *)this->stringToFunction.at(encryptionName);
        }
        if (this->stringToFunction.count(hashName) == 0)
        {
            std::cerr << "Unknow hash algorithm" << std::endl;
        }
        else
        {
            this->hashAlgorithm = (Hash *)this->stringToFunction.at(hashName);
        }
        if (this->stringToFunction.count(keyDerive) == 0)
        {
            std::cerr << "Unknow keyDerive algorithm" << std::endl;
        }
        else
        {
            this->keyDeriveAlgorithm = (KeyDerive *)this->stringToFunction.at(keyDerive);
        }
    }
    else
    {
        std::cerr << "Wrong Json Stucture" << std::endl;
        throw 1;
    }
    // checking if password from input is password from database
    
}
// Write plaintext database in 
nlohmann::json Database::noEncryptionToJson()
{
    nlohmann::json j = nlohmann::json::array();
    nlohmann::json databaseInfo;
    databaseInfo["hash"] = this->keyHash;
    databaseInfo["hashAlgo"] = this->hashAlgorithm->getName();
    databaseInfo["keyDerive"] = this->keyDeriveAlgorithm->getName();
    databaseInfo["encryption"] = this->encryptionAlgorithm->getName();
    databaseInfo["salt"] = this->salt;
    j.push_back(databaseInfo);
    for (auto i : this->Entries)
    {
        std::string serviceName = i->getServiceName();
        std::string login = i->getLogin();
        std::string password = i->getPassword();
        std::string salt = i->getSalt();
        nlohmann::json entry;
        entry["sN"] = serviceName;
        entry["L"] = login;
        entry["P"] = password;
        entry["S"] = salt;
        j.push_back(entry);
    }
    return j;
}
// compare DatabaseHash and key hash
bool Database::checkDatabasePassword()
{
    if (this->checkKey(this->key))
    {
        std::cout << "Database inited" << std::endl;
        std::cout << "Database hash: " << this->keyHash << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "Wrong password" << std::endl;
        return 0;
    }
}
// Read Json array and make std::vector<Entry*> from it
void Database::readEntriesFromJson(nlohmann::json j)
{
    std::vector<Entry*> vctr = {};
    if(j.is_array())
    {
        for(auto i:j)
        {
            if(i.contains("S") && i.contains("sN") && i.contains("L") && i.contains("P"))
            {
                std::string salt = i.value("S", "");
                Entry *entry = new Entry(salt);
                std::string encryptedServiceName = i.value("sN", "");
                std::string encryptedLogin = i.value("L", "");
                std::string encryptedPassword = i.value("P", "");
                // decrypt entries info
                std::string serviceName = this->encryptionAlgorithm->decryptData(encryptedServiceName, this->key, salt);
                std::string login = this->encryptionAlgorithm->decryptData(encryptedLogin, this->key, salt);
                std::string password = this->encryptionAlgorithm->decryptData(encryptedPassword, this->key, salt);
                // set values
                entry->setLogin(login);
                entry->setPassword(password);
                entry->setServiceName(serviceName);
                entry->setSalt(salt);
                // push in the back of Entries array
                vctr.push_back(entry);
            }
            else
            {
                std::cerr << "Wrong entry structure" << std::endl;
            }
        }
        this->Entries.assign(vctr.begin(),vctr.end());
    }
    else
    {
        std::cerr << "Wrong array structure" << std::endl;
    }
}
// Get password hash
std::string Database::getKeyHash()
{
    return this->keyHash;
}
// Check if password arg hash equal to databasse hash
bool Database::checkKey(std::string key)
{
    return this->keyHash == this->hashAlgorithm->getHash(key);
}
// Add new Entry to database
void Database::addEntry(Entry *entry)
{
    this->Entries.push_back(entry);
}