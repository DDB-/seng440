#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define N 2
typedef char bool;
#define true 1
#define false 0

/**
 * 	Takes a square matrix
 * 	The function prints the contents of the matrix
 */
void printMatrix( double matrix[N][N] ) {

	int i = 0,
	    j = 0;
	
	for ( i = 0; i < N; ++i ) {

		for ( j = 0; j < N; ++j ) {

			printf( "%f%s", matrix[i][j], (j<N-1)? ", ":"" );
		}

		printf("\n");
	}
}

void printMatrix2( double matrix[2][2] ) {

	int i = 0,
	    j = 0;
	
	for ( i = 0; i < 2; ++i ) {

		for ( j = 0; j < 2; ++j ) {

			printf( "%f%s", matrix[i][j], (j<2-1)? ", ":"" );
		}

		printf("\n");
	}

	printf("\n");
}

/**
 * 	Multiplies two 2x2 matrices, storing the result in a third
 */
void multMatrix( double m1[2][2], double m2[2][2], double target[2][2] ) {

	int i, j, k;

	for ( i = 0; i < 2; ++i ) {
		for ( j = 0; j < 2; ++j ) {

			target[i][j] = 0;
			for ( k = 0; k < 2; ++k ) {
				target[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
}

/**
 * 	Takes a square matrix and diagonalizes it
 */
void diagonalize( double S[N][N] ) {
	
	// declare some chincey variables
	int i = 0,
	    j = 0;

	bool diagonalized = false,
	     printedOut = false;

	for (;;) {

		// check to see whether we're diagonalized
		diagonalized = true;

		for ( i = 0; i < N; ++i ) {
			for ( j = 0; j < N; ++j ) {

				// diagonalized if all off-diagonals are zero
				// TODO: check for ~0 since we're dealing with doubles
				if ( i != j )
					diagonalized &= ( S[i][j] == 0 );
			}
		}

		if ( diagonalized )
			break;

		// find the indicies of the largest off-diagonal
		int maxI = 0, maxJ = 1; // gotta start somewhere

		for ( i = 0; i < N; ++i ) {
			for ( j = 0; j < N; ++j ) {

				if ( i != j && abs(S[i][j]) > abs(S[maxI][maxJ]) ) {

					maxI = i;
					maxJ = j;
				}
			}
		}

		// great. awesome. let's use those values.
		double	mii = S[maxI][maxI],
			mij = S[maxI][maxJ],
			mjj = S[maxJ][maxJ],
			mji = S[maxJ][maxI];

		// calculate rotation angle
		// WHO. THIS SHIT IS BROKE
		double	thetaSum = atan2( mij+mji, mjj-mii ),
			thetaDif = atan2( mij-mji, mjj+mii ),
			thetaL = (thetaSum - thetaDif) / 2,
			thetaR = (thetaSum + thetaDif) / 2;

		// rotate the thing
		double rotLT[2][2] = {{cos(thetaL), -sin(thetaL)}, {sin(thetaL), cos(thetaL)}},
		      rotR[2][2] = {{cos(thetaR), sin(thetaR)}, {-sin(thetaR), cos(thetaR)}},
		      s[2][2] = {{mii, mji}, {mji, mjj}};

		if ( !printedOut ) {

			printf("intermediary matrices!\n");
			printf("rotLT:\n");
			printMatrix2(rotLT);
			printf("rotR:\n");
			printMatrix2(rotR);
		}

		double sPrime[2][2],
		      sDoublePrime[2][2];

		multMatrix( rotLT, s, sPrime );
		multMatrix( sPrime, rotR, sDoublePrime );

		if ( !printedOut ) {

			printMatrix( S );
			printf("\n");
		}

		S[maxI][maxI] = sDoublePrime[0][0];
		S[maxI][maxJ] = sDoublePrime[1][0];
		S[maxJ][maxJ] = sDoublePrime[1][1];
		S[maxJ][maxI] = sDoublePrime[0][1];

		if ( !printedOut ) {

			printMatrix( S );
			printf("\n");
			printedOut = true;
		}
	}
}

int main() {

	double m[N][N]	= {{	1,	2	},
			   {	3,	4	}};

	printMatrix( m );
	printf("\r\n->\r\n\r\n");

	diagonalize( m );
	printMatrix( m );

	return 0;
}
