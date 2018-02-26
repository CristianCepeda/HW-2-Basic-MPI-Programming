// /*==========================================================================
// |   Source code:  [add_all.c]
// |        Author:  [Cristian C Cepeda]
// |    Student ID:  [4959207]
// |    Assignment:  Program #[2] Problem #[1] [add_all.c]
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
// |                      - mpicc -O -o add_all add_all.c
// |
// |                  - This will create an executable file named
// |                    "add_all"
// |
// |                  RUN
// |                  - Enter this to Run a test version of it
// |
// |                  - mpirun -np 4 --hostfile my-hostfile ./add_all
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
// |  Description:  [ The main goal of this program is to implement a function
// |                  named add_all() which will act as a collective function.
// |                  It should essentially be a binomial tree where it acts as
// |                  a reduction problem and as the tree is being reduces then
// |                  it adds the numbers together or the leafs of the tree.
// |                  This is an all-to-one reduction. ]
// |
// |        Input:  [ The input is done through the command line. An example
// |                  looks like this:
// |
// |    -  make
// |    -  mpirun -np 4 --hostfile my-hostfile ./add_all
// |                    - Where 4 is the number of processes you want to run the
// |                      program with. Depending on the number you input you
// |                      will get a different value at the end. ]
// |
// |
// |       Output:  [The output of the program depends on the number of process
// |                 you decide to create. If we put 4 then the answers will be
// |                 6. I would go ahead and insert different values to
// |                 see different outputs. However with the file that I have
// |                 named "my-hostfile" it will only let you run it up to 16
// |                 processors. You can configure it to the number of
// |                 processors that you desire to. If we input 16 then the
// |                 output should be 120.]
// |
// |      Process:  [The program’s steps are as follows:
// |                1. You have to do three essential steps so that we can
// |                create an MPI program. You call MPI_Init, MPI_Comm_size,
// |                MPI_Comm_rank.
// |                2. You call the last two MPI methods so that you can get the
// |                essential information so that you know who you need to
// |                communicate to.
// |                3. Then based on the process ID and the step that its
// |                on it will determine who it should receive from and who it
// |                should send to.
// |                4. This was done by determining the required steps needed.
// |                Which is determined by calling the function
// |                returnStepsRequired().
// |                4. When a process receives a value it updates a variable
// |                they hold with the current value or data that they are
// |                carrying to that they can send it to there respective next
// |                neighbor in the binomial tree.
// |                5. Another thing to note is that as they send a number they
// |                are done working so they call MPI_Finalize() becasue they
// |                have finsihed doing there task.
// |                5. Once the root receives the last number then the
// |                all-to-one reduction of the binomial tree has finsished.
// |
// |   Required Features Not Included:  [ Everything was completed ]
// |
// |   Known Bugs:  [ As of now there is a bug when running it with this number
// |                 of processes. And these numbers are from the range of
// |                 0 - 16 becasue thats the number of processes that I have
// |                 in the file named "my-hostfile". (6,10,11,12,14) ]
// |
// |  *===================================================================== */

/* The following function is a collective operation; that is, it shall be
   called by all mpi processes or none at all. (Use MPI_COMM_WORLD.) Each
   process is expected to provide an integer 'x', and the function returns the
   total sum for the process whose rank is 'root'. The return value of all
   other processes is zero. */

// int add_all(int x, int root);

// IMPORTANT
/*
    - For add_all(), you should use the binomial tree.
    - For add_all(), there can be an arbitrary number of MPI processes (not
    necessarily power of two).
 */

/* Expected output with 4 MPI processes

    [0] add_all->6

 */

/** EXAMPLE PROGRAM
 int p, id;
 MPI_Comm_size(MPI_COMM_WORLD, &p);
 MPI_Comm_rank(MPI_COMM_WORLD, &id);

 int sum = add_all(id, 0);
 if(id==0) printf("[0] add_all->%d\n", sum);
*/

#include "addAllAndCollectAllHeaderFile.h"

/** mpirun -np 0 --hostfile my-hostfile ./add_all
  We will get the answer as if we were running it on all processors which its
  currently defaulted to 16 processors.
*/


int main(int argc, char* argv[]) {
  int numberOfProcesses, processID;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &processID);

  int updatedValue = processID;
  int valueReceiving;
  int stepsREQUIRED = returnStepsRequired(numberOfProcesses);

  for (size_t stepON = 1; stepON <= stepsREQUIRED ; stepON++) {
    int moduloNUMBER = pow(2,stepON);
    int moduloRESULT = pow(2,(stepON - 1));

    if (processID%moduloNUMBER == 0) { // IF WE WANT TO RECEIVE
      valueReceiving = 0;
      printf("[%d] The value before receiving equals: {%d}\n", processID, updatedValue);
      if (processID == (numberOfProcesses-1)) {
        // You dont need to receive so move one
      } else {
        MPI_Recv(&valueReceiving, 1, MPI_INT, (processID + moduloRESULT), TAG_ID, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        updatedValue += valueReceiving;
      }
    } // END OF IF() LOOP FOR RECEIVING DATA
    if (processID%moduloNUMBER == moduloRESULT) { // IF WE WANT TO SEND DATA
      MPI_Send(&updatedValue, 1, MPI_INT, (processID - moduloRESULT), TAG_ID, MPI_COMM_WORLD);
      MPI_Finalize();
      return 0;
    } // END OF IF() LOOP FOR SENDING DATA
  } // END OF FOR() LOOP


  printf("[%d] The updated value after the send equals: {%d}\n", processID, updatedValue);
  MPI_Finalize();
  return 0;

}

int returnStepsRequired(int numberOfProcesses){
  int stepsREQUIRED = 0;
  switch (numberOfProcesses) {
    case 1 ... 2:
      stepsREQUIRED = 1;
      break;
    case 3 ... 4:
      stepsREQUIRED = 2;
      break;
    case 5 ... 8:
      stepsREQUIRED = 3;
      break;
    case 9 ... 16:
      stepsREQUIRED = 4;
      break;
    case 17 ... 32:
      stepsREQUIRED = 5;
      break;
    }
    return stepsREQUIRED;
}

/** EXAMPLE OF WHAT WE NEED TO DO
The person we need to send to starts at 1 and then each step it mutiples by 2
stepON(1) + 1     0<-1 2<-3 4<-5 6<-7 8<-9 10<-11 12<-13 14<-15 16<-17 18<-19 20<-21 22<-23 24<-25 26<-27 28<-29 30<-31
stepON(2) + 2     0<---2    4<---6    8<---10     12<----14     16<----18     20<----22     24<----26     28<----30
stepON(3) + 4     0<--------4         8<----------12            16<-----------20            24<-----------28
stepON(4) + 8     0<------------------8                         16<-------------------------24
stepON(5) + 16    0<--------------------------------------------16

                                        // this would be 2^(iteration) starting from 0
IN STEP 1: RECEIVE FROM (processID + 1) // this would be 2^(0)
IN STEP 2: RECEIVE FROM (processID + 2) // this would be 2^(1)
IN STEP 3: RECEIVE FROM (processID + 4) // this would be 2^(2)
IN STEP 4: RECEIVE FROM (processID + 8) // this would be 2^(3)

if processID % 2 == 0 then you are even

if processID % 2 == 1 then you are odd
  SEND YOUR NUMBER TO (processID - 1)
  THIS DELETED ALL THE ODD NUMBERS IN ONE STEP

*/
