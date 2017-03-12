#include<iostream>
#include<stdlib.h>
#include<queue>
#include<utility>
#include<stdio.h>
using namespace std;
int id[1500];   int arr[1500];
int cpu1[1500]; int io[1500];
int cpu2[1500]; int ans [1500];
int flag[1500]; bool if_arr[1500]; //if_arr[i]:at i,there's someone arraive
int N, kind;

int find_small(int time)
{
    int small= -1;
    for(int i=0; i<N; i++) if(flag[i]!=2 && arr[i]<=time){small=i; break;}
    if(small == -1) return -1;
    for(int j=0; j<N; j++) //find the shortest burst time
    {
        if(flag[j]<2)
        {
            if(arr[j]<=time) //arrived
                if(cpu1[j] < cpu1[small]) small = j;
                else if(cpu1[j]==cpu1[small]) 
                {
                    if(arr[j]<arr[small]) small = j;
                    else if(arr[j]==arr[small])
                        { if(id[j]<id[small]) small = j; }
                }        
        }
    }
    return small;
}

int find3_small(int time)
{
    int small= -1;
    for(int i=0; i<N; i++) if(flag[i]< 2 && arr[i]<=time){small=i; break;}
    if(small != -1) //there is at least one in RR
    {  
       for(int j=0; j<N; j++) //find the shortest arrive time
       {
         if(flag[j]<2)
         {
            if(arr[j]<arr[small]) small = j;
            else if(arr[j]==arr[small])
                { if(id[j]<id[small]) small = j; }        
          }
        }
         return small;
    }
    else
    {
        for(int i=0; i<N; i++) if(flag[i]>2 && flag[i]!=5 && arr[i]<=time){small=i; break;}
        if(small!=-1)
        {    
            for(int j=0; j<N; j++) //find the shortest arrive time
            {
              if(flag[j]>2 && flag[j]!=5)
              {
                if(arr[j]<arr[small]) small = j;
                else if(arr[j]==arr[small])
                 { if(id[j]<id[small]) small = j; }        
              }
            }
            return small;
        }
    }
    return -1;
}

int main()
{
    FILE * pFile, *pFile2;
    pFile = fopen("input.txt", "r");
    pFile2 = fopen("0316321.txt", "w");
    fscanf(pFile,"%d%d",&kind,&N);
    int n=0;
    for(int i=0; i<N ; i++)
    {    
        fscanf(pFile,"%d %d %d %d %d",id+i, arr+i, cpu1+i,io+i, cpu2+i);
        flag[i] = 0; if_arr[arr[i]]=true;
    }
    int time =0, small=0; int remain=2*N;
    if(kind==1)
    {
        while(remain)
        {
            small = find_small(time);
            if(small == -1) time++; //no process is available 
            else
            {
                time += cpu1[small];
                if(flag[small]==0)
                {
                    arr[small] = time + io[small];
                    cpu1[small] = cpu2[small];
                    flag[small] = 1;
                }
                else { flag[small]=2; fprintf(pFile2,"%d:%d\n",id[small],time); }
                remain--;
            }
        }
    }
    else if(kind == 2)
    {
        while(remain)
        {
            if(if_arr[time]) small = find_small(time);
            if(small == -1) time++;
            else 
            {
                cpu1[small]--; time++;
                if(!cpu1[small]) //finish a burst
                {
                    remain--;
                    if(flag[small]==0)
                    {
                        arr[small] = time+io[small];
                        cpu1[small] = cpu2[small]; flag[small]=1;
                        if_arr[arr[small]]=true;
                    }
                    else{flag[small]=2; 
                    fprintf(pFile2,"%d:%d\n",id[small],time);}
                    small = find_small(time);
                }
            }
        }
    }
    else
    {
        while(remain)
        {
            small = find3_small(time);    
            if(small == -1) time++;
            else if(flag[small] < 2)      //RR       
            {
                  if(cpu1[small]>4) //go to FCFS
                  {
                      time += 4;
                      cpu1[small]-=4;
                      arr[small]=time;
                      if(flag[small]==0)flag[small]=3;
                      else flag[small]=4;
                  }
                  else
                  {
                      remain--;
                      time += cpu1[small];
                      if(flag[small]==1)
                      { 
                          flag[small]=2;
                          fprintf(pFile2,"%d:%d\n",id[small],time);
                      }    
                      else
                      {
                          arr[small] = time+io[small];
                          cpu1[small] = cpu2[small]; flag[small]=1;
                          if_arr[arr[small]]=true;
                      }
                  }
            }
            else 
            {
                  while(!if_arr[time] && cpu1[small]) {cpu1[small]--; time++;}
                  if(if_arr[time]){arr[small] = time;}
                  if(!cpu1[small])
                  {
                      remain--;
                      if(flag[small]==3)
                      {
                          arr[small] = time + io[small];
                          cpu1[small] = cpu2[small];
                          flag[small] = 4;
                      }
                      else{
                           flag[small]=5; 
                           fprintf(pFile2,"%d:%d\n",id[small],time);
                      }
                  }
               
            }
                          
        }
        
    }
    fclose(pFile);
    fclose(pFile2);
}
