#include <iostream>
using namespace std;

const int MAX = 100;
int waiting[MAX];       // queue of patient IDs
int frontIdx = 0;       // index of the first patient
int rear = 0;           // index where the next patient will be stored
int itemCount = 0;      // how many patients are waiting
int nextId = 1;         // auto-generated ID, starts from 1

// give the next ID to a patient and add them to the queue
void RegisterPatient() {
    if (itemCount == MAX) {
        cout << "Waiting room is full" << endl;
    }
    else {
        waiting[rear] = nextId;
        rear = (rear + 1) % MAX;
        itemCount++;
        cout << "Patient registered with ID " << nextId << endl;
        nextId++;
    }
}

// call the patient at the front of the queue
void ServePatient() {
    if (itemCount == 0) {
        cout << "No patients are waiting" << endl;
    }
    else {
        cout << "Now serving patient " << waiting[frontIdx] << endl;
        frontIdx = (frontIdx + 1) % MAX;
        itemCount--;
    }
}

// remove everyone from the queue
void CancelAll() {
    frontIdx = 0;
    rear = 0;
    itemCount = 0;
    cout << "All appointments cancelled" << endl;
}

// true if nobody is waiting
bool CanDoctorGoHome() {
    return itemCount == 0;
}

// print the waiting IDs (front to rear is already in sorted order)
void ShowAllPatient() {
    if (itemCount == 0) {
        cout << "No patients are waiting" << endl;
    }
    else {
        cout << "Waiting patients: ";
        for (int i = 0; i < itemCount; i++) {
            cout << waiting[(frontIdx + i) % MAX] << " ";
        }
        cout << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "\n1. Register Patient\n2. Serve Patient\n3. Cancel All\n";
        cout << "4. Can Doctor Go Home?\n5. Show All Patients\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
            RegisterPatient();
        else if (choice == 2)
            ServePatient();
        else if (choice == 3)
            CancelAll();
        else if (choice == 4) {
            if (CanDoctorGoHome())
                cout << "Yes, no one is waiting" << endl;
            else
                cout << "No, patients are still waiting" << endl;
        }
        else if (choice == 5)
            ShowAllPatient();
    } while (choice != 0);

    return 0;
}