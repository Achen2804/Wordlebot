#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_map>


using namespace std;
string wordBank[2316]{};
string answerBank[2316]{};
string emptyBank[2316]{};
int answerSizeCounter{};
string answer{"crane"};
string *makeList();
void cutList(char first, char second, char third, char fourth, char fifth);
void firstCut(char ch,int position);
void nextCut(char ch,int position);
void score();
int main()
{
    char ch1,ch2,ch3,ch4,ch5{};
    int guesses=1;
    makeList();//This is making my list of words//

    cout << "My guess is '"<<answer<<"' please give feedback \n";//First guess//
    cin >>ch1>>ch2>>ch3>>ch4>>ch5;
    if(ch1=='g'&&ch2=='g'&& ch3=='g'&&ch4=='g'&& ch5=='g'){
        cout<<"And we're done.";}
    else{
    cutList(ch1,ch2,ch3,ch4,ch5);//This reduces my answer pool. 
    score();
    cout<<"Scoring done: ";
    while(guesses>=0){
    guesses++;
    cin >>ch1>>ch2>>ch3>>ch4>>ch5;
    if(ch1=='g'&&ch2=='g'&& ch3=='g'&&ch4=='g'&& ch5=='g'){
        cout<<"And we're done. It took me "<<guesses<<" guesses";
        break;
    }else{
        nextCut(ch1,0);
        nextCut(ch2,1);
        nextCut(ch3,2);
        nextCut(ch4,3);
        nextCut(ch5,4);
        for(int y=0;y<answerSizeCounter;y++){
            cout<< y<<" "<<answerBank[y]<<endl;
        }
        score();
            }
        }
    }
    return 0;
}
void score(){
    cout<<"Begining the scoring. ";
    unordered_map<char, int> letterScore;
    int wordScore[answerSizeCounter]{};
    for(int y=0;y<answerSizeCounter;y++){
        for (const char &c: answerBank[y]){
		// check if key `c` exists in the map or not
        unordered_map<char, int>::iterator it = letterScore.find(c);

		// key already present on the map
		if (it != letterScore.end()) {
			it->second++;	// increment map's value for key `c`
		    }else {//to add a key if we encounter a new letter
			letterScore.insert(std::make_pair(c, 1));
		    }
	    }
    }
    letterScore['0']=0;
	for(int y=0;y<answerSizeCounter;y++){
	   for (const char &c: answerBank[y]){
	    wordScore[y]+= letterScore[c];
	   }
	}
	int max=0;
	for(int sc = 0; sc<answerSizeCounter;sc++){
	    if(wordScore[sc]>max){
	        max=wordScore[sc];
	        answer=answerBank[sc];
	        cout << "My guess is '"<<answer<<"' based on new info please give feedback \n";//First guess//
	    }
	}
}
	
void cutList(char first, char second, char third, char fourth, char fifth){
    cout<<"Cutting list"<<endl;
    answerSizeCounter=0;
    firstCut(first,0);
    cout<<"First done"<<endl;
    nextCut(second,1);
    nextCut(third,2);
    nextCut(fourth,3);
    nextCut(fifth,4);
    for(int y=0;y<answerSizeCounter;y++){
	   cout<<"{ "<<y<<", "<<answerBank[y]<<"}";
	}
}
void nextCut(char ch, int position){
    if(ch=='y'){
        for(int y=0; y<answerSizeCounter;y++){//check every word
            int exclusive =1;
            for(int check=0; check<5;check++){//check every letter in the word
            if(answerBank[y].at(check)==answer.at(position) && check==position){
                exclusive=1;
                break;
                }else if(answerBank[y].at(check)==answer.at(position) && check!=position){
                exclusive=0;
                }
            }
            if(exclusive==1){
                answerBank[y]="00000";
            }
        }
    }else if(ch=='g') {
        for(int y=0; y<answerSizeCounter;y++){
            int exclusive =1;
            for(int check=0; check<5;check++){//check every letter in the word
            if(answerBank[y].at(check)==answer.at(position) && check==position){
                exclusive=0;
                break;
                }else if(answerBank[y].at(check)==answer.at(position) && check!=position){
                exclusive=1;
                }
            }
            if(exclusive==1){
                answerBank[y]="00000";
            }
        }
    }else if(ch=='b'){
        for(int y=0; y<answerSizeCounter;y++){
            int exclusive =1;
            for(int check=position; check<5;check++){//check every letter in the word
            if(answerBank[y].at(position)==answer.at(position)){
                answerBank[y]="00000";
                break;
                }
            }
        }
    }
}
void firstCut(char ch, int position){
    if(ch=='y'){
        for(int y=0; y<2315;y++){
            for(int check=0; check<5;check++){
            if(wordBank[y].at(check)==answer.at(position) && check==position){
                y++;
                break;
                }else if(wordBank[y].at(check)==answer.at(position) && check!=position) {
                answerBank[answerSizeCounter]=wordBank[y];
                answerSizeCounter++;
                break;
                } 
            }
        }
    }else if(ch=='g') {
        for(int y=0; y<2315;y++){
            int exclusive =1;
            for(int check=0; check<5;check++){
            if(wordBank[y].at(check)==answer.at(position) && check==position){
                exclusive=0;
                }else if(wordBank[y].at(check)==answer.at(position) && check!=position){
                exclusive=1;
                break;
                }
            }
            if(exclusive==0){
                answerBank[answerSizeCounter]=wordBank[y];
                answerSizeCounter++;
            }
        }
    }else if(ch=='b'){ 
        for(int y=0; y<2315;y++){
            int exclusive=0;
            for(int check=0; check<5;check++){
                if(wordBank[y].at(check) == answer.at(0)){
                    exclusive=1;
                    break;
                }
            }
            if(exclusive==0){
            answerBank[answerSizeCounter]=wordBank[y];
            answerSizeCounter++;
            }
        }
    }
    cout<<"Word bank: ";
    for(int y=0;y<answerSizeCounter;y++){
        cout << y <<" "<<answerBank[y];
    }
}
string *makeList(){
    int x{};
    ifstream fin("wordle-answers.txt");


	cout<< "This program reads and prints a text file" << endl;
	cout<< "Press Enter for every line of text to be displayed" << endl;


	if(cin.get() == '\n'){
	char str[6];
	int i = 6;

	while(fin) {
		fin.getline(str, i);
		wordBank[x]=str;
		if(fin) cout << wordBank[x] << endl;
		x++;
		if(x==2315){
		    cout<<"Done. ";
		    fin.close();
	  	  }
	}
    return wordBank;
    }
}
