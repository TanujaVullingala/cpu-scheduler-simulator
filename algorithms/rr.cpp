#include <bits/stdc++.h>
#define sz(a) ((int)((a).size()))
#define char unsigned char
 
using namespace std; 
typedef long long ll;
typedef long double ld;

struct Process{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
};

bool cmp(const Process &A,const Process &B){
    if(A.at == B.at){
        return A.id < B.id;
    }
    else{
        return A.at < B.at;
    }
}


int n, q;

map<int, int> m; // maps id to completion time
map<int, int> m2; // maps id to Time at which it ran on CPU for first time

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    input >> n; // no of process
    vector<Process> arrProcess(n);
    for(int i = 0; i < n; i++){
        int id, at, bt;
        input >> id >> at >> bt;
        arrProcess[i].id = id;
        arrProcess[i].at = at;
        arrProcess[i].bt = bt;
    }
    input >> q; // time quantum
    sort(arrProcess.begin(), arrProcess.end(), cmp);
    queue<Process> readyQueue;
    Process runningQueue;
    
    int currTime = 0, i = 0;
    if(arrProcess[i].at > currTime){
            currTime = arrProcess[i].at;
    }
    
    while(i < n && arrProcess[i].at <= currTime){
            readyQueue.push(arrProcess[i]);
            i++;
    }
      
    while(i < n){
        runningQueue = readyQueue.front();
        if(m2.count(runningQueue.id) == 0){
            m2[runningQueue.id] = currTime;
        }  
        readyQueue.pop();
        bool flag = true;
        if(runningQueue.bt <= q){
            currTime += runningQueue.bt;
            flag = false;
            m[runningQueue.id] = currTime;   
        }
        else {
            currTime += q;
            runningQueue.bt -= q;
        }
        while(i < n && arrProcess[i].at <= currTime){
            readyQueue.push(arrProcess[i]);
            i++;
        }
        if(flag){
            readyQueue.push(runningQueue);
        }
    }
    cout << "hi\n";
    
    while(!readyQueue.empty()){
        runningQueue = readyQueue.front();
        cout << runningQueue.id << " " << currTime << "\n";
        if(m2.count(runningQueue.id) == 0){
            m2[runningQueue.id] = currTime;
        }  
        readyQueue.pop();
        if(runningQueue.bt <= q){
            currTime += runningQueue.bt;
            m[runningQueue.id] = currTime;   
        }
        else{
            currTime += q;
            runningQueue.bt -= q;
            readyQueue.push(runningQueue);
        }
    }
    
    
    for (auto &p : arrProcess) {
        p.ct = m[p.id];
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;
        p.rt = m2[p.id] - p.at;
    }
    
    ld avgWaitingTime = 0;
    ld avgResponseTime = 0;
    ld avgTAT = 0;
    
    for(auto p : arrProcess){
        avgResponseTime += p.rt;
        avgWaitingTime += p.wt;
        avgTAT += p.tat;
    }
    
    avgWaitingTime = avgWaitingTime / n;
    avgResponseTime = avgResponseTime / n;
    avgTAT = avgTAT / n;
    
    output << avgWaitingTime << endl;
    output << avgTAT << endl;
    output << avgResponseTime << endl;
   
   return 0;
}