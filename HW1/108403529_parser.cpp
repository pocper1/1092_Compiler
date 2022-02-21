#include <cstddef>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

regex ID("[A-Za-z_][A-Za-z0-9_]*");
regex STRLIT("[^\"]*");
regex LBR("[\\(]");
regex RBR("[\\)]");
regex DOT("[\\.]");
// smatch sm;
void program();
void stmt(string);
void stmts(string);
void primary(string);
void primary_tail(string);
string check_validate(string);

int main(void) {
  program();
  return 0;
}

string check_validate(string str) {
  string error_msg = "invalid input";

  regex repPattern("[A-Za-z0-9_ | '“' | '”' | '\"' | '(' | ')' | '.']*",
                   regex_constants::extended);
  match_results<string::const_iterator> rerResult;

  bool validate = regex_match(str, rerResult, repPattern);
  if (validate) {
    return str;
  } else {
    cout << "invalid input" << endl;
    return error_msg;
  }
}

void program() {
  string input, tmp;
  bool flag = false;

  while (true) {
    getline(cin, input);
    if (input == "")
      flag = true;
    else {
      flag = false;
      tmp = check_validate(input);

      if (tmp != "invalid input")
        stmts(tmp);
    }
    if (flag == true) {
      break;
    }
  }
}

void stmts(string str) {
  if (str != "") {
    stmt(str);
  }
}

void stmt(string str) {
  regex STRLIT("\"[^\"]*\"", regex_constants::extended);
  regex ID("[A-Za-z_][A-Za-z0-9_]*", regex_constants::extended);
  match_results<string::const_iterator> rerResult;
  int count = 0;
  if (str.length() == 0) {
    return;
  }
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '\"')
      count++;
  }

  if (count % 2 == 0) {
    if (regex_match(str, rerResult, STRLIT)) {
      cout << "STRLIT " << str << endl;
    } else {
      primary(str);
    }
  } else {
    cout << "invalid input" << endl;
  }
}

void primary(string str) {
  size_t found = str.find_first_of("\\.\\(");
  string tmp_str;

  for (auto i = 0; i < str.length(); i++) {
    if (found != -1)
      break;
    found = str.find_first_of(".(", found + 1);
  }

  if (found != -1) {
    cout << "found: " << found << endl;
    tmp_str = str.substr(0, found);
    cout << "ID " << tmp_str << endl;
    primary_tail(str.substr(found, str.length()));
  } else {
    tmp_str = str.substr(0, str.length());
    cout << "ID " << tmp_str << endl;
  }
}

void primary_tail(string str) {
  if (str.length() == 0)
    return;
  int pos_dot, pos_lbr;
  string tmp_str, remain;
  pos_dot = -1;
  pos_lbr = -1;
  cout << endl;
  cout << str << endl;
  // cout << "primary_tail: " << str << endl;

  // DOT
  pos_dot = str.find(".");
  if (pos_dot != -1) {
    cout << "DOT ." << endl;

    // determine iD
    remain = str.substr(pos_dot + 1, str.length());
    // cout << "delet dot: " << remain << endl;
    // cout << "remain: " << remain << endl;

    size_t found = remain.find_first_of("\\.\\(");

    while (found != string::npos) {
      if (found != -1)
        break;
      found = str.find_first_of("\\.\\(", found + 1);
    }
    cout << "after: found: " << found << endl;

    tmp_str = remain.substr(0, found);

    if (found != -1) {
      cout << "ID " << tmp_str << endl;
      // cout << "callback" << str.substr(found + 1, str.length()) << endl;
      primary_tail(str.substr(found + 1, str.length()));
    }
  }

  // LBR
  pos_lbr = str.find("(");
  cout << "87" << endl;
  if (pos_lbr != -1) {
    cout << "LBR (" << endl;

    // primary_tail
    remain = str.substr(pos_lbr + 1, str.length()); // delete (
    size_t RBR = str.find_first_of(")");            // found )
    // cout << "pos: " << pos_lbr + 1 <<" "<< RBR << endl;
    remain = str.substr(pos_lbr + 1, RBR - (pos_lbr + 1));

    // cout << "1remain: " << remain << endl;
    if (remain != "") {
      cout << "fuck" << endl;
      stmt(remain);
    }

    // determine primary_tail

    cout << "RBR )" << endl;
    if (RBR != -1) {
      remain = str.substr(RBR + 1, str.length());
      cout << "after RBR: " << remain << endl;
      if (remain != "") {
        cout << "fuck you" << endl;
        primary_tail(remain);
      }
    }
  }
}
