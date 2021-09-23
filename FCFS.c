#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//typedef unsigned int size_t;
const size_t ArraySize = 10;
size_t Waiting_time = 0;
size_t TurnAround_time = 0;


struct Proc
{
	size_t BurstTime;

};

void Populate(struct Proc* Array)
{
	for(int i  = 0; i<ArraySize;i++)
	{
		Array[i].BurstTime = (size_t) random();
		//for entering data from console rewrite this to
		//scanf("%lu", &Array[i].BurstTime);
	}
};

void OutPut(struct Proc* Array)
{

	printf("Process \t TurnaroundTime \t Bursttime \t Waiting \t \n");
	for(int i = 0;i<ArraySize;i++)
	{
		TurnAround_time = Array[i]->BurstTime + Waiting_time;
		printf("P[%d] \t\t %lu \t\t %lu \t\t %lu \n",i,TurnAround_time,Array->BurstTime,Waiting_time);   
		Waiting_time = Waiting_time + Array->BurstTime;
	}
	
}

int main()
{
	struct Proc Array[ArraySize];
	Populate(Array);//Array decay
	OutPut(Array);
}
