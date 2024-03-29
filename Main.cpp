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
#include <cstdlib>

using namespace std;


struct Word{
    string name;
    unordered_map<char,int> wordInfo;
    unordered_set<char> wordletters;
    float score;
    Word* next;
};
/*
struct Word* newWord(string name,unordered_map<char,int> wordInfo,unordered_set<char> wordletters) {
   Word* word = new Word;
   string name;
    unordered_map<char,int> wordInfo;
    unordered_set<char> wordletters;
   word->next = NULL;
   return word;
}
*/
string answer{"salet"};
void makeList();
int cutList(string feedback);
void score(string feedback);
map<char,Word*> letter_mark;
Word* start = new Word;
string removalguess(string feedback);
vector<Word> masterList;
//void firstCut(char ch,int position);
//void cut(string feedback);

int main()
{
    string feedback;
    int guesses=1;
    makeList();//This is making my list of words//
    cout << "My guess is '"<<answer<<"' please give feedback by entering b y or g on each position depending if the letter is blank, yellow or green\n Example input, ggbyg. ";//First guess//
    cin >>feedback;
    
    if(feedback=="ggggg"){
        cout<<"And we're done.";}
    else{
    cutList(feedback);//This reduces my answer pool. 
    score(feedback);
    cout<<"Scoring done: ";
    while(guesses<6){
    guesses++;
    cout<<"My guess is "<<answer<<" please give feedback.";
    cin >>feedback;
    if(feedback=="ggggg"){
        cout<<"Aaaannnnd done. It took me "<<guesses<<" guesses";
        break;
    }else{
        int answercount = cutList(feedback);
        if(count(feedback.begin(),feedback.end(),'b')==1 && answercount>1){
            answer = removalguess(feedback);
        }else{
            score(feedback);
        }
    }
    }
    return 0;
}
    
}
string removalguess(string feedback){
    int check_index = feedback.find('b');
    unordered_map<char,int> letterScore;
    
    Word* head=start->next;
    while(head){
        char c = head->name[check_index];
        if(letterScore.find(c) != letterScore.end()){
            letterScore[c]++;
        }else{
            letterScore[c]=1;
        }
	    
	    head=head->next;
    }
    
    int max=0;
    for(int x=0;x<masterList.size();x++){
        int score = 0;
        for(const char &c : masterList[x].wordletters){
            score += letterScore[c];
        }
        masterList[x].score = score;
        if(score>max){
            max=score;
            answer=masterList[x].name;
        }
    }
    return answer;
}
void score(string feedback){
    unordered_map<char, float> letterScore;
    Word* head=start->next;
    while(head){
        for (const char &c: head->wordletters){
            if(letterScore.find(c) != letterScore.end()){
                letterScore[c]+=1+((head->wordInfo[c]-1)/2);
            }else{
                letterScore[c]=1;
            }
	    }
	    head=head->next;
    }
    
    head=start->next;
    int max=0;
    while(head){
        int score=0;
	    for (const char &c: head->wordletters){
	       score+=letterScore[c];
	    }
	    head->score=score;
	    if(head->score>max){
	        max=head->score;
	        answer=head->name;
	    }
	    head=head->next;
	}
}
int cutList(string feedback){
    int answercount=0;
    unordered_map<char,int> guessFeedback; //This tracks the number of times a letter appears
    Word* head=start->next;
    Word* previous_word = start;
    if(letter_mark.find(answer[0])!=letter_mark.end()){
        auto finder = letter_mark.find(answer[0]);
        auto nex = next(finder);
        Word* start_of_section = (*finder).second;
        Word* end_of_section = (*nex).second;
        
        switch(feedback[0]){
            case 'g':
            head=start_of_section->next;
            start_of_section->next = NULL;
            end_of_section->next=NULL;
            start->next=head;
            previous_word=start;
            guessFeedback[answer[0]]=1;
            break;
            case 'y':
            letter_mark.erase(answer[0]);
            start_of_section->next=end_of_section->next;
            end_of_section->next=NULL;
            guessFeedback[answer[0]]=1;
            head= start->next;
            
            while(head){
                //cout<<head->name<<"\n";
                if(head->wordletters.find(answer[0])==head->wordletters.end()){
                    previous_word->next=head->next;
                    head->next=NULL;
                    head=previous_word->next;
                }else{
                    previous_word=head;
                    head=head->next;
                }
            }
            //guessFeedback[answer[0]]=1;
            break;
            case 'b':
            letter_mark.erase(answer[0]);
            start_of_section->next=end_of_section->next;
            end_of_section->next=NULL;
            head=start->next;
            //cout<<head->name;
        }
    }
    /*
    head=start->next;
    previous_word=start;
    while(head){
        cout<<head->name<<"\n";
        head=head->next;
    }
    */
    for(int x=1;x<5;x++){
        head=start->next;
        previous_word=start;
        switch(feedback[x]){
            case 'g':
            if(guessFeedback.find(answer[x]) != guessFeedback.end()){
                guessFeedback[answer[x]]++;
            }else{
                guessFeedback[answer[x]]=1;
            }
                while(head){
                    if(answer[x]!=head->name[x]){
                        previous_word->next=head->next;
                        head->next=NULL;
                        head=previous_word->next;
                    }else{
                        previous_word=head;
                        head=head->next;
                    }
                }
                break;
                
            case 'y':
            if(guessFeedback.find(answer[x]) != guessFeedback.end()){
                guessFeedback[answer[x]]++;
            }else{
                guessFeedback[answer[x]]=1;
            }
                while(head){
                    if(answer[x]==head->name[x] || guessFeedback[answer[x]]>head->wordInfo[answer[x]]){
                        previous_word->next=head->next;
                        head->next=NULL;
                        head=previous_word->next;
                    }else{
                        previous_word=head;
                        head=head->next;
                    }
                }
                break;
            
        }
    }
    for(int x=0;x<5;x++){
        if(guessFeedback.find(answer[x]) != guessFeedback.end()){
            continue;
        }else{
            guessFeedback[answer[x]]=0;
        }
    }
    
    letter_mark.clear();
    char prev='0';
    head=start->next;
    previous_word=start;
    while(head){
        for(int x=0;x<5;x++){
	        if(feedback[x]=='b' && head){
	            //cout<<head->name<<"\n";
                while(head && head->wordInfo[answer[x]]>guessFeedback[answer[x]] ){
                    previous_word->next=head->next;
                    head->next=NULL;
                    head=previous_word->next;
               }
            }
        }
        if(!head){
            break;
        }
        if(head->name[0]!=prev){
            //Update my letter_mark since this is the first word with a new letter
            letter_mark[head->name[0]]=previous_word;
            prev=head->name[0];
        }
            previous_word=head;
            head=head->next;
            //answercount++;
        }
    letter_mark['z'+1] = previous_word;
    start=letter_mark.begin()->second;
    head=start->next;
    
    while(head){
        cout<<head->name<<"\n";
        head=head->next;
        answercount++;
    }
    for(auto &data : letter_mark){
        cout<<data.first<<" "<<data.second->name<<"\n";
    }
    return answercount;
    
}
void makeList(){
    ifstream fin("wordle-answers_shortened.txt");


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
		
		Word *ans = new Word;
		ans->name = str;
		ans->wordInfo = map;
		ans->wordletters = set;
		Word* prev = ans;
		
		start->next=prev;
		start->name="Starting";
		
		letter_mark['a']=start;
		
		masterList.push_back(*prev);
	while(fin>>str) {
	    if(str[0]!= prev->name[0]){
	        letter_mark[str[0]]=prev;
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
		Word *ans = new Word;
		ans->name = str;
		ans->wordInfo = map;
		ans->wordletters = set;
		masterList.push_back(*ans);
		prev->next=ans;
		prev=ans;
	}
	Word* head=start;
	
	cout<<"Done. ";
	fin.close();
    }
}
