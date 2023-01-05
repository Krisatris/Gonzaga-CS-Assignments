#to run: make
#to elminate .o file: make clean
project11: project11Tst.o project11.o 
	g++ -o project11 project11Tst.o project11.o 

project11Tst.o: project11Tst.cpp
	g++ -c project11Tst.cpp 

project11.o: project11.cpp
	g++ -c project11.cpp 

clean :
	rm *.o
