// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW8A - Student Roster Class Implementation
// ================================================================
// Program Description:
// Implementation of the MainWindow class logic.
// - 5-column model with sample student data.
// - Sets up a dual-view layout (Table and List).
// - Implements conditional formatting based on student GPA.
// ================================================================
#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFont>
#include <QColor>

// ================================================================
// Constructor: MainWindow
// - Initializes the model and UI components.
// - Triggers initial formatting and establishes data-change links.
// ================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupModel();
    setupUI();
    updateFormatting();
    
    // Connect data changes to re-format cells in real time.
    connect(model, &QStandardItemModel::dataChanged, this, &MainWindow::updateFormatting);
}

MainWindow::~MainWindow() = default;

// ================================================================
// Function: setupModel
// - Creates a QStandardItemModel with 5 columns.
// - Populates 8 sample students with realistic (sort of) data.
// ================================================================
void MainWindow::setupModel()
{
    model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({"Student ID", "First Name", "Last Name", "Major", "GPA"});

    struct Student {
        QString id,
        firstName,
        lastName,
        major;
        double gpa;
    };

    QList<Student> students = {
        {"101", "Saim", "Ahmed", "CS", 4.0},
        {"102", "John", "Pork", "Math", 1.8},
        {"103", "Bobby", "Lee", "Art", 3.2},
        {"104", "Naruto", "Uzumaki", "Physics", 3.8},
        {"105", "Donald", "Glover", "Music", 2.5},
        {"106", "Joseph", "Joestar", "History", 1.5},
        {"107", "Jackie", "Chan", "Kinesiology", 4.0},
        {"108", "Walter", "White", "Chemistry", 3.6}
    };

    //Populate model with student row, GPA as string for display.
    for (const Student& s : students) {
        QList<QStandardItem*> row;
        row << new QStandardItem(s.id);
        row << new QStandardItem(s.firstName);
        row << new QStandardItem(s.lastName);
        row << new QStandardItem(s.major);
        row << new QStandardItem(QString::number(s.gpa, 'f', 1));
        model->appendRow(row);
    }
}

// ================================================================
// Function: setupUI
// - Arranges the TableView and ListView in a horizontal layout.
// - Configures sorting, row colors, and header resizing.
// - Connects Add/Remove buttons to slots.
// ================================================================
void MainWindow::setupUI()
{
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Setup Table View
    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setSortingEnabled(true);
    tableView->setAlternatingRowColors(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Setup List View
    listView = new QListView;
    listView->setModel(model);
    listView->setModelColumn(1); 

    // Layout views
    auto *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(tableView, 2);
    viewLayout->addWidget(listView, 1);

    // Setup Control Buttons
    addButton = new QPushButton("Add Student");
    removeButton = new QPushButton("Remove Student");

    auto *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(addButton);
    btnLayout->addWidget(removeButton);

    //Main layout
    auto *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(viewLayout);
    mainLayout->addLayout(btnLayout);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addStudent);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeStudent);

    setWindowTitle("HW8A - Student Roster");
    resize(800, 400);
}

// ================================================================
// Function: updateFormatting
// - Iterates through all items to apply visual roles.
// ================================================================
void MainWindow::updateFormatting()
{
    model->blockSignals(true); // Prevent stack overflow issue from recursive call by preventing signal calls

    //Iterate row-column wise and repopulate/reformat table and list data.
    for (int r = 0; r < model->rowCount(); ++r) {
        double gpa = model->item(r, 4)->text().toDouble();
        QString info = QString("ID: %1\nName: %2 %3\nMajor: %4\nGPA: %5").arg(model->item(r, 0)->text()).arg(model->item(r, 1)->text()).arg(model->item(r, 2)->text()).arg(model->item(r, 3)->text()).arg(model->item(r, 4)->text());

        for (int c = 0; c < model->columnCount(); ++c) {
            //Setting roles on existing items
            QStandardItem *item = model->item(r, c);

            //Use ToolTripRole to show full information in case column box is too small (without needing to resize).
            item->setData(info, Qt::ToolTipRole);

            // GPA dependant background coloring
            if (gpa < 2.0)
                item->setData(QColor(255, 200, 200), Qt::BackgroundRole);
            else if (gpa >= 3.5)
                item->setData(QColor(200, 255, 200), Qt::BackgroundRole);
            else
                item->setData(QVariant(), Qt::BackgroundRole); // No color

            // Apply bolded font for students who make it on the Dean's list (gpa req).
            QFont font = item->font();
            font.setBold(gpa >= 3.7);
            item->setFont(font);
        }
    }
    model->blockSignals(false); //Reenables signal calls
}

// ================================================================
// Slot: addStudent
// - Appends a new student record with placeholder values.
// - Triggers re-formatting for the new row.
// ================================================================
void MainWindow::addStudent()
{
    //Populate column with empty student data following struct Student format.
    QList<QStandardItem*> row;
    row << new QStandardItem("000");
    row << new QStandardItem("New");
    row << new QStandardItem("Student");
    row << new QStandardItem("None");
    row << new QStandardItem("0.0");
    model->appendRow(row);
    updateFormatting();
}

// ================================================================
// Slot: removeStudent
// - Identifies the currently selected row in the TableView.
// - Removes the corresponding data from the model.
// ================================================================
void MainWindow::removeStudent()
{
    QModelIndex index = tableView->currentIndex();
    //Ensures student is highlighted to remove.
    if (index.isValid()) {
        model->removeRow(index.row());
    }
}