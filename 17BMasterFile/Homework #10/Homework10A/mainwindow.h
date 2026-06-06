// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10A - Thread-Safe Counter Application
// ================================================================
// Program Description:
// MainWindow Header File
// - Defines the user interface for the program.
// - Declares members for thread safety tests.
// - Manages the Worker/QThread lifecycle for progress reporting.
// ================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QTextEdit>
#include <QThread>
#include <QLabel>
#include <mutex>
#include <atomic>
#include "worker.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // ================================================================
    // Slots for UI Interactions and Threading:
    // - startExperiments(): Triggers Parts A, B, C and starts Worker.
    // - updateProgress(int, int): Updates bar and label from Worker.
    // - workerFinished(): Re-enables UI when thread completes.
    // ================================================================
    void startExperiments();
    void updateProgress(int value, int count);
    void workerFinished();

private:
    // ================================================================
    // UI Components and State:
    // - progressBar: Visual representation of Part D progress.
    // - progressLabel: Text representation of increment count.
    // - startButton: Trigger for all parts.
    // - resultOutput: Console log output for test results.
    // ================================================================
    QProgressBar *progressBar;
    QLabel *progressLabel;
    QPushButton *startButton;
    QTextEdit *resultOutput;
    
    // ================================================================
    // Threading and Logic Members:
    // - workerThread: QThread handle for background execution.
    // - worker: Object performing the increments for Part D.
    // - globalCounter: Unprotected int for Race Condition (Part A).
    // - safeCounter: Mutex-protected int for Part B.
    // - counterMutex: Synchronizer for Part B access.
    // - atomicCounter: Lock-free atomic for Part C.
    // ================================================================
    QThread *workerThread;
    Worker *worker;

    static const int ITERATIONS = 100000;
    static const int NUM_THREADS = 4;
    static const int EXPECTED_VALUE = ITERATIONS * NUM_THREADS;

    int globalCounter;
    int safeCounter;
    std::mutex counterMutex;
    std::atomic<int> atomicCounter;

    // Logic implementation methods
    void runPartA();
    void runPartB();
    void runPartC();

    void increment();
    void incrementSafe();
    void incrementAtomic();
};

#endif // MAINWINDOW_H
