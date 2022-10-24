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

const string Keyword[32] = { //�ؼ�������
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
	for (int i = 0; i < n; i++) { //�����з���ĸ���ַ��滻Ϊ�ո�
		if (!isalpha(b[i]))
			b[i] = ' ';
	}
	char p[] = " ";
	int buflen = 0;
	char *result = NULL;
	result = strtok(b, p);
	while (result != NULL) { //���ַ����鰴�ո�ת��Ϊ�ַ�������
//		cout<<result<<"---";
		buf[buflen] = result;
		result = strtok(NULL, p);
		buflen++;
	}
	int count = 0;
	for (int i = 0; i < buflen; i++) { //����keyword�ڸ������г��ֵĴ���
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
			switchnum++;//switch����
	}
	int casenum[switchnum] = {0};
	int n = 0, swindex = 0; //switch��ʼ����Ϊ0
	while (n < switchnum) {
		for (int i = swindex; i <= cnumber; i++) {
			int sw1, sw2;
			if (a[i] == 's' && a[i + 1] == 'w' && a[i + 2] == 'i' && a[i + 3] == 't' && a[i + 4] == 'c' && a[i + 5] == 'h') {
				sw1 = i; //�ȳ��ֵ�switch����sw1
				for (int j = sw1; j <= cnumber; j++) {
					if (a[j] == 's' && a[j + 1] == 'w' && a[j + 2] == 'i' && a[j + 3] == 't' && a[j + 4] == 'c' && a[j + 5] == 'h') { //������滹�г���switch
						sw2 = j; //����ֵ�����switch����sw2
						swindex = sw2; //����һ�α�����������Ϊsw2
						for (int k = sw1; k <= sw2; k++) { //������switch֮�����case���ֵĴ���
							if (a[k] == 'c' && a[k + 1] == 'a' && a[k + 2] == 's' && a[k + 3] == 'e')
								casenum[n]++;//case����
						}
					}
				}
				if (n == switchnum - 1) { //���Ѿ��Ǳ��������һ�飬֮��û���ٳ���switch
					for (int k = sw1; k <= cnumber; k++) { //�ڸ�λ��������ĩβ֮�����case���ִ���
						if (a[k] == 'c' && a[k + 1] == 'a' && a[k + 2] == 's' && a[k + 3] == 'e')
							casenum[n]++;//case����
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
			break;//index�ǵ�һ��else if��λ��
		}
	}
	for (int i = index; i <= fnumber; i++) { //���������ĵ�
		if (b[i] == 'e' && b[i + 1] == 'l' && b[i + 2] == 's' && b[i + 3] == 'e' && b[i + 6] == 'i' && b[i + 7] == 'f') { //�ҵ���һ�����ڵ�else if
			int left = 0, right = 0;
			for (int j = index; j <= i; j++) { //��������֮�����Ҵ����ŵ�����
				if (b[j] == '{')
					left++;
				if (b[j] == '}')
					right++;
			}
			if (left != right) //�����Ҵ�������������ȣ������һ��if_elseif_else�ṹ
				ieenum++;
		}
	}
	index = 0;
	for (int i = index; i <= fnumber; i++) {
		if (b[i] == 'i' && b[i + 1] == 'f' && (b[i - 3] != 'e' || b[i - 4] != 's' || b[i - 5] != 'l' || b[i - 6] != 'e')) {
			index = i; //if������λ
			int temp;
			int left = 0, right = 0;
			for (int k = index; k <= fnumber; k++) {
				if (b[k] == 'e' && b[k + 1] == 'l' && b[k + 2] == 's' && b[k + 3] == 'e' && b[k + 6] == 'i' && b[k + 7] == 'f') { //���if ����ĵ�һ��else��else if�����˳�ѭ��Ѱ����һ��if
					temp = 0; //��������ı�־��temp=0
					break;
				} else if (b[k] == 'e' && b[k + 1] == 'l' && b[k + 2] == 's' && b[k + 3] == 'e') { //else������λ
					temp = k; //��tempָ��else������λ
					break;
				}
			}
			if (temp == 0)
				continue;
			else {
				for (int j = index; j <= temp; j++) { //�������ڵ�if��else֮�����Ҵ����ŵ�����
					if (b[j] == '{')
						left++;
					if (b[j] == '}')
						right++;
				}
			}
			if (left == right) //������if��else֮�������Ҵ�����������ȣ������һ��if_else�ṹ
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
	//����������
	ifstream ifs;
	//�����ļ���
	string fname;
	while (temp == 0) { //ѭ��ֱ���ɹ����ļ�
		cout << "Please enter the file path:";
		cin >> fname;
		//���ļ������ж��Ƿ�򿪳ɹ�
		ifs.open(fname, ios::in) ;
		temp = 1;
		if (!ifs.is_open()) {
			temp = 0;
			cout << "�ļ���ʧ��" << endl;
		}
	}
	int lv;
	cout << "Please choose the completion level (from low to high as 1, 2, 3, 4):";
	cin >> lv;
	char a[1000], b[2000], c,b1[2000];
	int fnumber = 0, cnumber = 0;
	while ((c = ifs.get()) != EOF) {
		if (isalpha(c)) { //��������ĸ���a����
			a[cnumber] = c;
			cnumber++;
		}
		b[fnumber] = c; //Ϊ�ļ��������ַ������ַ�����
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
