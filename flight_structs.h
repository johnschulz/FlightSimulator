/*
 * CS61C Summer 2019
 * Name: John Schulz
 * Login: aeg
 */

#ifndef FLIGHT_STRUCTS_H
#define FLIGHT_STRUCTS_H

#include "timeHM.h"

typedef struct flightSys flightSys_t;
typedef struct airport airport_t;
typedef struct flight flight_t;
typedef struct linked linked_t;

struct flightSys {
  // Place the members you think are necessary for the flightSys struct here.
    struct airport *curAirport;
    struct flightSys *next;
    
    
};

struct airport {
  // Place the members you think are necessary for the airport struct here.
    struct flightSys *flightSystem;
    char *airportName;
    struct flight *curFlight;
    struct airport *nextAirport;
    
  
    

    };

struct flight {
  // Place the members you think are necessary for the flight struct here.
    struct airport *dest;
    timeHM_t *departureTime;
    timeHM_t *arrivalTime;
    int flightCost;
    struct flight *nextFlight;
};

#endif

