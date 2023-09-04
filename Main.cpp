#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include<bits/stdc++.h>


using namespace std;



vector<string> wordBank(2316); //This keeps track of my words
vector<unordered_map<char,int>> wordInfo(2316); //This tracks the number of times a letter appears
vector<unordered_set<char>> wordletters(2316); //This tracks what letters appear in each word


string answer{"salet"};
void makeList();
void cutList(string feedback);
void score();
//void firstCut(char ch,int position);
//void cut(string feedback);

int main()
{
    string feedback;
    int guesses=1;
    makeList();//This is making my list of words//

    cout << "My guess is '"<<answer<<"' please give feedback \n";//First guess//
    cin >>feedback;
    
    if(feedback=="ggggg"){
        cout<<"And we're done.";}
    else{
    cutList(feedback);//This reduces my answer pool. 
    score();
    cout<<"Scoring done: ";
    while(guesses>=0){
    guesses++;
    cin >>feedback;
    if(feedback=="ggggg"){
        cout<<"Aaaannnnd done. It took me "<<guesses<<" guesses";
        break;
    }else{
        cutList(feedback);
        score();
            }
        }
    }
    return 0;
}
void score(){
    cout<<"Begining the scoring. ";
    unordered_map<char, int> letterScore;
    vector<int> wordScore(wordletters.size());
    for(int y=0;y<wordletters.size();y++){
        for (const char &c: wordletters[y]){
		// check if key `c` exists in the map or not
            if(letterScore.find(c) != letterScore.end()){
                letterScore[c]++;
            }else{
                letterScore[c]=1;
            }
	    }
    }
    letterScore['0']=0;
	for(int y=0;y<wordletters.size();y++){
	   for (const char &c: wordletters[y]){
	    wordScore[y]+= letterScore[c];
	   }
	}
	int max=0;
	for(int sc = 0; sc<wordletters.size();sc++){
	    if(wordScore[sc]>max){
	        max=wordScore[sc];
	        answer=wordBank[sc];
	        
	    }
	    
	}
	cout << "My guess is '"<<answer<<"' based on new info please give feedback \n, score is"<<max;//First guess//
}
void cutList(string feedback){
    unordered_map<char,int> guessFeedback; //This tracks the number of times a letter appears
    for(int x=0;x<5;x++){
        int y=0;
        switch(feedback[x]){
            case 'g':
            if(guessFeedback.find(answer[x]) != guessFeedback.end()){
                guessFeedback[answer[x]]++;
            }else{
                guessFeedback[answer[x]]=1;
            }
                while(y<wordBank.size()){
                    if(answer[x]!=wordBank[y][x]){
                        cout<<wordBank[y];
                        wordInfo.erase(wordInfo.begin()+y);
                        wordBank.erase(wordBank.begin()+y);
                        wordletters.erase(wordletters.begin()+y);
                    }else{
                        y++;
                    }
                }
                break;
            case 'y':
            if(guessFeedback.find(answer[x]) != guessFeedback.end()){
                guessFeedback[answer[x]]++;
            }else{
                guessFeedback[answer[x]]=1;
            }
                while(y<wordBank.size()){
                    if(answer[x]==wordBank[y][x] || guessFeedback[answer[x]]>wordInfo[y][answer[x]]){
                        cout<<wordBank[y];
                        wordInfo.erase(wordInfo.begin()+y);
                        wordBank.erase(wordBank.begin()+y);
                        wordletters.erase(wordletters.begin()+y);
                    }else{
                        y++;
                    }
                }
                break;
            
        }
        
    }
    for(int x=0;x<5;x++){
        int y=0;
        if(guessFeedback.find(answer[x]) != guessFeedback.end()){
                continue;
            }else{
                guessFeedback[answer[x]]=0;
            }
        if(feedback[x]=='b'){
            while(y<wordBank.size()){
                if(wordInfo[y][answer[x]]>guessFeedback[answer[x]]){
                    wordInfo.erase(wordInfo.begin()+y);
                    wordBank.erase(wordBank.begin()+y);
                    wordletters.erase(wordletters.begin()+y);
                }else{
                    y++;
                }
            }
        }
    }
    for(auto &itr: guessFeedback){
        cout<<"We have "<<itr.second<<" "<<itr.first<<"\n";
    }
}
void makeList(){
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
    		for(int y=0;y<6;y++){
    		    wordletters[x].emplace(str[y]);
    		    if(wordInfo[x].find(str[y]) != wordInfo[x].end()){
    		        wordInfo[x][str[y]]++;
    		    }else{
    		        wordInfo[x][str[y]]=1;
    		    }
    		}
    		if(fin) cout << wordBank[x] << endl;
    		x++;
    		if(x==2315){
    		    cout<<"Done. ";
    		    fin.close();
    	  	  }
    	}
    }
}
