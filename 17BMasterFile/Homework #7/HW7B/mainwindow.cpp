// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW7B - Student Gradebook Class File
// ================================================================
// Program Description:
// Implementation of the Gradebook MainWindow.
// - Handles UI events and user interactions.
// - Performs grade calculations and data validation.
// - Implements JSON-based file storage.
// ================================================================
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGroupBox>
#include <QFile>
#include <algorithm>
#include <QPushButton>

// ================================================================
// Function: MainWindow
// - Constructs the main application window and its components.
// ================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupActions();
    setupMenus();
    setupToolbar();
    setupUI();
    
    // Set initial status and calculate stats
    statusBar()->showMessage("Ready");
    updateStats();
}

MainWindow::~MainWindow() = default;

// ================================================================
// Function: setupActions
// - Defines QAction objects shared between menus and toolbars.
// ================================================================
void MainWindow::setupActions() {
    // File operations
    saveAction = new QAction("&Save Grades", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveGrades);

    loadAction = new QAction("&Load Grades", this);
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadGrades);

    exitAction = new QAction("E&xit", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Course management
    addCourseAction = new QAction("Add Course", this);
    connect(addCourseAction, &QAction::triggered, this, &MainWindow::addCourse);

    removeCourseAction = new QAction("Remove Course", this);
    connect(removeCourseAction, &QAction::triggered, this, &MainWindow::removeCourse);

    // Grade management
    addGradeAction = new QAction("Add Grade", this);
    addGradeAction->setEnabled(false);
    connect(addGradeAction, &QAction::triggered, this, &MainWindow::addGrade);

    // Help bar
    aboutAction = new QAction("About", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

// ================================================================
// Function: setupMenus
// - Configures the applications menu bar
// ================================================================
void MainWindow::setupMenus() {
    // Setup File menu
    auto *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Setup Course menu
    auto *courseMenu = menuBar()->addMenu("&Course");
    courseMenu->addAction(addCourseAction);
    courseMenu->addAction(removeCourseAction);

    // Setup Help menu
    auto *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
}

// ================================================================
// Function: setupToolbar
// - Populates the main toolbar with primary action buttons.
// ================================================================
void MainWindow::setupToolbar() {
    // Add buttons to toolbar
    auto *toolbar = addToolBar("Main Toolbar");
    toolbar->addAction(addCourseAction);
    toolbar->addAction(addGradeAction);
    toolbar->addAction(saveAction);
}

// ================================================================
// Function: setupUI
// - Constructs the central layout and nested widgets.
// ================================================================
void MainWindow::setupUI() {
    auto *central = new QWidget(this);
    setCentralWidget(central);
    auto *mainLayout = new QVBoxLayout(central);

    // Top Section - Course Selection and Statistics
    auto *topLayout = new QHBoxLayout();
    courseCombo = new QComboBox();
    courseCombo->setPlaceholderText("Select a course...");
    connect(courseCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onCourseSelected);
    
    overallGpaLabel = new QLabel("Overall GPA: 0.00%");
    
    topLayout->addWidget(new QLabel("Course:"));
    topLayout->addWidget(courseCombo, 1);
    topLayout->addWidget(overallGpaLabel);
    mainLayout->addLayout(topLayout);

    // Middle Section - Grade Entry Form
    auto *middleFrame = new QGroupBox("Add New Grade", this);
    auto *middleLayout = new QFormLayout(middleFrame);
    
    assignEdit = new QLineEdit();
    earnedSpin = new QSpinBox();
    earnedSpin->setRange(0, 100);
    totalSpin = new QSpinBox();
    totalSpin->setRange(1, 100);
    totalSpin->setValue(100);
    
    categoryCombo = new QComboBox();
    categoryCombo->addItems({"Homework", "Quiz", "Exam", "Project"});
    
    auto *addGradeBtn = new QPushButton("Add Grade");
    connect(addGradeBtn, &QPushButton::clicked, this, &MainWindow::addGrade);
    
    middleLayout->addRow("Assignment:", assignEdit);
    middleLayout->addRow("Points Earned:", earnedSpin);
    middleLayout->addRow("Total Possible:", totalSpin);
    middleLayout->addRow("Category:", categoryCombo);
    middleLayout->addRow(addGradeBtn);
    
    mainLayout->addWidget(middleFrame);

    // Bottom Section - Grade Display Table and Status
    gradeTable = new QTableWidget(0, 5);
    gradeTable->setHorizontalHeaderLabels({"Assignment", "Category", "Score", "Percentage", "Letter"});
    gradeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    gradeTable->setAlternatingRowColors(true);
    gradeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    mainLayout->addWidget(gradeTable);

    auto *bottomActionLayout = new QHBoxLayout();
    auto *deleteBtn = new QPushButton("Delete Selected");
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteSelectedGrade);
    
    courseAvgProgress = new QProgressBar();
    courseAvgProgress->setRange(0, 100);
    courseAvgProgress->setValue(0);
    courseAvgProgress->setFormat("Course Average: %p%");

    bottomActionLayout->addWidget(deleteBtn);
    bottomActionLayout->addWidget(courseAvgProgress, 1);
    mainLayout->addLayout(bottomActionLayout);
}

// ================================================================
// Function: addCourse
// - Prompts user for a course name and adds it to the list.
// ================================================================
void MainWindow::addCourse() {
    bool ok;
    // Get course name from modal input dialog
    QString name = QInputDialog::getText(this, "Add Course", "Course Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.trimmed().isEmpty()) {
        Course c;
        c.name = name.trimmed();
        m_courses.append(c);
        // Sync UI with new data
        courseCombo->addItem(c.name);
        courseCombo->setCurrentIndex(m_courses.size() - 1);
        updateStats();
    }
}

// ================================================================
// Function: removeCourse
// - Deletes the current course after user confirmation.
// ================================================================
void MainWindow::removeCourse() {
    int i = courseCombo->currentIndex();
    if (i < 0) return;

    // Confirm removal if course is not empty
    if (!m_courses[i].grades.isEmpty()) {
        auto res = QMessageBox::question(this, "Confirm Removal", 
            "Are you sure you want to remove this course?",
            QMessageBox::Yes | QMessageBox::No);
        if (res != QMessageBox::Yes) return;
    }

    // Remove from memory and UI
    m_courses.removeAt(i);
    courseCombo->removeItem(i);
    updateStats();
}

// ================================================================
// Function: onCourseSelected
// - Updates UI state when the user switches between courses.
// ================================================================
void MainWindow::onCourseSelected(int i) {
    bool hasCourse = (i >= 0);
    // Toggle action state based on context
    addGradeAction->setEnabled(hasCourse);
    updateTable();
    updateStats();
    
    // Refresh status bar details
    if (hasCourse) {
        statusBar()->showMessage(QString("Course: %1 | Grades: %2")
            .arg(m_courses[i].name)
            .arg(m_courses[i].grades.size()));
    } else {
        statusBar()->showMessage("No course selected");
    }
}

// ================================================================
// Function: addGrade
// - Validates and adds a new grade entry to the current course.
// ================================================================
void MainWindow::addGrade() {
    int i = courseCombo->currentIndex();
    if (i < 0) {
        QMessageBox::warning(this, "Error", "No course is selected!");
        return;
    }
    
    // Ensure assignment has a name
    QString name = assignEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Assignment name is required!");
        return;
    }

    // Create grade object from form data
    Grade g;
    g.assignmentName = name;
    g.category = categoryCombo->currentText();
    g.pointsEarned = earnedSpin->value();
    g.pointsTotal = totalSpin->value();

    // Commit to memory and refresh views
    m_courses[i].grades.append(g);
    updateTable();
    updateStats();
    clearGradeInputs();
    
    onCourseSelected(i); // Update status bar info
}

// ================================================================
// Function: deleteSelectedGrade
// - Removes selected rows from the grade table and course data.
// ================================================================
void MainWindow::deleteSelectedGrade() {
    int coursei = courseCombo->currentIndex();
    if (coursei < 0) return;

    // Identify rows flagged for deletion
    auto items = gradeTable->selectionModel()->selectedRows();
    if (items.isEmpty()) return;

    // Sort descending to prevent shifting indices problem.
    QList<int> rows;
    for (const auto& item : items) rows.append(item.row());
    std::sort(rows.begin(), rows.end(), std::greater<int>());

    // Purge selected grades
    for (int row : rows) {
        m_courses[coursei].grades.removeAt(row);
    }

    // Refresh table and statistics
    updateTable();
    updateStats();
    onCourseSelected(coursei);
}

// ================================================================
// Function: updateTable
// - Refreshes the table view based on the current course's grades.
// ================================================================
void MainWindow::updateTable() {
    // Clear existing table content
    gradeTable->setRowCount(0);
    int i = courseCombo->currentIndex();
    if (i < 0) return;

    // Iterate through course grades to build table rows
    const auto& grades = m_courses[i].grades;
    for (const auto& g : grades) {
        int row = gradeTable->rowCount();
        gradeTable->insertRow(row);
        
        // Populate standard columns
        gradeTable->setItem(row, 0, new QTableWidgetItem(g.assignmentName));
        gradeTable->setItem(row, 1, new QTableWidgetItem(g.category));
        gradeTable->setItem(row, 2, new QTableWidgetItem(QString("%1/%2").arg(g.pointsEarned).arg(g.pointsTotal)));
        gradeTable->setItem(row, 3, new QTableWidgetItem(QString("%1%").arg(g.percentage(), 0, 'f', 1)));
        
        // Calculate and color-code letter grade
        auto *letterItem = new QTableWidgetItem(g.letterGrade());
        QString letter = g.letterGrade();
        if (letter == "A") letterItem->setForeground(Qt::green);
        else if (letter == "B") letterItem->setForeground(Qt::blue);
        else if (letter == "C") letterItem->setForeground(QColor("orange"));
        else letterItem->setForeground(Qt::red);
        
        gradeTable->setItem(row, 4, letterItem);
    }
}

// ================================================================
// Function: updateStats
// - Calculates and updates course and overall GPA metrics.
// ================================================================
void MainWindow::updateStats() {
    // Calculate and display course-specific average
    int i = courseCombo->currentIndex();
    if (i >= 0) {
        courseAvgProgress->setValue(static_cast<int>(m_courses[i].average()));
    } else {
        courseAvgProgress->setValue(0);
    }

    // Totals for global percentage calculation
    float totalEarned = 0;
    float totalPossible = 0;
    for (const auto& c : m_courses) {
        for (const auto& g : c.grades) {
            totalEarned += g.pointsEarned;
            totalPossible += g.pointsTotal;
        }
    }

    // Update global GPA display
    double overall = totalPossible > 0 ? (double)totalEarned / totalPossible * 100.0 : 0.0;
    overallGpaLabel->setText(QString("Overall GPA: %1%").arg(overall, 0, 'f', 2));
}

// ================================================================
// Function: clearGradeInputs
// - Resets the grade entry form to default values.
// ================================================================
void MainWindow::clearGradeInputs() {
    // Reset UI form fields
    assignEdit->clear();
    earnedSpin->setValue(0);
    totalSpin->setValue(100);
}

// ================================================================
// Function: saveGrades
// - Serializes all application data to a JSON file.
// ================================================================
void MainWindow::saveGrades() {
    // Open file dialog for destination path
    QString path = QFileDialog::getSaveFileName(this, "Save Grades", "", "JSON Files (*.json)");
    if (path.isEmpty()) return;

    // Map structs to JSON structure
    QJsonArray root;
    for (const auto& c : m_courses) {
        QJsonObject cObj;
        cObj["name"] = c.name;
        QJsonArray gArr;
        for (const auto& g : c.grades) {
            QJsonObject gObj;
            gObj["name"] = g.assignmentName;
            gObj["category"] = g.category;
            gObj["earned"] = g.pointsEarned;
            gObj["total"] = g.pointsTotal;
            gArr.append(gObj);
        }
        cObj["grades"] = gArr;
        root.append(cObj);
    }

    // Write data to file
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

// ================================================================
// Function: loadGrades
// - Loads application data from a JSON file.
// ================================================================
void MainWindow::loadGrades() {
    // Open file dialog for source path
    QString path = QFileDialog::getOpenFileName(this, "Load Grades", "", "JSON Files (*.json)");
    if (path.isEmpty()) return;

    // Read raw file content
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return;

    // Convert raw content to JSON
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return;

    // Clear current statee before loading
    m_courses.clear();
    courseCombo->clear();

    // Map JSON objects back to internal structs
    QJsonArray root = doc.array();
    for (int i = 0; i < root.size(); ++i) {
        QJsonObject cObj = root[i].toObject();
        Course c;
        c.name = cObj["name"].toString();
        QJsonArray gArr = cObj["grades"].toArray();
        for (int j = 0; j < gArr.size(); ++j) {
            QJsonObject gObj = gArr[j].toObject();
            Grade g;
            g.assignmentName = gObj["name"].toString();
            g.category = gObj["category"].toString();
            g.pointsEarned = gObj["earned"].toInt();
            g.pointsTotal = gObj["total"].toInt();
            c.grades.append(g);
        }
        m_courses.append(c);
        courseCombo->addItem(c.name);
    }
    // Finalize UI refresh
    updateStats();
    if (!m_courses.isEmpty()) courseCombo->setCurrentIndex(0);
}

// ================================================================
// Function: about
// - Displays application metadata to the user.
// ================================================================
void MainWindow::about() {
    // Show static information dialog
    QMessageBox::about(this, "About Gradebook", "Student Gradebook Application, programmed by Saim Ahmed");
}
