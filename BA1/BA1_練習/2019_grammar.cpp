#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

// regex
regex ID("[A-Za-z_][A-Za-z0-9_]*");
regex STRLIT("[^\"]*");
regex LBR("[\\(]");
regex RBR("[\\)]");
regex DOT("[\\.]");
regex SEMICOLON(";");

void program();
void stmts(string);
void stmt(string);
void exp(string);
void primary(string);
void primary_tail(string);

bool flag = 1;

int main() {
  program();
  return 0;
}

void program() {
  string input;
  getline(cin, input);
  stmts(input);

  if (flag == 0)
    cout << "Invalid" << endl;
  else
    cout << "Valid" << endl;
}

void stmts(string input) {
  if (input != "")
    stmt(input);
  else
    stmts(input);
}

void stmt(string str) {
  match_results<string::const_iterator> rerResult;
  size_t find = str.find_first_of(";");
  if (find != -1) {
    cout << "in stmt: " << str.substr(0, find) << endl;
    exp(str.substr(0, find));
  } else
    flag = 0;
}

void exp(string str) {
  if (str.length() == 0)
    return;
  match_results<string::const_iterator> rerResult;
  regex STRLIT("[^\"]*", regex_constants::extended);
  cout << "exp: " << str << endl;
  size_t find = str.find_first_of("\"");
  if (find != -1) {
    primary(str.substr(0, find));
  } else
    flag = 0;
}

void primary(string str) {
  if (str.length() == 0)
    return;
  cout << "primary: " << str << endl;
  regex ID("[A-Za-z_][A-Za-z0-9_]*", regex_constants::extended);
  regex LBR("[\\(]", regex_constants::extended);
  regex DOT("[\\.]", regex_constants::extended);
  match_results<string::const_iterator> rerResult;

  size_t find = str.find_first_of(".(");
  if (find != -1) {
    primary_tail(str.substr(find, str.length()));
  }
}

void primary_tail(string str) {
  if (str.length() == 0)
    return;
  cout << "primary_tail: " << str << endl;
  size_t find_dot = str.find_first_of(".");
  size_t find_lbr = str.find_first_of("(");
  // DOT ID primary_tail
  if (find_dot != -1) {
    size_t find = str.find_first_of(".(", find_dot + 1);
    if (find != -1) {
      primary_tail(str.substr(find, str.length()));
    }
  }
  // LBR exp RBR primary_tail
  else if (find_lbr != -1) {
    size_t find_rbr = str.find_first_of(")", find_lbr + 1);
    exp(str.substr(find_lbr, find_rbr));
    primary(str.substr(find_rbr, str.length()));
  }
}