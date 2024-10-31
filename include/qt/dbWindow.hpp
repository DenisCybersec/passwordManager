#ifndef DBWINDOW_HPP
#define DBWINDOW_HPP

#include <QFileDialog>
#include <include/structure/database.hpp>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidget>
#include <iostream>

class DatabaseWindow : public QWidget{
Q_OBJECT
public:
    DatabaseWindow(QWidget *parent = nullptr,Database* bd = nullptr);
    void addEntry(std::string serviceName,std::string login,std::string password); 
    void editEntry(std::string serviceName,std::string login,std::string password, int place);
    ~DatabaseWindow(){
        delete display_label_;
        delete main_layout_;
        delete button_layout_;
        delete add_button_;
        delete delete_button_;
        delete edit_button_;
        delete save_button_;
    }

    private:
        QListWidget* display_label_ = new QListWidget();
        QVBoxLayout *main_layout_;
        QHBoxLayout *button_layout_;
        QPushButton* add_button_;
        QPushButton* delete_button_;
        QPushButton* edit_button_;
        QPushButton* save_button_;
        Database* db_;
        Salt* salt_;

        void updateDisplay();
        void onAddClicked();
        void onEditClicked();
        void onSaveClicked();

    private slots:
        void onDeleteClicked() {
            int number = this->display_label_->currentRow();
            if(number >= 0 && number < this->db_->getEntries().size())
            {
                std::vector<Entry*>& vctr = this->db_->getEntries();
                vctr.erase(vctr.begin() + number);
                this->updateDisplay();
            }
        }
    
};
#endif