#ifndef MainWindow_HPP
#define MainWindow_HPP

#include<QMainWindow>
#include<QLabel>
#include<QVBoxLayout>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif
