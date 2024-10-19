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
    this->layout = new QVBoxLayout(this);
    this->password = new QLineEdit(this);
    this->submit = new QPushButton(this);
    this->submit->setText("Submit password");
    this->layout->addWidget(password);
    this->layout->addWidget(submit);
    int saltLength = 32;
    this->sha256 = new Sha256();
    this->hex = new hexFormating();
    this->pbkdf2 = new PBKDF2(1000,32,hex);
    this->aes = new AES(pbkdf2,hex);
    this->saltGenerator = new Salt();
    connect(submit, &QPushButton::clicked, this, [this,filePath]() {
    QString inputText = this->password->text();
    this->pass = inputText.toStdString();
    std::fstream f;
    f.open(filePath,std::ios::in);
    std::string jsStr;
    nlohmann::json j;
    f >> j;
    std::map<std::string, void*> mp = {{"SHA256",this->sha256},{"AES",this->aes},{"PBKDF2",this->pbkdf2}};
    Database* db = new Database(j,this->pass,mp,filePath);
    DatabaseWindow* dbWindow = new DatabaseWindow(nullptr,db);
    dbWindow->setWindowTitle("Database");
    dbWindow->resize(300,200);
    dbWindow->show();
    this->close();
    });
}