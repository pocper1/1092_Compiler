#include <iostream>
#include <stack>

using namespace std;

int main() {
  string line;

  while (getline(cin, line)) {
    if (line == "$") {
      break;
    }
    line.substr()
    cout << "this is test"<< line << endl;
}
  return 0;
}

/*
stack<int> sta; //宣告一個專門存放int的stack
int i = 45;     //宣告要存放的元素
sta.empty();    //回傳stack是否為空
sta.size();     //回傳stack內堆疊了幾個元素
sta.push(i);    //將45放到stack最頂端
i = sta.top(); //取得stack最頂端的元素45，如果stack內沒有東西則會回傳error
sta.pop(); //移除stack最頂端的元素45，如果stack內沒有東西則會回傳error
*/

/*
push 2
push 18
inverse
push 66
push 59
dec
push 3
inverse
push 78
inverse
$

58
*/