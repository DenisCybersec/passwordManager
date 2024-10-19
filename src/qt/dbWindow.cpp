#include<include/qt/dbWindow.hpp>
#include <include/qt/entryDialogue.hpp>
#include <include/qt/editEntryDialogue.hpp>
#include <fstream>
DatabaseWindow::DatabaseWindow(QWidget *parent,Database* db) : QWidget(parent)
{
    this->setWindowTitle("Database");
    this->resize(300,200);
    this->show();
    // Initialize the layout and UI elements
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        this->db = db;
        QPushButton* addButton = new QPushButton("Add", this);
        QPushButton* deleteButton = new QPushButton("Delete", this);
        QPushButton* editButton = new QPushButton("Edit", this);
        QPushButton* saveButton = new QPushButton("Save", this);
        // Add buttons to horizontal layout
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(deleteButton);
        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(saveButton);
        std::vector<std::string> dataVector = {};
        for(auto i:db->getEntries())
        {
            dataVector.push_back(i->getServiceName());
        }
        // Label to display vector content
        for(auto i: dataVector)
        {
            QString qs = QString::fromStdString(i);
            this->displayLabel->addItem(qs);
        }
        // Add layouts to main layout
        mainLayout->addLayout(buttonLayout);
        mainLayout->addWidget(this->displayLabel);

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
    Entry* entry = new Entry("1234");
    entry->setLogin(login);
    entry->setServiceName(serviceName);
    entry->setPassword(password);
    std::cout << "Adding" << std::endl;
    std::cout << "E" << std::endl;
    std::cout << "Added" << std::endl;
    this->db->addEntry(entry);
    QString qs = QString::fromStdString(serviceName);
    this->displayLabel->addItem(qs);
    updateDisplay();
}
void DatabaseWindow::editEntry(std::string serviceName,std::string login,std::string password,int place)
{
    Entry* entry = this->db->getEntries().at(place);
    entry->setLogin(login);
    entry->setPassword(password);
    entry->setServiceName(serviceName);
}
void DatabaseWindow::onAddClicked() {
    int number = this->displayLabel->currentRow();
    EntryDialog* e = new EntryDialog(this);
    e->exec();
    updateDisplay();
}
void DatabaseWindow::onEditClicked() {
    int number = this->displayLabel->currentRow();
    Entry* entry = this->db->getEntries().at(number);
    std::string login = entry->getLogin();
    std::string password = entry->getPassword();
    std::string serviceName = entry->getServiceName();
    EditEntryDialog* e = new EditEntryDialog(this,serviceName,login,password,number);
    e->exec();
    updateDisplay();
}
void DatabaseWindow::updateDisplay()
    {
        std::vector<Entry*> vc = this->db->getEntries();
        for(int i = 0;i < this->displayLabel->size().height();i++)
        {
            std::cout << i << std::endl;
            this->displayLabel->takeItem(0);
        }
        for(auto i:vc)
        {
            std::cout << i->getServiceName() << std::endl;
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