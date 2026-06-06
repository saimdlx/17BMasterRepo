// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8B - Book Inventory Main File
// ================================================================
#include <QApplication>
#include "mainwindow.h"

// ================================================================
// Main Function:
// Initializes the Qt environment and the main window.
// ================================================================
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
