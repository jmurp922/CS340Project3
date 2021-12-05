#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

class Process {
    // A class is needed to store all the data read in from the file
    // All important data is kept inside this object
    private :
        string processName;
        int priority;
        int burstTime;
        int arrivalTime;
        int burstTimeLeft;
        int turnAroundTime;
        int timeWaited;
    
    public :
    Process(string processN, int prio, int burst, int arrival) {
        //Constructor for the Process class
        processName = processN;
        priority = prio;
        burstTime = burst;
        arrivalTime = arrival;
        burstTimeLeft = burst;
        turnAroundTime = 0;
        timeWaited = 0;
    }
    Process() {
        //Default constructor
        processName = "";
        priority = 0;
        burstTime = 0;
        arrivalTime = 0;
        burstTimeLeft = 0;
        turnAroundTime = 0;
        timeWaited = 0;
    }
    void decrementTime(){
        //After each loop in the forloop, decrement the time unit by 1
        burstTimeLeft--;
    }
    void incrementWait() {
        //Increment the time waited
        timeWaited++;
    }
    int getWait() {
        return timeWaited;
    }
    int timeLeft() {
        return burstTimeLeft;
    }
    int getTurnAroundTime(int i) {
        //Turn around time is the current time - the arrival time
        return turnAroundTime = i - arrivalTime;
    }
    void setProcessName(string process) {
        processName = process;
    }
    void setPriority(int p) {
        priority = p;
    }
    void setBurst(int b) {
        burstTime = b;
    }
    void setArrival(int a) {
        arrivalTime = a;
    }
    string getProcessName() {
        return processName;
    }
    int getPriority() {
        return priority;
    }
    int getBurst() {
        return burstTime;
    }
    int getArrival() {
        return arrivalTime;
     }
    void toString() {
        //Get the basic information from the process
        cout << processName << " " << priority << " " << burstTime << " " << arrivalTime << endl;
    }
    void completeString() {
        //Output the process wait time and turn around time
        cout << processName << " had a wait time of : " << getWait() << " and had a turnaround time of  : " << turnAroundTime << endl;
    }
};

class Node {
public:
    Node* next;
    Process data;
    Node(Process d) {
        //Constructor that initalizes the process into the data node
        data = d;
    }
    Node() {
        //Default Constructor
    }
    ~Node() {
        //Destructor
    }
};

class LinkedList {
public:
    int length;
    Node* head;

LinkedList(){
    this->length = 0;
    this->head = NULL;
}

~LinkedList(){
    //Destructor
}
    
void addEnd(Process data) {
    Node* node = new Node(data);
    node->next = NULL;
    if (this -> head == NULL) {
        //If there's no node as the head, set this node to be the head.
        head = node;
        length++;
    }
    else {
        //If the linked list has a head, traverse through the whole list until we find the end
        //The end is found when lastNode -> next is equal to null since nothings there
        Node* lastNode = head;
        while (lastNode -> next != NULL) {
            lastNode = lastNode -> next;
        }
        //Reached the end of the list since the list hit null. Insert the new node into the end of the list now.
        lastNode -> next = node;
        length++;
    }
}
void swapPointerProcc(Process data) {
    //
    Node* temp = this -> head -> next;
    delete this -> head;
    this -> head = temp;
    addFront(data);
}
void swapPointer(Node* a){
    //If we want to add something to the front of the list, create a pointer to the next node in the head. Delete the current head and then set the temp node to next so it is the head. Then, add the incoming node to the front of the list.
    Node *temp = this -> head -> next;
    delete this -> head;
    this -> head = temp;
    addFront(a -> data);
    }
    
    void addFront(Process data){
        //Take the incoming Process type, create a new node to hold it. Take the pointer from the head and assign it to the next of the newly created node and then set it as the head of the linked list.
        Node* newHead = new Node(data);
        newHead -> next = this -> head;
        this->head = newHead;
        this->length++;
    }
    void print(){
        //Iterate through the list by taking a temp node pointer and iterating through the linked list. Print the nodes data through our defined toString()function and then set the node equal to the next node of hte current node
        Node* head = this -> head;
        while(head){
            head->data.toString();
            head = head->next;
        }
    }
    void printComp(){
        //Same thing as print but calling a different string printing function for different data.
        Node* head = this -> head;
        while(head){
            head->data.completeString();
            head = head->next;
        }
    }
};


int main(int argc, const char * argv[]) {
    string line;
    string processName, priority, burst, arrival;
    string test = "";
    //Declare the singly linked list which will be the ready queue, and the completed queue which the nodes that finish executing will be moved into. There's 2 booleans declared, same priority and decremented. If a new process enters and it has the same priority as the current process in the run state then this boolean is set to true and the 10 second time quantum is activated. After each time you decrement, set the decremented boolean to true so that you don't over incremented through all the if else statements.
    LinkedList readyQueue, completedQueue;
    bool samePriority = false;
    int timeQuantum = 10;
    int totalTime;
      for (int i = 0; i < 96; i++) {
          totalTime = i;
          cout << "At time " << i << endl;
          readyQueue.print();
          ifstream readFile;
          bool decremented = false;
          if (i == 0) {
              //No work is being done at time 0
              decremented = true;
          }
           readFile.open("/Users/james/Desktop/processes.txt");
           if(!readFile) {
               //If file cant be opened print out an error statement and quit
               cout << "ERROR! Unable to open file. \n";
               exit(1);
           }
          // We need to increment the wait time of each process in the linked list. If it's not in the running state or the head, iterate through the whole linked list and call the incrementWait function.
          if (readyQueue.head != NULL && readyQueue.head -> next != NULL) {
             Node* temp = readyQueue.head -> next;
             while(temp){
                 temp->data.incrementWait();
                 cout << "Incrementing the wait at time " << totalTime << " on process " << temp -> data.getProcessName() << "\n Total time the process has waited : " << temp -> data.getWait() << endl;
                 temp = temp->next;
             }
          }
           while(getline(readFile, line)) {
              stringstream stringStream(line);
            //I used the string stream class to manipulate the line string. The file was formatted to be tab delimitted, so we take in the string stream as the first parameter and then the variable we're going to assign the designated information tooThe information is tab delimitted so we use \t to have it parse the tab
              getline(stringStream, processName, '\t');
              getline(stringStream, priority, '\t');
              getline(stringStream, burst, '\t');
              getline(stringStream, arrival, '\t');
              //The string stream class saves the variable as a string, so it needs to be converted into an integer
              stringstream convertToInt(arrival);
              int numArrival = 0;
              convertToInt >> numArrival;
              if (numArrival == i)  {
                  if (readyQueue.head != NULL && !decremented) {
                      readyQueue.head -> data.decrementTime();
                      decremented = true;
                  }
                  //if the arrival time is = to the current time, create a new process object
                  //and put it into the ready queue (linked list)
                  stringstream strPriority(priority), strBurst(burst);
                  int numPriority, numBurst;
                  strPriority >> numPriority;
                  strBurst >> numBurst;
                  Process a(processName, numPriority, numBurst, numArrival);
                  // Need to check if head is null and priority to see if we need to preempt the process
                  if (readyQueue.head != NULL && readyQueue.head -> data.getPriority() < a.getPriority()) {
                      //If the new nodes priority is higher than the current node in the running state, preempt
                      cout << "Entered preempt statement at time " << totalTime << " process " << readyQueue.head -> data.getProcessName() << " has a priority of " << readyQueue.head -> data.getPriority() << " and is getting prempted by " << a.getProcessName() << " with a priority of " << a.getPriority() << endl;
                      readyQueue.addEnd(readyQueue.head -> data);
                      readyQueue.swapPointerProcc(a);
                  }
                  else if (readyQueue.head == NULL) {
                      //If there's no head, set this process to be the head of the linked list
                      cout << "Ready queue is null, adding process " << a.getProcessName() << " to the front of the queue at time " << totalTime << endl;
                      readyQueue.addFront(a);
                  }
                  else if (readyQueue.head != NULL && readyQueue.head -> data.getPriority() == a.getPriority()) {
                      //If the processes have the same priority we need to apply the round robin 10 second algorithm and subtract from the time quantum. Need to assign this process to the next pointer of the head, and the current heads next pointer to the new process with the same priority.
                      samePriority = true;
                      Node* temp = readyQueue.head -> next;
                      Node* nextProc = new Node(a);
                      nextProc -> next = temp;
                      readyQueue.head -> next = nextProc;
                      cout << "SAME PRIORITY FOUND!" <<endl;
                      
                  }
                  else {
                      //If it's not, just add it to the back of the queue.
                      cout << "Process " << a.getProcessName() << " entered at time " << totalTime << " and is being added to the back of the queue." << endl;
                      readyQueue.addEnd(a);
                  }
           }
              else if (samePriority && !decremented) {
                  //Enter this branch of code if 2 processes have the same priority and we haven't decremented yet.
                  if (timeQuantum != 0) {
                      //If the time quantum is not 0, decrement the time quantum set the boolean to true and then decrement the data in the node. This is how we keep track of the 10 seconds of the time quantum.
                      timeQuantum--;
                      decremented = true;
                      readyQueue.head -> data.decrementTime();
                      cout << "Process " << readyQueue.head -> data.getProcessName() << " decremented at time " << totalTime << " it currently has " << readyQueue.head -> data.timeLeft() << " seconds left in the same priority section where time quantum is not 0.\n";
                  }

                  else if (timeQuantum == 0 && !decremented) {
                      //If we reach the end of the time quantum and we haven't decremented, decrement the time quantum variable, set the bool to true set the quantum back to 10, move the current process to the end of the queue, set the next process with the same priority as the head.
                      cout << "Time quantum is 0 decrementing at time " << totalTime << " then moving to back of the queue." <<endl;
                      timeQuantum--;
                      decremented = true;
                      readyQueue.head -> data.decrementTime();
                      timeQuantum = 10;
                      Process a = readyQueue.head -> data;
                      readyQueue.addEnd(a);
                      readyQueue.head = readyQueue.head -> next;
                      samePriority = false;
                  }
              }
              else {
                  //if there isnt a new process being inserted into the queue
                  //we can make progress on the current running processs
                  if (!decremented && readyQueue.head != NULL && readyQueue.head -> next != NULL && readyQueue.head -> data.getPriority() < readyQueue.head -> next -> data.getPriority()) {
                      //if the priority of the next node is higher than the current node in the run state, swap them since this is a priority based algorithm.
                      cout << "Swapping process " << readyQueue.head -> data.getProcessName() << " with a priority of " << readyQueue.head->data.getPriority() << " with " << readyQueue.head -> next -> data.getProcessName() << " which has a priority of " << readyQueue.head -> next -> data.getPriority() << " and decrementing it and time " << totalTime <<endl;;
                      Process a = readyQueue.head -> data;
                      readyQueue.addEnd(a);
                      readyQueue.head = readyQueue.head -> next;
                      readyQueue.head -> data.decrementTime();
                      decremented = true;
                      
                  }
                  if (!decremented && readyQueue.head != NULL) {
                      //If there's no specific things that need to be checked for then the only thing that needs to be done is work decrement the head.
                      readyQueue.head -> data.decrementTime();
                      decremented = true;
                      cout << "Process " << readyQueue.head -> data.getProcessName() << " decremented at time " << totalTime << " it currently has " << readyQueue.head -> data.timeLeft() << " seconds left.\n";
                  }
              }

          }

          if (readyQueue.head != NULL && (readyQueue.head -> data.timeLeft() <= 0)) {
              // Process is completed, add the process to the end of the completed queue and swap processes. Set the time quantum back to 10 incase of a new priority conflict
              cout << "Turn around time is : " << readyQueue.head -> data.getTurnAroundTime(i)
                   << " at time " << i << " for process " << readyQueue.head -> data.getProcessName() << endl;
                  completedQueue.addEnd(readyQueue.head -> data);
                  readyQueue.head = readyQueue.head -> next;
              timeQuantum = 10;
          }
          //Close the ifle
          readFile.close();
      }
    //Print out the results
    readyQueue.print();
    completedQueue.printComp();
    return 0;
}
