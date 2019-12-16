// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#ifndef _patientqueue_h
#define _patientqueue_h

#include <iostream>
#include <string>
#include "patient.h"
using namespace std;

class PatientQueue {
public:
    PatientQueue(bool isMinHeap = true);
    ~PatientQueue();
    void changePriority(string value, int newPriority);
    void clear();
    void debug();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const PatientQueue& queue);

private:
    // TODO: add specified member variables and any needed helper functions

    int _size;
    int _capacity;
    bool _isMinHeap;
    Patient *MyPatients;
    int findPatient(string value);
    void nameSwap(string& v1, string& v2);
    void prioritySwap(int& p1, int& p2);
    void bubbleUp(int Index);
    void bubbleDown(int Index);
    bool isSmaller(Patient* patCmp, int i, int j);
};

#endif
