/**************************************************************************************************

This program creates a makefile for testing 2120 labs more efficiently.
(it is used to compile and run all given test cases at once)
I made this for personal use; it isnt very polished but it works well enough.
obviously all of this can be edited to fit your own workflow 

note: I found it useful to make my own tests. 
      You can make your own file with main() or anything else you need 
      then put the name of your custom testing file in SELFTEST 
      and use the commands compmytest and mytest to compile and run

How to use newMakefile.c:
    -compile and run this program
    -when it says "What is the number of the test case with the highest number?" do that
    -when it says "Which ones are we missing? 0 to stop",
     enter the number of each missing test case (the order doesnt matter, 
     it doesnt matter if you enter them on one line or multiple lines)
     once you listed them all type 0 and hit enter
    -when it asks for the program files enter all the files needed to compile
     (for example Node.h, List.h, etc)
    -then your makefile will be created and ready to use

makefile commands are:
    compile: compiles only what is listed as base program into main.exe 
             (sometimes the program files have a main in them)
    run: (also executes compile) runs main.exe (only the base program)

    comptests: compiles all given test cases (T1.cpp, T2.cpp, etc)
    runtests: (also executes comptests) runs all given tests

    compmytest: compiles program files and custom testing file 
    mytest: (also executes comptests) runs custom test

**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isMissing(int n, int msngLst[], int msng);

int main() {

    FILE* newMakefile = fopen("makefile", "w");
    if (newMakefile == NULL) { return -1; }

    int highestCase;
    printf("What is the number of the test case with the highest number?\n");
    scanf("%d", &highestCase);
    
    int missingCases[highestCase];
    int numMissing = 0;
    printf("Which ones are we missing? 0 to stop\n");
    do {
        scanf("%d", &missingCases[numMissing++]);
    } while (missingCases[numMissing - 1] > 0);

    
    char baseProgram[50];
    printf("What are the program files?\n"); 
    scanf(" %[^\n]", baseProgram); //read in program files until newline character
    


    fprintf(newMakefile, "COMP = g++\nFLAGS = -Wall\n");
    fprintf(newMakefile, "SELFTEST = myTest.cpp #for personal testing\n");
    fprintf(newMakefile, "BASE = %s\n", baseProgram);
    fprintf(newMakefile, "\n");

    fprintf(newMakefile, "compile: $(BASE)\n");
    fprintf(newMakefile, "\t$(COMP) $(FLAGS) $(BASE) -o main.exe\n");
    fprintf(newMakefile, "\n");

	fprintf(newMakefile, "run: compile\n\t./main.exe\n");
    fprintf(newMakefile, "\n");

    fprintf(newMakefile, "comptests: $(BASE) ");
    for (int i = 1; i <= highestCase; ++i) {
        if (!isMissing(i, missingCases, numMissing)) {
            fprintf(newMakefile, "T%d.cpp ", i); 
        }
    } 
    fprintf(newMakefile, "\n");
    for (int i = 1; i <= highestCase; ++i) {
        if (!isMissing(i, missingCases, numMissing)) {
            fprintf(newMakefile, "\t$(COMP) $(FLAGS) $(BASE) T%d.cpp -o T%d.exe\n", i, i);
        }
    }
    fprintf(newMakefile, "\n");
    
    fprintf(newMakefile, "runtests: comptests\n");
    for (int i = 1; i <= highestCase; ++i) {
        if (!isMissing(i, missingCases, numMissing)) {
            //the - in front makes it so if a test case fails the rest still run instead of stopping the whole thing
            fprintf(newMakefile, "\t-./T%d.exe\n", i);
        }
    }
    fprintf(newMakefile, "\n");

    fprintf(newMakefile, "compmytest: $(BASE) $(SELFTEST)\n");
    fprintf(newMakefile, "\t$(COMP) $(FLAGS) $(BASE) $(SELFTEST) -o myTest.exe\n");
    fprintf(newMakefile, "\n");

    fprintf(newMakefile, "mytest: compmytest\n");
    fprintf(newMakefile, "\t./myTest.exe\n");
    fprintf(newMakefile, "\n");

    fprintf(newMakefile, "clean:\n");
    fprintf(newMakefile, "\trm -f *.exe\n");

    printf("your makefile is ready!");

    return 0;
}



bool isMissing(int n, int msngLst[], int msng) {
    for (int k = 0; k < msng; ++k) {
        if (msngLst[k] == n) {
            return true;
        }
    }
    return false;
}
