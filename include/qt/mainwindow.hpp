#ifndef MainWindow_H
#define MainWindow_H
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
