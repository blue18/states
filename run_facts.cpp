// May 18, 2018

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "state_facts.h"

int main(int argc, char *argv[]) {

    bool valid = is_valid_arguments(argv, argc);
    std::ifstream aFile;

    // Check to see if the input is valid. 
    if (valid != 0) {
	std::cout << valid << std::endl;
	perror ("Invalid number of arguments.");
	exit(1);
    }

    State * currentState;
    int numberOfStates = atoi(argv[2]);

    // Initialize states 
    currentState = create_states(numberOfStates);

    // Get data from file
    get_state_data(currentState, 2, aFile);

    largestStatePop(currentState);	
    largestCounty(currentState);
    menu(currentState);
    avgHouseholdCost(currentState);
    statesByName(currentState); 
    statesByPopulation(currentState);
    countiesByName(currentState);
    countiesByPopulation(currentState);
    freeMemory(currentState);
    return 0;
}

