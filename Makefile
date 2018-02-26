output: add_all.o collect_all.o
	mpicc -O add_all.o -o add_all
	mpicc -O collect_all.o -o collect_all

add_all.o: add_all.c
	mpicc -c add_all.c -o add_all.o

collect_all.o: collect_all.c
	mpicc -c collect_all.c -o collect_all.o

clean:
	rm *.o *~ add_all collect_all
