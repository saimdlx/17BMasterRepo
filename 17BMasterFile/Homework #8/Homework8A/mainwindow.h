// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8A - Student Roster Header File
// ================================================================
// Program Description:
// Student Roster Application using Qt Model/View Architecture
// - Implements QStandardItemModel to store student data.
// - Connects multiple views (QTableView, QListView) to one model.
// - Features row insertion/deletion and column sorting.
// ================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QListView>
#include <QPushButton>

// ================================================================
// Class: MainWindow
// - Manages the lifecycle of the data model and UI components.
// - Handles signals/slots for interactive features and formatting.
// - Declares function and variables for implementation file
// ================================================================
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // ================================================================
    // Slots:
    // - addStudent(): Inserts a new row with default values.
    // - removeStudent(): Deletes the currently selected student.
    // - updateFormatting(): Re-evaluates cell styles based on data.
    // ================================================================
    void addStudent();
    void removeStudent();
    void updateFormatting();

private:
    QStandardItemModel *model;  // data storage
    QTableView *tableView;      // Table view of all data
    QListView *listView;        // Simple list showing names
    QPushButton *addButton;     // Button for row insertion
    QPushButton *removeButton;  // Button for row deletion

    void setupModel();          // Initializes columns and sample data
    void setupUI();             // Configures layouts and view properties
};
#endif // MAINWINDOW_H