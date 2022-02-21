#include <iostream>
#include <regex>
#include <string>

using namespace std;
void htmlDocument(string);
void htmlElement(string);
void htmlContent(string);
void htmlAttributeList(string);
void htmlAttribute(string);
void htmlChardata(string);
void attribute(string);

regex TAG_OPEN_SLASH("</", regex_constants::extended);
regex TAG_OPEN("<", regex_constants::extended);
regex TAG_CLOSE(">", regex_constants::extended);
regex TAG_EQUALS("=", regex_constants::extended);
regex SINGLE_QUOTE_STRING("'[^\'<]*'", regex_constants::extended);
regex DOUBLE_QUOTE_STRING("[^\"<]*", regex_constants::extended);
regex TAG_NAME("[a-z|A-Z|0-9]+", regex_constants::extended);
regex HTML_TEXT("[^<]+", regex_constants::extended);

int main() {
  string input;
  getline(cin, input);

  htmlDocument(input);
  return 0;
}

void htmlDocument(string str) {
  if (str != "")
    htmlElement(str);
  else
    htmlDocument(str);
}

void htmlElement(string str) {
  
  bool inTagDef = false;
  string tmp_str, tmp_htmlstr;
  char tmp, tmp_htmlchr;
  int length = 0, pointer = 0;
  for (int i = 0; i < str.length(); i++) {
    if (i < str.length() - 1 && str[i] == '<' && str[i + 1] == '/') {
      inTagDef = true;
      // ... generate TAG_OPEN_SLASH token

      tmp_htmlstr = "";
      cout << "TAG_OPEN_SLASH </" << endl;
      i++;
    } else if (str[i] == '<') {
      // ... generate TAG_OPEN token
      inTagDef = true;
      cout << "TAG_OPEN <" << endl;

    } else if (str[i] == '>') {
      inTagDef = false;
      // ... generate TAG_CLOSE token

      cout << "TAG_CLOSE >" << endl;
    } else if (str[i] == '=') {
      // ... generate TAG_EQUALS token
      cout << "TAG_EQUALS =" << endl;
    } else if (str[i] == '\'' && inTagDef == true) {
      // ... generate SINGLE_QUOTE_STRING token
      size_t fi = str.find_first_of("\'", i + 1);

      if (fi != -1) {
        cout << "SINGLE_QUOTE_STRING " << str.substr(i + 1, fi - i - 1) << endl;
        i = fi;
      }
    } else if (str[i] == '"' && inTagDef == true) {
      // ... generate DOUBLE_QUOTE_STRING token
      size_t fi = str.find_first_of("\"", i + 1);

      if (fi != -1) {
        cout << "DOUBLE_QUOTE_STRING " << str.substr(i + 1, fi - i - 1) << endl;
        i = fi;
      }

    } else if (str[i] == ' ') {
      continue;
    } else if (inTagDef) {
      // ... generate TAG_NAME token

      char tmp = str[i];
      while (true) {

        if (tmp == ' ' || tmp == '>' || tmp == '=') {
          tmp_str[tmp_str.size()] = '\0';
          --i;
          break;
        } else {
          tmp_str += tmp;
          tmp = str[++i];
        }
      }
      cout << "TAG_NAME " << tmp_str << endl;
      tmp_str = "";
    } else {
      // ... generate HTML_TEXT token
      // htmlChardata(str);
      
      char tmp_htmlchr = str[i];
      while (true) {
        if (tmp_htmlchr == '<') {
          tmp_htmlstr[tmp_htmlstr.size()] = '\0';
          --i;
          break;
        } else {
          tmp_htmlstr += tmp_htmlchr;
          tmp_htmlchr = str[++i];
        }
      }
      cout << "HTML_TEXT " << tmp_htmlstr << endl;
      tmp_htmlstr = "";
    }
  }
}

//========================================================================
void htmlContent(string str) {
  /*
          |4| htmlContent         | htmlChardata htmlContent |
    |5| htmlContent         | htmlElement htmlContent |
    |6| htmlContent         | λ |
  */
  // abc
  cout << "htmlContent" << str << endl;
}

void htmlAttributeList(string str) {
  /*
    |7| htmlAttributeList   | htmlAttribute htmlAttributeList |
    |8| htmlAttributeList   | λ |
  */
  // class='red' id='main'

  cout << "htmlAttributeList " << str << endl;
  if (str != "")
    htmlAttribute(str);
  else
    htmlAttributeList(str);
}

void htmlAttribute(string str) {
  /*
                |9| htmlAttribute       | TAG_NAME TAG_EQUALS attribute |
  */
  
}

void htmlChardata(string str) {
  /*
                |10| htmlChardata       | HTML_TEXT |
  */
}

void attribute(string str) {
  /*
    |11| attribute          | DOUBLE_QUOTE_STRING |
                |12| attribute          | SINGLE_QUOTE_STRING |
  */
  if (regex_match(str, DOUBLE_QUOTE_STRING)) {
    cout << "DOUBLE_QUOTE_STRING" << endl;
  } else if (regex_match(str, SINGLE_QUOTE_STRING)) {
    cout << "SINGLE_QUOTE_STRING" << endl;
  }
}

/*
example:
<html> <div class='red'>text in div</div> </html>

TAG_OPEN <
TAG_NAME html
TAG_CLOSE >
TAG_OPEN <
TAG_NAME div
TAG_NAME class
TAG_EQUALS =
SINGLE_QUOTE_STRING red
TAG_CLOSE >
HTML_TEXT text in div
TAG_OPEN_SLASH </
TAG_NAME div
TAG_CLOSE >
TAG_OPEN_SLASH </
TAG_NAME html
TAG_CLOSE >

<div>"test"</div>
*/