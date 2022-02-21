#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

void scanner(string str) {
  smatch sm;
  regex NUM("([1-9][0-9]*)|0");
  regex PLUS("\\+");
  regex MINUS("\\-");
  regex MUL("\\*");
  regex DIV("\\/");
  regex LPR("\\(");
  regex RPR("\\)");

  if (regex_match(str, NUM)) {
    cout << "NUM " << str << endl;
  } else if (regex_match(str, PLUS)) {
    cout << "PLUS" << endl;
  } else if (regex_match(str, MINUS)) {
    cout << "MINUS" << endl;
  } else if (regex_match(str, MUL)) {
    cout << "MUL" << endl;
  } else if (regex_match(str, DIV)) {
    cout << "DIV" << endl;
  } else if (regex_match(str, LPR)) {
    cout << "LPR" << endl;
  } else if (regex_match(str, RPR)) {
    cout << "RPR" << endl;
  }
}
int main() {
  regex NUM("([1-9][0-9]*)|0");
  string input, tmp_input;
  string tmp = "", tmp_char = "";
  int count = 0;

  while (true) {
    getline(cin, tmp_input);

    if (tmp_input == "") {
      count++;
    } else {
      input += tmp_input;
      count = 0;
    }

    if (count == 2) {
      break;
    }
  }
  input.erase(remove(input.begin(), input.end(), ' '), input.end());

  for (int i = 0; i < input.size(); i++) {
    tmp_char = input[i];
    tmp = tmp_char;
    while (regex_match(tmp_char, NUM)) {

      i = i + 1;
      tmp_char = input[i];
      if (!regex_match(tmp_char, NUM)) {
        i--;
        break;
      }
      tmp += input[i];
    }

    scanner(tmp);

    tmp = "";
    tmp_char = "";
  }

  return 0;
}
