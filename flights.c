/*
 * CS61C Summer 2019
 * Name: John Schulz
 * Login: aeg
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "flight_structs.h"
#include "timeHM.h"

/*
 *  This should be called if memory allocation failed.
 */
static void allocation_failed(void) {
  fprintf(stderr, "Out of memory.\n");
  exit(EXIT_FAILURE);
}


/*
 *  Creates and initializes a flight system, which stores the flight schedules of several airports.
 *  Returns a pointer to the system created.
 */
flightSys_t* createSystem(void) {
  // Replace this line with your code
    flightSys_t *newFlightSystem = malloc(sizeof(flightSys_t));
    if (newFlightSystem == NULL) {
        allocation_failed();
    }
    newFlightSystem->curAirport = NULL;
    newFlightSystem->next = NULL;
  return newFlightSystem;
}


/*
 *   Given a destination airport, departure and arrival times, and a cost, return a pointer to new flight_t.
 *
 *   Note that this pointer must be available to use even after this function returns.
 *   (What does this mean in terms of how this pointer should be instantiated?)
 *   Additionally you CANNOT assume that tdhe `departure` and `arrival` pointers will persist after this function completes.
 *   (What does this mean about copying dep and arr?)
 */

flight_t* createFlight(airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
  // Replace this line with your code
    if ((destination != NULL) && (departure != NULL) && (arrival != NULL)) {
        if (isAfter(arrival, departure) && cost >= 0) {
            flight_t *newFlight = malloc(sizeof(flight_t));
            newFlight->dest = destination;
            if (newFlight == NULL) {
                allocation_failed();
            }
            timeHM_t *arr = malloc(sizeof(timeHM_t));;
            if (arr == NULL) {
                allocation_failed();
            }
            arr->hours = arrival->hours;
            arr->minutes = arrival->minutes;
            newFlight->arrivalTime = arr;
            timeHM_t *dep = malloc(sizeof(timeHM_t));
            if (dep == NULL) {
                allocation_failed();
            }
            dep->hours = departure->hours;
            dep->minutes = departure->minutes;
            newFlight->departureTime = dep;
            newFlight->flightCost = cost;
            newFlight->nextFlight = NULL;
            return newFlight;
        }
        return NULL;
    }
    return NULL;
}

/*
 *  Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* system) {
  // Replace this line with your code
  //Might have to go in to each airport and remove all flights as well.
  flightSys_t *ptr = system;
  while(system != NULL){
      ptr = system->next;
      airport_t *airport = system->curAirport;
      airport_t *pointer = system->curAirport;
      while (airport != NULL){
          pointer = airport->nextAirport;
          flight_t *flight = airport->curFlight;
          flight_t *ptrFlight = airport->curFlight;
          while (flight != NULL){
              ptrFlight = flight->nextFlight;
              deleteFlight(flight);
              flight = ptrFlight;
          }
          free(airport->airportName);
          free(airport);
          airport = pointer;
      }
      free(system);
      system = ptr;
  }
  system = NULL;
}

/*
 *  Frees all memory allocated for a single flight. You may or may not decide
 *  to use this in delete system but you must implement it.
 */
void deleteFlight(flight_t* flight) {
  // Replace this line with your code
  //Free just the flight or also the time it points to?
  if (flight != NULL) {
      free(flight->departureTime);
      free(flight->arrivalTime);
      free(flight);
  }
}


/*
 *  Adds a airport with the given name to the system. You must copy the string and store it.
 *  Do not store `name` (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* system, char* name) {
  // Replace this line with your code

    if(system != NULL && name != NULL) {
        if (getAirport(system, name) == NULL) {
            airport_t *newAirport = malloc(sizeof(airport_t));
            if (newAirport == NULL) {
                allocation_failed();
            }
            newAirport->flightSystem = system;
            newAirport->airportName = malloc(sizeof(name+1));
            if (newAirport->airportName == NULL) {
                allocation_failed();
            }
            strcpy(newAirport->airportName, name);
            newAirport->nextAirport = NULL;
            newAirport->curFlight = NULL;
            if (system->curAirport == NULL) {
                system->curAirport = newAirport;
            }
            else {
                airport_t *point = system->curAirport;
                while (point->nextAirport != NULL){
                    point = point->nextAirport;
                }
                point->nextAirport = newAirport;
            }
        }
    }






}


/*
 *  Returns a pointer to the airport with the given name.
 *  If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* system, char* name) {
  // Replace this line with your cod
  if (system != NULL){
      airport_t *curAir = system->curAirport;
      while (curAir != NULL){
          char* attempt = curAir->airportName;
          if (strcmp(attempt, name) == 0){
              return curAir;
          }
          curAir = curAir->nextAirport;
      }
      return NULL;
  }
  return NULL;
}


/*
 *  Print each airport name in the order they were added through addAirport, one on each line.
 *  Make sure to end with a new line. You should compare your output with the correct output
 *  in `flights.out` to make sure your formatting is correct.
 */
void printAirports(flightSys_t* system) {
  // Replace this line with your code
  if (system != NULL) {
      airport_t *curAir = system->curAirport;
      while (curAir != NULL) {
          printf("%s", curAir->airportName);
          printf("\n");
          curAir = curAir->nextAirport;
      }
  }
}


/*
 *  Adds a flight to source's schedule, stating a flight will leave to destination at departure time and arrive at arrival time.
 */
void addFlight(airport_t* source, airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
  // Replace this line with your code
  // Stating??????????
  if ((source != NULL) && (destination != NULL) && (departure != NULL) && (arrival != NULL) && (cost >= 0)) {
      flight_t *newFlight = createFlight(destination, departure, arrival, cost);
      if (newFlight != NULL) {
          if (source->curFlight == NULL) {
              source->curFlight = newFlight;
          } else {
              flight_t *ptr = source->curFlight;
              while (ptr->nextFlight != NULL) {
                  ptr = ptr->nextFlight;
              }
              ptr->nextFlight = newFlight;
          }
      }
  }


}


/*
 *  Prints the schedule of flights of the given airport.
 *
 *  Prints the airport name on the first line, then prints a schedule entry on each
 *  line that follows, with the format: "destination_name departure_time arrival_time $cost_of_flight".
 *
 *  You should use `printTime()` (look in `timeHM.h`) to print times, and the order should be the same as
 *  the order they were added in through addFlight. Make sure to end with a new line.
 *  You should compare your output with the correct output in flights.out to make sure your formatting is correct.
 */
void printSchedule(airport_t* airport) {
  // Replace this line with your code
  if (airport != NULL) {
      printf("%s ", airport->airportName);
      printf("\n");
      flight_t *ptr = airport->curFlight;
      while (ptr != NULL) {
          printf("%s ", ptr->dest->airportName);
          printTime(ptr->departureTime);
          printf(" ");
          printTime(ptr->arrivalTime);
          printf(" $%d", ptr->flightCost);
          ptr = ptr->nextFlight;
          printf("\n");
      }
  }

}


/*
 *   Given a source and destination airport, and the time now, finds the next flight to take based on the following rules:
 *   1) Finds the earliest arriving flight from source to destination that departs after now.
 *   2) If there are multiple earliest flights, take the one that costs the least.
 *
 *   If a flight is found, you should store the flight's departure time, arrival time, and cost in the `departure`, `arrival`,
 *   and `cost` params and return true. Otherwise, return false.
 *
 *   Please use the functions `isAfter()` and `isEqual()` from `timeHM.h` when comparing two timeHM_t objects and compare
 *   the airport names to compare airports, not the pointers.
 */
bool getNextFlight(airport_t* source, airport_t* destination, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival,
                   int* cost) {
  // Replace this line with your code
    if ((source != NULL) && (destination != NULL) && (now != NULL) && (departure != NULL) && (arrival != NULL) && (cost >= 0)) {
        if (source->curFlight == NULL) {
            return false;
        } else {
            flight_t *ptr = source->curFlight;
            flight_t *bestFlight = source->curFlight;
            while (ptr->nextFlight != NULL) {
                if ((ptr->nextFlight->dest == destination) && (isAfter(ptr->nextFlight->departureTime, now))) {
                    if (isAfter(bestFlight->departureTime, ptr->nextFlight->departureTime) ||
                        ((isEqual(bestFlight->departureTime, ptr->nextFlight->departureTime)) &&
                         (bestFlight->flightCost > ptr->nextFlight->flightCost))) {
                        bestFlight = ptr->nextFlight;
                    }
                }
                ptr = ptr->nextFlight;
            }
            if (bestFlight->dest != destination || !(isAfter(bestFlight->departureTime, now))) {
                return false;
            }
            departure = bestFlight->departureTime;
            arrival->hours = bestFlight->arrivalTime->hours;
            arrival->minutes = bestFlight->arrivalTime->minutes;
            *cost = bestFlight->flightCost;
            return true;


        }
    }
    return false;

}

/*
 *  Given a list of flight_t pointers (`flight_list`) and a list of destination airport names (`airport_name_list`),
 *  first confirm that it is indeed possible to take these sequences of flights, (i.e. be sure that the i+1th flight departs
 *  after or at the same time as the ith flight arrives) (HINT: use the `isAfter()` and `isEqual()` functions).
 *  Then confirm that the list of destination airport names match the actual destination airport names of the provided flight_t structs.
 *
 *  `size` tells you the number of flights and destination airport names to consider. Be sure to extensively test for errors.
 *  As one example, if you encounter NULL's for any values that you might expect to be non-NULL return -1, but test for other possible errors too.
 *
 *  Return from this function the total cost of taking these sequence of flights.
 *  If it is impossible to take these sequence of flights,
 *  if the list of destination airport names doesn't match the actual destination airport names provided in the flight_t struct's,
 *  or if you run into any errors mentioned previously or any other errors, return -1.
 */
int validateFlightPath(flight_t** flight_list, char** airport_name_list, int size) {
  // Replace this line with your code
  if ((flight_list == NULL) || (airport_name_list == NULL) || (size <= 0)) {
      return -1;
  } else{
      int cost = flight_list[0]->flightCost;
      int i = 0;
      while (i < size - 1) {
          if ((isAfter(flight_list[i+1]->departureTime, flight_list[i]->arrivalTime)) || isEqual(flight_list[i+1]->departureTime, flight_list[i]->arrivalTime)){
              cost = cost + flight_list[i+1]->flightCost;
          } else {
              return -1;
          }
          if (strcmp(flight_list[i]->dest->airportName, airport_name_list[0]) != 0) {
              return -1;
          }
          i = i + 1;
      }
      return cost;
  }
}

