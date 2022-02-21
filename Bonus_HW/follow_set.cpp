#include <algorithm>
#include <iostream>
#include <set>
#include <string.h>
#include <vector>

using namespace std;

// struct
struct Rule {
  // if has a rule like 「A -> BCD」
  // its nonTerminal would be A
  // its production would be BCD
  char nonTerminal;
  string production;

public:
  Rule(char nonTerminal, string production) {
    this->nonTerminal = nonTerminal;
    this->production = production;
  }
};
struct FirstSet {
  // if A's first set contains b, c, d three symbol
  // its nonTerminal would be A
  // its set would be bcd
  char nonTerminal;
  string set;

public:
  FirstSet(char nonTerminal, string set) {
    this->nonTerminal = nonTerminal;
    this->set = set;
  }
};

struct FollowSet {
  // if A's first set contains b, c, d three symbol
  // its nonTerminal would be A
  // its set would be bcd
  char nonTerminal;
  string set;

public:
  FollowSet(char nonTerminal, string set) {
    this->nonTerminal = nonTerminal;
    this->set = set;
  }
};

// variable
vector<Rule> rules;
vector<FirstSet> firstSets;
vector<FollowSet> followSets;
vector<FollowSet> initFollowSets;

// functions
void firstset();
void followset();

bool checkChanged(vector<FollowSet> initFollowSets,
                  vector<FollowSet> followSets);
void output();
bool mycompare(FollowSet a, FollowSet b);
bool compare(FollowSet a, FollowSet b);

int main() {
  firstset();
  followset();
  return 0;
}

void firstset() {
  // put the follow code into start of your main function
  const int maxLineLength = 500;
  // the code to handle input

  char input[maxLineLength];
  // handle grammar part
  cin.getline(input, maxLineLength);
  while (strcmp(input, "END_OF_GRAMMAR")) { // if same, strcmp would return 0
    char nonTerminal = input[0];
    string production;
    for (int i = 2; i < strlen(input); i++) {
      if (input[i] != '|') {
        production += input[i];
      } else {
        rules.push_back(Rule(nonTerminal, production));
        production = "";
      }
    }
    rules.push_back(Rule(nonTerminal, production));
    cin.getline(input, maxLineLength);
  }

  // handle first set part
  cin.getline(input, maxLineLength);
  while (strcmp(input, "END_OF_FIRST_SET")) { // if same, strcmp would return 0
    char nonTerminal = input[0];
    string production;
    for (int i = 2; i < strlen(input); i++) {
      production += input[i];
    }
    firstSets.push_back(FirstSet(nonTerminal, production));
    cin.getline(input, maxLineLength);
  }
}

void followset() {
  cout << "in the follow set" << endl;
  //   sample code for observing the data, which constructed by input
  for (int i = 0; i < rules.size(); i++) {
    cout << rules[i].nonTerminal << " -> " << rules[i].production << endl;
  }
  for (int i = 0; i < firstSets.size(); i++) {
    cout << firstSets[i].nonTerminal << "'s first set is " << firstSets[i].set
         << endl;
  }

  //   Rules 1
  //   add $ into Follow(start symbol)
  for (int i = 0; i < firstSets.size(); i++) {
    char nonTerminal = firstSets[i].nonTerminal;
    string set;
    if (nonTerminal == 'S') {
      followSets.push_back(FollowSet(nonTerminal, "$"));
    } else {
      followSets.push_back(FollowSet(nonTerminal, set));
    }
  }

  int counter = 0;

  int step = 0;
  set<char> chars;
  string tmp;
  // init followSet
  for (int aa = 0; aa < followSets.size(); aa++) {
    char nonTerminal = followSets[aa].nonTerminal;
    string set = followSets[aa].set;
    initFollowSets.push_back(FollowSet(nonTerminal, set));
  }

  do {
    bool end_null = false;
    cout << "========= step:" << step << " =========" << endl;

    for (int i = 0; i < initFollowSets.size(); i++) {

      if (initFollowSets[i].nonTerminal == followSets[i].nonTerminal) {
        initFollowSets[i].set = followSets[i].set;
      }
    }

    for (int ss = 0; ss < initFollowSets.size(); ss++) {
      cout << "times: " << ss << "nonTerminal "
           << initFollowSets[ss].nonTerminal << endl;
      cout << "times: " << ss << "set " << initFollowSets[ss].set << endl;
    }

    // loop each rule R like A -> B1 B2 B3 ... Bn in production rules:
    for (int i = 0; i < rules.size(); i++) {
      cout << "- terminals: " << rules[i].nonTerminal << endl;
      cout << "-- rule: " << rules[i].production << endl;

      //   loop each nonTerminal symbol B in rule R's RHS - 「B1 B2 B3 ...
      //   Bn」:
      for (int j = 0; j < rules[i].production.length(); j++) {
        if (rules[i].production[j] >= 'A' && rules[i].production[j] <= 'Z') {
          cout << "find " << rules[i].production[j] << " index: " << j << endl;
          end_null = true;
          //   loop each symbol C after B in rule R:x
          for (int k = j + 1; k < rules[i].production.length(); k++) {

            if (rules[i].production[k] >= 'A' &&
                rules[i].production[k] <= 'Z') {
              end_null = true;
              cout << rules[i].production[k] << "'s first ";

              for (int z = 0; z < firstSets.size(); z++) {
                if (firstSets[z].nonTerminal == rules[i].production[k]) {
                  cout << firstSets[z].set << endl;
                  tmp = firstSets[z].set;
                  break;
                }
              }

              cout << "add first(" << rules[i].production[k] << ") into follow("
                   << rules[i].production[j] << ")" << endl;
              cout << rules[i].production[j] << " + " << tmp << endl;
              for (int q = 0; q < followSets.size(); q++) {
                if (followSets[q].nonTerminal == rules[i].production[j]) {
                  for (int s = 0; s < tmp.length(); s++) {
                    if (tmp[s] == ';') {
                      tmp.erase(s, 1);
                      //   cout << "trim:tmp->" << tmp << endl;
                    }
                  }
                  set<char> chars;
                  followSets[q].set += tmp;
                  followSets[q].set.erase(remove_if(followSets[q].set.begin(),
                                                    followSets[q].set.end(),
                                                    [&chars](char i) {
                                                      if (chars.count(i)) {
                                                        return true;
                                                      }

                                                      chars.insert(i);
                                                      return false;
                                                    }),
                                          followSets[q].set.end());

                  cout << "----- " << followSets[q].nonTerminal
                       << "'s follow: " << followSets[q].set << endl;
                }
              }
            } else {
              end_null = false;
              cout << "---- add char " << rules[i].production[k]
                   << " into follow(" << rules[i].production[j] << endl;
              cout << rules[i].production[j] << " + " << rules[i].production[k]
                   << endl;

              for (int q = 0; q < followSets.size(); q++) {
                if (followSets[q].nonTerminal == rules[i].production[j]) {
                  set<char> chars;
                  followSets[q].set += rules[i].production[k];
                  followSets[q].set.erase(remove_if(followSets[q].set.begin(),
                                                    followSets[q].set.end(),
                                                    [&chars](char i) {
                                                      if (chars.count(i)) {
                                                        return true;
                                                      }

                                                      chars.insert(i);
                                                      return false;
                                                    }),
                                          followSets[q].set.end());

                  cout << "----- " << followSets[q].nonTerminal
                       << "'s follow: " << followSets[q].set << endl;
                }
              }
            }
            // if symbol C can not be λ:

            for (int cv = 0; cv < firstSets.size(); cv++) {
              if (firstSets[cv].nonTerminal == rules[i].production[k]) {
                size_t found = -1;
                found = firstSets[cv].set.find(";");
                if (found == -1) {
                  { end_null = false; }
                }
              }
            }
          }
          //   RULE3
          if (end_null) {
            size_t found;
            set<char> chars;
            int A_index = -1, B_index = -1;
            // if 「each symbol C after B in rule R」 can be λ:

            for (int q = 0; q < followSets.size(); q++) {

              if (followSets[q].nonTerminal == rules[i].nonTerminal) {

                A_index = q;
              }
              if (followSets[q].nonTerminal == rules[i].production[j]) {
                B_index = q;
              }
            }
            // if (followSets[A_index].set != "$") {
            followSets[B_index].set += followSets[A_index].set;
            // }

            // followSets[B_index].set += tmp;
            followSets[B_index].set.erase(
                remove_if(followSets[B_index].set.begin(),
                          followSets[B_index].set.end(),
                          [&chars](char i) {
                            if (chars.count(i)) {
                              return true;
                            }

                            chars.insert(i);
                            return false;
                          }),
                followSets[B_index].set.end());
          }
        }
      }
    }
    step++;
  } while (checkChanged(initFollowSets, followSets));

  //   ===================================================================
  cout << endl << "the result follow set" << endl;
  sort(followSets.begin(), followSets.end(), mycompare);
  for (int kk = 0; kk < followSets.size(); kk++) {
    sort(followSets[kk].set.begin(), followSets[kk].set.end());
  }

  for (int i = 0; i < followSets.size(); i++) {
    cout << followSets[i].nonTerminal << " " << followSets[i].set << endl;
  }
}

bool mycompare(FollowSet a, FollowSet b) {
  return a.nonTerminal < b.nonTerminal; // 降序排列
}

bool checkChanged(vector<FollowSet> initFollowSets,
                  vector<FollowSet> followSets) {
  for (int i = 0; i < initFollowSets.size(); i++) {
    cout << "initFollowSets[i].nonTerminal: " << initFollowSets[i].nonTerminal
         << " initFollowSets[i].set: " << initFollowSets[i].set << endl;
  }
  for (int i = 0; i < followSets.size(); i++) {
    cout << "followSets[i].nonTerminal: " << followSets[i].nonTerminal
         << " followSets[i].set: " << followSets[i].set << endl;
  }
  cout << "----------check change-----------  " << endl;
  int count = 0;
  for (int i = 0; i < initFollowSets.size(); i++) {

    if (initFollowSets[i].set.length() == followSets[i].set.length()) {
      count++;
    } else {
      cout << initFollowSets[i].set << " changed" << endl;
    }
  }

  cout << "----------end check change-----------  " << endl;
  cout << "count: " << count << " followSets.size(): " << followSets.size()
       << endl;
  if (count == followSets.size()) {
    return false;
  } else {

    return true;
  }
}