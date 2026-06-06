// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8A - Student Roster Main File
// ================================================================
// Program Description:
// Application Entry Point
// - Instantiates and displays the MainWindow.
// - Starts the event loop for user interaction.
// ================================================================
#include "mainwindow.h"
#include <QApplication>

// ================================================================
// Main Function:
// - Serves as the entry point for program execution.
// - Creates the QApplication object to manage GUI state.
// - Displays the Student Roster window and executes the event loop.
// ================================================================
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Main UI
    MainWindow w;
    w.show();
    
    // Execute main event loop
    return QCoreApplication::exec();
}