#include<iostream>
#include <string>
#include "Grid.h"
#include "cVaccum.h"


using namespace std;

int main()
{
	srand(time(NULL));
	

	//grid.consolePrintGrid();

	//Grid grid02(0, 0, 0, "GridSmall.txt", 5 );

	//grid02.setTileValue(5, '0');


	bool done = false;
	char answer; 

	while (!done)
	{
		
		int p = NULL;
		int s = NULL;
		int d = NULL;
		bool i = false;
		
		
		
		cout << "\n\nEnter Grid Size: ";
		cin >> s;

		cout << "\n\nEnter Filth Percentage: ";
		cin >> p;

		
		cout << "\n\nDROP VAC AT: ";
		cin >> d;

		cout << "Do You want it to stop if it hits the same tile? [1 = yes, 0 = no]: ";
		cin >> i;
		
		Grid grid(0, 0, 0, s, s, p);
		cout << "\n\n\n=========GRID=============\n Grid Size: " << grid.getMod() << " x " << grid.getMod() << endl;
		
		Vaccum myvac(grid, d, i);
		grid.consolePrintFloorGrid();

		cout << "\n\n=======================================================\n\nTRY AGAIN? :";
		cin >> answer;

			if (answer == 'n' || 'N')
			{
				false;
			}
			else
				done = true;		
	}
	

	

	


}