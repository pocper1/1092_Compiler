#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

void output(string input);
vector<string> words;
int main() {
  string input;
  getline(cin, input);
  cout << "in int:" << input << endl;
  output(input);
  return 0;
}

void output(string input) {
  cout << input << endl;
  string tmp_input;
  vector<string> words;
  size_t pos = 0;
  string space_delimiter = " ";
  int num = 0;
  float f_num = 0.0;
  tmp_input = input;

  
  for (auto str : words) {
    cout << "ibn for: " << str << endl;
  }
  cout << "int:" << endl;
  cout << num << endl;
  cout << "double:" << endl;
  cout << f_num << endl;
}

/*
#include <string>
find
substr
*/