/*
// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW7 - Personal Contact Book Main File
// ================================================================
// Program Description:
// An application for managing personal contacts.
// - Adding, editing, and deleting contacts.
// - Provides real-time search/filtering by name or email.
// - Features input validation using Regular Expressions.
// - Implements JSON data persistence for saving and loading contacts.
// - Includes a QMainWindow with menu bars, toolbars, and status bars.
// ================================================================
#include "mainwindow.h"
#include <QApplication>

// ================================================================
// Main Function:
// - Serves as the entry point for the GUI application.
// - Initializes the QApplication and MainWindow.
// ================================================================
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    
    // Create main application window
    MainWindow w;
    w.setWindowTitle("Personal Contact Book");
    w.show();
    
    // Execute application event loop
    return a.exec();

}
*/