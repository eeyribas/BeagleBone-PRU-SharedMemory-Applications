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

int main()
{
	int rtn = 0;
	prussdrv_init();

	unsigned int ret = prussdrv_open(PRU_EVTOUT_0);
	if (ret) {
		cout << "\nprussdrv_open open failed\n";
		return 0;
	}

	cout << "\n\tINFO: Starting PRU...\n";
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	prussdrv_pruintc_init(&pruss_intc_initdata);
    prussdrv_exec_program(PRU0, "ASMCode.bin");

	rtn = prussdrv_pru_wait_event(PRU_EVTOUT_0);
	cout << "PRU program completed, event number: " << rtn;
	cout << "\n";

	prussdrv_pru_clear_event(PRU0_ARM_INTERRUPT, PRU_EVTOUT_0);
	prussdrv_exit ();

	return 0;
}