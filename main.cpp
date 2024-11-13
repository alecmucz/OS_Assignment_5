#include <iostream>
#include <iomanip>
#define N 5
using namespace std;

struct Process {
    int burst;
    int priority; //never need for assignment
};

int* turnAroundTime(Process processes[], int size, const string& algorithm){
    int* arr{new int[size]};

    if (algorithm == "FCFS") {
        arr[0] = processes[0].burst;
        for (int i{1}; i < size; i++) {
            arr[i] = arr[i-1] + processes[i].burst; //cumulative burst time
            //arr[i] = processes[i].burst;
        }

    } else if (algorithm == "SJF"){
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        for(int i{0}; i < size; i++){
            minHeap.emplace(processes[i].burst, i);
        }

        int cumulativeTime = 0;
        while (!minHeap.empty()) {
            auto [burstTime, index] = minHeap.top();
            minHeap.pop();

            cumulativeTime += burstTime;
            arr[index] = cumulativeTime;
        }
    }
    return arr;
}

int* waitingTime(Process processes[], int size, const string& algorithm){
    int* arr{new int[size]};

    if (algorithm == "FCFS") {
        arr[0] = 0;
        for (int i{1}; i < size; i++){
            arr[i] = arr[i-1] + processes[i-1].burst;
        }

    } else if (algorithm == "SJF"){
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        for(int i{0}; i < size; i++){
            minHeap.emplace(processes[i].burst, i);
        }
        int time{0};
        while (!minHeap.empty()){
            auto[burstTime, index] = minHeap.top();
            minHeap.pop();

            arr[index] = time;
            time += burstTime;
        }
    }
    return arr;
}


int main() {
    Process processes[N] = {{2,2}, {1,1}, {8,4}, {4,2}, {5,3}};
    

    cout << "----------------- FCFS -----------------" << endl;
    cout << "Process Id  |  Wait Time   |  Turnaround" << endl;

    string algorithm = "FCFS";
    int* time{waitingTime(processes, N, algorithm)};
    int* time2{turnAroundTime(processes, N, algorithm)};
    float maxWait{0};
    float maxTurn{0};
    for(int i{0}; i < N; i++){
        maxWait += (float) time[i];
        maxTurn += (float) time2[i];
        cout << "     0" << i+1 << "     |      "  << setw(2) << setfill('0') << time[i] << "      |     " << setw(2) << setfill('0')<<  time2[i] << endl;
    }
    cout << "Average Waiting Time : " << maxWait/N << endl;
    cout << "Average Turnaround Time : " << maxTurn/N << endl;
    cout << endl;

    cout << "------------------ SJF -----------------" << endl;
    cout << "Process Id  |  Wait Time   |  Turnaround" << endl;

    string algorithm2 = "SJF";
    int* time3{waitingTime(processes, N, algorithm2)};
    int* time4{turnAroundTime(processes, N, algorithm2)};
    float maxWait1{0};
    float maxTurn1{0};
    for(int i{0}; i < N; i++){
        maxWait1 += (float) time3[i];
        maxTurn1 += (float) time4[i];
        cout << "     0" << i+1 << "     |      "  << setw(2) << setfill('0') << time3[i] << "      |     " << setw(2) << setfill('0')<<  time4[i] << endl;
    }
    cout << "Average Waiting Time : " << maxWait1/N << endl;
    cout << "Average Turnaround Time : " << maxTurn1/N << endl;

    delete[] time;
    delete[] time2;
    delete[] time3;
    delete[] time4;

    return 0;
}
