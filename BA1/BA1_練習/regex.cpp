
// 字元	說明
// {n}	重複n次
// {n,}	重複n或更多次
// {n,m}	重複[n ~ m]次
// *	重複0次或多次，等同於{0,}
// +	重複1次或多次，等同於{1,}
// ?	重複0次或1次，等同於{0,1}
//
// C++ regex函式有3個：regex_match、regex_search 、regex_replace
// regex_match是正則表示式匹配的函式->全詞匹配
// regex_search是另外一個正則表示式匹配的函式->搜尋其中匹配的字串
//regex_replace是替換正則表示式匹配內容的函式