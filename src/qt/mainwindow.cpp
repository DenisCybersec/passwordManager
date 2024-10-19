#include<include/qt/mainwindow.hpp>
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    setFixedSize(800, 600);
    setWindowTitle("Password Manager");
    QLabel *label = new QLabel("Welcome to the Password Manager!", this);
    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);
}
MainWindow::~MainWindow(){};
