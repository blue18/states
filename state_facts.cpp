#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "state_facts.h"

// Name of the file
static std::string filename;
int numOfStates;

// Description - Check to see if the initial arguments are vaild
// Parameters  - argv[]: list contain the flags and arguments
//       	   - argc: number of arguments
// Return 	   - true if is valid, false if it is invalid
bool is_valid_arguments(char * argv[], int argc) {

    bool isValid = false;
    if (argc == 3 && strcmp(argv[2],"-s") == 0)	{ 
	    isValid = true; 
    }

    filename = argv[4];
    return isValid;
}

// Description - Initialize list of states
// Parameters  - someState list of states
// 			   - index size of list of states
void initState(State* someState, size_t index) {
    for(size_t i = 0; i < index; i++) {
	someState[i].name = "";
	someState[i].counties = 0;
	someState[i].population = 0;
    }
}

// Description - Create a list of states
// Parameters  - numberOfState number of states
// Return      - List of newly created states
State* create_states(int numberOfStates) {

    State *listOfStates = new State[numberOfStates + 5];
    initState(listOfStates, numberOfStates + 5);

    listOfStates[0].name = "Alabama";
    listOfStates[0].counties = 0;
    listOfStates[0].population = 3001112;

    listOfStates[1].name = "California";
    listOfStates[1].counties = 0;
    listOfStates[1].population = 101231234;

    listOfStates[0].c = create_counties(2);
    numOfStates = 2;
    return listOfStates;
}

// Description - Create a list of counties
// Parameters  - numberOfCounties number of counties
// Return      - List of newly created counties
County* create_counties(int numberOfCounties) {

    County *listOfCounties = new County[numberOfCounties + 5];

    listOfCounties[0].name = "Washington";
    listOfCounties[0].cities = 5;
    listOfCounties[0].population = 500000;
    listOfCounties[0].avg_income = 900000;
    listOfCounties[0].avg_house = 400000;
    listOfCounties[0].city = new std::string[2];
    listOfCounties[0].city[0] = "Hillsboro";
    listOfCounties[0].city[1] = "Cornelious";

    return listOfCounties;
}

// Description - Prints all states
// Parameter   - someState list of states
//             - size length of the state list
void printState(State* someState, size_t size) {
    if(size <= 0) {
	    return;	
    } else {
	if(someState == nullptr) {
		std::cout << "undefined state" << std::endl;
	} else {
	    if(size > 0) {
		for (size_t i = 0; i < size; i++) {
		    std::cout << "-----------[" << i << "]" << std::endl;
		    std::cout << "State name: " << someState[i].name << std::endl;
		    std::cout << "State counties: " << someState[i].counties << std::endl;
		    std::cout << "State population: " << someState[i].population << std::endl;
		    std::cout << "-----------" << std::endl;
		    printCounties(someState[i].c, someState[i].counties);
		}
	    }
	}
    }
}

// Description - Copy list of states
// Parameters  - fromState source list
// 			   - toState destination list
// 			   - index size of fromState
// Return      - New copy of state list 
State* cpyState(State* fromState, State* toState, size_t index) {
	
    if(fromState != nullptr) {
	// copy old to new array
	for(size_t i = 0; i < index; i++) {
	    toState[i].name = fromState[i].name;
	    toState[i].counties = fromState[i].counties;
	    toState[i].population = fromState[i].population;
	}

	delete [] fromState;
	return toState;

    } else {
	return fromState;
    }
}

// Description - Prints all counties 
// Parameters  - aCounty list of counites
// 			   - size length of county list
void printCounties(County* aCounty, size_t size) {

	if(size <= 0) {
		return;
	} else {
		if(aCounty == nullptr) { 
			std::cout << "County is undefined" << std::endl;
			return; 
		} else {
			for (size_t i = 0; i < size; i++) {
				std::cout << "-----------[" << i << "]" << std::endl;
				std::cout << "County name: " << aCounty[i].name << std::endl;
				std::cout << "County cities: " << aCounty[i].cities << std::endl;
				std::cout << "County population: " << aCounty[i].population << std::endl;
				std::cout << "County average income: " << aCounty[i].avg_income << std::endl;
				std::cout << "County average house: " << aCounty[i].avg_house << std::endl;
				if(aCounty[i].city != nullptr) {
					std::cout << "County city: " << aCounty[i].city[0] << std::endl;
				}
				std::cout << "-----------" << std::endl;
			}
		}
	}
}

// Description - Reads in state data from file 
// Parameters  - aState list states
// 			   - aValue number of states already in the list
// 			   - aFile file where data is extracted

void get_state_data(State* aState, int aValue, std::ifstream& aFile) { 

	// open file
	std::string line; 
	aFile.open(filename, std::ifstream::in);
	// if the file is open
	if(aFile.is_open()) { 

		std::string::size_type sz; // alias of size_t
		std::string delimiter = " ";
		std::string token;

		int i = aValue;

		// add data from the file to the new array
		while(getline(aFile, line)) {

			// Get state
			token = line.substr(0, line.find(delimiter));
			aState[i].name = token;
			line.erase(0, line.find(delimiter) + delimiter.length());

			// Get population of state
			token = line.substr(0, line.find(delimiter));
			aState[i].population = std::stoi(token, &sz);
			line.erase(0, line.find(delimiter) + delimiter.length());

			// Get number of counties of state
			if(line.find("\n")) {
				aState[i].counties = std::stoi(line, &sz);
			}

			// Now read the data in the counties 
			aState[i].c = create_counties(aState[i].counties);

			get_county_data(aState[i].c, aState[i].counties, aFile);
			line = "";
			i++;
			numOfStates++;
		}

		aFile.close();

	} else {
		std::cout << "Unable to open file" << std::endl;
	}
}

// Description - Reads in county data from file 
// Parameters  - aCounty list of counties 
// 			   - aValue number of states already in the list
// 			   - aFile file where data is extracted
void get_county_data(County* tempListCounty, int aValue, std::ifstream& aFile) {

    // open file
    int numOfCounties = aValue;

    // if file is open
    if(aFile.is_open()) {

	std::string line; 
	std::string::size_type sz; // alias of size_t	
	std::string delimiter = " ";
	std::string token;

	// Count number of counties
	int i = 0;

	while(i < numOfCounties) {

	    getline(aFile, line);

	    // get name
	    token = line.substr(0, line.find(delimiter));
	    tempListCounty[i].name = token;
	    line.erase(0, line.find(delimiter) + delimiter.length());

	    // get population
	    token = line.substr(0, line.find(delimiter));
	    tempListCounty[i].population = std::stoi(token, &sz);
	    line.erase(0, line.find(delimiter) + delimiter.length());

	    // get avg income 
	    token = line.substr(0, line.find(delimiter));
	    tempListCounty[i].avg_income = std::stoi(token, &sz);
	    line.erase(0, line.find(delimiter) + delimiter.length());

	    // get avg home
	    token = line.substr(0, line.find(delimiter));
	    tempListCounty[i].avg_house = std::stoi(token, &sz);
	    line.erase(0, line.find(delimiter) + delimiter.length());
		    
	    // get number of cities
	    token = line.substr(0, line.find(delimiter));
	    tempListCounty[i].cities = std::stoi(token, &sz);
	    line.erase(0, line.find(delimiter) + delimiter.length());

	    tempListCounty[i].city = new std::string[5];
	    
	    if(tempListCounty[i].cities >= 2) {
		    std::string cityOne;	
		    std::string cityTwo;
		    cityOne = line.substr(0, line.find(delimiter));
		    tempListCounty[i].city[0] = cityOne;
		    line.erase(0, line.find(delimiter) + delimiter.length());

		    cityTwo = line;
		    tempListCounty[i].city[1] = cityTwo;

	    } else {
		    token = line;
		    tempListCounty[i].city[0] = token;
	    }
	    i++;
	}
    } else {
	    std::cout << "Unable to open file" << std::endl;
    }
}

// Description - Free all associated allocated memory from state list
// Paramters   - stateList state list 
void freeMemory(State* stateList) {	
    delete [] stateList;
    delete [] stateList->c;
    delete [] stateList->c->city;
    std::cout << "Freed block for allocated memory" << std::endl;
}

// Description - Display state with largest population in the list
// Parameters  - stateList list of states
void largestStatePop(State* stateList) {	
    int num = 0;

    std::cout << "************* Largest State *************" << std::endl;

    State largestState;
    num = numOfStates; 
    largestState = largestStatePopHelper(stateList, num);
    std::cout << "Population: " << largestState.population << std::endl;
    std::cout << "Name: " << largestState.name << std::endl;
    std::cout << "Counties: " << largestState.counties << std::endl;
}

// Desciprtion - Finds the state with the largest population
// Parameters  - arr list of states
// 			   - n size of list
// Return 	   - State with the largest population
State largestStatePopHelper(State* arr, int n) {
    int i, j;
    State temp;
    for(i = 0; i < n-1; i++) {
	// Last i elements are already in place	
	for(j = 0; j < n-i-1; j++) {
	    if(arr[j].population > arr[j + 1].population) {
		temp = arr[j];	
	    } else { 
		temp = arr[j + 1];
	    }
	}
    }
    return temp;	
}

// Description - Finds the county with the largest population
// Parameters  - arr list of counties
//  		   - n size of list
// Return      - County with the largest population
County largestCountyHelper(County* arr, int n) {
    int i, j;
    County temp;

    for(i = 0; i < n - 1; i++) {
	// Last i elements are already in place	
	for(j = 0; j < n - i - 1; j++) {
	    if(arr[j].population > arr[j + 1].population) {
		temp = arr[j];	
	    } else { 
		temp = arr[j + 1];
	    }
	}
    }
    return temp;	
}

// Description - Display the state with the largest county in the list
// Parameters  - stateList list of states
void largestCounty(State* stateList) {

    County tempCounty;
    std::vector<County> countyList;
    std::vector<County>::size_type sz;

    std::cout << "************* Largest County ********************" << std::endl;

    // Get the county with the highest population for the given state
    for(size_t i = 0; i < numOfStates; i++) {
	if(stateList[i].counties != 0) {
	    tempCounty = largestCountyHelper(stateList[i].c, stateList[i].counties);
	    countyList.push_back(tempCounty);
	}
    }

    sz = countyList.size();
    // Find the county with the largest population 
    for(size_t i = 0; i < sz - 1; i++) {
	for(size_t j = 0; j < sz - i - 1; j++) {
	    if(countyList.at(i).population < countyList.at(i + 1).population) {	
		std::cout << "Name: " << countyList.at(i + 1).name << std::endl;	
		std::cout << "Population: " << countyList.at(i + 1).population << std::endl;
		std::cout << "Cities: " << countyList.at(i + 1).cities << std::endl;
		std::cout << "Average Income: " << countyList.at(i + 1).avg_income << std::endl;
		std::cout << "Average House: " << countyList.at(i + 1).avg_house << std::endl;
	    } else {
		std::cout << "Name: " << countyList.at(i).name << std::endl;	
		std::cout << "Population: " << countyList.at(i).population << std::endl;
		std::cout << "Cities: " << countyList.at(i).cities << std::endl;
		std::cout << "Average Income: " << countyList.at(i).avg_income << std::endl;
		std::cout << "Average House: " << countyList.at(i).avg_house << std::endl;
	    }
	}
    }
}

// Description - Display all average income that is greater than the user's input 
// Parameters  - stateList list of states
void menu(State* stateList) {

    float avg_income = 0; 	

    std::cout << "Hello User." << std::endl;
    std::cout << "Enter the counties average income you would like to view (5-6 digits): ";
    std::cin >> avg_income;

    if(std::cin.fail()) {
	std::cout << "valid is not number" << std::endl;
	return;
    }

    for(size_t i = 0; i < numOfStates; i++) {
	for(size_t j = 0; j < stateList[i].counties; j++) {
	    if(avg_income < stateList[i].c[j].avg_income) {	
		std::cout << stateList[i].name << " " << stateList[i].c[j].name << " " << stateList[i].c[j].avg_income << std::endl;
	    }
	}
    }
}

// Description - Average household cost for all counties in each state
// Parameters  - stateList list of states
void avgHouseholdCost(State* stateList) {
    std::cout << "************ Average Household Cost **************" << std::endl;
    for(size_t i = 0; i < numOfStates; i++) {
	for(size_t j = 0; j < stateList[i].counties; j++) {
	    std::cout << "County Name: " << stateList[i].c[j].name << ", average household cost: " << stateList[i].c[j].avg_house << std::endl;
	}
    }
}

// Description - Display stats in sorted order by name
// Parameters  - stateList list of states
void statesByName(State* stateList) {
    std::vector<State> listOfNames;

    std::cout << "************* States by name *************" << std::endl;

    // Add data of states in new list 
    for(size_t i = 0; i < numOfStates; i++) {
	listOfNames.push_back(stateList[i]);
    }
    // Sort the list by state name
    std::sort(listOfNames.begin(), listOfNames.end(), byNameHelper<State>); 

    // Display all state names
    for(size_t i = 0; i < numOfStates; i++) {		
	std::cout << stateList[i].name << std::endl;
    }
}

// Description - Display states in sorted order by population
// Parameters - stateList list of states
void statesByPopulation(State* stateList) {
    std::vector<State> listOfPop; 
    
    std::cout << "************* States by population *************" << std::endl;

    // Add data of states in new list
    for(size_t i = 0; i < numOfStates; i++) {
	listOfPop.push_back(stateList[i]);
    }

    // Sort the list by state population 
    std::sort(listOfPop.begin(), listOfPop.end(), byPopulationHelper<State>); 
    
    // Print county list
    for(size_t i = 0; i < listOfPop.size(); i++) {
	std::cout << listOfPop.at(i).name << " " << listOfPop.at(i).population << std::endl;
    }
}

// Description - Display counties within states sorted by population
// Parameters  - arr list of states
void countiesByPopulation(State arr[]) {
    // County population
    std::vector<County> listOfPop;
    int totalNumOfCounties = 0;

    std::cout << "************* Counties by population *************" << std::endl;

    // Get the number of counites
    for(size_t i = 0; i < numOfStates; i++) {
	totalNumOfCounties += arr[i].counties;
    }
    
    // Add data of counties in new list 
    for(size_t i = 0; i < numOfStates; i++) {
	for(size_t j = 0; j < arr[i].counties; j++) {	
	    listOfPop.push_back(arr[i].c[j]);
	}
    }
    // Sort list by population  
    std::sort(listOfPop.begin(), listOfPop.end(), byPopulationHelper<County>); 

    // Print county list
    for(size_t i = 0; i < listOfPop.size(); i++) {
	std::cout << listOfPop.at(i).name << " " << listOfPop.at(i).population << std::endl;
    }
}

// Description - Display counties within states sorted by name 
// Paramters   - arr list of states
void countiesByName(State arr[]) {

    // County names
    std::vector<County> listOfNames;
    int totalNumOfCounties = 0;

    std::cout << "************* Counties by name *************" << std::endl;

    // Get the number of counties
    for(size_t i = 0; i < numOfStates; i++) { 
	totalNumOfCounties += arr[i].counties;
    }

    // Add names of counites in new list
    for(size_t i = 0; i < numOfStates; i++) {
	for(size_t j = 0; j < arr[i].counties; j++) {	
	    listOfNames.push_back(arr[i].c[j]);
	}
    }

    // Sort list by name
    std::sort(listOfNames.begin(), listOfNames.end(), byNameHelper<County>);

    // Print county list
    for(size_t i = 0; i < listOfNames.size(); i++) {
	std::cout << listOfNames.at(i).name << std::endl;
    }
}

