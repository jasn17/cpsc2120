COMP = g++
FLAGS = -Wall
SELFTEST = myTest.cpp #for personal testing
BASE = infixToPostfix.cpp

compile: $(BASE)
	$(COMP) $(FLAGS) $(BASE) -o main.exe

run: compile
	./main.exe

comptests: $(BASE) T1.cpp T2.cpp T4.cpp T5.cpp T6.cpp T9.cpp T13.cpp T16.cpp T17.cpp T18.cpp T19.cpp 
	$(COMP) $(FLAGS) $(BASE) T1.cpp -o T1.exe
	$(COMP) $(FLAGS) $(BASE) T2.cpp -o T2.exe
	$(COMP) $(FLAGS) $(BASE) T4.cpp -o T4.exe
	$(COMP) $(FLAGS) $(BASE) T5.cpp -o T5.exe
	$(COMP) $(FLAGS) $(BASE) T6.cpp -o T6.exe
	$(COMP) $(FLAGS) $(BASE) T9.cpp -o T9.exe
	$(COMP) $(FLAGS) $(BASE) T13.cpp -o T13.exe
	$(COMP) $(FLAGS) $(BASE) T16.cpp -o T16.exe
	$(COMP) $(FLAGS) $(BASE) T17.cpp -o T17.exe
	$(COMP) $(FLAGS) $(BASE) T18.cpp -o T18.exe
	$(COMP) $(FLAGS) $(BASE) T19.cpp -o T19.exe

runtests: comptests
	-./T1.exe
	-./T2.exe
	-./T4.exe
	-./T5.exe
	-./T6.exe
	-./T9.exe
	-./T13.exe
	-./T16.exe
	-./T17.exe
	-./T18.exe
	-./T19.exe

compmytest: $(BASE) $(SELFTEST)
	$(COMP) $(FLAGS) $(BASE) $(SELFTEST) -o myTest.exe

mytest: compmytest
	./myTest.exe

clean:
	rm -f *.exe
