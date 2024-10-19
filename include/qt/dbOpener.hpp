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
    Q_OBJECT;
    public:
        DataBaseOpener(QWidget *parent = nullptr,std::string filePath = "");
    private:
        std::string pass;
};
#endif