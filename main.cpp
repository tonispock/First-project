#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <math.h>
#include <iterator>

using namespace std;


typedef struct Sentence {
    string word;	     //记录句子
    int num;			 //记录字数
}Sentence;

string a, b;
double sum = 0;
double f = 0;
char num[5000][5000];       //记录中间结果的数组
char flag[5000][5000];    //标记数组，用于标识下标的走向，构造出公共子序列
void LCS();                //动态规划求解
void getLCS();              //采用倒推方式求最长公共子序列
void lib(string file);
void txt(string file);
Sentence S[100000];
Sentence T[100000];
int n, m;

//int main(int argc,char* argv[])
int main()
{
    lib("D://test//orig.txt");
    txt("D://test//orig_0.8_add.txt");
    //cout << "libfile:" << argv[1] << endl;
    //cout << "textfile:" << argv[2] << endl;
    //cout << "outfile:" << argv[3] << endl;
    //lib(argv[1]);
    //txt(argv[2]);
    memset(num, 0, n);
    memset(flag, 0, m);
    double rate = f / sum;
    cout << "copy rate:" << f / m;
    //ofstream out(argv[3]);
    //out<< "copy rate:" << f / m;
    //out.close();
    getchar();
    return 0;
}

void lib(string file) {
    ifstream infile;
    infile.open(file);   //将文件流对象与文件连接起来 
    assert(infile.is_open());
    string temp;
    n = 0;
    while (getline(infile, temp)) {
        S[n].word = temp;
        S[n].num = temp.length();
        n++;
    }
    infile.close();
}

void txt(string file) {
    ifstream infile;
    infile.open(file);   //将文件流对象与文件连接起来 
    assert(infile.is_open());
    string temp;
    m = 0;
    sum = 0;
    while (getline(infile, temp)) {
        T[m].word = temp;
        T[m].num = temp.length();
        LCS();
        sum += temp.length();
        m++;
    }
    infile.close();
}

void LCS()
{
    sum = 0;
    int Max = 0;
    for (int k = 0; k < n; k++)
    {
        for (int i = 1; i <= S[k].num; i++)
        {
            for (int j = 1; j <= T[m].num; j++)
            {
                a = S[k].word;
                b = T[m].word;
                if (a[i - 1] == b[j - 1])   ///注意这里的下标是i-1与j-1
                {
                    num[i][j] = num[i - 1][j - 1] + 1;
                    flag[i][j] = 1;  ///斜向下标记
                    Max = num[i][j] > Max ? num[i][j] : Max;
                    if (Max > 13) {
                        f++;
                        break;
                    }
                }
                else if (num[i][j - 1] > num[i - 1][j])
                {
                    num[i][j] = num[i][j - 1];
                    flag[i][j] = 2;  ///向右标记
                }
                else
                {
                    num[i][j] = num[i - 1][j];
                    flag[i][j] = 3;  ///向下标记
                }
            }
            if (Max > 13) {
                break;
            }
        }
    }
}
/*
void getLCS()
{

    char res[500];
    int i = a.length();
    int j = b.length();
    int k = 0;    ///用于保存结果的数组标志位
    while (i > 0 && j > 0)
    {
        if (flag[i][j] == 1)   ///如果是斜向下标记
        {
            res[k] = a[i - 1];
            k++;
            i--;
            j--;
        }
        else if (flag[i][j] == 2)  ///如果是斜向右标记
            j--;
        else if (flag[i][j] == 3)  ///如果是斜向下标记
            i--;
    }

    for (i = k - 1; i >= 0; i--)
        printf("%c", res[i]);
}*/