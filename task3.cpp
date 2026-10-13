#include <iostream>
using namespace std;

struct Request {
    int id;
    int arrival;        // arrival time
    int processing;     // processing time
};

Request *q;             // the queue array (made with new so it can be resized)
int capacity;           // size of the array
int frontIdx = 0;       // index of the first request
int rear = 0;           // index where the next request will be stored
int itemCount = 0;      // how many requests are in the queue

bool isEmpty() {
    return itemCount == 0;
}

bool isFull() {
    return itemCount == capacity;
}

// make a new array, copy requests in order starting from the front
void resize(int new_capacity) {
    Request *newQ = new Request[new_capacity];

    for (int i = 0; i < itemCount; i++) {
        newQ[i] = q[(frontIdx + i) % capacity];
    }

    delete[] q;
    q = newQ;
    capacity = new_capacity;
    frontIdx = 0;
    rear = itemCount % capacity;

    cout << "Queue resized to capacity " << capacity << endl;
}

void enqueue(Request x) {
    if (isFull()) {
        resize(capacity * 2);                 // too full: double the size
    }
    q[rear] = x;
    rear = (rear + 1) % capacity;             // wrap around
    itemCount++;
}

Request front() {
    return q[frontIdx];
}

Request dequeue() {
    Request x = q[frontIdx];
    frontIdx = (frontIdx + 1) % capacity;     // wrap around
    itemCount--;

    if (capacity > 2 && itemCount <= capacity / 4) {
        resize(capacity / 2);                 // too empty: halve the size
    }
    return x;
}

int main() {
    capacity = 4;
    q = new Request[capacity];

    int choice;
    int currentTime = 0;       // time when the printer becomes free
    int totalWait = 0;
    int served = 0;

    do {
        cout << "\n1. Add print request (enqueue)\n2. Process next request (dequeue)\n";
        cout << "3. Show average waiting time\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            Request r;
            cout << "Enter request ID: ";
            cin >> r.id;
            cout << "Enter arrival time: ";
            cin >> r.arrival;
            cout << "Enter processing time: ";
            cin >> r.processing;
            enqueue(r);
        }
        else if (choice == 2) {
            if (isEmpty()) {
                cout << "No requests to process" << endl;
            }
            else {
                Request r = dequeue();

                int start = currentTime;           // printer starts when it is free...
                if (r.arrival > start) {
                    start = r.arrival;             // ...but not before the request arrives
                }
                int wait = start - r.arrival;
                currentTime = start + r.processing;

                totalWait = totalWait + wait;
                served++;
                cout << "Processed request " << r.id << ", waiting time = " << wait << endl;
            }
        }
        else if (choice == 3) {
            if (served == 0)
                cout << "No requests processed yet" << endl;
            else
                cout << "Average waiting time = " << totalWait * 1.0 / served << endl;
        }

        // show the queue state after every enqueue and dequeue
        if (choice == 1 || choice == 2) {
            cout << "Queue state (capacity " << capacity << ", front index " << frontIdx
                 << ", rear index " << rear << ", requests " << itemCount << "):" << endl;
            for (int i = 0; i < itemCount; i++) {
                Request r = q[(frontIdx + i) % capacity];
                cout << "  [ID " << r.id << ", arrival " << r.arrival
                     << ", processing " << r.processing << "]" << endl;
            }
            if (!isEmpty()) {
                cout << "Front request: ID " << front().id << endl;
            }
        }
    } while (choice != 0);

    delete[] q;
    return 0;
}