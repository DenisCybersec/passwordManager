#ifndef FILESELECTOR_H
#define FILESELECTOR_H
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include<include/qt/dbCreator.hpp>
#include<include/qt/dbOpener.hpp>
#include<include/qt/dbWindow.hpp>
#include <iostream>
// class used for choosing whether to open database or create new one
class FileSelector : public QWidget
{
    Q_OBJECT;
    public:
        FileSelector(QWidget *parent = nullptr);
        
    private:
        void openDatabase();
        void createDatabase();
        QVBoxLayout* layout = nullptr;
        QPushButton* openDbButton = nullptr;
        QPushButton* createDbButton = nullptr;
        DataBaseOpener* opener = nullptr;
        DataBaseCreator* creator = nullptr;
};
#endif