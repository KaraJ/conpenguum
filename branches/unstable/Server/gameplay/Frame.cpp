#include <iostream> // only used for testing
#include "Frame.h"
#include "general.h"
#include <cstdlib>
#include <QVector2D>
#include <cmath>

using namespace std;

/*-----------------------------------------------------------------------------
--  FUNCTION:   fragShip
--
--  DATE:       February 19, 2010
--
--  REVISIONS:  v1.0
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  fragShip(size_t shipID)
--
--  NOTES:      Removes a ship from play.
--
--  RETURNS:    VOID
--
------------------------------------------------------------------------------*/
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
list<Event> Frame::tick(void){
	list<Event> events = updateShips();
    list<Event> events2 = updateShots();
    events.insert(events.end(), events2.begin(), events2.end());
    ++frameTimer;
    return events;
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
    ship->active = true;
    ship->position = map.getSpawn(0, SHIPSIZE);
    map.add(ship, ship->position, SHIPSIZE);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   updateShipsSHIPRADIUS
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
list<Event> Frame::updateShips(void)
{
    double dist;
	QVector2D oldPosition;
	QVector2D newVector;
	list<Event> events;

    for(size_t i = 0; i < MAX_CLIENTS; ++i)
    {
    	Ship *currShip = listShip[i];

        if(currShip != 0)
        {
        	if (currShip->active)
        	{
				oldPosition.setX(currShip->position.x());
				oldPosition.setY(currShip->position.y());

				//TODO: Iterating over all shots is inefficient, this will be changed once testing is complete.
				/*for (list<Shot>::iterator it = listShot.begin(); it != listShot.end(); ++it)
				{
					QVector2D pos = it->getPosition();

				}*/

				if (currShip->vector.x() != 0)
				{
					dist = map.canMove(currShip->position, false, SHIPSIZE, currShip->vector.x());

					if((currShip->vector.x() > 0 && dist < 0) || (currShip->vector.x() < 0 && dist > 0))
					{
						currShip->vector.setX(-currShip->vector.x());

						if (currShip->shield > 0) //Hit a wall, take damage
							currShip->shield -= 10;
						else if (currShip->health > 0)
							currShip->health -= 10;
						if (currShip->health <= 0)
						{
							currShip->health = 0;
							Event t;
							t.type = Event::ET_DEATH;
							t.killed = currShip->id;
							events.push_back(t);
							fragShip(currShip->id);
						}
					}

					currShip->position.setX(currShip->position.x() + dist);
				}

				if (currShip->vector.y() != 0)
				{
					dist = map.canMove(currShip->position, true, SHIPSIZE, currShip->vector.y());

					if((currShip->vector.y() > 0 && dist < 0) || (currShip->vector.y() < 0 && dist > 0))
					{
						currShip->vector.setY(-currShip->vector.y());

						if (currShip->shield > 0) //Hit a wall, take damage
							currShip->shield -= 10;
						else if (currShip->health > 0)
							currShip->health -= 10;
						if (currShip->health <= 0)
						{
							currShip->health = 0;
							Event t;
							t.type = Event::ET_DEATH;
							t.killed = currShip->id;
							events.push_back(t);
							fragShip(currShip->id);
						}
					}

					currShip->position.setY(currShip->position.y() + dist);
				}

				map.remove(currShip, oldPosition, SHIPSIZE);
				map.add(currShip, currShip->position, SHIPSIZE);

				if(currShip->actionMask.isAccelerating()) // thrust forward
					newVector = currShip->vector + rotVelToVec(currShip->rotation * 2, VELOCITY_THRUST);

				if(currShip->actionMask.isDecelerating()) // thrust reverse
					newVector = currShip->vector + rotVelToVec(currShip->rotation * 2, -VELOCITY_THRUST);

				if(currShip->actionMask.isDecelerating() || currShip->actionMask.isAccelerating())
				{
					//currently, if you are at max speed your direction doesn't change because of this
					//fixing -- JT
					double magnitude = newVector.lengthSquared();

					if(magnitude > VELOCITY_MAX)
					{
						newVector /= magnitude/VELOCITY_MAX;
					}
					currShip->vector = newVector;
				}

				if(currShip->actionMask.isTurningRight()) // turn right
				{
					currShip->rotation -= ROTATION_RATE;
					if (currShip->rotation < 0)
						currShip->rotation = 180 + currShip->rotation;
				}

				if(currShip->actionMask.isTurningLeft()) // turn left
					currShip->rotation = (currShip->rotation + ROTATION_RATE) % 180;

				if(currShip->shotCooldown > 0)
					currShip->shotCooldown--;

				if(currShip->shotCooldown == 0 && currShip->actionMask.isFiring())
				{
					QVector2D spawnVec, shotVec;
					spawnVec = rotVelToVec(currShip->rotation * 2, SHOTSPAWNRAD);
					shotVec =  rotVelToVec(currShip->rotation * 2, VELOCITY_SHOT);
					Shot shot(currShip->position.x() + spawnVec.x(), currShip->position.y()
						+ spawnVec.y(), shotVec.x(), shotVec.y(), currShip->getNextShotID(), (frameTimer + 60));
					addShot(shot);
					map.add(&shot, shot.position);
					currShip->shotCooldown = 15;
				}

				if (currShip->shieldCooldown == 0)
				{
					if (currShip->shield < 100 && currShip->active)
						currShip->shield = MIN(100, (currShip->shield + 10));

					currShip->shieldCooldown = 150;
				}
				else
					currShip->shieldCooldown--;

				for (list<NewtObject>::iterator it = listPwrup.begin(); it != listPwrup.end(); ++it)
				{
					QVector2D pos = it->getPosition();
					if (abs(currShip->position.x() - pos.x()) < SHIPRADIUS && abs(currShip->position.y() - pos.y()) < SHIPRADIUS)
					{
						if (currShip->health == 100)
							break;
						currShip->health = MIN(100, (currShip->health + 50));
						listPwrup.erase(it);
						break;
					}
				}
        	}
        	else
        	{
        		if (--currShip->deathCooldown == 0)
        		{
        			currShip->active = true;
        			currShip->health = 100;
        			currShip->shield = 100;
        		}
        	}
        }
    }
    return events;
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
list<Event> Frame::updateShots(void)
{
	QVector2D oldPos, oldShipPos;
    list<Shot>::iterator it;
    list<Ship*>::iterator itr;
    list<Ship*> shiplist;
    list<Event> events;

    for(it = listShot.begin(); it != listShot.end();)
    {
    	oldPos = it->position;
    	if(frameTimer == it->deathTime)
    	{
    		map.remove(&(*it), it->position);
    		it = listShot.erase(it);
    		continue;
    	}
		it->position += it->vector;

        if(map.isWall(it->position))
        {
        	map.remove(&(*it), oldPos);
        	it = listShot.erase(it);
        	continue;
        }

		if(map.hasShip(oldPos))
		{
			Ship *currShip;
            shiplist = map.ships(oldPos);
			for(itr = shiplist.begin(); itr != shiplist.end(); ++itr)
			{
				currShip = *itr;
			    if(currShip->active && dist2Points((*itr)->position, oldPos) < SHIP_HIT_DIST)
			    {
					if (currShip->shield >= 40)
						currShip->shield -= 40;
					else if (currShip->shield > 0)
					{
						currShip->shield -= 40;
						currShip->health += currShip->shield;
						currShip->shield = 0;
					}
					else
						currShip->health -= 40;
					if (currShip->health <= 0)
					{
						currShip->health = 0;//DEAD
						Event t;
						t.type = Event::ET_KILL;
						t.killer = (it->getID() - 32) / 10;
						t.killed = currShip->id;
						events.push_back(t);
						fragShip(currShip->id);
					}
					it = listShot.erase(it);
					continue;
				}
			}
		}
        map.move(&(*it++), oldPos, it->position);
    }
    return events;
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
--  INTERFACE:  dist2Points(QVector2D point1, QVector2D point2)
--
--  NOTES:      Given two points, returns the squared distance between them. For
--              testing only.
--
--  RETURNS:    Int value of the distance
--
------------------------------------------------------------------------------*/
int Frame::dist2Points(QVector2D point1, QVector2D point2)
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

/*-----------------------------------------------------------------------------
--  FUNCTION:   fragShip
--
--  DATE:       February 19, 2010
--
--  REVISIONS:  v1.0
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  fragShip(size_t shipID)
--
--  NOTES:      Removes a ship from play.
--
--  RETURNS:    VOID
--
------------------------------------------------------------------------------*/
vector<UpdateObject> Frame::ListShip2listUpdateObject()
{
    vector<UpdateObject> udList;
    for (size_t i = 0; i < MAX_CLIENTS; ++i)
    {
		if (listShip[i] != 0 && listShip[i]->active)
		{
			UpdateObject uo(listShip[i]->actionMask);
			uo.setRotation(listShip[i]->rotation);
            uo.setPosition(listShip[i]->position.toPoint());
			uo.setHealth(listShip[i]->health);
			uo.setShield(listShip[i]->shield);
			udList.push_back(uo);
			uo.print();
		}
	}
    for(list<Shot>::iterator it = listShot.begin(); it != listShot.end(); ++it)
    {
        UpdateObject uo(it->id);
		uo.setPosition(it->position.toPoint());
		udList.push_back(uo);
    }
    for(list<NewtObject>::iterator it = listPwrup.begin(); it != listPwrup.end(); ++it)
	{
		UpdateObject uo(it->id);
		uo.setPosition(it->position.toPoint());
		udList.push_back(uo);
	}
    return udList;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:
--
--  DATE:
--
--  REVISIONS:
--
--  DESIGNER:
--
--  PROGREMMER:
--
--  INTERFACE:
--
--  NOTES:
--
--  RETURNS:
--
------------------------------------------------------------------------------*/
void Frame::updateClientActions(vector<ClientAction> clientActions)
{
	for (size_t i = 0; i < clientActions.size(); ++i)
		listShip[clientActions[i].getObjectId()]->applyActionMask(clientActions[i]);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   fragShip
--
--  DATE:       February 19, 2010
--
--  REVISIONS:  v1.0
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  fragShip(size_t shipID)
--
--  NOTES:      Removes a ship from play.
--
--  RETURNS:    VOID
--
------------------------------------------------------------------------------*/
void Frame::fragShip(size_t shipID){
    Ship *ship = getShip(shipID);
    ship->active = false;
    ship->deathCooldown = 150;
    map.remove(ship, ship->position, SHIPSIZE);
}
