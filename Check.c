#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>


const size_t CPUTick = 3; //Quantum
const size_t ArraySize = 10;
size_t TurnAroundTime = 0; 


struct Proc
{
	size_t BTCopy;
	size_t Temp;
	size_t BurstTime;
	size_t WaitTime;
	size_t TurnAroundTime;
	_Bool Finished;
};

struct ProcHandle
{
	size_t RefCount;
	struct Proc Array[10];
};


void Populate(struct Proc* Array)
{
	for (int i = 0; i<ArraySize; i++)
	{
		Array[i].BurstTime = (size_t) random();
		Array[i].BTCopy = Array->BurstTime;
		Array[i].Temp = 0;
		Array[i].WaitTime = 0;
		Array[i].TurnAroundTime = 0;
		Array[i].Finished = 0;
	}
};

void FillHandler(struct ProcHandle* Handle)
{
	Handle->RefCount = ArraySize;
	Populate(Handle->Array);//array decay
};


void RoundRobin(struct ProcHandle* Handle)
{
	while(Handle->RefCount > 0)
	{
		for(int i = 0;i < ArraySize;i++)
		{
			struct Proc Now = Handle->Array[i]; 
			if(!Now.Finished)
			{
				TurnAroundTime += CPUTick;
				Now.BurstTime -= CPUTick;
				Now.WaitTime += TurnAroundTime - Now.Temp; 
				Now.Temp = TurnAroundTime; 
				if(Now.BurstTime <= 0)
				{
					Now.Finished = 1;
					Handle->RefCount -= 1; 
					Now.TurnAroundTime = TurnAroundTime;
				}
			}
		}
	}
};

void Print(struct Proc* Array)
{
	printf("process \t WaitTime \t TurnAroundTime \t BurstTime ");
	for(int i = 0; i <ArraySize; i++)
	{
		printf("%ls \t\t %ln \t\t %ln \t\t %ln \n",&i,&Array->WaitTime,&Array->TurnAroundTime,&Array->BTCopy);
	}
}

int main(int arg , char* argv)
{
	struct ProcHandle Handle;
	FillHandler(&Handle);
	RoundRobin(&Handle);
	Print(Handle.Array);
}
