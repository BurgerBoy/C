#include<stdio.h>
#include<string.h>

int main(int argc, char **argv){
	
	FILE *f = fopen(argv[2], "r");
	
	char *a = argv[2];
	strcat(a, ".out");

	FILE *f2 = fopen(a, "w");

	//FILE *fo = fopen(*argv[2] + ,"a");
	int generations; 


	//Initialize the emptys
	int cell[5][5];
	int cellCopy[5][5];
	int i, j, k, count;
	sscanf(argv[1], "%d", &generations);



	for(i=0; i<5; i++) {
		for(j=0;j<5;j++) {
			fscanf(f, "%d", &cell[i][j]);
		}
	}


	//Build new generation from old generation
	for(k = 0; k < generations; k++){
		for(i=0; i<5; i++) {
			for(j=0;j<5;j++) {
				if (cell[i][j] == 1){
					count = 0;
					
					switch(i){
						
						case 0:
							if(j==0){
								if(cell[i][j+1] == 1){
									count++;
								}
								
								if(cell[i+1][j] == 1){
									count++;
								}
								
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j==4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
							
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}

								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j > 0 && j < 4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}
								//Down Right
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}
							break;
						
						case 4:
							if(j==0){
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								
								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j==4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
							
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}

								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j > 0 && j < 4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								
								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}
							break;

						default :
							if(j==0){
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Right
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j==4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}	
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}

								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j > 0 && j < 4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}
								//Down Right
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count== 2 || count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count < 2 || count > 3){
									cellCopy[i][j] = 0;
								}
							}
							break;
			
					}
				} 

				else{
					count = 0;
					
					switch(i){
						
						case 0:
							if(j == 0){
								if(cell[i][j+1] == 1){
									count++;
								}
								
								if(cell[i+1][j] == 1){
									count++;
								}
								
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count == 3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j == 4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
							
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}

								if(count == 3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j > 0 && j < 4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}
								//Down Right
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count == 3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}
							break;
						
						case 4:
							if(j==0){
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								
								if(count == 3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j==4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
							
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}

								if(count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j > 0 && j < 4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								
								if(count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}
							break;

						default :
							if(j==0){
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Right
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j==4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}	
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}

								if(count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}

							else if(j > 0 && j < 4){
								//Left
								if(cell[i][j-1] == 1){
									count++;
								}
								//Right
								if(cell[i][j+1] == 1){
									count++;
								}
								//Up
								if(cell[i-1][j] == 1){
									count++;
								}
								//Up Left
								if(cell[i-1][j-1] == 1){
									count++;
								}
								//Up Right
								if(cell[i-1][j+1] == 1){
									count++;
								}
								//Down
								if(cell[i+1][j] == 1){
									count++;
								}
								//Down Left
								if(cell[i+1][j-1] == 1){
									count++;
								}
								//Down Right
								if(cell[i+1][j+1] == 1){
									count++;
								}
								
								if(count ==3){
									cellCopy[i][j] = 1;
								}
								else if(count != 3){
									cellCopy[i][j] = 0;
								}
							}
							break;
			
					}
				}

			}
		}
		//Copy new generation over old generation
		for(i=0; i<5; i++) {
			for(j=0;j<5;j++) {
				cell[i][j] = cellCopy[i][j];
			}
		}
	}
	//cell = cellCopy for loop to set orignal equal to copy

//Display elements
   for(i=0; i<5; i++) {
      for(j=0;j<5;j++) {
        fprintf(f2, "%d ", cell[i][j]);
            
        if(j==4){
         	fprintf(f2, "\n");
         }
      }
   }
   fclose(f);
   fclose(f2);
   return 0;
}