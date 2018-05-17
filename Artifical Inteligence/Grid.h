#ifndef CLASS_GRID_H
#define CLASS_GRID_H
#include <iostream>
#include<vector>
#include <fstream>
#include <math.h>
#include <time.h> 
#include<string>
#include "cBaseNode.h"
#include "cTile.h"



using namespace std;

class Grid : public BaseNode
{
private:
	vector<Tile> tiles;
	int col;
	int row;	
	int modulous; 
	int iDirtyAmount = 0;
	float tileGap = 0;
	
public:
	//CONSTRUCTORS
	Grid() {};
	Grid(int x, int y, int z, string fileName, int tilesize)
	{
		this->setPosX(x);
		this->setPosY(y);
		this->setPosZ(z);
		LoadGrid(fileName, tilesize);
	
	}
	Grid(int x, int y, int z)
	{
		setPosition(x, y, z);
	
	}	
	Grid(int x, int y, int z, int tilesize, int gridsize, int percent)
	{	

		
		setPosition(x, y, z);
		modulous = gridsize;

		
		for (int i = 0; i < gridsize*gridsize; i++)
		{


			Tile t(tilesize);

			t.setClean(dirtyChance(percent));

			if (t.isClean() == false)
			{
				t.setTileValue('x');
			}
			else
			{
				t.setTileValue(' ');
			}


			

			
			t.setID(i);
			if (t.getID() > 0)
			{
				t.setPosY(this->getPosY());

				if (i%modulous == 0)
				{					
					t.setPosX(this->getPosX());					
					t.setPosZ(tiles.at(i - gridsize).getPosZ() -tilesize);
				}
				else
				{
					t.setPosX(tiles.at(i - 1).getPosX() + gridsize);
					t.setPosZ(tiles.at(i - 1).getPosZ());					
				}		
			}
			else
			{
				t.setPosition(this->getPosX(), this->getPosY(), this->getPosZ());			
			}

			tiles.push_back(t);
		}	
		
	}
	
	//GRID FUNCTIONS GETTERS AND SETTERS
	vector<float> getGridVectorPos()
	{
		return getVectPos();
	}
	vector<float> getTileVectorPos(int i)
	{
		return tiles.at(i).getVectPos();
	
	}
	int getDirtyAmount()
	{
		return this->iDirtyAmount;
	}
	int getCol()
	{
		return col;
	}
	int getRow()
	{
		return row; 
	}
	int getMod()
	{
		return modulous;
	}
	int getTileGap()
	{
		return tileGap;
	}
	
	bool dirtyChance(int percent)
	{
		//srand(time(NULL));
		int chance = (rand() % 100 + 1);


		if (chance < percent)
		{
			iDirtyAmount += 1;
			return false;

		}
		else
			return true;


	}
	bool isTileNeighborsFound(int id)
	{
		return this->tiles.at(id).isNeigborsFound();
	}

	void setCol(int c)
	{
		col = c;
	}
	void setRow(int r)
	{
		row = r; 
	}
	
	//GRID ACTION FUNCTIONS
	void setTilePosition(Tile &t, int gridsize, int tilesize)
	{
		if (t.getID() > 0)
		{

			t.setPosY(this->getPosY());

			if (t.getID() % modulous == 0)
			{
				t.setPosX(this->getPosX());
				t.setPosZ(tiles.at(t.getID() - gridsize).getPosZ() - tilesize);
			}
			else
			{
				t.setPosX(tiles.at(t.getID() - 1).getPosX() + gridsize);
				t.setPosZ(tiles.at(t.getID() - 1).getPosZ());
			}
		}
		else if (t.getID() <= 0)
		{
			t.setPosition(this->getPosX(), this->getPosY(), this->getPosZ());
		}
		else
		{
			cout << "\n====================================================================\n";
		}


	}
	void consolePrintGrid()
	{
		for (int i = 0; i < modulous*modulous; i++)
		{
			if (i % modulous == 0)
			{
				cout << "\n";
			}

			//cout << "\n";
			cout << "[(" << i;
			cout << ")" << tiles.at(i).getPosX();
			cout << ", " << tiles.at(i).getPosY();
			cout << ", " << tiles.at(i).getPosZ();
			cout << " ]";

		}


	}
	void consolePrintFloorGrid()
	{
		cout << "\n ===================================================\nGRID: \n";
		cout << "Dirty Tiles: " << iDirtyAmount << endl;
		for (int i = 0; i < modulous*modulous; i++)
		{
			if (i % modulous == 0)
			{
				cout << "\n";
			}

			//cout << "\n";
			cout << "[" << tiles.at(i).getValue() << "]";

		}


	}
	void LoadGrid(const string& fileName, int tilesize)
	{
		int x = 0;
		ifstream file;
		file.open((fileName).c_str());

		string line;

		if (file.is_open())
		{
			//cout << "\n\nFILE " << fileName << " is open" << endl;

			while (file.good())
			{
				getline(file, line);

				int linesize = line.size();

				for (int i = 0; i < linesize; i++)
				{
					char currentChar = line.at(i);
					if (currentChar == ' ')
					{
						continue;
					}
					else
					{
						Tile t(tilesize);
						t.setID(x);
						t.setTileValue(currentChar);
						tiles.push_back(t);
						x++;
					}
				}
			}
		}
		else
		{
			cerr << "UNABLE OPEN FILE" << fileName << endl;
		}

		int a_sqrt = sqrt(x);
		int b_sqrt = a_sqrt;
		//cout << x << "<-------------x\n";
		if (a_sqrt == b_sqrt);
		{
			modulous = a_sqrt;
			//cout << modulous << "<-------------Mod\n";
			for (int i = 0; i < x; i++)
			{

				this->setTilePosition(this->tiles.at(i), modulous, tilesize);
				//this->tiles.at(i).printTileInfo();

			}
		}

		cout << "\n GRID SIZE: " << (modulous * modulous) << endl;
		//this->consolePrintGrid();
	}
	void CreateGridSquare(int size, int tilesize, float x, float y)
	{
		this->setPosX(x);
		this->setPosY(y);
		this->setRow(size);
		this->setCol(size);

		int id = 0;
		for (int r = 0; r < this->row; r++)
			for (int c = 0; c < this->col; c++)
			{
				Tile temp;

				temp.setPosition(c, r, 0);
				temp.setID(id);
				temp.setHeight(tilesize);
				temp.setWidth(tilesize);
				id++;
				tiles.push_back(temp);
			}

	
	}
	void decreaseDirtyAmount()
	{
		this->iDirtyAmount -= 1;

	}
	
	
	///////////////////////////////////////TILE FUNCTIONS///////////////////////////////////////////////////
	char  getTileValue     (int id)
	{
		return this->tiles.at(id).getValue();
	}
	float getTilePosX      (int id)
	{
		return this->tiles.at(id).getPosX();
	}
	float getTilePosY      (int id)
	{
		return this->tiles.at(id).getPosY();
	}
	int   getTileWidth     (int id)
	{
		return this->tiles.at(id).getWidth();
	}
	int   getTileHeight    (int id)
	{
		return this->tiles.at(id).getHeight();
	}
	int   getTileID        (int id)
	{
		return this->tiles.at(id).getID();
	}
	bool  isTileClean      (int id)
	{
		return this->tiles.at(id).isClean();

	}
	bool  isTileVisited    (int id)
	{
		return this->tiles.at(id).isVisited();
	}
	bool  isTileNeborsFound(int id)
	{
		return this->tiles.at(id).isNeigborsFound();
	}

	void setTilePosX         (int id, float  x)
	{
		this->tiles.at(id).setPosX(x);	
	}
	void setTilePosY         (int id, float  y)
	{
		this->tiles.at(id).setPosX(y);
	}
	void setTileWidth        (int id, int w)
	{
		tiles.at(id).setWidth(w);
	}
	void setTileHeight        (int id, int h)
	{
		tiles.at(id).setHeight(h);
	}
	void setTileClean        (int id, bool b)
	{
		tiles.at(id).setClean(b);
	}
	void setTileValue        (int id, char val)
	{
		this->tiles.at(id).setTileValue(val);
	}
	void setTileNeigborsFound(int id, bool b)
	{
		this->tiles.at(id).setIsNeigborsFound(b);
	}	
	void setTileVisited      (int id, bool   b)
	{		this->tiles.at(id).setIsVisited(b);   }
	///////////////////////////////////////TILE FUNCTIONS///////////////////////////////////////////////////



};
#endif // !CLASS_GRID_H

