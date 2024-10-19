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
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLineEdit *password = new QLineEdit(this);
    QPushButton *submit = new QPushButton(this);
    submit->setText("Submit password");
    layout->addWidget(password);
    layout->addWidget(submit);
    int saltLength = 2;
    Hash* sha256 = new Sha256();
    hexFormating* hex = new hexFormating();
    KeyDerive* pbkdf2 = new PBKDF2(1000,32,hex);
    Encryption* aes = new AES(pbkdf2,hex);
    Salt* saltGenerator = new Salt();
    connect(submit, &QPushButton::clicked, this, [this,sha256,aes,pbkdf2,password,filePath]() {
        // Retrieve the text from QLineEdit
        QString inputText = password->text();
        this->pass = inputText.toStdString();
        std::fstream f;
        f.open(filePath,std::ios::in);
        std::string jsStr;
        nlohmann::json j;
        f >> j;
        std::map<std::string, void*> mp = {{"SHA256",sha256},{"AES",aes},{"PBKDF2",pbkdf2}};
        Database* db = new Database(j,this->pass,mp,filePath);
        DatabaseWindow* dbWindow = new DatabaseWindow(nullptr,db);
        dbWindow->setWindowTitle("Database");
        dbWindow->resize(300,200);
        dbWindow->show();
        this->setHidden(1);
        // Process the input (for demonstration, we'll just print it)
        std::cout << "User input:" << inputText.toStdString() << std::endl;;
});
 
}