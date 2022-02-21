#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

regex strdcl("s");
regex id("[a-o|q|r|t-z]");
regex quote("\"");
regex str("[a-z|A-Z|0-9]*");
regex print("p");
vector<string> ve;
void Proc();
void Dcl(string);
void Astring();
void Stmt(string);

int main() {
  Proc();
  return 0;
}

void Proc() {
  string input,input_tmp;
  bool flag = 1;
  regex strdcl("s", regex_constants::extended);
  regex print("p", regex_constants::extended);
  match_results<string::const_iterator> rerResult;

  while (cin >> input) {
    if (input == "0")
      break;
    for (int i = 0; i < input.size(); i++) {
      if (input[i] == 's' || input[i] == 'p') {
        input_tmp += input[i];
        ve.push_back(input_tmp);
        input_tmp="";
      }else if()
        
      
    }
  }
  for (int i = 0; i < ve.size(); i++) {
    cout << "str: " << ve[i] << endl;
    
  }
}
/*
|Proc   | Dcl Stmt $
|Dcl    | strdcl id Astring
|Astring| quote string quote
|Stmt   | print id
|
|

*/
