// /*==========================================================================
// |   Source code:  [addAllAndCollectAllHeaderFile.h]
// |        Author:  [Cristian C Cepeda]
// |    Student ID:  [4959207]
// |    Assignment:  Program #[2] [addAllAndCollectAllHeaderFile.h]
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
// |
// |
// |    This is the header
// |
// *==========================================================================*/

#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h> // So we can use the pow(2,step) function in add_all();

// ENUMS OR CONSTANTS
#define TAG_ID 0
#define EVEN_NUM 0
#define ODD_NUM 1
#define ROOT_NUMBER 0


// Prototypes for add_all.c
int returnStepsRequired(int numberOfProcesses);
void add_all(int iD, int rootNUM);


// Prototypes for collect_all.c
