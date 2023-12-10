#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<random>
using namespace std;


#ifdef _WIN32
    const char* clearCommand = "cls";
#else
    const char* clearCommand = "clear";
#endif

void clearScreen() {
    system(clearCommand);
}



class userDetails{
private:
	string name;
	int age;
public:

	void setName(string name){
		this->name = name;
	}

	void setAge(int age){
		this->age = age;
	}

	string getName(){
		return this->name;
	}
	int getAge(){
		return this->age;
	}

	void handleUserData(string, int);
};


void userDetails::handleUserData(string winner, int score){
	// create the file handler
	fstream fp;
	// open the file
	fp.open("UserDetails", ios::app);

	// check file existence
	if (!fp.is_open()) {
        cerr << "Error opening the file." << endl;
        exit(EXIT_FAILURE);
    }
	// create the time value;
	time_t now = time(0);
	char *date = ctime(&now);

	fp<<"--------------------------------------------"<<endl;
	fp<<"UID: "<<this->name.substr(0,3)+to_string(this->age)<<endl;
	fp<<"Name: "<<" "<<this->name<<endl;
	fp<<"Age: "<<" "<<this->age<<endl;
	fp<<"time: "<<" "<<date;
	fp<<"\nGame Result"<<endl;
	fp<<winner<<score<<endl;
	fp<<"--------------------------------------------"<<endl;
	fp.close();
}




// create the game menu for the user
string menu(){

	int selection;
	string Choices[] = {"ROCK", "PAPER","SCISSORS"};

	cout<<"\nSELECT YOUR MOVE WISELY"<<endl;
	cout<<"User Options"<<endl;
	cout<<"1. ROCK"<<endl;
	cout<<"2. PAPER"<<endl;
	cout<<"3. SCISSORS"<<endl;

	cin>>selection;
	if(selection > 3){
		cout<<"Wrong Input"<<endl;
		exit(1);
	}

	return Choices[selection-1];

}

// this is to generate the random choice of the computer
string getRandomChoice(){	

	// this is the seeder function that uses the current time to generate the random number 
    static std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));

	string Choices[] = {"ROCK", "PAPER","SCISSORS"};
	int len = 3;

    uniform_int_distribution<> dis(0, len - 1);
    int randomIndex = dis(gen);

    return Choices[randomIndex];
}


// main game logic is here and it returns a pair that contains winnner and his score
pair<string, int> startGame(string username){

	int counter = 3;
	int userPoints = 0;
	int computerPoints = 0;


	while(counter)
	{

		string userChoice = menu();

		if(userChoice == getRandomChoice()){
			cout<<"TIE : "<<userPoints<<","<<computerPoints<<endl;
		}
		else if((userChoice == "ROCK" && getRandomChoice() == "SCISSORS") || 
			(userChoice == "PAPER" && getRandomChoice() == "ROCK") || 
			(userChoice == "SCISSORS" && getRandomChoice() == "PAPER")){
			userPoints+=5;
			cout<<username<<" : "<<userPoints;
		}
		else{
			computerPoints+=5;
			cout<<"COMPUTER : "<<computerPoints<<endl;
		}

		counter--;
	}

	if(userPoints > computerPoints){
		return make_pair("User wins: ", userPoints);
	}

	return make_pair("Computer Wins: ", computerPoints);

};





// driver
int main(){
	
	clearScreen();
	string username;
	int age;
	userDetails ud;

	cout<<"Enter Player name: ";
	cin>>username;
	cout<<"Enter Player age: ";
	cin>>age;

	ud.setName(username);
	ud.setAge(age);
	string name = ud.getName();


	cout<<"------------------------ROCK PAPER SCISSORS--------------------------"<<endl;

	pair<string, int> winnerPair = startGame(name);
	cout<<winnerPair.first<<winnerPair.second<<endl;



	ud.handleUserData(winnerPair.first, winnerPair.second);
}