#ifndef DBOPENER_H
#define DBOPENER_H
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <include/structure/database.hpp>
class DataBaseOpener : public QWidget
{
    Q_OBJECT
    public:
        DataBaseOpener(QWidget *parent = nullptr,std::string filePath = "");
        ~DataBaseOpener()
        {
            delete this->layout;
            delete this->password;
            delete this->submit;
        }
    private:
        std::string pass;
        QVBoxLayout* layout;
        QLineEdit* password;
        QPushButton* submit;
        Hash* sha256;
        hexFormating* hex;
        KeyDerive* pbkdf2;
        Encryption* aes;
        Salt* saltGenerator;
};
#endif