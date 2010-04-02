#include <iostream> // only used for testing
#include "Frame.h"
#include "general.h"
#include <cstdlib>

using namespace std;


Frame::Frame(QString filename): frameTimer(0), map(QString(filename))
{
	for (size_t i = 0; i < MAX_CLIENTS; ++i)
		listShip[i] = 0;
}
/*-----------------------------------------------------------------------------
--  FUNCTION:   tick
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.2 - Calls updateShots and udateShips before incrementing the
--                     frame counter.
--              v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  tick(void)
--
--  NOTES:      Advances the frame one tick.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::tick(void){
    updateShots();
    updateShips();
    ++frameTimer;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   addShip
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  addShip(void)
--
--  NOTES:      Adds a ship to the ship list. Useful for adding new players.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::addShip(size_t clientID)
{
    // adds a ship to the ship list
	listShip[clientID] = new Ship(clientID);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   spawnShot
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  spawnShot(shot newShot)
--
--  NOTES:      Adds a shot to the shot list. Useful for when players shoot.
--              TASK: spawnShot should take the ship firing and spawn a shot
--                    according to the ships data, like rotation and typesvn checkout
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::addShot(Shot newShot){
    // adds a shot to the shot list
    listShot.push_back(newShot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   getShip
--
--  DATE:       March 14, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Ship getShip(int shipID)
--
--  NOTES:      returns the ship with the ID equal to shipID.
--  RETURNS:    Ship
--
------------------------------------------------------------------------------*/
Ship* Frame::getShip(size_t shipID)
{
    for(size_t i = 0; i < MAX_CLIENTS; ++i)
    {
        if(listShip[i] != 0 && listShip[i]->getID() == shipID)
            return listShip[i];
    }

    return 0;
}

void Frame::removeShip(size_t clientID)
{
    for(size_t i = 0; i < MAX_CLIENTS; ++i)
    {
        if(listShip[i] != 0 && listShip[i]->getID() == clientID)
        {
        	delete listShip[i];
        	listShip[i] = 0;
            return;
        }
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   spawnShip
--
--  DATE:       March 14, 2010svn checkout 
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  spawnShip(int shipID)
--
--  NOTES:      Makes a ship active. Is will be spawned at a valid spawn point
--              and able to make actions as well as be destroyed.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::spawnShip(size_t shipID)
{
    Ship *ship = getShip(shipID);
    QPoint spawnPoint(100,100); // map function to return a safe spawn point
    ship->active = true;
    ship->position = spawnPoint;
    map.add(ship, ship->position, 50);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   updateShips
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.2 - Untested collision.
--              v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  updateShips(void)
--
--  NOTES:      Updates all ships positions using their vectors.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::updateShips(void)
{
    int dist;
	QPoint oldPosition;
    for(size_t i = 0; i < MAX_CLIENTS; ++i)
    {
        if(listShip[i] != 0 && listShip[i]->active)
        {
		oldPosition =  listShip[i]->position;
            if (listShip[i]->vector.x() != 0)
            {
                dist = map.canMove(listShip[i]->position, false, SHIPSIZE, listShip[i]->vector.x());
                if(abs(dist) < abs(listShip[i]->vector.x()))
                {
                	listShip[i]->vector.setX(-(listShip[i]->vector.x()));
                	//Hit a wall, take damage
					if (listShip[i]->shield > 0)
						listShip[i]->shield -= 10;
					else if (listShip[i]->health > 0)
						listShip[i]->health -= 10;
					//-----------------------
                }
                listShip[i]->position.setX(listShip[i]->position.x() + dist);
                cout << "X:" << oldPosition.x() << "->" <<  listShip[i]->position.x() << "|" << dist << endl;
            }


            if (listShip[i]->vector.y() != 0)
            {
                dist = map.canMove(listShip[i]->position, true, SHIPSIZE, listShip[i]->vector.y());
                if(abs(dist) < abs(listShip[i]->vector.y()))
                {
                	listShip[i]->vector.setY(-(listShip[i]->vector.y()));
                	//Hit a wall, take damage
                	if (listShip[i]->shield > 0)
						listShip[i]->shield -= 10;
					else if (listShip[i]->health > 0)
						listShip[i]->health -= 10;
					//-----------------------
                }
                listShip[i]->position.setY(listShip[i]->position.y() + dist);
            }
	
		map.move(listShip[i], oldPosition, listShip[i]->position, 50);
			
			QPoint newVector;
			if(listShip[i]->actionMask.isAccelerating()) // thrust forward
				newVector = listShip[i]->vector + rotVelToVec(listShip[i]->rotation * 2, VELOCITY_THRUST);

			if(listShip[i]->actionMask.isDecelerating()) // thrust reverse
			{
				// '-=' on a negative vector was causing more acceleration - changed to +=
				newVector = listShip[i]->vector + rotVelToVec(listShip[i]->rotation * 2, -VELOCITY_THRUST);
			}
			if(listShip[i]->actionMask.isDecelerating() || listShip[i]->actionMask.isAccelerating()){
			if(VECTORMAGNITUDE(newVector) < VELOCITY_MAX)
			{
				listShip[i]->vector = newVector;
			}
			}
			
			if(listShip[i]->actionMask.isTurningRight()) // turn right
			{
				listShip[i]->rotation -= ROTATION_RATE;
				if (listShip[i]->rotation < 0)
					listShip[i]->rotation = 180 + listShip[i]->rotation;
			}

			if(listShip[i]->actionMask.isTurningLeft()) // turn left
			{
				listShip[i]->rotation = (listShip[i]->rotation + ROTATION_RATE) % 180;
			}
			if(listShip[i]->shotCooldown > 0){
				listShip[i]->shotCooldown--;
                        }
                        if(listShip[i]->shotCooldown == 0){
				if(listShip[i]->actionMask.isFiring())
				{
					QPoint spawnVec, shotVec;
					spawnVec = rotVelToVec(listShip[i]->rotation * 2, SHIPRADIUS);
					shotVec =  rotVelToVec(listShip[i]->rotation * 2, VELOCITY_SHOT);
					Shot shot(listShip[i]->position.x() + spawnVec.x(), listShip[i]->position.y()
						+ spawnVec.y(), shotVec.x(), shotVec.y(), listShip[i]->getNextShotID(), (frameTimer + 60));
					addShot(shot);
					map.add(&shot, shot.position);
					listShip[i]->shotCooldown = 30;
				}
			}
        }
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   updateShots
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--				v0.2 - added deathTimer for shots - March 27, 2010		
--				v0.3 - added wall detection for shots - March 27, 2010	
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  updateShots(void)
--
--  NOTES:      Updates all shots positions using their vectors. This is done in
--              frame because it has access to the Map and the Shot which both
--              need to be updated.
--
--  RETURNS:    void
------------------------------------------------------------------------------*/
void Frame::updateShots(void)
{
	QPoint oldPos;
    list<Shot>::iterator it;

    for(it = listShot.begin(); it != listShot.end(); ++it)
    {
    	oldPos = it->position;
    	if(frameTimer == it->deathTime)
    	{
    		map.remove(&(*it), it->position);
    		listShot.erase(it);
    		return;
    	}

		it->position += it->vector;

        if(map.isWall(it->position))
        {
        	map.remove(&(*it), oldPos);
        	listShot.erase(it);
        	return;
        }

        map.move(&(*it), oldPos, it->position);
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   printShip
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  printShips(void)
--
--  NOTES:      **FOR TESTING** Prints the positions of all the ships.
--
--  FORMAT:     "<id>: <x>,<y>"
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::printShips(void)
{
    int i;
    for(i = 0; i != 31; ++i){
		if(listShip[i] != NULL){		
		    cout << listShip[i]->id << ": P" << listShip[i]->position.x()
		        << ',' <<  listShip[i]->position.y() << " V" << listShip[i]->vector.x()
		        << ',' <<  listShip[i]->vector.y() <<(listShip[i]->active?" a":" d") <<
            " r" << listShip[i]->rotation << endl;
		}
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   dist2Points
--
--  DATE:       February 19, 2010
--
--  REVISIONS:  v0.1 - For testing only
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  dist2Points(QPoint point1, QPoint point2)
--
--  NOTES:      Given two points, returns the squared distance between them. For
--              testing only.
--
--  RETURNS:    Int value of the distance
--
------------------------------------------------------------------------------*/
int Frame::dist2Points(QPoint point1, QPoint point2)
{
    return (point1.x()-point2.x())*(point1.x()-point2.x()) +
            (point1.y()-point2.y())*(point1.y()-point2.y());
}

/**
UpdateObject getObjectObservers(int objectID, list<int> observers){
    UpdateObject uo;
    
    for(int i = 0; i < MAX_CLIENTS; ++i){
        if(listShip[i] != 0){
            if((listShip[i]->position.x()+562>objectId.pos.x && listShip[i]->position.x()-562<objectID.pos.x) && (listShip[i]->position.y()+434>objectId.pos.y && listShip[i]->position.y()-434<objectID.pos.y)){
                observers.push_back(objectID);
            }
        }
    }
        
}

UpdateObject getShipObservers(int shipID, list<int> observers){
    UpdateObject uo;
    
    for(int i = 0; i < MAX_CLIENTS; ++i){
        if(listShip[i] != 0){
            if((listShip[i]->position.x()+562>shipID.pos.x && listShip[i]->position.x()-562<shipID.pos.x) && (listShip[i]->position.y()+434>shipID.pos.y && listShip[i]->position.y()-434<objectID.pos.y)){
                observers.push_back(objectID);
            }
        }
    }
}
**/

vector<UpdateObject> Frame::ListShip2listUpdateObject()
{
    vector<UpdateObject> udList;
    list<Shot>::iterator it;
    for (size_t i = 0; i < MAX_CLIENTS; ++i)
    {
		if (listShip[i] != 0)
		{
			UpdateObject uo(listShip[i]->actionMask);
			uo.setRotation(listShip[i]->rotation);
			uo.setPosition(listShip[i]->position);
			uo.setHealth(listShip[i]->health);
			uo.setShield(listShip[i]->shield);
			udList.push_back(uo);
			uo.print();
		}
	}
    
    
    for(it = listShot.begin(); it != listShot.end(); ++it){
        UpdateObject uo(it->id);
		uo.setPosition(it->position);
		udList.push_back(uo);
    }

    return udList;
}

/**
NEEDS COMMENTS
**/
void Frame::updateClientActions(vector<ClientAction> clientActions)
{
	for (size_t i = 0; i < clientActions.size(); ++i)
		listShip[clientActions[i].getObjectId()]->applyActionMask(clientActions[i]);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   printShots
--
--  DATE:       March 27, 2010
--
--  REVISIONS:  v0.1 - Ships can shoot now with proper bullet spawn position
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  printShots(void)
--
--  NOTES:      **FOR TESTING** Prints the positions of all the ships.
--
--  FORMAT:     "<id>: <x>,<y>"
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::printShots(void)
{
    std::list<Shot>::iterator it;
    for(it = listShot.begin(); it != listShot.end(); it++){		
		    cout << "P" << it->position.x()
		        << ',' <<  it->position.y() << " V" << it->vector.x()
		        << ',' <<  it->vector.y() << endl;
    }
}

