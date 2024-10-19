#ifndef EDITENTRYWINDOW_H
#define EDITENTRYWINDOW_H
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
class EditEntryDialog : public QDialog
{
    Q_OBJECT;
    public:
        EditEntryDialog(DatabaseWindow* window,std::string serviceName, std::string login, std::string password,int place);
    private:
        QLineEdit* serviceName;
        QLineEdit* login;
        QLineEdit* password;
        QPushButton *submitButton;
        QVBoxLayout *layout;
        void* f;
        int place;
        void onSubmit();
        DatabaseWindow* window;
};
#endif