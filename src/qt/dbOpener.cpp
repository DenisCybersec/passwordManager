#include<include/qt/dbOpener.hpp>
#include<include/structure/database.hpp>
#include<include/qt/dbWindow.hpp>
#include<nlohmann/json.hpp>
#include<fstream>
DataBaseOpener::DataBaseOpener(QWidget *parent,std::string filePath) : QWidget(parent)
{
    this->setWindowTitle("Enter password");
    this->resize(300,200);
    this->show();
    this->layout_ = new QVBoxLayout(this);
    this->password_ = new QLineEdit(this);
    this->submit_ = new QPushButton(this);
    this->submit_->setText("Submit password");
    this->layout_->addWidget(password_);
    this->layout_->addWidget(submit_);
    int saltLength = 32;
    this->sha256_ = new Sha256();
    this->hex_ = new hexFormating();
    this->pbkdf2_ = new PBKDF2(1000,32,hex_);
    this->aes_ = new AES(pbkdf2_,hex_);
    this->salt_generator_ = new Salt();
    connect(submit_, &QPushButton::clicked, this, [this,filePath]() {
    QString inputText = this->password_->text();
    this->pass_ = inputText.toStdString();
    std::fstream f;
    f.open(filePath,std::ios::in);
    std::string jsStr;
    nlohmann::json j;
    f >> j;
    std::map<std::string, void*> mp = {{"SHA256",this->sha256_},{"AES",this->aes_},{"PBKDF2",this->pbkdf2_}};
    Database* db = new Database(j,this->pass_,mp,filePath);
    DatabaseWindow* dbWindow = new DatabaseWindow(nullptr,db);
    dbWindow->setWindowTitle("Database");
    dbWindow->resize(300,200);
    dbWindow->show();
    this->close();
    });
}