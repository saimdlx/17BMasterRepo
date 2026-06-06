// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10B - Producer-Consumer Task Processor
// ================================================================
// Program Description:
// Worker Header File
// - Defines the consumer logic for task processing.
// - Operates in a separate thread to poll the thread-safe queue.
// ================================================================
#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>
#include "threadsafequeue.h"

// ================================================================
// Class: Worker
// - Represents a consumer that processes tasks from the shared queue.
// ================================================================
class Worker : public QObject {
    Q_OBJECT

public:
    explicit Worker(int id, ThreadSafeQueue<QString>& queue, QObject *parent = nullptr);

public slots:
    // ================================================================
    // Slot: process
    // - Continuous loop that pops tasks from the queue and processes them.
    // ================================================================
    void process();

signals:
    // ================================================================
    // Signals:
    // - taskStarted(QString): Emitted when a task begins processing.
    // - taskCompleted(QString, int): Emitted when a task is finished.
    // - finished(): Emitted when the worker stops (queue shutdown).
    // ================================================================
    void taskStarted(QString taskName);
    void taskCompleted(QString taskName, int workerId);
    void finished();

private:
    int id_;
    ThreadSafeQueue<QString>& queue_;
};

#endif // WORKER_H
