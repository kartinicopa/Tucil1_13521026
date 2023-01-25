#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <fstream>
#include <sstream>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());


int num[4];
int numPosition[4];
char sign[3], myOp[] = {'+','-','*','/'};
bool check;

void printTitle() {
    cout << "==================================================="  << endl;
    cout << "||   ___  _  _       ____                         ||" << endl;              
    cout << "||  |__ )| || |    / ____|                        ||" << endl;
    cout << "||     ) | || |_  | |  __  __ _ _ __ ___   ___    ||" << endl;
    cout << "||    / /|__   _| | | |_ |/ _` | '_ ` _ ) / _ )   ||" << endl;
    cout << "||   / /_   | |   | |__| | (_| | | | | | |  __/   ||" << endl;
    cout << "||  |____|  |_|   (_ ____|(__,_|_| |_| |_|(___|   ||" << endl;
    cout << "||                                                ||" << endl;
    cout << "====================================================" << endl;

}

bool isValid(string card) {
    // validate the input is A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
    vector<string> cards = {"A", "J", "Q", "K", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    for (int i = 0; i < cards.size(); i++) {
        if (card == cards[i]) {
            return true;
        }
    }
    return false;
}

int translateInput(string card) {
    vector<string> cards = {"A", "J", "Q", "K", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    vector<int> num = {1, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < cards.size(); i++) {
        if (card == cards[i]) {
            return num[i];
        }
    }

}

int calculate(int x, int y, char z)
{
    // x + y
    if(z == '+'){
        return x + y;
    }
    // x - y
    else if(z == '-'){
        return x - y;
    }
    // x * y
    else if(z == '*'){
        return x * y;
    }
    // x / y
    else if(z == '/'){
        if(y == 0)
            return 999;
        else if(x % y != 0)
            return 999;
        else return x/y;
    }

}


void operation(int* countAll) {
    if(calculate(calculate(calculate(numPosition[0], numPosition[1], sign[0]), numPosition[2], sign[1]), numPosition[3], sign[2]) == 24.0){
        check = true;
        cout<<"(("<<numPosition[0]<<sign[0]<<numPosition[1]<<')'<<sign[1]<<numPosition[2]<<')'<<sign[2]<<numPosition[3]<<" = 24"<<endl;
        (*countAll)++;
    }
    if(calculate(calculate(numPosition[0], numPosition[1], sign[0]), calculate(numPosition[2], numPosition[3], sign[2]), sign[1]) == 24.0){
        check = true;
        cout<<"("<<numPosition[0]<<sign[0]<<numPosition[1]<<')'<<sign[1]<<'('<<numPosition[2]<<sign[2]<<numPosition[3]<<") = 24"<<endl;
        (*countAll)++;
    }
    if(calculate(calculate(numPosition[0], calculate(numPosition[1], numPosition[2], sign[1]), sign[0]), numPosition[3], sign[2]) == 24.0){
        check = true;
        cout<<"("<<numPosition[0]<<sign[0]<<'('<<numPosition[1]<<sign[1]<<numPosition[2]<<"))"<<sign[2]<<numPosition[3]<<" = 24"<<endl;
        (*countAll)++;
    }
    if(calculate(numPosition[0], calculate(calculate(numPosition[1], numPosition[2], sign[1]), numPosition[3], sign[2]), sign[0]) == 24.0){
        // if check = true then countAll += 1
        check = true;
        cout<<numPosition[0]<<sign[0]<<"(("<<numPosition[1]<<sign[1]<<numPosition[2]<<')'<<sign[2]<<numPosition[3]<<") = 24"<<endl;
        (*countAll)++;
    }
    if(calculate(numPosition[0], calculate(numPosition[1], calculate(numPosition[2], numPosition[3], sign[2]), sign[1]), sign[0]) == 24.0){
        check = true;
        cout<<numPosition[0]<<sign[0]<<'('<<numPosition[1]<<sign[1]<<'('<<numPosition[2]<<sign[2]<<numPosition[3]<<")) = 24"<<endl;
        (*countAll)++;
    }

}

void randomNumPosition(int * countAll)
{
	for(int a=0; a<4; a++)
		for(int b=0; b<4; b++)
		{
			if(b==a) continue;
			for(int c=0; c<4; c++)
			{
				if(c==a or c==b) continue;
				for(int d=0; d<4; d++)
				{
					if(d==a or d==b or d==c) continue;

					numPosition[0] = num[a];
					numPosition[1] = num[b];
					numPosition[2] = num[c];
					numPosition[3] = num[d];

					operation(countAll);
				}
			}
		}
}

void signOperation(int * countAll) {
	for(int a=0; a<4; a++)
		for(int b=0; b<4; b++)
			for(int c=0; c<4; c++)
			{
				sign[0] = myOp[a];
				sign[1] = myOp[b];
				sign[2] = myOp[c];
				
				randomNumPosition(countAll);
			}
}

int main()
{
	// print title
    printTitle();
    // 3 types keyboard, file, random
    char choose;
    cout << "Keyboard (k), File (f), Random (r): ";
    cin >> choose;
    if (choose == 'k') { // Menerima string A, 2, 3, 4, 5, 6, 7, 8, 9, 10
        string card1, card2, card3, card4;
        cout << "Card 1: ";
        cin >> card1;
        cout << "Card 2: ";
        cin >> card2;
        cout << "Card 3: ";
        cin >> card3;
        cout << "Card 4: ";
        cin >> card4;
        // validasi input with boolean isValid
        if (isValid(card1) && isValid(card2) && isValid(card3) && isValid(card4)) {
            // translate card to integer
            num[0] = translateInput(card1);
            num[1] = translateInput(card2);
            num[2] = translateInput(card3);
            num[3] = translateInput(card4);

        } else {
            cout << "Invalid Input" << endl;
            return 0;
        }
    } 
    else if (choose == 'f') { // Menerima file
        string filename;
        cout << "Filename: ";
        cin >> filename;
        ifstream file(filename);
        string card1, card2, card3, card4;
        file >> card1 >> card2 >> card3 >> card4;
        // print cards
        cout << "Cards: " << card1 << " " << card2 << " " << card3 << " " << card4 << endl;
        num[0] = translateInput(card1);
        num[1] = translateInput(card2);
        num[2] = translateInput(card3);
        num[3] = translateInput(card4);
    } 
    else if (choose == 'r') { // Random A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K using vector
        int i;
        vector<string> cards = {"A", "J", "Q", "K", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937_64 rng(seed);
        shuffle(cards.begin(), cards.end(), rng);
        cout << "Random cards: " << cards[0] << " " << cards[1] << " " << cards[2] << " " << cards[3] << endl;
        num[0] = translateInput(cards[0]);
        num[1] = translateInput(cards[1]);
        num[2] = translateInput(cards[2]);
        num[3] = translateInput(cards[3]);
    }
    else {
        cout << "Invalid Input" << endl;
        return 0;
    }
    // start timer
    auto start = chrono::high_resolution_clock::now();
   // count all solution
    int countAll = 0;
    signOperation(&countAll);
    // if countAll == 0
    if (countAll == 0) {
        cout << "No solution" << endl;
    }
    else {
        cout << "Total solution: " << countAll << endl;
    }

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << endl;
    // want to save output?
    char save;
    cout << "Save output? (y/n): ";
    cin >> save;
    if (save == 'y') {
        string filename;
        cout << "Filename: ";
        cin >> filename;
        ofstream file(filename);
        file << "Card 1: " << num[0] << endl;
        file << "Card 2: " << num[1] << endl;
        file << "Card 3: " << num[2] << endl;
        file << "Card 4: " << num[3] << endl;
        // save operaation
        file << "Total solution: " << countAll << endl;
        file << "Elapsed time: " << elapsed.count() << endl;
    }
    return 0;
}



