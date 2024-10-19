#include <QApplication>
#include <QPushButton>
#include <include/cli/mainCycle.hpp>
#include <include/gui/gui.hpp>
int main(int argc, char **argv)
{
    GUI* gui = new GUI();
    gui->start(argc,argv);
}

