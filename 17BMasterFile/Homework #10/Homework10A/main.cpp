// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10A - Thread-Safe Counter Application
// ================================================================
// Program Description:
// Main Output File
// - Required 5 Run Outpu:
//    Run 1 (Part A - Race):
//    Expected: 400000
//    Actual:   194458
//    Run 2 (Part A - Race):
//    Expected: 400000
//    Actual:   200011
//    Run 3 (Part A - Race):
//    Expected: 400000
//    Actual:   179789
//    Run 4 (Part A - Race):
//    Expected: 400000
//    Actual:   140029
//    Run 5 (Part A - Race):
//    Expected: 400000
//    Actual:   135639
// ================================================================

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}