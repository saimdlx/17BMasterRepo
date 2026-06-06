// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW7B - Student Gradebook Header File
// ================================================================
// Program Description:
// Header file for the Gradebook MainWindow.
// - Defines Grade and Course data structures.
// - Declares the MainWindow class and its UI/logic members.
// ================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QProgressBar>
#include <QAction>

// ================================================================
// Struct: Grade
// - Represents a single assignment entry.
// - Stores name, category, and score details.
// ================================================================
struct Grade {
    QString assignmentName;
    QString category;
    int pointsEarned;
    int pointsTotal;

    // Calculates percentage for the individual grade
    // based on points total, can change if specific scale needed.
    double percentage() const {
        return pointsTotal > 0 ? (double)pointsEarned / pointsTotal * 100.0 : 0.0;
    }

    // Determines letter grade based on percentage
    QString letterGrade() const {
        double p = percentage();
        if (p >= 90) return "A";
        if (p >= 80) return "B";
        if (p >= 70) return "C";
        if (p >= 60) return "D";
        return "F";
    }
};

// ================================================================
// Struct: Course
// - Represents a course containing multiple grades.
// - Provides statistical calculation for the course average.
// ================================================================
struct Course {
    QString name;
    QList<Grade> grades;

    // Calculates weighted average of all grades in the course
    // based on points total, can change if specific scale needed.
    double average() const {
        int earned = 0;
        int total = 0;
        for (const auto& g : grades) {
            earned += g.pointsEarned;
            total += g.pointsTotal;
        }
        return total > 0 ? (double)earned / total * 100.0 : 0.0;
    }
};

// ================================================================
// Class: MainWindow
// - Orchestrates the User Interface and Application Logic.
// - Handles course/grade management and data persistence.
// ================================================================
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void addCourse();
    void removeCourse();
    void onCourseSelected(int index);
    void addGrade();
    void deleteSelectedGrade();
    void saveGrades();
    void loadGrades();
    void about();

private:
    // UI Initialization
    void setupUI();
    void setupActions();
    void setupMenus();
    void setupToolbar();

    // State Awareness Functions
    void updateStats();
    void updateTable();
    void clearGradeInputs();

    // For Data Persistence
    QList<Course> m_courses;
    
    // UI Components
    QComboBox *courseCombo;
    QLabel *overallGpaLabel;
    QLineEdit *assignEdit;
    QSpinBox *earnedSpin;
    QSpinBox *totalSpin;
    QComboBox *categoryCombo;
    QTableWidget *gradeTable;
    QProgressBar *courseAvgProgress;
    
    // Menu/Toolbar Actions
    QAction *saveAction;
    QAction *loadAction;
    QAction *exitAction;
    QAction *addCourseAction;
    QAction *removeCourseAction;
    QAction *addGradeAction;
    QAction *aboutAction;
};

#endif // MAINWINDOW_H
