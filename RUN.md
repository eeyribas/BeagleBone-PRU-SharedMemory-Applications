Connect to BeagleBone from the PC.
1. ssh debian@192.168.7.2
2. sudo su

Boot settings are configured.
1. lsmod | grep uio
2. nano /boot/uEnv.txt
3. uboot_overlay.....PRU-RPOC-4-14-TI # with close
4 uboot_overlay.....PRU-UIO-00A0.dtbo # with open
5. lsmod | grep uio

Create the folder where the project will be created.
1. mkdir PRU #(FileName)
2. cd PRU

Download the PRU configuration files.
1. git clone https://github.com/beagleboard/am335x_pru_package.git
2. cd am335x_pru_package
3. ls -l

PRU configuration attachments are included and compiled.
1. wget http://e2e.ti.com/cfs-file.ashx/__key/telligent-evolution-components-attachments/00-791-00-00-00-23-97-35/attachments.tar.gz
2. ls -l
3. tar -xzf attachments.tar.gz
4. patch -p1 < 0001-Fix-for-duplicated-interrupts-when-interrupts-are-se.patch
5. cd pru_sw/app_loader/interface
6. gcc -I. -Wall -I../include -c -fPIC -O3 -mtune=cortex-a8 -march=armv7-a -shared -o prussdrv.o prussdrv.c
7. gcc -shared -o libprussdrv.so prussdrv.o
8. cp libprussdrv.so /usr/lib/
9. cp ../include/*.h /usr/include/
10. cd ../../utils/pasm_source
11. ./linuxbuild
12. cp ../pasm /usr/bin/
13. cat /sys/kernel/debug/pinctrl/44e10800.pinmux/pinmux-pins
14. cd

The PRU0-00A0.dts file is compiled and copied to the specified directory.
1. cd PRU # or Enter any example available in the repository
2. mkdir DTSFiles
3. cd DT_Files
4. PRU0-00A0.dts in the example is selected.
5. dtc -O dtb -o PRU0-00A0.dtbo -b 0 -@ PRU0-00A0.dts
6. ls -l
7. cp PRU0-00A0.dtbo /lib/firmware/
8. nano /boot/uEnv.txt
9. uboot_overlay_addr4=/lib/firmware/PRU0-00A0.dtbo <file4> # Overwrite, open, save
10. cd ..

The code is compiled and executed.
1. mkdir PRUCode
2. cd PRUCode
3. The ASMCode.p used in the example is compiled
4. pasm -b ASMcode.p
5. The .cpp codes used in the example is compiled
6. g++ Server.cpp -o Server1 -lpthread -lprussdrv
7. ./Server1

The code in the examples has been compiled and executed by creating folders within the BeagleBone.