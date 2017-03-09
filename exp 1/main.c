#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
/* I use "define" for don't use stdbool.h library */

void transmitSystem(int **, int, double *, int);		/* function prototypes */
int generateRandomCellRowAndColumn(int **, int);
void transmitWater(int **, int, int, int);
void closeAllCells(int **, int);
void displayLastVersionOfGrid(FILE *, int **, int);
void calculateAndDisplayMeanAndStandartDeviation(FILE *, double *, int);
double squareRootDoubleNumber(double);

int main(int argc, char *argv[]){

    int gridSize = atoi(argv[1]);							/* definitions */
    int numberOfIndependentExperiment = atoi(argv[2]);
    int i;
    int **cells;
    double *fractionOfOpenCellsArray = malloc(numberOfIndependentExperiment * sizeof(double));
    FILE *outputFile;

    outputFile = fopen("output.txt","w");

    if(outputFile){

		cells = calloc(gridSize, sizeof(int *));

		for(i=0; i<gridSize; i++){

			cells[i] = calloc(gridSize, sizeof(int ));		/* because of using "calloc", all cells is closed automatically */
		}

        for(i=0; i<numberOfIndependentExperiment; i++){ 	/* this loop for T value */

			transmitSystem(cells, gridSize, fractionOfOpenCellsArray, i);	/* i is fractionOfOpenCellsArrayIndex */

            if(i != numberOfIndependentExperiment-1)
                closeAllCells(cells, gridSize);

        }

        displayLastVersionOfGrid(outputFile, cells, gridSize);

        calculateAndDisplayMeanAndStandartDeviation(outputFile, fractionOfOpenCellsArray, numberOfIndependentExperiment);

	}

	free(cells);
	free(fractionOfOpenCellsArray);
    fclose(outputFile); /* when program is completed, close output file */

    return 0;
} /* end of main function */

/* this function using Monte Carlo Approach rule */
void transmitSystem(int **cells, int gridSize, double *fractionOfOpenCellsArray, int fractionOfOpenCellsArrayIndex){

    int isSystemTransmit = 0;
    int i, j;
    int randomCellRow, randomCellColumn, randomCellRowAndColumn;
    int totalOfOpenCells = 0;

    while(isSystemTransmit == 0){	/* repeat until system transmit */

        randomCellRowAndColumn = generateRandomCellRowAndColumn(cells, gridSize);		/* assign randomCellColumn and randomCellRow by generateRandomCellRowAndColumn */
        randomCellRow = randomCellRowAndColumn / gridSize;
        randomCellColumn = randomCellRowAndColumn % gridSize;

        cells[randomCellRow][randomCellColumn] = 1;		/* open cell that generate by random */

        if(randomCellRow == 0){								/* if cell is top of grid then make full open cell so transmit water in cell */
            cells[randomCellRow][randomCellColumn] = 2;
        }

        for(i=0; i<gridSize; i++){			/* control all cells */

            for(j=0; j<gridSize; j++){

                if(cells[i][j] == 2){		/* call transmitWater function for each full open cells */

                    transmitWater(cells, gridSize, i, j);

                }

            }

        }

        for(i=gridSize-1, j=0; j<gridSize; j++){	/* control for system transmit */
            if( cells[i][j] == 2 )
                isSystemTransmit = 1;
        }

    } /* end while */

    for(i=0; i<gridSize; i++){			/* When system transmit, calculate total of open cells */

        for(j=0; j<gridSize; j++){

            if( cells[i][j] != 0 )
                totalOfOpenCells++;

        }

    }

	/* divide totalOfOpenCells to total cells and assign dynamic array according to index */
    *(fractionOfOpenCellsArray+fractionOfOpenCellsArrayIndex) = (double)totalOfOpenCells / (double)(gridSize*gridSize);

} /* end of transmitSystem function */

/* this function generate random number*/
int generateRandomCellRowAndColumn(int **cells, int gridSize){

    int randomRow = rand() % gridSize;				/* generate random two number for row and column */
    int randomColumn = rand() % gridSize;			/* mod according to gridSize so generated random number between 0 and gridSize-1 */

    if(cells[randomRow][randomColumn] == 0){		/* if these random numbers is not generated again then return number */

        return (randomRow*gridSize+randomColumn);
    }
    else{											/* else call generateRandomCellRowAndColumn again */

        generateRandomCellRowAndColumn(cells, gridSize);
    }

} /* end of generateRandomCellRowAndColumn function */

/* this function transmit water in cells */
void transmitWater(int **cells, int gridSize, int row, int column){

    if( row+1 <= gridSize-1 && cells[row+1][column] == 1 ){ 	/* if bottom of cell is inside limit of grid and open cell */

        cells[row+1][column] = 2;
        transmitWater(cells, gridSize, row+1, column);		/* call transmitWater for bottom cells because bottom cell is full open cell */

    }

    if( column+1 <= gridSize-1 && cells[row][column+1] == 1 ){	/* if right of cell is inside limit of grid and open cell */

        cells[row][column+1] = 2;
        transmitWater(cells, gridSize, row, column+1);		/* call transmitWater for right cells because right cell is full open cell */

	}

    if( column-1 >= 0 && cells[row][column-1] == 1 ){			/* if left of cell is inside limit of grid and open cell */

		cells[row][column-1] = 2;
		transmitWater(cells, gridSize, row, column-1);		/* call transmitWater for left cells because left cell is full open cell */

	}

    if( row-1 >= 0 && cells[row-1][column] == 1 ){ 			/* if top of cell is inside limit of grid and open cell */

		cells[row-1][column] = 2;
		transmitWater(cells, gridSize, row-1, column);		/* call transmitWater for top cells because top cell is full open cell */

	}

} /* end of transmitWater function */

/* this function for close after system transmit except for last transmit */
void closeAllCells(int **cells, int gridSize){

    int i, j;

    for(i=0; i<gridSize; i++){

        for(j=0; j<gridSize; j++){

            cells[i][j] = 0;

        }

    }

} /* end of closeAllCells function */

/* this function display last version of grid in output.txt file */
void displayLastVersionOfGrid(FILE *outputFile, int **cells, int gridSize){

    int i, j;

    for(i=0; i<gridSize; i++){

        for(j=0; j<gridSize; j++){

            fprintf(outputFile, "%d ", cells[i][j]);
        }

        fprintf(outputFile, "\n");

    }

    fprintf(outputFile, "\n");

} /* end of displayLastVersionOfGrid function */

/* this function get fractionOfOpenCellsArray and index */
void calculateAndDisplayMeanAndStandartDeviation(FILE *outputFile, double *fractionOfOpenCellsArray, int numberOfIndependentExperiment){

    double mean, standartDeviation, squareOfStandartDeviation;
    double sumOfFractionOfOpenCellsArray = 0.0, sumOfSquareOfFractionOfOpenCellsSubtractionMean = 0.0;
    int i;

    for(i=0; i<numberOfIndependentExperiment; i++){
        sumOfFractionOfOpenCellsArray += *(fractionOfOpenCellsArray+i);
    }

    mean = sumOfFractionOfOpenCellsArray / numberOfIndependentExperiment;

    for(i=0; i<numberOfIndependentExperiment; i++){
        sumOfSquareOfFractionOfOpenCellsSubtractionMean += ( *(fractionOfOpenCellsArray+i)-mean )*( *(fractionOfOpenCellsArray+i)-mean );
    }

    squareOfStandartDeviation = sumOfSquareOfFractionOfOpenCellsSubtractionMean / (numberOfIndependentExperiment-1);

    standartDeviation = squareRootDoubleNumber(squareOfStandartDeviation);

    fprintf(outputFile, "mean()     = %.7lf\n", mean);	/* display mean and standartDeviation in output.txt file */
    fprintf(outputFile, "stddev()	= %.7lf\n", standartDeviation);

} /* end of calculateAndDisplayMeanAndStandartDeviation function */

/* this function for calculate square root of standart deviation without use math.h library */
double squareRootDoubleNumber(double doubleNumber){
	/* reference http://www.geeksforgeeks.org/square-root-of-a-perfect-square/ */
    double tempDoubleNumber = doubleNumber;
    double squareRootOfDoubleNumber = 1.0;
    double accuracyLevel = 0.000001; /* accuracy of result connected accuracyLevel so accuracyLevel is less then result is so true */
    double temp;

    while(1){ /* calculate square root */
        temp = tempDoubleNumber/squareRootOfDoubleNumber - squareRootOfDoubleNumber;
        if(temp < 0) /* if doubleNumber is less than 1.0 */
            temp = temp*(-1);

        if(temp > accuracyLevel){
            squareRootOfDoubleNumber = (squareRootOfDoubleNumber+tempDoubleNumber/squareRootOfDoubleNumber)/2.0;
        }else
            break;
    }

    return squareRootOfDoubleNumber;

} /* end of squareRootDoubleNumber function */

