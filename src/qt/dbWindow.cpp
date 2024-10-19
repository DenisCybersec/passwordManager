#include<include/qt/dbWindow.hpp>
#include <include/qt/entryDialogue.hpp>
#include <include/qt/editEntryDialogue.hpp>
#include <fstream>
DatabaseWindow::DatabaseWindow(QWidget *parent,Database* db) : QWidget(parent)
{
    this->setWindowTitle("Database");
    this->resize(300,200);
    this->show();
    this->salt = new Salt();
    // Initialize the layout and UI elements
    this->mainLayout = new QVBoxLayout(this);
    this->buttonLayout = new QHBoxLayout();
    this->db = db;
    this->addButton = new QPushButton("Add", this);
    this->deleteButton = new QPushButton("Delete", this);
    this->editButton = new QPushButton("Edit", this);
    this->saveButton = new QPushButton("Save", this);
    // Add buttons to horizontal layout
    this->buttonLayout->addWidget(addButton);
    this->buttonLayout->addWidget(deleteButton);
    this->buttonLayout->addWidget(editButton);
    this->buttonLayout->addWidget(saveButton);
    std::vector<std::string> dataVector = {};
    for(auto i:this->db->getEntries())
    {
        QString qs = QString::fromStdString(i->getServiceName());
        this->displayLabel->addItem(qs);
    }
    // Add layouts to main layout
    this->mainLayout->addLayout(buttonLayout);
    this->mainLayout->addWidget(this->displayLabel);
    // Initialize vector and update display
    this->updateDisplay();
    // Connect buttons to their respective slots
    connect(addButton, &QPushButton::clicked, this, &DatabaseWindow::onAddClicked);
    connect(deleteButton, &QPushButton::clicked, this, &DatabaseWindow::onDeleteClicked);
    connect(editButton, &QPushButton::clicked, this, &DatabaseWindow::onEditClicked);
    connect(saveButton, &QPushButton::clicked, this, &DatabaseWindow::onSaveClicked);
}
void DatabaseWindow::addEntry(std::string serviceName,std::string login,std::string password)
{
    Entry* entry = new Entry(this->db->getGen()->generateSalt(32));
    entry->setLogin(login);
    entry->setServiceName(serviceName);
    entry->setPassword(password);
    this->db->addEntry(entry);
    QString qs = QString::fromStdString(serviceName);
    this->displayLabel->addItem(qs);
    updateDisplay();
}
void DatabaseWindow::editEntry(std::string serviceName,std::string login,std::string password,int number)
{
    Entry* entry = this->db->getEntries().at(number);
    if(number >= 0 && number < this->db->getEntries().size())
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
    int number = this->displayLabel->currentRow();
    if(number >= 0 && number < this->db->getEntries().size())
    {
        Entry* entry = this->db->getEntries().at(number);
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
    std::vector<Entry*> vc = this->db->getEntries();
    for(int i = 0;i < this->displayLabel->size().height();i++)
    {
        this->displayLabel->takeItem(0);
    }
    for(auto i:vc)
    {
        QString qs = QString::fromStdString(i->getServiceName());
        this->displayLabel->addItem(qs);
    }
    this->displayLabel->update();
}
void DatabaseWindow::onSaveClicked()
{
    nlohmann::json j = this->db->exportToJson();
    std::fstream f;
    f.open(this->db->getPath(),std::ios::out);
    f << j.dump(4);
}