#include <iostream>
#include <iterator>
#include <regex>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

string peek();
void Proc();
void Dcl();
void Astring();
void Stmt();


vector<string> sentence;
string input,cin_temp,temp;
bool isValid;
regex strdcl("[s]");
regex id("[a-o|q|r|t-z]");
regex quote("[\"]");
regex rstring("[a-zA-Z0-9]*");
regex print("[p]");

int main()
{
    int string_symbol_num=0;
    while (cin >> cin_temp) {
        if (cin_temp == "0") {
            break;
        }
        input += cin_temp;
    }
    for (int i = 0; i < input.size();i++) {
        //cout << input[i];
        if (input[i] != '\\') {
            if (input[i] == 's' || input[i] == 'p') {
                //如果有還沒push的部分先push
                if (temp != "") {
                    sentence.push_back(temp);
                    temp = "";
                }
                temp += input[i];
                sentence.push_back(temp);
                temp = "";
            }
            else if (input[i] == '\"') {
                string_symbol_num += 1;
                if (string_symbol_num % 2 == 0) {
                    sentence.push_back(temp);
                    temp = "";
                    temp += input[i];
                    sentence.push_back(temp);
                    temp = "";
                    //cout << " 3" << endl;
                }
                else {
                    //vector_num += 1;
                    sentence.push_back(temp);
                    temp = "";
                    temp += input[i];
                    sentence.push_back(temp);
                    temp = "";
                    //cout << " 4" << endl;
                }   
            }
            else {
                if (i == 0) {
                    temp += input[i];
                    //cout << " 5" << endl;
                }
                else if (input[i - 1] != '\\') {
                    temp += input[i];
                    //cout << " 6" << endl;
                    if (i == input.size() - 1) {
                        sentence.push_back(temp);
                    }
                }   
            }
        }
    }
    
    for (int j = 0; j < sentence.size(); j++) {
        cout << j+1 << ":" << sentence[j] << endl;
    }

    Proc();
    if(isValid==0){
        cout<<"valid input"<<endl;
    }
}

string peek() {
    if (sentence.size() == 0) {
        return "";
    }
    else if (regex_match(sentence.front(), strdcl)) {
        return "strdcl";
    }
    else if (regex_match(sentence.front(), id)) {
        return "id";
    }
    else if (regex_match(sentence.front(), quote)) {
        return "quote";
    }
    else if (regex_match(sentence.front(), rstring)) {
        return "string";
    }
    else if (regex_match(sentence.front(), print)) {
        return "print";
    }
    return "invalid input";
}

void Proc() {
    Dcl();
    Stmt();
}

void Dcl() {
    cout << "strdcl " << sentence.front() << endl;
    sentence.erase(sentence.begin());
    cout<<peek()<<endl;
    if(peek()=="invalid input"){
        isValid=0;
    }
    else{
        cout << "id " << sentence.front() << endl;
        sentence.erase(sentence.begin());
        Astring();
    }
}

void Astring() {
    cout << "quote " << sentence.front() << endl;
    sentence.erase(sentence.begin());
    cout << "string " << sentence.front() << endl;
    sentence.erase(sentence.begin());
    cout << "quote " << sentence.front() << endl;
    sentence.erase(sentence.begin());
}

void Stmt() {
    cout << "print " << sentence.front() << endl;
    sentence.erase(sentence.begin());
    cout << "id " << sentence.front() << endl;
    sentence.erase(sentence.begin());
}





// s a "g6hf "
// p a