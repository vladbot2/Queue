#include <iostream>
#include <string>

using namespace std;

class PrintJob {
public:
    string user;
    int priority;

    PrintJob(string user, int priority) {
        this->user = user;
        this->priority = priority;
    }

    bool operator<(const PrintJob& other) const {
        return priority < other.priority;
    }
};

class PrintQueue {
private:
    PrintJob* printQueue[100];
    int size;

public:
    PrintQueue() : size(0) {}

    void addJob(string user, int priority) {
        PrintJob* job = new PrintJob(user, priority);
        int i = size - 1;
        while (i >= 0 && *printQueue[i] < *job) {
            printQueue[i + 1] = printQueue[i];
            i--;
        }
        printQueue[i + 1] = job;
        size++;
    }

    void processJob() {
        if (size > 0) {
            PrintJob* job = printQueue[0];
            cout << "Printing job for user: " << job->user << " with priority: " << job->priority << endl;
            delete job;
            for (int i = 1; i < size; i++) {
                printQueue[i - 1] = printQueue[i];
            }
            size--;
        }
        else {
            cout << "No jobs in the queue." << endl;
        }
    }

    void showStats() {
        cout << "Printing statistics:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "User: " << printQueue[i]->user << " | Priority: " << printQueue[i]->priority << endl;
        }
    }
};

int main() {
    PrintQueue printer;

    printer.addJob("Vlad", 4);
    printer.addJob("Maks", 3);
    printer.addJob("pop", 5);

    printer.processJob();
    printer.processJob();
    printer.processJob();

    printer.showStats();
}
