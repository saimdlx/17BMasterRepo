// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW10A - Thread-Safe Counter Application
// ================================================================
// Program Description:
// Worker Class implementation file
// - Executes the counting loop and emits progress signals.
// - Ensures thread safety using std::atomic for its internal counter.
// ================================================================
#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent), counter(0) {}

// ================================================================
// Function: process
// - Runs the main increment loop for Part D.
// - Emits progress signals every 10k iterations.
// ================================================================
void Worker::process() {
    const int TOTAL = 400000;
    const int STEP = 10000;
    
    counter = 0;
    for (int i = 1; i <= TOTAL; ++i) {
        counter++;
        if (i % STEP == 0) {
            emit progressChanged(i / (TOTAL / 100), i);
        }
    }
    emit progressChanged(100, TOTAL); // Ensure final state is sent
    emit finished();
}
