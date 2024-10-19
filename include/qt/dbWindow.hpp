#ifndef DBWINDOW_H
#define DBWINDOW_H
#include <QFileDialog>
#include <include/structure/database.hpp>
#include <include/qt/base.hpp>
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
    private:
        QListWidget* displayLabel = new QListWidget();
        std::vector<std::string> dataVector = {"123"};
        Database* db;
        void updateDisplay();
        void onAddClicked();
        void onEditClicked();
        void onSaveClicked();
    private slots:
        void onDeleteClicked() {
            int number = this->displayLabel->currentRow();
            std::vector<Entry*>& vctr = this->db->getEntries();
            vctr.erase(vctr.begin() + number);
            this->updateDisplay();
        }
    
};
#endif