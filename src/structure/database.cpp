#include <include/structure/database.hpp>
// Init new database
Database::Database(Hash *hashAlgo, Encryption *encryptionAlgo, KeyDerive *keyDeriveAlgo, std::string databasePassword, std::string salt,std::string path)
{
    this->hash_algorithm_ = hashAlgo;
    this->encryption_algorithm_ = encryptionAlgo;
    this->key_derive_algorithm_ = keyDeriveAlgo;
    std::string key = keyDeriveAlgo->getKey(databasePassword, salt);
    this->key_ = key;
    this->path_ = path;
    this->salt_ = salt;
    this->key_hash_ = hashAlgo->getHash(key);
}
// Init database from json with password
Database::Database(nlohmann::json j, std::string password, std::map<std::string, void *> mp,std::string path)
{
    this->string_to_function_ = mp;
    this->path_ = path;
    this->readDatabaseInfoFromJson(j.at(0));
    this->key_=this->key_derive_algorithm_->getKey(password,this->salt_);
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
    return this->entries_;
}
// Set vector of Entries
void Database::setEntries(std::vector<Entry *> &vector)
{
    this->entries_.assign(vector.begin(), vector.end());
}
// Get  password after KeyDerive
std::string Database::getKey()
{
    return this->key_;
}
// Set password after KeyDerive
void Database::setKey(std::string key)
{
    this->key_ = key;
}
std::string Database::getPath()
{
    return this->path_;
}
Salt* Database::getGen()
{
    return this->gen;
}
// Dump database to json for export
nlohmann::json Database::exportToJson()
{
    nlohmann::json j = nlohmann::json::array();
    nlohmann::json databaseInfo;
    databaseInfo["hash"] = this->key_hash_;
    databaseInfo["hashAlgo"] = this->hash_algorithm_->getName();
    databaseInfo["keyDerive"] = this->key_derive_algorithm_->getName();
    databaseInfo["encryption"] = this->encryption_algorithm_->getName();
    databaseInfo["salt"] = this->salt_;
    j.push_back(databaseInfo);
    for (auto i : this->entries_)
    {
        std::string serviceName = i->getServiceName();
        std::string login = i->getLogin();
        std::string password = i->getPassword();
        std::string salt = i->getSalt();
        std::string encryptedServiceName = this->encryption_algorithm_->encryptData(serviceName, this->key_, salt);
        std::string encryptedLogin = this->encryption_algorithm_->encryptData(login, this->key_, salt);
        std::string encryptedPassword = this->encryption_algorithm_->encryptData(password, this->key_, salt);
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
        this->key_hash_ = i.value("hash", "");
        this->salt_ = i.value("salt","");
        std::string encryptionName = i.value("encryption", "");
        std::string hashName = i.value("hashAlgo", "");
        std::string keyDerive = i.value("keyDerive", "");
        if (this->string_to_function_.count(encryptionName) == 0)
        {
            std::cerr << "Unknow encryption algorithm" << std::endl;
        }
        else
        {
            this->encryption_algorithm_ = (Encryption *)this->string_to_function_.at(encryptionName);
        }
        if (this->string_to_function_.count(hashName) == 0)
        {
            std::cerr << "Unknow hash algorithm" << std::endl;
        }
        else
        {
            this->hash_algorithm_ = (Hash *)this->string_to_function_.at(hashName);
        }
        if (this->string_to_function_.count(keyDerive) == 0)
        {
            std::cerr << "Unknow keyDerive algorithm" << std::endl;
        }
        else
        {
            this->key_derive_algorithm_ = (KeyDerive *)this->string_to_function_.at(keyDerive);
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
    databaseInfo["hash"] = this->key_hash_;
    databaseInfo["hashAlgo"] = this->hash_algorithm_->getName();
    databaseInfo["keyDerive"] = this->key_derive_algorithm_->getName();
    databaseInfo["encryption"] = this->encryption_algorithm_->getName();
    databaseInfo["salt"] = this->salt_;
    j.push_back(databaseInfo);
    for (auto i : this->entries_)
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
    if (this->checkKey(this->key_))
    {
        std::cout << "Database inited" << std::endl;
        std::cout << "Database hash: " << this->key_hash_ << std::endl;
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
                std::string serviceName = this->encryption_algorithm_->decryptData(encryptedServiceName, this->key_, salt);
                std::string login = this->encryption_algorithm_->decryptData(encryptedLogin, this->key_, salt);
                std::string password = this->encryption_algorithm_->decryptData(encryptedPassword, this->key_, salt);
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
        this->entries_.assign(vctr.begin(),vctr.end());
    }
    else
    {
        std::cerr << "Wrong array structure" << std::endl;
    }
}
// Get password hash
std::string Database::getKeyHash()
{
    return this->key_hash_;
}
// Check if password arg hash equal to databasse hash
bool Database::checkKey(std::string key)
{
    return this->key_hash_ == this->hash_algorithm_->getHash(key);
}
// Add new Entry to database
void Database::addEntry(Entry *entry)
{
    this->entries_.push_back(entry);
}