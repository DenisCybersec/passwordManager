#include<include/gui/gui.hpp>
#include<include/qt/fileselector.hpp>
int GUI::start(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // Create and show the Database Selection Window
    FileSelector dbSelector;
    dbSelector.setWindowTitle("Database Selector");
    dbSelector.resize(300, 200);  // Set initial size
    dbSelector.show();
    // Run the application
    return app.exec();
}