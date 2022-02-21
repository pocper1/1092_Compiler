#include <iostream>
#include <regex>
#include <string>

using namespace std;
void s1();
void s2(string);
void s3(string);
void s4(string);

int main() {
  s1();
  return 0;
}

void s1() {
  string input;
  getline(cin, input);
  if (input[0] == 'a') {
    s2(input.substr(1, input.size()));
  } else if (input[0] == 'b') {
    s3(input.substr(1, input.size()));
  } else {
    cout << "NO";
  }
}

void s2(string str) {
  //   cout << "this is s2: " << str << endl;
  if (str[0] == 'a') {
    s2(str.substr(1, str.size()));
  } else if (str[0] == 'b') {
    s4(str.substr(1, str.size()));
  } else {
    cout << "NO";
  }
}

void s3(string str) {
  //   cout << "this is s3: " << str << endl;
  if (str[0] == 'a') {
    s3(str.substr(1, str.size()));
  } else if (str[0] == 'c') {
    s4(str.substr(1, str.size()));
  } else if (str[0] == '$') {
    cout << "YES s3";
  } else {
    cout << "NO";
  }
}

void s4(string str) {
  //   cout << "this is s4" <<str << endl;
  if (str[0] == '$') {
    cout << "YES s4";
  } else {
    cout << "NO";
  }
}