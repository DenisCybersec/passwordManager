#ifndef FILESELECTOR_H
#define FILESELECTOR_H
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <iostream>
class FileSelector : public QWidget
{
    Q_OBJECT;
    public:
        FileSelector(QWidget *parent = nullptr);
        
    private:
        void openDatabase();
        void createDatabase();
        
};
#endif