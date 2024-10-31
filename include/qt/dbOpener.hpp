#ifndef DBOPENER_HPP
#define DBOPENER_HPP

#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <include/structure/database.hpp>

class DataBaseOpener : public QWidget{
Q_OBJECT
public:
    DataBaseOpener(QWidget *parent = nullptr,std::string filePath = "");
    ~DataBaseOpener(){
        delete this->layout_;
        delete this->password_;
        delete this->submit_;
    }
    
private:
    std::string pass_;
    QVBoxLayout* layout_;
    QLineEdit* password_;
    QPushButton* submit_;
    Hash* sha256_;
    hexFormating* hex_;
    KeyDerive* pbkdf2_;
    Encryption* aes_;
    Salt* salt_generator_;
};
#endif