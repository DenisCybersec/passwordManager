#ifndef EDITENTRYWINDOW_HPP
#define EDITENTRYWINDOW_HPP

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

class EditEntryDialog : public QDialog{
Q_OBJECT
public:
    EditEntryDialog(DatabaseWindow* window,std::string serviceName, std::string login, std::string password,int place);

private:
    QLineEdit* service_name_;
    QLineEdit* login_;
    QLineEdit* password_;
    QPushButton *submit_button_;
    QVBoxLayout *layout_;
    DatabaseWindow* window_;

    void* f_;
    int place_;
    
    void onSubmit();
};
#endif