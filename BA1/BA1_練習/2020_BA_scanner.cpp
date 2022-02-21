#include <iostream>
#include <regex>
#include <string>

using namespace std;

regex ID("[A-Za-z_][A-Za-z0-9_]*");
regex SEMICOLON(";");
regex LBR("\\(");
regex RBR("\\)");
regex OP("[ + | - | * | / | = ]");
regex NUM("-?[1-9][0-9]*");

void scanner(string);
bool input_check(string);

int main() {
  string input;
  while (true) {
    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    // if (input_check(input))
      scanner(input);
    // else
    //   cout << "invalid input" << endl;
  }
}
bool input_check(string str) {
  regex IN("([A-Za-z_][A-Za-z0-9_]*) | ; | \\( | \\) | ([ + | - | * | / | = ])",
           regex_constants::extended);
  match_results<string::const_iterator> res;

  if (regex_match(str, res, IN)) {
    return true;
  } else {
    return false;
  }
}

void scanner(string str) {
  string tmp, str_tmp;
  int po;
  for (auto i = 0; i < str.size(); i++) {

    tmp = str[i];

    if (regex_match(tmp, ID)) {

      str_tmp += tmp;
      po = i;
      while (true) {
        tmp = str[++i];
        ++po;

        if (po == str.size())
          break;

        if (regex_match(str_tmp, ID)) {
          str_tmp += tmp;

        } else {
          str_tmp[str_tmp.length() - 1] = '\0';
          po -= 2;
          break;
        }
      }

      cout << "ID " << str_tmp << endl;
      str_tmp = "";
      i = po;

    } else if (regex_match(tmp, SEMICOLON)) {
      cout << "SEMICOLON " << tmp << endl;
    } else if (regex_match(tmp, LBR)) {
      cout << "LBR " << tmp << endl;
    } else if (regex_match(tmp, RBR)) {
      cout << "RBR " << tmp << endl;
    } else if (regex_match(tmp, OP)) {
      cout << "OP " << tmp << endl;
    } else if (regex_match(tmp, NUM)) {

      str_tmp += tmp;

      po = i;
      while (true) {
        if (po == str.size()) {
          break;
        }
        tmp = str[++i];
        ++po;
        if (regex_match(tmp, NUM)) {
          str_tmp += tmp;
        } else {
          --po;
          break;
        }
      }

      cout << "NUM " << str_tmp << endl;
      str_tmp = "";
      i = po;
    } else {
      cout << "invalid input" << endl;
    }
  }
}

/*
HELLO87 (1 + 2 + 3)
*/