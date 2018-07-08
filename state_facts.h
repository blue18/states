#include <iostream>
#include <string>
#include <vector>

typedef struct County { 
    std::string name; 
    std::string *city;
    int cities;
    int population;
    float avg_income;
    float avg_house;
} County;

typedef struct State { 
    std::string name; 
    County *c;	
    int counties;
    int population;
} State;
template <typename T>
bool byPopulationHelper(T a, T b) {
    return(a.population < b.population);
}

template <typename T>
bool byNameHelper(T a, T b) {
    return(a.name < b.name);
}

bool is_valid_arguments(char**, int);

State* create_states(int);
State* cpyState(State* fromState, State* toState, size_t index);

State largestStatePopHelper(State*, int); 

County* create_counties(int);

County largestCountyHelper(County*, int); 

void get_state_data(State*, int, std::ifstream&);
void get_county_data(County*, int, std::ifstream&);
void printState(State*, size_t);
void printCounties(County*, size_t);
void freeMemory(State* stateList);
void printCounties(State* someState, size_t size);
void largestStatePop(State*);
void largestCounty(State*);
void menu(State*);
void avgHouseholdCost(State*);
void statesByName(State*);
void statesByPopulation(State*);
void countiesByName(State*);
void countiesByPopulation(State*);
