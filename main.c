#include <stdio.h>
#include <time.h>

int main(void) {
	char input = '\O';
	int count = 0;
	printf("Enter input:\t");
	//Testing button input
	while (input != 'z') {

		scanf_s("%c", &input);

		switch (input) {

		case 'a': 
			printf("\nOption 1");
			count = 1;
			printf("\n%d\n", count);
			break;
		
		case 's': 
			printf("\nOption 2");
			count = 2;
			printf("\n%d\n", count);
			break;
		
		case 'd': 
			printf("\nOption 3");
			count = 3;
			printf("\n%d\n", count);
			break;
		
		//default:
			//printf("\nInvalid input, try again");
			//break;
		}

		if (input == 'g') {
			switch (count) {

			case 1:
				printf("\nMp3 player selected");
				break;

			case 2:
				printf("\nPhoto Galelry Selected");
				break;
			
			case 3:
				printf("\nGame Selected\n");
				game();
				break;

			default:
				printf("\nNothing selected...");
				break;
			}
		}
	}
}