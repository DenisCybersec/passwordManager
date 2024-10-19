#include<include/qt/dbCreator.hpp>
#include<include/crypto/aes.hpp>
#include<include/crypto/sha256.hpp>
#include<include/crypto/pbkdf2.hpp>
#include<include/crypto/salt.hpp>
#include<include/structure/database.hpp>
#include<include/qt/dbWindow.hpp>
void DataBaseCreator::onClick(QLineEdit* password,Hash* sha256,Encryption* aes,KeyDerive* pbkdf2,std::string filePath)
{
    QString inputText = password->text();
    std::string salt = this->saltGenerator->generateSalt(32);
    std::string pass = inputText.toStdString();
    Database* db = new Database(sha256,aes,pbkdf2,pass,salt,filePath);
    this->db = db;
    this->dbWindow = new DatabaseWindow(nullptr,this->db);
}
DataBaseCreator::DataBaseCreator(QWidget *parent,std::string filePath) : QWidget(parent)
{
    this->setWindowTitle("Enter password");
    this->resize(300,200);
    this->show();
    this->saltGenerator = new Salt();
    this->layout = new QVBoxLayout(this);
    this->password = new QLineEdit(this);
    this->submitButton = new QPushButton(this);
    this->hexFunction = new hexFormating();
    this->keyDeriveFunction = new PBKDF2(1000,32,this->hexFunction);
    this->hashFunction = new Sha256();
    this->encryptionFunction = new AES(this->keyDeriveFunction,this->hexFunction);
    this->submitButton->setText("Submit password");
    this->layout->addWidget(this->password);
    this->layout->addWidget(this->submitButton);
    connect(this->submitButton, &QPushButton::clicked, this, [this,filePath]() {
        this->onClick(this->password, this->hashFunction, this->encryptionFunction, this->keyDeriveFunction,filePath);
    });

}