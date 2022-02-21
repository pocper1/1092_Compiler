#include <cstring>
#include <iostream>

using namespace std;

// //藉助strtok實現split
// #include<iostream>
// #include <cstring>
// using namespace std;

// int main()
// {
//     char s[] = "Hello    Nice, to meet  ,* you";
//     /*
//     ** 用 空格，星號，逗號進行分割
//     ** 無論多少個，都會被當作一個key
//     */
//     const char* d = "  *,";   //分割依據
//     char *p;  //儲存每次分割結果
//     p = strtok(s,d);

//     while(p)
//     {
//     	cout<<p<<endl;
//         p=strtok(NULL,d);
//     }

//     return 0;
// }
// ========================================================
// //藉助strtok實現split
int main() {
  char s[] = "Hello    Nice, to meet  ,* you";

  const char *d = "  *,"; //分割依據
  char *p;                //儲存每次分割結果
  //第一次呼叫需引數s
  p = strtok(s, d);
  cout << "first:" << p << endl;
  //後面的呼叫，引數為NULL
  p = strtok(NULL, d);
  cout << "second: " << p << endl;

  return 0;
}
// ========================================================
// find函式用法一
// size_type find(const basic_string &str, size_type index);
//  str：尋找依據，即要尋找什麼；

//       index：從哪裡開始尋找。

// 2）一個引數：

//       一個引數，預設從第一個字元開始尋找。

// 3）未找到則返回string::npos;

// ========================================================
// substr函式用法
// basic_string substr( size_type index, size_type num = npos );
// index：子串起始位置；

// num：子串長度。

// ========================================================
// 使用 std::string::find 和 std::string::substr 函式在 C++ 中按空格分割字串
// find 和 substr
// 是std::string內建函式，可用於通過字串值或單個字元指定的任何定界符來分割字串。
// find 函式使用一個
// string引數，並返回給定子字串開始的位置；否則，如果找不到，則返回
// string::npos。 因此，我們在 while 迴圈中進行迭代，直到 find 函式返回 npos
// 為止。 同時，可以使用 substr
// 方法訪問分隔符之前的字串部分，在這種情況下，分隔符是單個空格字元，並儲存到
// vector 中供以後使用。之後，我們呼叫 erase
// 函式刪除第一個序列，包括定界符，這時可能會進行新的迭代以重複操作。

// #include <iostream>
// #include <string>
// #include <sstream>
// #include <iterator>
// #include <vector>
// #include <algorithm>

// using std::cout; using std::cin;
// using std::endl; using std::string;
// using std::vector; using std::istringstream;
// using std::stringstream;

// int main(){
//     string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
//                   "Sed laoreet sem leo, in posuere orci elementum.";
//     string space_delimiter = " ";
//     vector<string> words{};

//     size_t pos = 0;
//     while ((pos = text.find(space_delimiter)) != string::npos) {
//         words.push_back(text.substr(0, pos));
//         text.erase(0, pos + space_delimiter.length());
//     }
//     for (const auto &str : words) {
//         cout << str << endl;
//     }

//     return EXIT_SUCCESS;
// }

// ========================================================
// vector 使用方式
// #include <vector>
// vector 類別是以容器模式為基準設計的
// begin(), end(), size(), max_size(), empty(), swap()  等用法。

// vec[i] - 存取索引值為 i 的元素值。
// vec.at(i) - 存取索引值為 i 的元素的值，
// vec.front() - 回傳 vector 第一個元素的值。
// vec.back() - 回傳 vector 最尾元素的值。

//  新增或移除元素的用法
// vec.push_back() - 新增元素至 vector 的尾端，必要時會進行記憶體配置。
// vec.pop_back() - 刪除 vector 最尾端的元素。
// vec.insert() - 插入一個或多個元素至 vector 內的任意位置。
// vec.erase() - 刪除 vector 中一個或多個元素。
// vec.clear() - 清空所有元素。

// 取得長度/容量的用法
// vec.empty() - 如果 vector 內部為空，則傳回 true 值。
// vec.size() - 取得 vector 目前持有的元素個數。
// vec.resize() - 改變 vector 目前持有的元素個數。
// vec.capacity() - 取得 vector
// 目前可容納的最大元素個數。這個方法與記憶體的配置有關，它通常只會增加，不會因為元素被刪減而隨之減少。

// 疊代 (Iterator)
// vec.begin() - 回傳一個 iterator，它指向 vector 第一個元素。
// vec.end() - 回傳一個 iterator，它指向 vector
// 最尾端元素的下一個位置（請注意：它不是最末元素）。 vec.rbegin() -
// 回傳一個反向 iterator，它指向 vector 最尾端元素的。 vec.rend() - 回傳一個
// iterator，它指向 vector 的第一個元素。