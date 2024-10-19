#ifndef DBWINDOW_H
#define DBWINDOW_H
#include <QFileDialog>
#include <include/structure/database.hpp>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidget>
#include <iostream>
class DatabaseWindow : public QWidget
{
    Q_OBJECT;
    public:
        DatabaseWindow(QWidget *parent = nullptr,Database* bd = nullptr);
        void addEntry(std::string serviceName,std::string login,std::string password); 
        void editEntry(std::string serviceName,std::string login,std::string password, int place);
        ~DatabaseWindow()
        {
            delete displayLabel;
            delete mainLayout;
            delete buttonLayout;
            delete addButton;
            delete deleteButton;
            delete editButton;
            delete saveButton;
        }
    private:
        QListWidget* displayLabel = new QListWidget();
        QVBoxLayout *mainLayout;
        QHBoxLayout *buttonLayout;
        QPushButton* addButton;
        QPushButton* deleteButton;
        QPushButton* editButton;
        QPushButton* saveButton;
        Database* db;
        Salt* salt;
        void updateDisplay();
        void onAddClicked();
        void onEditClicked();
        void onSaveClicked();
    private slots:
        void onDeleteClicked() {
            int number = this->displayLabel->currentRow();
            if(number >= 0 && number < this->db->getEntries().size())
            {
                std::vector<Entry*>& vctr = this->db->getEntries();
                vctr.erase(vctr.begin() + number);
                this->updateDisplay();
            }
        }
    
};
#endif