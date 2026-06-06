// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10B - Producer-Consumer Task Processor
// ================================================================
// Program Description:
// Worker Implementation File
// - Handles task retrieval and simulated processing time.
// ================================================================
#include "worker.h"
#include <QThread>
#include <QRandomGenerator>

// ================================================================
// Constructor: Worker
// - Initializes worker ID and references the shared task queue.
// ================================================================
Worker::Worker(int id, ThreadSafeQueue<QString>& queue, QObject *parent)
    : QObject(parent), id_(id), queue_(queue) {}

// ================================================================
// Function: process
// - Polling loop that waits for tasks and simulates work.
// - Reports progress via signals to the main window.
// ================================================================
void Worker::process() {
    QString task;
    while (queue_.pop(task)) {
        emit taskStarted(task);
        
        // Simulate processing time (500ms - 1500ms)
        int delay = QRandomGenerator::global()->bounded(500, 1501);
        QThread::msleep(delay);
        
        emit taskCompleted(task, id_);
    }
    emit finished();
}
