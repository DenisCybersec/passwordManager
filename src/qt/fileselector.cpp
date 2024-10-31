#include<include/qt/fileselector.hpp>
FileSelector::FileSelector(QWidget *parent) : QWidget(parent) {
        this->layout_ = new QVBoxLayout(this);
        this->open_db_button = new QPushButton("Open Database", this);
        this->create_db_button = new QPushButton("Create New Database", this);
        this->layout_->addWidget(this->open_db_button);
        this->layout_->addWidget(this->create_db_button);
        connect(this->open_db_button, &QPushButton::clicked, this, &FileSelector::openDatabase);
        connect(this->create_db_button, &QPushButton::clicked, this, &FileSelector::createDatabase);
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