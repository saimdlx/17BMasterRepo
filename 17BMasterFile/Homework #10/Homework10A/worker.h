// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10A - Thread-Safe Counter Application
// ================================================================
// Program Description:
// Worker Header File
// - Defines the Worker class for background thread execution.
// - Uses moveToThread pattern to keep UI responsive.
// ================================================================
#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <atomic>

// ================================================================
// Class: Worker
// - Performs Part D increment logic in a separate thread.
// ================================================================
class Worker : public QObject {
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

public slots:
    // ================================================================
    // Slots for Background Tasks:
    // - process(): Loop for 400k increments with signal reporting.
    // ================================================================
    void process();

signals:
    // ================================================================
    // Signals for UI Feedback:
    // - progressChanged(int, int): Sends % and raw count to UI.
    // - finished(): Signals task completion.
    // ================================================================
    void progressChanged(int value, int count);
    void finished();

private:
    std::atomic<int> counter;
};

#endif // WORKER_H
