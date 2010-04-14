#ifndef SHIPTYPE_H
#define SHIPTYPE_H

class ShipType
{
	public:
	enum Types
	{
		JVSHIP = 0,
		LVSHIP,
		NWSHIP,
		SHSHIP,
		SPSHIP,
		TESHIP,
	    WARBIRD,
	    WESHIP,

	    NUMSHIPS
	};
	static std::string getShipString(int id)
	{
		switch (id)
		{
		case 0: return "jvship";
		case 1: return "lvship";
		case 2: return "nwship";
		case 3: return "shship";
		case 4: return "spship";
		case 5: return "teship";
		case 6: return "wbship";
		case 7: return "weship";
		default: return "wbship";
		}
	}
	static int getShipId(std::string name)
	{
		if (name == "jvship")
			return 0;
		else if (name == "lvship")
			return 1;
		else if (name == "nwship")
			return 2;
		else if (name == "shship")
			return 3;
		else if (name == "spship")
			return 4;
		else if (name == "teship")
			return 5;
		else if (name == "wbship")
			return 6;
		else //if (name == "weship")
			return 7;
	}
	/*void b1Clicked(){selectedShip = "jvship";}
	void b2Clicked(){selectedShip = "lvship";}
	void b3Clicked(){selectedShip = "nwship";}
	void b4Clicked(){selectedShip = "shship";}
	void b5Clicked(){selectedShip = "spship";}
	void b6Clicked(){selectedShip = "teship";}
	void b7Clicked(){selectedShip = "wbship";}
	void b8Clicked(){selectedShip = "weship";}*/
};

#endif
