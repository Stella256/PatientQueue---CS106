// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "patientqueue.h"
using namespace std;
static const int DEFAULT_CAPACITY = 10;
static const int HEAD=1;

PatientQueue::PatientQueue(bool isMinHeap) {
    // TODO: write this constructor
    MyPatients = new Patient[DEFAULT_CAPACITY];
    _size = 0;
    _capacity = DEFAULT_CAPACITY;
    _isMinHeap = isMinHeap;
    for (int i =0;i<_capacity;i++) {
        MyPatients[i].name = "";
        MyPatients[i].priority = 0;
    }
}

PatientQueue::~PatientQueue() {
    // TODO: write this destructor
    delete [] MyPatients;
}

// Find the particular patient to change the priority
int PatientQueue::findPatient(string value){
    int Index=0;
    for (int i=0; i<=_size; i++) {
        if(MyPatients[i].name == value){
           Index = i;
    }
  }
 return Index;
}

// Swap the name of two patients
void PatientQueue::nameSwap(string& v1, string& v2){
    string tName;
    tName = v1;
    v1 = v2;
    v2 = tName;
}
//Swap the priority of two patients
void PatientQueue::prioritySwap(int& p1, int& p2){
    int tmp;
    tmp = p1;
    p1 = p2;
    p2 = tmp;
}

//Compare the priority of two patients
bool PatientQueue::isSmaller(Patient* patCmp, int i, int j){
    int p1 = patCmp[i].priority;
    int p2 = patCmp[j].priority;
    string v1 = patCmp[i].name;
    string v2 = patCmp[j].name;
    if(p1 > p2){
        return true;
    }
    else if (p1 < p2) {
        return false;
    }
 // if the priority is the same, break the tie
    else {
        if(v1 > v2){
            return true;
        }
        else if (v1 < v2) {
            return false;
        }
        else {
            return false;
        }
   }

}

//Compare the priority of two patients(from the left queue to the right) and swap them if necessary
void PatientQueue::bubbleUp(int Index){
// MinHeap
    if(_isMinHeap){
        while(2*Index <= _size){
        if(2*Index == _size && isSmaller(MyPatients, Index, 2*Index)){
            prioritySwap(MyPatients[Index].priority, MyPatients[2*Index].priority);
            nameSwap(MyPatients[Index].name, MyPatients[2*Index].name);
            Index = 2*Index;
        }
        else if (isSmaller(MyPatients, 2*Index+1, 2*Index) && isSmaller(MyPatients, Index, 2*Index)) {
                prioritySwap(MyPatients[Index].priority, MyPatients[2*Index].priority);
                nameSwap(MyPatients[Index].name, MyPatients[2*Index].name);
                Index = 2*Index;
        }
        else if (isSmaller(MyPatients, 2*Index, 2*Index+1) && isSmaller(MyPatients, Index, 2*Index+1)) {
                prioritySwap(MyPatients[Index].priority, MyPatients[2*Index+1].priority);
                nameSwap(MyPatients[Index].name, MyPatients[2*Index+1].name);
                Index = 2*Index+1;
        }
        else {
            Index = 2*Index;
        }
    }
  }
 //Max Heap
    else {
            while(2*Index <= _size){
            if(2*Index == _size && !isSmaller(MyPatients, Index, 2*Index)){
                prioritySwap(MyPatients[Index].priority, MyPatients[2*Index].priority);
                nameSwap(MyPatients[Index].name, MyPatients[2*Index].name);
                Index = 2*Index;
            }
            else if (!isSmaller(MyPatients, 2*Index+1, 2*Index) && !isSmaller(MyPatients, Index, 2*Index)) {
                    prioritySwap(MyPatients[Index].priority, MyPatients[2*Index].priority);
                    nameSwap(MyPatients[Index].name, MyPatients[2*Index].name);
                    Index = 2*Index;
            }
            else if (!isSmaller(MyPatients, 2*Index, 2*Index+1) && !isSmaller(MyPatients, Index, 2*Index+1)) {
                    prioritySwap(MyPatients[Index].priority, MyPatients[2*Index+1].priority);
                    nameSwap(MyPatients[Index].name, MyPatients[2*Index+1].name);
                    Index = 2*Index+1;
            }
            else {
                Index = 2*Index;
            }
        }
    }
}
//Compare the priority of two patients(from the right queue to the left) and swap them if necessary
void PatientQueue::bubbleDown(int Index){
    if(_isMinHeap){
        while((Index/2)!=0){
            if(!isSmaller(MyPatients, Index, Index/2)){
                prioritySwap(MyPatients[Index].priority, MyPatients[Index/2].priority);
                nameSwap(MyPatients[Index].name, MyPatients[Index/2].name);
        }
        Index = Index/2;
      }
    }
    else {
        while((Index/2)!=0){
            if(isSmaller(MyPatients, Index, Index/2)){
                prioritySwap(MyPatients[Index].priority, MyPatients[Index/2].priority);
                nameSwap(MyPatients[Index].name, MyPatients[Index/2].name);
        }
        Index = Index/2;
      }
    }
}

//Change the priority of the given patient
void PatientQueue::changePriority(string value, int newPriority) {
    int Index = findPatient(value);
    MyPatients[Index].name = value;
    MyPatients[Index].priority = newPriority;
    bubbleUp(Index);
    bubbleDown(Index);
}

void PatientQueue::clear() {
    // TODO: write this function
    for (int i=1; i<_size; i++){
        MyPatients[i].name = "";
        MyPatients[i].priority = 0;
    }
    _size = 0;
}

void PatientQueue::debug() {
    // empty
}

string PatientQueue::dequeue() {
    // TODO: write this function
    string pName, tName;
    int tail, i=1;
    if(isEmpty()){
        throw "Queue is empty, no patient to be dequeued";
    }
    else if(_size == 1 ){
        pName = MyPatients[HEAD].name;
        MyPatients[HEAD].name = "";
        MyPatients[HEAD].priority = 0;
        _size--;
        return pName;
    }
    else {
        pName = MyPatients[HEAD].name;
        tail = _size % _capacity;
        MyPatients[HEAD].name = MyPatients[tail].name;
        MyPatients[HEAD].priority = MyPatients[tail].priority;
        MyPatients[tail].name = "";
        MyPatients[tail].priority = 0;
        _size--;
        bubbleUp(i);
   }
   return pName;
}

void PatientQueue::enqueue(string value, int priority) {
    // TODO: write this function
    int tailNext;
    string tName;
    if((_size+1) == _capacity){
        //resize to an array twice as large
        Patient* NewMyPatients = new Patient [2*_capacity];
        for (int i=1;i<=_size; i++) {
            NewMyPatients[i].name = MyPatients[i].name;
            NewMyPatients[i].priority = MyPatients[i].priority;
        }
        MyPatients = NewMyPatients;
        _capacity = 2*_capacity;
        tailNext = (_size+1)%_capacity;
        MyPatients[tailNext].name = value;
        MyPatients[tailNext].priority = priority;
        _size++;
        bubbleDown(tailNext);
    }
    else if (isEmpty()) {
        tailNext = HEAD;
        MyPatients[tailNext].name = value;
        MyPatients[tailNext].priority = priority;
        _size++;
    }
    else {
        tailNext = (_size+1)%_capacity;
        MyPatients[tailNext].name = value;
        MyPatients[tailNext].priority = priority;
        _size++;
        bubbleDown(tailNext);
    }
 }

bool PatientQueue::isEmpty() const {
    // TODO: write this function
    return _size == 0;
}

string PatientQueue::peek() const {
    // TODO: write this function
    if(isEmpty()){
        throw "Queue is Empty, just like my head in midterm";
    }
    else
        return MyPatients[HEAD].name;
}

int PatientQueue::peekPriority() const {
    // TODO: write this function
    if(isEmpty()){
        throw "Queue is Empty";
}
    else {
        return MyPatients[HEAD].priority;
    }
}

int PatientQueue::size() const {
    // TODO: write this function
    return _size;
}

ostream& operator <<(ostream& out, const PatientQueue& queue) {
    // TODO: write this functionss
    out << "{";
    for (int i = 1; i < queue._size; i++){
        out << queue.MyPatients[i].name << " (" << queue.MyPatients[i].priority << ")"<< ", ";
    }
    out << queue.MyPatients[queue._size].name << " (" << queue.MyPatients[queue._size].priority << ")}";
    return out;
}
