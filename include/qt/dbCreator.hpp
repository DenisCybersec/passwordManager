#ifndef DBCREATOR_HPP
#define DBCREATOR_HPP

#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <include/crypto/aes.hpp>
#include <include/crypto/sha256.hpp>
#include <include/structure/database.hpp>
#include<include/qt/dbWindow.hpp>
#include <include/crypto/salt.hpp>

class DataBaseCreator : public QWidget{
Q_OBJECT
public:
    DataBaseCreator(QWidget *parent = nullptr,std::string filePath = "");
    void onClick(QLineEdit* password,Hash* hash,Encryption* encryption,KeyDerive* keyDerive,std::string path);
    ~DataBaseCreator(){
        delete layout_;
        delete password_;
        delete submit_button_;
    }

private:
    Database* db_ = nullptr;
    Salt* salt_generator_ = nullptr;
    QVBoxLayout* layout_;
    QLineEdit* password_;
    QPushButton* submit_button_;
    KeyDerive* key_derive_function_;
    Hash* hash_function_;
    DatabaseWindow* db_window_;
    Encryption* encryption_function_;
    hexFormating* hex_function_;
};
#endif