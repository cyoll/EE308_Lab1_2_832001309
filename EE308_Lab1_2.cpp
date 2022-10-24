/*
	MU_ID:20124881
	FZU_ID:832001309
	EE308FZ_Lab1_2.cpp
	AUTHOR:YANG_YANG_EE03
	DATE:2022/10/24
*/
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

const string Keyword[32] = { //关键字数组
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

void test1(int n, char b[]) {
	string buf[100];
	for (int i = 0; i < n; i++) { //将所有非字母的字符替换为空格
		if (!isalpha(b[i]))
			b[i] = ' ';
	}
	char p[] = " ";
	int buflen = 0;
	char *result = NULL;
	result = strtok(b, p);
	while (result != NULL) { //将字符数组按空格转化为字符串数组
//		cout<<result<<"---";
		buf[buflen] = result;
		result = strtok(NULL, p);
		buflen++;
	}
	int count = 0;
	for (int i = 0; i < buflen; i++) { //计算keyword在该数组中出现的次数
		for (int j = 0; j < 32; j++) {
			if (Keyword[j] == buf[i])
				count++;
		}
	}
	cout << "Total num:" << count;
}

void test234(int cnumber, char a[], int fnumber, char b[], int lv) {

	int switchnum = 0, ienum = 0, ieenum = 0;
	for (int i = 0; i <= cnumber; i++) {
		if (a[i] == 's' && a[i + 1] == 'w' && a[i + 2] == 'i' && a[i + 3] == 't' && a[i + 4] == 'c' && a[i + 5] == 'h')
			switchnum++;//switch数量
	}
	int casenum[switchnum] = {0};
	int n = 0, swindex = 0; //switch初始索引为0
	while (n < switchnum) {
		for (int i = swindex; i <= cnumber; i++) {
			int sw1, sw2;
			if (a[i] == 's' && a[i + 1] == 'w' && a[i + 2] == 'i' && a[i + 3] == 't' && a[i + 4] == 'c' && a[i + 5] == 'h') {
				sw1 = i; //先出现的switch索引sw1
				for (int j = sw1; j <= cnumber; j++) {
					if (a[j] == 's' && a[j + 1] == 'w' && a[j + 2] == 'i' && a[j + 3] == 't' && a[j + 4] == 'c' && a[j + 5] == 'h') { //如果后面还有出现switch
						sw2 = j; //后出现的相邻switch索引sw2
						swindex = sw2; //将下一次遍历的索引设为sw2
						for (int k = sw1; k <= sw2; k++) { //在相邻switch之间计算case出现的次数
							if (a[k] == 'c' && a[k + 1] == 'a' && a[k + 2] == 's' && a[k + 3] == 'e')
								casenum[n]++;//case数量
						}
					}
				}
				if (n == switchnum - 1) { //若已经是遍历的最后一遍，之后没有再出现switch
					for (int k = sw1; k <= cnumber; k++) { //在该位置与数组末尾之间计算case出现次数
						if (a[k] == 'c' && a[k + 1] == 'a' && a[k + 2] == 's' && a[k + 3] == 'e')
							casenum[n]++;//case数量
					}
				}
			}
		}
		n++;
	}
	int index;
	for (int i = 0; i <= fnumber; i++) {
		if (b[i] == 'e' && b[i + 1] == 'l' && b[i + 2] == 's' && b[i + 3] == 'e' && b[i + 6] == 'i' && b[i + 7] == 'f') {
			index = i;
			break;//index是第一个else if的位置
		}
	}
	for (int i = index; i <= fnumber; i++) { //遍历整个文档
		if (b[i] == 'e' && b[i + 1] == 'l' && b[i + 2] == 's' && b[i + 3] == 'e' && b[i + 6] == 'i' && b[i + 7] == 'f') { //找到下一个相邻的else if
			int left = 0, right = 0;
			for (int j = index; j <= i; j++) { //计算两者之间左右大括号的数量
				if (b[j] == '{')
					left++;
				if (b[j] == '}')
					right++;
			}
			if (left != right) //若左右大括号数量不相等，则存在一个if_elseif_else结构
				ieenum++;
		}
	}
	index = 0;
	for (int i = index; i <= fnumber; i++) {
		if (b[i] == 'i' && b[i + 1] == 'f' && (b[i - 3] != 'e' || b[i - 4] != 's' || b[i - 5] != 'l' || b[i - 6] != 'e')) {
			index = i; //if的索引位
			int temp;
			int left = 0, right = 0;
			for (int k = index; k <= fnumber; k++) {
				if (b[k] == 'e' && b[k + 1] == 'l' && b[k + 2] == 's' && b[k + 3] == 'e' && b[k + 6] == 'i' && b[k + 7] == 'f') { //如果if 后面的第一个else是else if，则退出循环寻找下一个if
					temp = 0; //这种情况的标志是temp=0
					break;
				} else if (b[k] == 'e' && b[k + 1] == 'l' && b[k + 2] == 's' && b[k + 3] == 'e') { //else的索引位
					temp = k; //用temp指代else的索引位
					break;
				}
			}
			if (temp == 0)
				continue;
			else {
				for (int j = index; j <= temp; j++) { //计算相邻的if和else之间左右大括号的数量
					if (b[j] == '{')
						left++;
					if (b[j] == '}')
						right++;
				}
			}
			if (left == right) //在相邻if和else之间若左右大括号数量相等，则存在一个if_else结构
				ienum++;
		}
	}
	if (lv > 1) {
		cout << "\nswitch num:" << switchnum << endl;
		cout << "case num:";
		for (int i = 0; i < switchnum; i++)
			cout << casenum[i] << " ";
		if (lv > 2) {
			cout << "\nif_else:" << ienum;
			if (lv > 3)
				cout << "\nif_elseif_else:" << ieenum;
		}
	}
}

int main() {
	int temp = 0;
	//创建流对象
	ifstream ifs;
	//输入文件名
	string fname;
	while (temp == 0) { //循环直到成功打开文件
		cout << "Please enter the file path:";
		cin >> fname;
		//打开文件并且判断是否打开成功
		ifs.open(fname, ios::in) ;
		temp = 1;
		if (!ifs.is_open()) {
			temp = 0;
			cout << "文件打开失败" << endl;
		}
	}
	int lv;
	cout << "Please choose the completion level (from low to high as 1, 2, 3, 4):";
	cin >> lv;
	char a[1000], b[2000], c,b1[2000];
	int fnumber = 0, cnumber = 0;
	while ((c = ifs.get()) != EOF) {
		if (isalpha(c)) { //将所有字母存进a数组
			a[cnumber] = c;
			cnumber++;
		}
		b[fnumber] = c; //为文件中所有字符创建字符数组
		fnumber++;
	}
	for(int i=0;i<fnumber;i++){
		b1[i]=b[i];
	}
	test1(fnumber, b1);
	test234(cnumber, a, fnumber, b, lv);
	ifs.close();
	return 0;
}
