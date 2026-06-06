// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10B - Producer-Consumer Task Processor
// ================================================================
// Program Description:
// MainWindow Header File
// - Defines the user interface for the producer-consumer application.
// - Manages task submission, worker threads, and consolidated logging.
// - Tracks statistics for Part B and C processing.
// ================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QTextEdit>
#include <QThread>
#include <QVector>
#include <QMap>
#include <QElapsedTimer>
#include <atomic>
#include "threadsafequeue.h"
#include "worker.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    // ================================================================
    // Slot: appendLog
    // - Appends a message to the system log text edit.
    // ================================================================
    void appendLog(const QString &message);

private slots:
    // ================================================================
    // Slots for UI Interactions:
    // - addTask(): Adds a manual task entered by the user.
    // - onTaskStarted(QString): Handles the start of a task.
    // - onTaskCompleted(QString, int): Handles task completion and stats.
    // - startPartB(): Initiates the automated Part B simulation.
    // ================================================================
    void addTask();
    void onTaskStarted(QString taskName);
    void onTaskCompleted(QString taskName, int workerId);
    void startPartB();

private:
    // ================================================================
    // UI Components:
    // - taskInput: Input field for manual tasks.
    // - addTaskButton: Triggers manual task addition.
    // - startPartBButton: Starts the Part B auto-producer.
    // - queueList: UI representation of the pending tasks.
    // - completedList: UI representation of processed tasks.
    // - workerStatusLabel: Shows the number of active consumers.
    // - outputLog: Main output area for system activity and reports.
    // ================================================================
    QLineEdit *taskInput;
    QPushButton *addTaskButton;
    QPushButton *startPartBButton;
    QListWidget *queueList;
    QListWidget *completedList;
    QLabel *workerStatusLabel;
    QTextEdit *outputLog;

    // ================================================================
    // Application Logic and Threading:
    // - taskQueue: Thread-safe storage for pending tasks.
    // - workerThreads: Collection of QThread objects for consumers.
    // - workers: Collection of Worker objects running in threads.
    // - activeWorkers: Counter for initialized consumer threads.
    // ================================================================
    ThreadSafeQueue<QString> taskQueue;
    QVector<QThread*> workerThreads;
    QVector<Worker*> workers;
    int activeWorkers = 0;

    // ================================================================
    // Part B Statistics:
    // - partBActive: Flag to identify if Part B is running.
    // - partBCompletedCount: Counter for tasks finished in Part B.
    // - partBWorkerStats: Maps worker ID to their processed task count.
    // - partBTimer: Measures the duration of the Part B simulation.
    // ================================================================
    bool partBActive = false;
    int partBCompletedCount = 0;
    QMap<int, int> partBWorkerStats;
    QElapsedTimer partBTimer;

    // ================================================================
    // Function: setupWorkers
    // - Initializes and starts the consumer threads.
    // ================================================================
    void setupWorkers();
};

#endif // MAINWINDOW_H
