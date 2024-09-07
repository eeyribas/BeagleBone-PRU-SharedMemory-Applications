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

	cout << "\n\tINFO: Starting PRU...\n";
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	prussdrv_pruintc_init(&pruss_intc_initdata);

	prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &SharedMem);
	memory_ptr = (unsigned int*) SharedMem;
	memory_ptr[OFFSET_SHARED_RAM + 0] = 11;
	memory_ptr[OFFSET_SHARED_RAM + 1] = 22;
	memory_ptr[OFFSET_SHARED_RAM + 2] = 33;
	memory_ptr[OFFSET_SHARED_RAM + 3] = 44;
	prussdrv_exec_program(PRU0, "ASMCode.bin");

	unsigned int a;
	while (1) {
		std::cin >> a;
		if (a == 255) {
			memory_ptr[OFFSET_SHARED_RAM + 0] = a;
			break;
		} else if (a == 1) {
			memory_ptr[OFFSET_SHARED_RAM + 0] = a;
		} else if (a == 2) {
			memory_ptr[OFFSET_SHARED_RAM + 1] = a;
		} else if (a == 3) {
			memory_ptr[OFFSET_SHARED_RAM + 2] = a;
		} else if (a == 4) {
			memory_ptr[OFFSET_SHARED_RAM + 3] = a;
		} else if (a == 11) {
			memory_ptr[OFFSET_SHARED_RAM + 0] = a;
		} else if (a == 22) {
			memory_ptr[OFFSET_SHARED_RAM + 1] = a;
		} else if (a == 33) {
			memory_ptr[OFFSET_SHARED_RAM + 2] = a;
		} else if (a == 4) {
			memory_ptr[OFFSET_SHARED_RAM + 3] = a;
		} else {
			cout << "\\tWarning: Entered wrong parameter!\n";
		}
	}

	prussdrv_pru_wait_event (PRU_EVTOUT_0);
	cout << "\tINFO: PRU completed transfer.\n";

	prussdrv_pru_clear_event (PRU0_ARM_INTERRUPT, PRU_EVTOUT_0);
	prussdrv_exit ();

	return 0;
}