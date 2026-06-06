// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10A - Thread-Safe Counter Application
// ================================================================
// Program Description:
// MainWindow Class Implementation Filee
// - Sets up the UI layout with results log, progress bar, and label.
// - Implements logic for Parts A (Race), B (Mutex), and C (Atomic).
// - Manages background thread via Worker/QThread pattern.
// ================================================================
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>

MainWindow::MainWindow(QWidget *parent)  : QMainWindow(parent), workerThread(nullptr), worker(nullptr), globalCounter(0), safeCounter(0), atomicCounter(0) {
    setWindowTitle("HW10A - Thread-Safe Counter Application");
    resize(450, 500);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    resultOutput = new QTextEdit(this);
    resultOutput->setReadOnly(true);
    resultOutput->setPlaceholderText("Console Log Output Here");

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    progressLabel = new QLabel("0 / 400000 increments", this);
    progressLabel->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton("Start Steps (A-D)", this);

    layout->addWidget(resultOutput);
    layout->addWidget(progressBar);
    layout->addWidget(progressLabel);
    layout->addWidget(startButton);

    setCentralWidget(centralWidget);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startExperiments);
}

// ================================================================
// Destructor: MainWindow
// - Ensures thread cleanup on application exit.
// ================================================================
MainWindow::~MainWindow() {
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
    }
}
// ================================================================
// Function: increment
// - Increments globalCounter without protection to show race.
// ================================================================
void MainWindow::increment() {
    for (int i = 0; i < ITERATIONS; ++i) {
        globalCounter++;
    }
}

// ================================================================
// Function: incrementSafe
// - Increments safeCounter using std::lock_guard and mutex.
// ================================================================
void MainWindow::incrementSafe() {
    for (int i = 0; i < ITERATIONS; ++i) {
        std::lock_guard<std::mutex> lock(counterMutex);
        safeCounter++;
    }
}

// ================================================================
// Function: incrementAtomic
// - Increments atomicCounter using std::atomic operator++.
// ================================================================
void MainWindow::incrementAtomic() {
    for (int i = 0; i < ITERATIONS; ++i) {
        atomicCounter++;
    }
}

// ================================================================
// Function: runPartA
// - Launches 4 threads running increment() to demonstrate race.
// ================================================================
void MainWindow::runPartA() {
    globalCounter = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(&MainWindow::increment, this);
    }
    for (auto& t : threads) t.join();
}

// ================================================================
// Function: runPartB
// - Launches 4 threads running incrementSafe() using Mutex.
// ================================================================
void MainWindow::runPartB() {
    safeCounter = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(&MainWindow::incrementSafe, this);
    }
    for (auto& t : threads) t.join();
}

// ================================================================
// Function: runPartC
// - Launches 4 threads running incrementAtomic() using Atomics.
// ================================================================
void MainWindow::runPartC() {
    atomicCounter = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(&MainWindow::incrementAtomic, this);
    }
    for (auto& t : threads) t.join();
}

// ================================================================
// Function: startExperiments
// - Orchestrates all 4 parts of the HW assignment.
// - Logs A, B, C results to the UI text edit.
// - Starts the Part D Worker thread.
// ================================================================
void MainWindow::startExperiments() {
    startButton->setEnabled(false);
    resultOutput->clear();
    progressBar->setValue(0);
    progressLabel->setText("0 / 400000 increments");

    std::stringstream ss;
    
    // Part A: Race Condition
    ss << "=== Part A: Race Condition ===\n";
    runPartA();
    ss << "Expected: " << EXPECTED_VALUE << "\n";
    ss << "Actual:   " << globalCounter << "\n";
    ss << "Race condition OBSERVED (data lost)\n";

    // Part B: Mutex
    auto startB = std::chrono::high_resolution_clock::now();
    runPartB(); 
    auto endB = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedB = endB - startB;
    ss << "\n=== Part B: Mutex Fix ===\n";
    ss << "Result:    " << safeCounter << "\n";
    ss << "Time:     " << elapsedB.count() << " ms\n";

    // Part C: Atomic
    auto startC = std::chrono::high_resolution_clock::now();
    runPartC();
    auto endC = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedC = endC - startC;
    ss << "\n=== Part C: Atomic Fix ===\n";
    ss << "Result:    " << atomicCounter.load() << "\n";
    ss << "Time:     " << elapsedC.count() << " ms\n";

    // Outputs StringStream outputs to resultOutput box.
    resultOutput->setPlainText(QString::fromStdString(ss.str()));

    // Part D: Asynchronous Worker (Progress Tracking)
    workerThread = new QThread;
    worker = new Worker;
    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::started, worker, &Worker::process);
    connect(worker, &Worker::progressChanged, this, &MainWindow::updateProgress);
    connect(worker, &Worker::finished, this, &MainWindow::workerFinished);
    connect(worker, &Worker::finished, workerThread, &QThread::quit);
    connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);

    workerThread->start();
}

// ================================================================
// Function: updateProgress
// - Updates the progress bar percentage and the text label.
// ================================================================
void MainWindow::updateProgress(int value, int count) {
    progressBar->setValue(value);
    progressLabel->setText(QString("%1 / 400000 increments").arg(QString::number(count)));
}

// ================================================================
// Function: workerFinished
// - Cleans up UI state after the background thread finishes.
// ================================================================
void MainWindow::workerFinished() {
    startButton->setEnabled(true);
}
