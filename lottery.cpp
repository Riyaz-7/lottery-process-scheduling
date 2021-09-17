#include <bits/stdc++.h>
#include<cstdio>
using namespace std;

void fifo(queue<char> &process_queue, vector<int> &burst_time, int n)
{
  // wait[i] = bt[i-1]+wait[i-1];
  // tot[i] = wait[i]+bt[i];

  vector<int> wait_time(n,0);
  vector<int> turn_around_time(n,0);
  wait_time[0]=0;
  turn_around_time[0]=wait_time[0]+burst_time[0];
  for(int i=1;i<n;i++)
  {
   wait_time[i]=burst_time[i-1]+wait_time[i-1];
   turn_around_time[i]=wait_time[i]+burst_time[i];
  }
  cout<<"process\t |"<<"wait\t |"<<"turnaround\n";
  for(int i=0;i<n;i++)
  {
    cout <<process_queue.front()<<"\t |"<< wait_time[i] << "\t |" << turn_around_time[i] <<"\n";
    process_queue.pop();
  }

}

int main() 
{
  int totalTickets = 1000;
  int tot_tic;  //total no of tickets
  vector<int> t_tickets;  //total tickets for individual process
  int n;
  vector<int> pid;
  vector<int> bt(n,0);
  vector<int> prio(n);
  cout<<"Enter no of processes:"<<endl;
  cin>>n;
  for(int i=0;i<n;i++){
    pid.push_back(i+65);
    cout<<"Enter thr burst time and priority of the process ";
    printf("%c:\n",pid[i]);
    cin>>bt[i];
    cin>>prio[i];
  }
  // for(int i=0;i<n;i++){
  //  printf("process %c",pid[i]);
  //  cout<<" burst time is : "<<bt[i]<<endl;
  // }
  for(int i=0;i<n;i++){
    t_tickets.push_back(((n-prio[i])*5)+4);
    tot_tic+=t_tickets[i];
    printf("process %c got %d tickets\n",pid[i],t_tickets[i]);
  }
  cout << endl;
  // ith process t_tickets[i] tickets
  vector<vector<int>> ticket_number;
  map<int,pair<bool,char>> hash_map;
  for(int i=0;i<n;i++)
  {
    vector<int> temp;
    for(int j=0;j<t_tickets[i];j++)
    {
      int rt = rand()%100+1;
      if(!hash_map[rt].first)
      {
        temp.push_back(rt);
        hash_map[rt].first = true;
        hash_map[rt].second = (char)pid[i];
      }
      else{
        while(hash_map[rt].first)
        {
            rt = rand()%100+1;
        }
        temp.push_back(rt);
        hash_map[rt].first = true;
        hash_map[rt].second = (char)pid[i];
      }
    }
    ticket_number.push_back(temp);
  }
  cout<<" Ticket Numbers\n";
  for(int i=0;i<n;i++)
  {
   for(int j=0;j<t_tickets[i];j++)
   {
     cout << ticket_number[i][j] << " ";
     cout << hash_map[ticket_number[i][j]].second << " ";
   }
   cout << endl;
  }

queue<char> process_queue;
vector<int> visited(150,0);
vector<int> new_bt(n,0);
int j=0;
while(process_queue.size()!=n )
{
  int r=rand()%100+1;
  if(hash_map[r].first && !visited[hash_map[r].second]){
    process_queue.push(hash_map[r].second);
    cout<<"process "<<hash_map[r].second<<" is selected "<<endl;
    //hash_map[r].first=false;
    visited[hash_map[r].second]=1;
    new_bt[j++]=bt[hash_map[r].second-'A'];
  }

}

fifo(process_queue, new_bt, n);
}
