build: serial parallel

clean:
	rm g_omp g_serial
serial: g_serial.c 
	gcc g_serial.c -o g_serial
parallel: g_omp.c
	gcc -fopenmp g_omp.c -o g_omp
