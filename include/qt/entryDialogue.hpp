#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H
#include <QFileDialog>
#include <include/structure/database.hpp>
#include <include/qt/dbWindow.hpp>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
class EntryDialog : public QDialog
{
    Q_OBJECT;
    public:
        EntryDialog(DatabaseWindow* window);
    private:
        QLineEdit* serviceName;
        QLineEdit* login;
        QLineEdit* password;
        void* f;
        void onSubmit();
        DatabaseWindow* window;
};
#endif