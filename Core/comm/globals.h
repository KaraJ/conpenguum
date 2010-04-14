#ifndef GLOBALS_H
#define GLOBALS_H

#define BYTE unsigned char
#define UDP_PORT_CLI  9000
#define UDP_PORT_SERV 9003
#define UDP_MAXMSG    100
typedef unsigned char uint8;

//Game Object IDs
#define MAX_CLIENTS	  32 //Maximum number of connected clients on server.
#define MAX_SHOTS_ID  360
#define MAX_PWRUP_ID  501
#define MAX_REAL_OBJECT 1024

//Degree macros
#define RADIANSINDEG    0.017453293 //PI/180
#define DEGREESINRAD    57.295779513 //180/PI
#define DEGTORAD(a)     ((a) * RADIANSINDEG)
#define RADTODEG(a)     ((a) * DEGREESINRAD)


#endif
