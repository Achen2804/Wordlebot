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

map<char,int> letter_mark{{'a',0}};
struct Word{
    string name;
    unordered_map<char,int> wordInfo;
    unordered_set<char> wordletters;
};

vector<Word> masterList;
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
    while(guesses<6){
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
    vector<int> wordScore(masterList.size());
    for(int y=0;y<masterList.size();y++){
        for (const char &c: masterList[y].name){
		// check if key `c` exists in the map or not
            if(letterScore.find(c) != letterScore.end()){
                letterScore[c]++;
            }else{
                letterScore[c]=1;
            }
	    }
    }
    letterScore['0']=0;
	for(int y=0;y<masterList.size();y++){
	   for (const char &c: masterList[y].wordletters){
	    wordScore[y]+= letterScore[c];
	   }
	}
	int max=0;
	for(int sc = 0; sc<masterList.size();sc++){
	    if(wordScore[sc]>max){
	        max=wordScore[sc];
	        answer=masterList[sc].name;
	    }
	    
	}
	/*
	for(auto word:masterList){
	  cout<<word.name<<"\n";
	}*/
	cout << "My guess is '"<<answer<<"' based on new info please give feedback \n, score is"<<max;//First guess//
	
}
void cutList(string feedback){
    unordered_map<char,int> guessFeedback; //This tracks the number of times a letter appears
    
    auto finder = letter_mark.find(answer[0]);
    auto nex = next(finder);
    int cur_letter = (*finder).second;
    int next_letter = (*nex).second;
    int y=0;
    switch(feedback[0]){
        case 'g':
        masterList.erase(masterList.begin()+ next_letter,masterList.end());
        masterList.erase(masterList.begin(),masterList.begin()+ cur_letter);
        for(int x =0; x<masterList.size();x++){
            if(masterList[x].wordletters.find(answer[0])==masterList[x].wordletters.end()){
                masterList.erase(masterList.begin()+x);
            }
        }
        guessFeedback[answer[0]]=1;
        break;
        case 'y':
        masterList.erase(masterList.begin()+ cur_letter,masterList.begin()+ next_letter);
        guessFeedback[answer[0]]=1;
        while(y<masterList.size()){
            if(masterList[y].wordletters.find(answer[0])==masterList[y].wordletters.end()){
                masterList.erase(masterList.begin()+y);
            }else{
                y++;
            }
        }
        guessFeedback[answer[0]]=1;
        break;
        case 'b':
        masterList.erase(masterList.begin()+ cur_letter,masterList.begin()+ next_letter);
        while(y<masterList.size()){
            if(masterList[y].wordletters.find(answer[0])!=masterList[y].wordletters.end()){
                masterList.erase(masterList.begin()+y);
            }else{
                y++;
            }
        }
    }
    int test=0;
    
    /*for(auto word:masterList){
	  cout<<word.name<<"\n";
	}
    cout<<"First is done, press enter to keep going";
    
    cin>>test;
    */
    for(int x=1;x<5;x++){
        //cout<<"Working on it mate\n";
        y=0;
        switch(feedback[x]){
            case 'g':
            if(guessFeedback.find(answer[x]) != guessFeedback.end()){
                guessFeedback[answer[x]]++;
            }else{
                guessFeedback[answer[x]]=1;
            }
                while(y<masterList.size()){
                    if(answer[x]!=masterList[y].name[x]){
                        masterList.erase(masterList.begin()+y);
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
                while(y<masterList.size()){
                    //cout<<masterList[y].name<<"\n";
                    if(answer[x]==masterList[y].name[x] || guessFeedback[answer[x]]>masterList[y].wordInfo[answer[x]]){
                        masterList.erase(masterList.begin()+y);
                    }else{
                        y++;
                    }
                }
                break;
            
        }
        /*
        for(auto word:masterList){
	        cout<<word.name<<"\n";
	    }
        cout<<"next is done, press enter to keep going";
        cin>>test;
*/
    }
    for(int x=0;x<5;x++){
        if(guessFeedback.find(answer[x]) != guessFeedback.end()){
            continue;
        }else{
            guessFeedback[answer[x]]=0;
        }
    }
    /*
    for(auto &letter : guessFeedback){
        cout<<letter.first <<" "<<letter.second<<"\n";
    }
    cin>>test;
    */
    letter_mark.clear();
    y=0;
    char prev='0';
    while(y<masterList.size()){
            
            bool cut=false;
        for(int x=0;x<5;x++){
	       if(feedback[x]=='b'){
           if(masterList[y].wordInfo[answer[x]]>guessFeedback[answer[x]]){
                //cout<<masterList[y].name;
                masterList.erase(masterList.begin()+y);
                cut=true;
           }
        }
        char start=masterList[y].name[0];
        if(start!=prev){
            letter_mark[start]=y;
            prev=start;
        }
    }
    
    if(cut)
        y--;
    y++;
}
letter_mark['z'+1] = masterList.size();
/*
for(auto word:masterList){
	cout<<word.name<<"\n";
}
    cout<<"next is done, press enter to keep going";
    cin>>test;
    for(auto &data : letter_mark){
        cout<<data.first<<" "<<masterList[data.second].name<<"\n";
    }
    */
}
void makeList(){
    ifstream fin("wordle-answers.txt");


	cout<< "This program reads and prints a text file" << endl;
	cout<< "Press Enter to begin" << endl;


	if(cin.get() == '\n'){
	string str;
	fin>>str;
	unordered_map<char,int> map;
		unordered_set<char> set;
		for(int y=0;y<5;y++){
		    set.emplace(str[y]);
		    if(map.find(str[y]) != map.end()){
		        map[str[y]]++;
		    }else{
		        map[str[y]]=1;
		    }
		}
		Word ans;
		ans.name = str;
		ans.wordInfo = map;
		ans.wordletters = set;
		masterList.push_back(ans);
	while(fin>>str) {
	    if(str[0]!=masterList[masterList.size()-1].name[0]){
	        letter_mark[str[0]]=(masterList.size());
	    }
		unordered_map<char,int> map;
		unordered_set<char> set;
		for(int y=0;y<6;y++){
		    set.emplace(str[y]);
		    if(map.find(str[y]) != map.end()){
		        map[str[y]]++;
		    }else{
		        map[str[y]]=1;
		    }
		}
		Word ans;
		ans.name = str;
		ans.wordInfo = map;
		ans.wordletters = set;
		masterList.push_back(ans);
	}
		cout<<"Done. ";
		 fin.close();
	    }
	    letter_mark['z'+1] = masterList.size();
    }
