#ifndef DBCREATOR_H
#define DBCREATOR_H
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
class DataBaseCreator : public QWidget
{
    Q_OBJECT;
    public:
        DataBaseCreator(QWidget *parent = nullptr,std::string filePath = "");
        void onClick(QLineEdit* password,Hash* hash,Encryption* encryption,KeyDerive* keyDerive,std::string path);
        ~DataBaseCreator()
        {
            delete layout;
            delete password;
            delete submitButton;
        }
    private:
        Database* db = nullptr;
        Salt* saltGenerator = nullptr;
        QVBoxLayout* layout;
        QLineEdit* password;
        QPushButton* submitButton;
        KeyDerive* keyDeriveFunction;
        Hash* hashFunction;
        DatabaseWindow* dbWindow;
        Encryption* encryptionFunction;
        hexFormating* hexFunction;
};
#endif