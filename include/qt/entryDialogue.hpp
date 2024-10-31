#ifndef ENTRYWINDOW_HPP
#define ENTRYWINDOW_HPP

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

class EntryDialog : public QDialog{
Q_OBJECT
public:
    EntryDialog(DatabaseWindow* window);
private:
    QPushButton *submit_button_;
    QVBoxLayout *layout_;
    QLineEdit* service_name_;
    QLineEdit* login_;
    QLineEdit* password_;
    DatabaseWindow* window_;

    void* f_;
    
    void onSubmit();    
};
#endif