#include<include/qt/fileselector.hpp>
FileSelector::FileSelector(QWidget *parent) : QWidget(parent) {
        this->layout = new QVBoxLayout(this);
        this->openDbButton = new QPushButton("Open Database", this);
        this->createDbButton = new QPushButton("Create New Database", this);
        this->layout->addWidget(this->openDbButton);
        this->layout->addWidget(this->createDbButton);
        connect(this->openDbButton, &QPushButton::clicked, this, &FileSelector::openDatabase);
        connect(this->createDbButton, &QPushButton::clicked, this, &FileSelector::createDatabase);
}
void FileSelector::openDatabase()
{
    QString dbPath = QFileDialog::getOpenFileName(this, "Open Database", "", "");
    std::string path = dbPath.toStdString();
    this->opener = new DataBaseOpener(nullptr,path);
}
void FileSelector::createDatabase()
{
    QString dbPath = QFileDialog::getSaveFileName(this, "Create Database", "", "");
    std::string path = dbPath.toStdString();
    this->creator = new DataBaseCreator(nullptr,path);
}