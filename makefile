run: prob1para.o
	mpicc -Wall -o run prob1para.o
	
prob1para.o: prob1para.c 
	mpicc -Wall -c prob1para.c 

clean:
	rm -f run prob1para.o
	
rebuild:
	make
	make clean