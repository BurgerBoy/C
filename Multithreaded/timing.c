// must compile with -std=c99 -Wall -o checkdiv 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <time.h>


int main(int argc, char *argv[]){
	 
	
	unsigned int x, n;
	unsigned int i, j;

	double start_p2, end_p2;

	
	FILE * fp; //for creating the output file
	char filename[100]=""; // the file name
	//char * nx; //the numbers in the range [2, N]
	

	int comm_sz;
	int my_rank;

	float art[comm_sz];

	float time2, ptime;

	clock_t start_p1, start_p3, end_p1,  end_p3;

	

	/////////////////////////////////////////
	// start of part 1

	if(my_rank == 0){
		start_p1 = clock();
	}
	
	// Check that the input from the user is correct.
	if(argc != 3){

	  printf("usage:  ./checkdiv N x\n");
	  printf("N: the upper bound of the range [2,N]\n");
	  printf("x: divisor\n");
	  exit(1);
	}  


	n = (unsigned int)atoi(argv[1]); 
	x = (unsigned int)atoi(argv[2]);
	unsigned int xn[2] = {x, n};

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	

	// Process 0 must send the x and n to each process.
	// Other processes must, after receiving the variables, calculate their own range.
	
	if(comm_sz > 1){
		if(my_rank == 0){

			for(i = 1; i < comm_sz; i++){
				MPI_Send(xn, 2, MPI_UNSIGNED, i, 2, MPI_COMM_WORLD);
				//printf("Sent %d and %d to process %d\n ", x, n, i);
			}
		}

		else{
			MPI_Recv(xn, 2, MPI_UNSIGNED, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("Process %d recieved data\n ", my_rank);
		}

	}
	

	if(my_rank == 0){
		end_p1 = clock();
		printf("Time Part 1: %f\n ", (float)(end_p1 - start_p1) / CLOCKS_PER_SEC );
	}
	
	MPI_Barrier (MPI_COMM_WORLD);
	//printf("END OF PART 1\n ");

	//end of part 1
	/////////////////////////////////////////

	

	/////////////////////////////////////////
	//start of part 2
	// The main computation part starts here

	//xn[0]; //x
	//xn[1]; //N

	int range = (xn[1]-1)/comm_sz;
	int rRange = range + ((xn[1]-1) % comm_sz);
	int base;

	//printf("%d IS THE CURRENT PROCESS\n ", my_rank);

	if(comm_sz >1){


		if((my_rank > 0) &&  (my_rank < (comm_sz-1)) ){
			start_p2 = MPI_Wtime();

			base = 0;
			int *ra = &range;


			for(i = 0; i < *ra; i++){
				if( ((i+2)+(*ra * my_rank)) % xn[0] == 0){
					base++;
				}
			}

			int* array = malloc(base * sizeof(int));
			base = 0;

			for(i = 0; i < *ra; i++){
				if( ((i+2)+(*ra * my_rank)) % xn[0] == 0){
					array[base] = ((i+2)+(*ra * my_rank)); 
					base++;
				}
			}

			MPI_Send(array, base, MPI_INT, 0, 0, MPI_COMM_WORLD);
			end_p2 = MPI_Wtime();
			//printf("Proc %d  > Elapsed time = %e seconds\n ", my_rank, end_p2 - start_p2);

			//Send time to 0
			ptime = (end_p2 - start_p2);
			MPI_Send(&ptime, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
		}

		else if(my_rank == (comm_sz-1)){
			start_p2 = MPI_Wtime();

			base = 0;
			//If this needs remainder, set ra to &rRange
			int *ra;
			if(rRange != range){
				ra = &rRange;
			}

			else if(rRange == range){
				ra = &range;
			}
			//printf("THIS IS THE rRANGE %d\n ", *ra);

			for(i = 0; i < *ra; i++){
				if( ((i+2)+(*ra * my_rank)) % xn[0] == 0){
					base++;
				}
			}

			MPI_Send(&base, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

			int* array = malloc(base * sizeof(int));
			base = 0;
			
			for(i = 0; i < *ra; i++){
				if( ((i+2)+(*ra * my_rank)) % xn[0] == 0){
					array[base] = ((i+2)+(*ra * my_rank)); 
					base++;
				}
			}		

			MPI_Send(array, base, MPI_INT, 0, 0, MPI_COMM_WORLD);
			end_p2 = MPI_Wtime();

			//send time to 0
			ptime = (end_p2 - start_p2);
			MPI_Send(&ptime, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
		}
		
		else if(my_rank == 0){
			start_p2 = MPI_Wtime();

			base = 0;
			int *ra = &range;

			for(i = 0; i < *ra; i++){
				if( ((i+2)+(*ra * my_rank)) % xn[0] == 0){
					base++;
				}
			}

			int* array = (int*)malloc(base * sizeof(int));
			int a = base;

			//recieve modified base, store as b
			MPI_Recv(&base, 1, MPI_INT, (comm_sz-1), 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			int b = base;
		
			int* array1 = (int*)malloc((a*(comm_sz-1) + b) * sizeof(int));

			base = 0;

			//Start filling big array with Process 0 values
			for(i = 0; i < *ra; i++){
				if( ((i+2)+(*ra * my_rank)) % xn[0] == 0){
					array1[base] = ((i+2)+(*ra * my_rank));
					base++;
				}
			}
			
			//Start filling big array with Process 1 -commsz-1 values values
			MPI_Status status;
			for(i = 1; i < comm_sz-1; i++){
				
				MPI_Recv(array, (a+1), MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				
				for(j = 0; j < a; j++){
					array1[base] = array[j];
					base++;
				}
			}
			
			MPI_Recv(array, b, MPI_INT, comm_sz-1, 0, MPI_COMM_WORLD, &status);
			
			for(j = 0; j < b; j++){
				array1[base] = array[j];
				base++;
			}
		
			//free(array);

			end_p2 = MPI_Wtime();

			time2 = (end_p2 - start_p2);

			for(i =1; i < comm_sz; i++){
				MPI_Recv(&ptime, 1, MPI_INT, i, 4, MPI_COMM_WORLD, &status);
				if(time2 < ptime){
					time2 = ptime;
				}
			}
			
			//printf("THIS IS THE TIME %f\n", time2)
			printf("Time Part 2: %f\n ", time2);
			

			///////////////////////////PART 2 END

			///////////////////////////PART 3 START
			start_p3 = clock();

			strcpy(filename, argv[1]);
			strcat(filename, ".txt");

			if( !(fp = fopen(filename,"w+t")))
			{
			  printf("Cannot create file %s\n", filename);
			  exit(1);
			}

			for(i = 0; i < base; i++){
				if(array1[i]< n){
			    	fprintf(fp,"%d\n ", array1[i]);
				}
			}
			

			fclose(fp);

			end_p3 = clock();
			printf("Time Part 3: %f\n ",(float) (end_p3 - start_p3)/ CLOCKS_PER_SEC);
			free(array1);
		}
	}
	
	else if(comm_sz==1){
		start_p2 = MPI_Wtime();

		base = 0;

		for(i = 2; i < xn[1]+1; i++){
			if( (i) % xn[0] == 0){
				base++;
			}
		}

		int* array = (int*)malloc(base * sizeof(int));
		base = 0 ;

		for(i = 2; i < xn[1]+1; i++){
			if( (i) % xn[0] == 0){
				array[base] = i;
				base++;
			}
		}

		end_p2 = MPI_Wtime();

		printf("Time Part 2: %f\n ", end_p2 - start_p2);


		///////////////////////////PART 3 START
		start_p3 = clock();

		strcpy(filename, argv[1]);
		strcat(filename, ".txt");

		if( !(fp = fopen(filename,"w+t")))
		{
		  printf("Cannot create file %s\n", filename);
		  exit(1);
		}

		for(i = 0; i < base; i++){
			if(array[i]< n){
		    	fprintf(fp,"%d\n", array[i]);
			}
		}
		

		fclose(fp);

		end_p3 = clock();

		printf("Time Part 3: %f\n ",(float) (end_p3 - start_p3)/ CLOCKS_PER_SEC  );


	}

	MPI_Finalize();
	return 0;
}