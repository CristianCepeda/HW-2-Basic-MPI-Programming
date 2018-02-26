// /*==========================================================================
// |   Source code:  [collect_all.c]
// |        Author:  [Cristian C Cepeda]
// |    Student ID:  [4959207]
// |    Assignment:  Program #[2] Problem #[2] [collect_all.c]
// |
// |        Course:  [COP 4520 (Introduction to Parallel Computing)]
// |       Section:  [U01]
// |    Instructor:  Jason Liu
// |      Due Date:  [27 February 2018], at the beginning of class
// |
// |	I hereby certify that this collective work is my own
// |	and none of it is the work of any other person or entity.
// |
// |	__Cristian C Cepeda____________________________________ [Signature]
// |
// |        Language:  [Program Language: C]
// |     Compile/Run:
// |
// |                  COMPILE
// |                  Once you are in the correct directory where all the
// |                  files are found enter
// |
// |                  make
// |
// |                  - This will compile all the necessary files needed to
// |                    run the program. Incase you just want to compile this
// |                    file then you can run this command to compile
// |
// |                      - mpicc -O -o collect_all collect_all.c
// |
// |                  - This will create an executable file named
// |                    "collect_all"
// |
// |                  RUN
// |                  - Enter this to Run a test version of it
// |
// |                  - mpirun -np 4 --hostfile my-hostfile ./collect_all
// |
// |                  - Where 4 is an arbitrary number and you can insert any
// |                    number to create that set of processes run the program.
// |
// |                  - The "--hostfile my-hostfile" was necessary in my case so
// |                  that I could run the programs on my computer. The max
// |                  number of process that my computer would let me run was
// |                  2. This is why I had to create this file and add this
// |                  extension. As it is now you can run up 10 processes.
// |                  However if you intend to run more than 10 processes then
// |                  you will have to go into the file named "my-hostfile" and
// |                  change the number 10 to the number of desired processes.
// |                  This might just be system dependent so it might just be
// |                  that I'm the only one that needs to run it like this.
// |
// |  +------------------------------------------------------------------------
// |
// |  Description:  [ The main goal of this program is to have the processes
// |                  communicate between each other. You can picture
// |                  this program to be a circular array. But we are starting
// |                  from an initial location the root and the last element can
// |                  communicate with the root. From the root we will send a
// |                  number to our neighbor and they will continue sending
// |                  that number to there next neighbor until it reaches the
// |                  root again. Once it reaches the root we will print this
// |                  two numbers out. These two numbers are our solution to the
// |                  program. When we move to the right in the array we are
// |                  adding the results. And when we move towards the left we
// |                  are subtracting the values. We should essentially get the
// |                  same number but one positive and one negative. To compile
// |                  and run the program look at that subsection. ]
// |
// |        Input:  [ The input is done through the command line. An example
// |                  looks like this:
// |
// |    -  make
// |    -  mpirun -np 4 --hostfile my-hostfile ./collect_all
// |                    - Where 4 is the number of processes you want to run the
// |                      program with. Depending on the number you input you
// |                      will get a different value at the end. ]
// |
// |
// |       Output:  [The output of the program depends on the number of process
// |                 you decide to create. If we put 4 then the answers will be
// |                 6 and -6. I would go ahead and insert different values to
// |                 see different outputs.
// |
// |      Process:  [The program’s steps are as follows:
// |                1. You have to do three essential steps so that we can
// |                create an MPI program. You call MPI_Init, MPI_Comm_size,
// |                MPI_Comm_rank.
// |                2. You call the last two MPI methods so that you can get the
// |                essential information so that you know who you need to
// |                communicate to.
// |                3. We then determine if you're the first process. This is
// |                because the first process needs to send its initial value to
// |                both its neighbors. Before anyone else decides to send a
// |                value. The first process also starts to receive but it waits
// |                until it gets its value before adding it to the corresponding
// |                counter.
// |                4. As for the rest of the processes they will all have to
// |                be out in the look out or receiving a value before they
// |                decide to send a value to their neighbor. When they call the
// |                receive function they also have to wait. Once they get
// |                the value from there neighbor they perform the addition or
// |                subtraction and then they send that value to their next
// |                neighbor.
// |                5. Its now that everyone has received and sent a number that
// |                the first process needs to print out the total value.
// |
// |   Required Features Not Included:  [ Everything was completed ]
// |
// |   Known Bugs:  [There are no Bugs]
// |  *===================================================================== */

/* The following function is a collective operation; that is, it shall be
called by all mpi processes or none at all. (Use MPI_COMM_WORLD.) Each process
is expected to provide a block of data of size 'sendcnt' stored in  'sendbuf'.
When the function returns, each process will have the data blocks sent from all
other processes (including itself) stored in 'recvbuf'. recvbuf will be an
array of pointers to the received data (the function is in charge of allocating
the array and the buffer for the received data). recvcnt is an array storing
the size of the data. Again, the function is responsible for  allocating the
array. More specifically, the data from the i-th process is  received by every
process and placed in the i-th element of the 'recvbuf' and its size is put in
the i-th element of 'recvcnt'. One must not assume that  all processes would
provide the same 'sendcnt'. */

// void collect_all(char* sendbuf, int sendcnt, char** recvbuf, int* recvcnt);

// IMPORTANT
/*
   - For collect_all(), you should use the hypercube.
   - You may assume that the number of MPI processes must be
     a power of two for collect_all().
*/

/* Expected output with 4 MPI processes

    [2] collect_all[3]->"hello from rank 3" (sz=18)

*/

#include "addAllAndCollectAllHeaderFile.h"

int main(int argc, char* argv[]) {

  int numberOfProcesses, processID;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &processID);


  MPI_Finalize();
  return 0;
}
