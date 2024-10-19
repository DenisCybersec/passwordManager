#include<include/qt/fileselector.hpp>
#include<include/qt/dbCreator.hpp>
#include<include/qt/dbOpener.hpp>
#include<include/qt/dbWindow.hpp>
 FileSelector::FileSelector(QWidget *parent) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QPushButton *openDbButton = new QPushButton("Open Database", this);
        QPushButton *createDbButton = new QPushButton("Create New Database", this);

        layout->addWidget(openDbButton);
        layout->addWidget(createDbButton);

        connect(openDbButton, &QPushButton::clicked, this, &FileSelector::openDatabase);
        connect(createDbButton, &QPushButton::clicked, this, &FileSelector::createDatabase);
}
void FileSelector::openDatabase()
{
    QString dbPath = QFileDialog::getOpenFileName(this, "Open Database", "", "");
    std::string path = dbPath.toStdString();
    DataBaseOpener* opener = new DataBaseOpener(nullptr,path);
}
void FileSelector::createDatabase()
{
    QString dbPath = QFileDialog::getSaveFileName(this, "Create Database", "", "");
    std::string path = dbPath.toStdString();
    DataBaseCreator* dbCreator = new DataBaseCreator(nullptr,path);
    
}