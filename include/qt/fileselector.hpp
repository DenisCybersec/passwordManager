#ifndef FILESELECTOR_HPP
#define FILESELECTOR_HPP

#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include<include/qt/dbCreator.hpp>
#include<include/qt/dbOpener.hpp>
#include<include/qt/dbWindow.hpp>
#include <iostream>

// class used for choosing whether to open database or create new one
class FileSelector : public QWidget{
Q_OBJECT

public:
    FileSelector(QWidget *parent = nullptr);    

private:
    QVBoxLayout* layout_ = nullptr;
    QPushButton* open_db_button = nullptr;
    QPushButton* create_db_button = nullptr;
    DataBaseOpener* opener = nullptr;
    DataBaseCreator* creator = nullptr;
        
    void openDatabase();
    void createDatabase();
};
#endif