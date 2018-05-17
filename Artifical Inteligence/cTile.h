#ifndef CLASS_TILE_H
#define CLASS_TILE_H
#include"cBaseNode.h"

class Tile: public BaseNode
{
private:

	vector<int> neigbors;
	char tileValue;

	int iWidth;
	int iHeight;	
	int starttime = NULL;
	int endtime = NULL;
	int iDirtAmount = 0;
	bool bClean = true; 
	bool bVisited = false;
	bool bNeigborsfound = false;
	string sAttributeCode;
	
public:
	//CONSTRUCTORS
	Tile() {}
	Tile(int w, int h)
	{
		iWidth = w;
		iHeight = h;	
	}
	Tile(int size)
	{
		iWidth = size;
		iHeight = size;
	}
	
	
	//CHAR FUNCTIONS
	char getValue()
	{
		return tileValue;

	}
	//INT FUNCTIONS
	int getWidth()
	{
		return iWidth;
	}
	int getHeight()
	{
		return iHeight;
	}
	int getStartTime()
	{
		return starttime;
	}
	int getEndTime()
	{
		return endtime;
	}
	int getDirtyAmmount()
	{
		return iDirtAmount;
	}
	//STRING FUNCTIONS
	string getAttributeCode()
	{
		return sAttributeCode;
	
	}
	//BOOL FUNCTIONS
	bool isClean()
	{
		if (iDirtAmount > 0)
		{
			bClean = false;
		}
		if (iDirtAmount == 0)
			return bClean;
	}
	bool isVisited()
	{
		return this->bVisited;
	}
	bool isNeigborsFound()
	{

		return this->bNeigborsfound;
	}

	
	//VOID FUNCTIONS

	void setWidth          (int           w)
	{
		iWidth = w;
	}
	void setHeight         (int           h)
	{
		iHeight = h;
	}
	void setStartTime      (int        time)
	{
		this->starttime = time;
	}
	void setEndTime        (int        time)
	{
		endtime = time;
	}
	
	void setIsNeigborsFound(bool      found)
	{
		this->bNeigborsfound = found;
	}
	void setIsVisited      (bool          b)
	{
		this->bVisited = b;
	}
	void setClean          (bool          b)
	{
		this->bClean = b;
	}
	void setTileValue      (char          x)
	{
		this->tileValue = x;
	}
	void printTileInfo     (               )
	{
		cout << "\tPOSITION: " << this->getPosX() << ", " << this->getPosY() << ", " << this->getPosZ() << "\n";
		cout << "\t      ID: " << this->getID()<< "\n";
		cout << "\t   Value: " << this->getValue() << "\n\n";
	}
	
	//ACTION FUNCTIONS
	void cleanTile(int cleanAmount)
	{
		if (iDirtAmount > 0)
			iDirtAmount -= cleanAmount;
	}
	void dirtyTile(int  dirtAmount)
	{
		if (iDirtAmount == 0)
			iDirtAmount += dirtAmount;
	}
};
#endif // !CLASS_TILE_H
