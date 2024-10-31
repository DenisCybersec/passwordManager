#include<include/qt/dbWindow.hpp>
#include <include/qt/entryDialogue.hpp>
#include <include/qt/editEntryDialogue.hpp>
#include <fstream>
DatabaseWindow::DatabaseWindow(QWidget *parent,Database* db) : QWidget(parent)
{
    this->setWindowTitle("Database");
    this->resize(300,200);
    this->show();
    this->salt_ = new Salt();
    // Initialize the layout and UI elements
    this->main_layout_ = new QVBoxLayout(this);
    this->button_layout_ = new QHBoxLayout();
    this->db_ = db;
    this->add_button_ = new QPushButton("Add", this);
    this->delete_button_ = new QPushButton("Delete", this);
    this->edit_button_ = new QPushButton("Edit", this);
    this->save_button_ = new QPushButton("Save", this);
    // Add buttons to horizontal layout
    this->button_layout_->addWidget(add_button_);
    this->button_layout_->addWidget(delete_button_);
    this->button_layout_->addWidget(edit_button_);
    this->button_layout_->addWidget(save_button_);
    std::vector<std::string> dataVector = {};
    for(auto i:this->db_->getEntries())
    {
        QString qs = QString::fromStdString(i->getServiceName());
        this->display_label_->addItem(qs);
    }
    // Add layouts to main layout
    this->main_layout_->addLayout(button_layout_);
    this->main_layout_->addWidget(this->display_label_);
    // Initialize vector and update display
    this->updateDisplay();
    // Connect buttons to their respective slots
    connect(add_button_, &QPushButton::clicked, this, &DatabaseWindow::onAddClicked);
    connect(delete_button_, &QPushButton::clicked, this, &DatabaseWindow::onDeleteClicked);
    connect(edit_button_, &QPushButton::clicked, this, &DatabaseWindow::onEditClicked);
    connect(save_button_, &QPushButton::clicked, this, &DatabaseWindow::onSaveClicked);
}
void DatabaseWindow::addEntry(std::string serviceName,std::string login,std::string password)
{
    Entry* entry = new Entry(this->db_->getGen()->generateSalt(32));
    entry->setLogin(login);
    entry->setServiceName(serviceName);
    entry->setPassword(password);
    this->db_->addEntry(entry);
    QString qs = QString::fromStdString(serviceName);
    this->display_label_->addItem(qs);
    updateDisplay();
}
void DatabaseWindow::editEntry(std::string serviceName,std::string login,std::string password,int number)
{
    Entry* entry = this->db_->getEntries().at(number);
    if(number >= 0 && number < this->db_->getEntries().size())
    {
        entry->setLogin(login);
        entry->setPassword(password);
        entry->setServiceName(serviceName);
    }
}
void DatabaseWindow::onAddClicked() {
    EntryDialog* e = new EntryDialog(this);
    e->exec();
    updateDisplay();
}
void DatabaseWindow::onEditClicked() {
    int number = this->display_label_->currentRow();
    if(number >= 0 && number < this->db_->getEntries().size())
    {
        Entry* entry = this->db_->getEntries().at(number);
        std::string login = entry->getLogin();
        std::string password = entry->getPassword();
        std::string serviceName = entry->getServiceName();
        EditEntryDialog* e = new EditEntryDialog(this,serviceName,login,password,number);
        e->exec();
        updateDisplay();
    }
}
void DatabaseWindow::updateDisplay()
{
    std::vector<Entry*> vc = this->db_->getEntries();
    for(int i = 0;i < this->display_label_->size().height();i++)
    {
        this->display_label_->takeItem(0);
    }
    for(auto i:vc)
    {
        QString qs = QString::fromStdString(i->getServiceName());
        this->display_label_->addItem(qs);
    }
    this->display_label_->update();
}
void DatabaseWindow::onSaveClicked()
{
    nlohmann::json j = this->db_->exportToJson();
    std::fstream f;
    f.open(this->db_->getPath(),std::ios::out);
    f << j.dump(4);
}