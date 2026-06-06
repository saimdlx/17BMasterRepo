// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW7B - Student Gradebook Main File
// ================================================================
// Program Description:
// Student Gradebook application using Qt Widgets.
// - Manage multiple courses and individual grade entries.
// - Calculation of course averages and overall GPA.
// - Data persistence via JSON files
// ================================================================
#include "mainwindow.h"
#include <QApplication>

// ================================================================
// Main Function:
// - Serves as the entry point for the Gradebook application.
// - Initializes the QApplication and shows the MainWindow.
// ================================================================
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
