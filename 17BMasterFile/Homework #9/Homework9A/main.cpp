// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Image Viewer Application Main File
// ================================================================
// Program Description:
// Image Viewer Application
// - Initializes the Qt environment and launches the main window.
// - Handles the application event loop.
// ================================================================
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}