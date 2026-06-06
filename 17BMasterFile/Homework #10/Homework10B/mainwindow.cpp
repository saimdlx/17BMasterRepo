// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10B - Producer-Consumer Task Processor
// ================================================================
// Program Description:
// MainWindow Class IMplementation File
// - Sets up the UI layout with inputs, lists, and log areas.
// - Implements logic for manual task entry and automated production (part b).
// - Manages worker statistics and generates Part B summary reports.
// ================================================================
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

// ================================================================
// Constructor: MainWindow
// - Sets window properties and initializes UI components.
// - Establishes signal-slot connections for interactive elements.
// - Launches initial worker threads.
// ================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("HW10B - Producer-Consumer Task Processor");
    resize(800, 600);

    // UI Setup
    taskInput = new QLineEdit;
    taskInput->setPlaceholderText("Enter manual task name...");
    addTaskButton = new QPushButton("Add Task");
    startPartBButton = new QPushButton("Run Part B (Auto-Producer)");

    queueList = new QListWidget;
    completedList = new QListWidget;
    workerStatusLabel = new QLabel("Active Workers: 0");
    
    outputLog = new QTextEdit;
    outputLog->setReadOnly(true);
    outputLog->setFontPointSize(10);

    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(startPartBButton, &QPushButton::clicked, this, &MainWindow::startPartB);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    
    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(taskInput);
    controlLayout->addWidget(addTaskButton);
    controlLayout->addWidget(startPartBButton);
    mainLayout->addLayout(controlLayout);

    QHBoxLayout *listsLayout = new QHBoxLayout;
    QVBoxLayout *queueLayout = new QVBoxLayout;
    queueLayout->addWidget(new QLabel("Task Queue:"));
    queueLayout->addWidget(queueList);
    
    QVBoxLayout *completedLayout = new QVBoxLayout;
    completedLayout->addWidget(new QLabel("Completed Tasks:"));
    completedLayout->addWidget(completedList);

    listsLayout->addLayout(queueLayout);
    listsLayout->addLayout(completedLayout);
    mainLayout->addLayout(listsLayout);
    
    mainLayout->addWidget(new QLabel("Application Log:"));
    mainLayout->addWidget(outputLog);
    mainLayout->addWidget(workerStatusLabel);

    QWidget *central = new QWidget;
    central->setLayout(mainLayout);
    setCentralWidget(central);

    setupWorkers();
    appendLog("--- Part B Beep Boop ---");
}

// ================================================================
// Destructor: ~MainWindow
// - Shuts down the task queue and terminates worker threads.
// ================================================================
MainWindow::~MainWindow() {
    taskQueue.shutdown();
    for (QThread *thread : workerThreads) {
        thread->quit();
        thread->wait();
    }
}

// ================================================================
// Function: addTask
// - Adds a user-defined task to the queue and updates the UI.
// ================================================================
void MainWindow::addTask() {
    QString taskName = taskInput->text().trimmed();
    if (taskName.isEmpty()) {
        return;
    }

    taskQueue.push(taskName);
    queueList->addItem(taskName);
    taskInput->clear();
    appendLog("User added manual task: " + taskName);
}

// ================================================================
// Function: startPartB
// - Starts the automated 20-task production simulation.
// - Outputs program requirements and suppresses UI list updates for ease of viewing.
// ================================================================
void MainWindow::startPartB() {
    startPartBButton->setEnabled(false);
    
    partBActive = true;
    partBCompletedCount = 0;
    partBWorkerStats.clear();
    
    appendLog("================================================================");
    appendLog("[Part B] Starting Auto-Producer...");
    
    partBTimer.start();
    
    // Run producer in a separate thread using QtConcurrent
    QtConcurrent::run([this]() {
        for (int i = 1; i <= 20; ++i) {
            QString task = QString("Task-%1").arg(i);
            taskQueue.push(task);
            
            // Invoke UI update safely
            QMetaObject::invokeMethod(this, [this, task]() {
                appendLog("[Producer] Pushed: " + task);
            });
            
            QThread::msleep(100);
        }

    });
}

// ================================================================
// Function: onTaskStarted
// - Logs the beginning of a task's processing.
// ================================================================
void MainWindow::onTaskStarted(QString taskName) {
    appendLog("[Worker] Processing: " + taskName);
}

// ================================================================
// Function: onTaskCompleted
// - Updates statistics for Part B and generates a final report.
// - Updates UI lists for manual (Part C) tasks.
// ================================================================
void MainWindow::onTaskCompleted(QString taskName, int workerId) {
    if (partBActive && taskName.startsWith("Task-")) {
        partBCompletedCount++;
        partBWorkerStats[workerId]++;
        
        appendLog(QString("[Worker %1] Completed: %2").arg(workerId).arg(taskName));
        
        if (partBCompletedCount == 20) {
            qint64 elapsed = partBTimer.elapsed();
            partBActive = false;
            
            appendLog("\n" + QString(64, '='));
            appendLog("PART B SUMMARY REPORT");
            appendLog(QString(64, '-'));
            appendLog(QString("Total Tasks Processed: %1").arg(partBCompletedCount));
            for (auto it = partBWorkerStats.begin(); it != partBWorkerStats.end(); ++it) {
                appendLog(QString("- Consumer %1: %2 tasks").arg(it.key()).arg(it.value()));
            }
            appendLog(QString("Total Time Elapsed: %1 ms").arg(elapsed));
            appendLog(QString(64, '=') + "\n");
            
            startPartBButton->setEnabled(true);
        }
    } else {
        // Part C / Manual Tasks: Update UI lists
        QList<QListWidgetItem*> items = queueList->findItems(taskName, Qt::MatchExactly);
        if (!items.isEmpty()) {
            delete queueList->takeItem(queueList->row(items.at(0)));
        }
        completedList->addItem(taskName);
        appendLog(QString("[Worker %1] Completed: %2").arg(workerId).arg(taskName));
    }
}

// ================================================================
// Function: appendLog
// - Thread-safe way to append information to the system log.
// ================================================================
void MainWindow::appendLog(const QString &message) {
    outputLog->append(message);
}

// ================================================================
// Function: setupWorkers
// - Initializes workers and starts their respective threads.
// ================================================================
void MainWindow::setupWorkers() {
    // Requirements specify at least 2 workers for Part C
    for (int i = 0; i < 2; ++i) {
        QThread *thread = new QThread(this);
        Worker *worker = new Worker(i + 1, taskQueue);
        
        worker->moveToThread(thread);

        connect(thread, &QThread::started, worker, &Worker::process);
        connect(worker, &Worker::taskStarted, this, &MainWindow::onTaskStarted);
        connect(worker, &Worker::taskCompleted, this, &MainWindow::onTaskCompleted);
        connect(worker, &Worker::finished, thread, &QThread::quit);
        connect(worker, &Worker::finished, worker, &Worker::deleteLater);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        workerThreads.push_back(thread);
        workers.push_back(worker);
        
        thread->start();
        activeWorkers++;
    }
    workerStatusLabel->setText(QString("Active Workers: %1").arg(activeWorkers));
}
