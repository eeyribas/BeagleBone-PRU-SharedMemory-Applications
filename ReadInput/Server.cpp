#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <bitset>
#include <string.h>
#include <time.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU0 0

using namespace std;

unsigned int* memory_ptr;
void *SharedMem;
const unsigned int OFFSET_SHARED_RAM = 2048;

int main()
{
	prussdrv_init ();

	unsigned int ret = prussdrv_open(PRU_EVTOUT_0);
	if (ret) {
		cout << "\nprussdrv_open open failed\n";
		return 0;
   }

	cout << "\n\tINFO: Starting PRU Server...\n";
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	prussdrv_pruintc_init(&pruss_intc_initdata);

	prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &SharedMem);
	memory_ptr = (unsigned int*) SharedMem;
	prussdrv_exec_program(PRU0, "ASMCode.bin");

	int get_data;
	clock_t t = clock();

	while (1) {
		get_data = memory_ptr[OFFSET_SHARED_RAM + 0];
		if(get_data == 16) {
			break;
		}
	}
	
	cout << "Reading completed...\n";
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "Time = " << time_taken;
	cout << " second \n";
 
	prussdrv_pru_wait_event(PRU_EVTOUT_0);
	cout << "\tINFO: PRU completed transfer.\n";

	prussdrv_pru_clear_event(PRU0_ARM_INTERRUPT, PRU_EVTOUT_0);
	prussdrv_exit ();

	return 0;
}