
#include "main.h"
#include "system.h"
#include "task.h"
#include "hardware.h"
#include "application.h"

int main(void)
{
	System_Init();
	TaskInit();

	Hardware_Init();
	App_Init();

	while(1)
	{
		if (GET_TaskExeFlag())
		{
			CLR_TaskExeFlag();
			TaskExe();
		}
	}
}
