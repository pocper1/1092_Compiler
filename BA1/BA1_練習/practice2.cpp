#include <iostream>
#include <regex>
#include <string>

using namespace std;
regex LPH("\\(", regex_constants::extended);
regex RPH("\\)", regex_constants::extended);
regex LBR("\\[", regex_constants::extended);
regex RBR("\\]", regex_constants::extended);
regex LCB("\\{", regex_constants::extended);
regex RCB("\\}", regex_constants::extended);

void program();
void exprs(string);
void expr(string);
bool check_input(string);

int main() {
  program();
  return 0;
}

void program() {
  string input;
  getline(cin, input);

  if(check_input(input))
    exprs(input);
  else
    cout << "error" << endl;
}

bool check_input(string str) {
    regex in("[\\( | \\) | \\[ | \\] | \\{ || \\}]");
    match_results<string::const_iterator> res;
    if (regex_match(str, res, in)) {
      return true;
    } else {
      return false;
    }
}

void exprs(string str) {
  expr(str);
  exprs(str);
}

void expr(string str) {
  match_results<string::const_iterator> res;
  if (regex_match(str, res, LPH)) {

  } else if (regex_match(str, res, LBR)) {

  } else if (regex_match(str, res, LCB)) {
    
  }
}