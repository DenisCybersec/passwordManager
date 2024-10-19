#include<include/qt/dbCreator.hpp>
#include<include/crypto/aes.hpp>
#include<include/crypto/sha256.hpp>
#include<include/crypto/pbkdf2.hpp>
#include<include/crypto/salt.hpp>
#include<include/structure/database.hpp>
#include<include/qt/dbWindow.hpp>
void DataBaseCreator::onClick(QLineEdit* password,Sha256* sha256,AES* aes,PBKDF2* pbkdf2,std::string filePath)
{
    // Retrieve the text from QLineEdit
    QString inputText = password->text();
    // Process the input (for demonstration, we'll just print it)
    std::string salt = "1234";
    std::string pass = inputText.toStdString();
    Database* db = new Database(sha256,aes,pbkdf2,pass,salt,filePath);
    std::cout << "User input:" << inputText.toStdString() << std::endl;
    this->db = db;
    DatabaseWindow* dbWindow = new DatabaseWindow(nullptr,this->db);
}
DataBaseCreator::DataBaseCreator(QWidget *parent,std::string filePath) : QWidget(parent)
{
    this->setWindowTitle("Enter password");
    this->resize(300,200);
    this->show();
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLineEdit *password = new QLineEdit(this);
    QPushButton *submit = new QPushButton(this);
    hexFormating* hex = new hexFormating();
    PBKDF2* pbkdf2 = new PBKDF2(1000,32,hex);
    Sha256* sha256 = new Sha256();
    AES* aes = new AES(pbkdf2,hex);
    submit->setText("Submit password");
    layout->addWidget(password);
    layout->addWidget(submit);
    std::string& pass();
    connect(submit, &QPushButton::clicked, this, [password, sha256, aes, pbkdf2,filePath, this]() {
        this->onClick(password, sha256, aes, pbkdf2,filePath);
    });

}