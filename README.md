# BeagleBone-PRU-SharedMemory-Applications
On the BeagleBone, applications have been created using PRUs with shared memory. With the applications in this repo, you will learn how to use BeagleBone PRUs and how to utilize shared memory. The applications;

InterruptCount: The PRU counts interrupts and shares this information with the Server application through shared memory.

ReadGPIO: The PRU reads GPIOs and shares this information with the Server application through shared memory.

ReadInput: The PRU reads inputs and shares this information with the Server application through shared memory.

ServerClient: The PRU acts as a client and sends a "HelloWorld" message to the Server application. The Server application listens to the client through shared memory.

SharedMemory: Communication is established between the Server and the PRU through shared memory.

RUN.md Dosyası: The document provides a sequential overview of information, from establishing a connection between the PC and BeagleBone to compiling and running the applications.