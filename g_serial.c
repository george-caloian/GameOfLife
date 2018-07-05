#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>

int main(int argc, char **argv)
{

	//declarari
	FILE *f;
	
	int Lin,Col; 	//nr linii si coloane
	int Incr; 	//nr incrementari


	char **A;
	char **B;
	char **aux;

	//deschid fisier intrare
	f=fopen(argv[1],"r"); 	

	//citesc nr de linii si coloane
	fscanf(f,"%d",&Lin); 	
	fscanf(f,"%d",&Col);


	//alocare memorie
	A=(char**)malloc((Lin+2)*sizeof(char*));
	for(int i=0;i<Lin+2;++i)
		A[i]=(char*)malloc((Col+2)*sizeof(char));

	B=(char**)malloc((Lin+2)*sizeof(char*));
	for(int i=0;i<Lin+2;++i)
		B[i]=(char*)malloc((Col+2)*sizeof(char));
	
	//citesc matricea
	for(int i=1;i<Lin+1;++i)
		for(int j=1;j<Col+1;++j)
			fscanf(f," %c",&A[i][j]);	

	fclose(f);

	//salvez nr incrementari
	Incr = atoi(argv[2]); 	
	
	while(Incr>0)
	{
	
		//bordare sus jos
		
		for(int j=1;j<Col+1;++j)	
		{
			A[Lin+1][j]=A[1][j];
			A[0][j]=A[Lin][j];
			
		}

		//bordare stanga dreapta

		for(int i=1;i<Lin+1;++i)	
		{
			A[i][Col+1]=A[i][1];
			A[i][0]=A[i][Col];
			
		}

		//bordare colturi
		A[Lin+1][Col+1]=A[1][1];
		A[0][Col+1]=A[Lin][1];
		A[Lin+1][0]=A[1][Col];
		A[0][0]=A[Lin][Col];

	

		for(int i=1;i<Lin+1;i++)
			for(int j=1;j<Col+1;j++)
			{

				//verific fiecare vecin si calculez nr total de vecini ALIVE
				int sum=0;
				if(A[i+1][j-1]=='X') sum++;
				if(A[i+1][j]=='X') sum++;
				if(A[i-1][j]=='X') sum++;
				if(A[i+1][j+1]=='X') sum++;
				if(A[i][j+1]=='X') sum++;
				if(A[i-1][j-1]=='X') sum++;
				if(A[i-1][j+1]=='X') sum++;
				if(A[i][j-1]=='X') sum++;
				

			
				//verific fiecare caz in parte
				//si completez matricea B corespunzator fiecarei reguli
				if(sum==2 && A[i][j]=='.') B[i][j]= '.';
				else if(sum<2) B[i][j]= '.';
				else if((sum==2 || sum==3) && A[i][j]=='X') B[i][j]= 'X';
				else if(sum==3 && A[i][j]=='.') B[i][j]= 'X';
				else if(sum>3) B[i][j]= '.';
			}

		Incr--;
		

		//copiez matricea B in A pt a o avea ca matrice la pas curent in urmatoarea iteratie
		for(int i=1;i<Lin+1;i++)	
			for(int j=1;j<Col+1;j++)	
				A[i][j]=B[i][j];
	
	}


	//deschid fisier iesire
	f=fopen(argv[3],"w+");	

	//afisare fisier
	for(int i=1;i<Lin+1;i++)	
	{

		for(int j=1;j<Col+1;j++)
			fprintf(f,"%c ",A[i][j]);
		fprintf(f,"\n");
	}

	fclose(f);

	return 0;
}
