// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8B - Book Inventory Main Window Header File
// ================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include "bookmodel.h"

// ================================================================
// Class: MainWindow
// Main UI for BookModel Use.
// Manages a BookModel for data.
// Uses a QSortFilterProxyModel to provide sorting capabilities without
// altering the underlying data model's storage order.
// Connects button clicks to model modification methods.
// ================================================================
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // Slots handle UI events like button clicks.
    void onAddBookClicked();
    void onRemoveBookClicked();

private:
    BookModel *model;                   // Book data.
    QSortFilterProxyModel *proxyModel;  // Used for column sorting without needing to overwrite sort() for vectors (refer to https://doc.qt.io/qt-6/qsortfilterproxymodel.html)
    QTableView *tableView;              // The visual grid display for the books.
    QPushButton addButton;              // Button to trigger addition logic.
    QPushButton removeButton;           // Button to trigger deletion logic.
};

#endif // MAINWINDOW_H
