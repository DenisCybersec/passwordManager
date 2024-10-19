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
#include <include/structure/database.hpp>
class DataBaseCreator : public QWidget
{
    Q_OBJECT;
    public:
        DataBaseCreator(QWidget *parent = nullptr,std::string filePath = "");
        void onClick(QLineEdit* password,Sha256* sha256,AES* aes,PBKDF2* pbkdf2,std::string path);
    private:
        Database* db = nullptr;

};
#endif