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
    std::string salt = this->salt_generator_->generateSalt(32);
    std::string pass = inputText.toStdString();
    Database* db = new Database(sha256,aes,pbkdf2,pass,salt,filePath);
    this->db_ = db;
    this->db_window_ = new DatabaseWindow(nullptr,this->db_);
}
DataBaseCreator::DataBaseCreator(QWidget *parent,std::string filePath) : QWidget(parent)
{
    this->setWindowTitle("Enter password");
    this->resize(300,200);
    this->show();
    this->salt_generator_ = new Salt();
    this->layout_ = new QVBoxLayout(this);
    this->password_ = new QLineEdit(this);
    this->submit_button_ = new QPushButton(this);
    this->hex_function_ = new hexFormating();
    this->key_derive_function_ = new PBKDF2(1000,32,this->hex_function_);
    this->hash_function_ = new Sha256();
    this->encryption_function_ = new AES(this->key_derive_function_,this->hex_function_);
    this->submit_button_->setText("Submit password");
    this->layout_->addWidget(this->password_);
    this->layout_->addWidget(this->submit_button_);
    connect(this->submit_button_, &QPushButton::clicked, this, [this,filePath]() {
        this->onClick(this->password_, this->hash_function_, this->encryption_function_, this->key_derive_function_,filePath);
    });

}