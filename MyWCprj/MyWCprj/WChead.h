#ifndef __WCHEAD_H__
#define __WCHEAD_H__
#define _CRT_SECURE_NO_WARNINGS
//#pragma execution_character_set("utf-8")

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdarg.h>
#include<io.h>
using namespace std;

typedef enum{en_success,en_fail,en_true,en_false,en_nullptr} Status;
typedef struct {
	bool bEffective;		//有效行标识
	bool bComm1;			//	"//"	注释行标识
	bool bComm2;			//	"/**/"	注释行标识
	//bool bEmpty;			//空行标识
}AllStatus;	//高级统计状态标识结构体


class class_Data
{
public:
	int iNumOfChar;				//存储当前文件的字符数
	int	iNumOfWord;				//存储当前文件的单词数
	int iNumOfLine;				//存储当前文件的行数
	int iNumOfEffectiveLine;	//存储当前文件的有效代码行数
	int iNumOfEmptyLine;		//存储当前文件的空行数
	int iNumOfCommentLine;		//存储当前文件的注释行数
	string strTmpRowStr;		//临时存储刚从文件读入的一行代码
	AllStatus allStatus;		//高级统计状态机
	
	class_Data()
	{
		iNumOfChar = 0;
		iNumOfWord = 0;
		iNumOfLine = 0;
		iNumOfEffectiveLine = 0;
		iNumOfEmptyLine = 0;
		iNumOfCommentLine = 0;
		allStatus.bComm1 = false;
		allStatus.bComm2 = false;
		allStatus.bEffective = false;
		//allStatus.bEmpty = false;
	}

	~class_Data()
	{

	}

};


class class_WordCal : public class_Data
{
public:
	bool bOpChar;						//字符统计输出开关						
	bool bOpLine;						//行数统计输出开关
	bool bOpWord;						//词组统计输出开关
	bool bOpRecursion;					//递归统计开关
	bool bOpAll;						//更复杂数据统计开关
	int iFileNameIndex;					//存储文件名的stringVector中带操作的文件名下标
	ifstream tmpifs;					//存储当前打开文件的文件读操作类
	vector<string> vStrFileOrDirName;	//存储当前文件名的stringVector
	vector<string> vStrCodeFilePath;	//存储文件或目录路径的stringVector
	string strFilePath;					//存储当前文件的路径


	void Option(int argc, char *argv[]);			//功能选择函数
	void Display(int Index);						//统计输出函数
	void StringSkip(string s, int &pos);			//当s中存在' ' '\t' '\n' '\r'时，将pos置于该字符之后
	void myFileFind(string DirPath);				//对传入目录路径下的所有代码文件(.c .cpp .h) 录入至 vStrCodeFilePath 中
	void DirList(vector<string> &vStr, const string strPath);	//从strPath指定的路径中递归查找代码文件，并录入至vStrCodeFilePath中

	int getword(FILE *fp);							//从输入流中获取下一个词组，读取至文件结尾或异常情况出现时返回0，返回1则为其他情况
	Status SetIfstream(vector<string> vStr, int Index);	//设置打开文件的文件读操作类
	//Status CountFromFile(int Index);				//(旧代码，不兼容-s统计功能)对vStrFileOrDirName中第Index个文件名对应文件进行代码统计(-l -w -c)
	//Status CountFromFileAll(int Index);			//(旧代码，不兼容-s统计功能)对vStrFileOrDirName中第Index个文件名对应文件进行高级代码统计(-a)

	Status CountFromDir(int Index);					//对vector<string>中第Index个目录下的所有代码文件进行递归统计(-s)
	Status CountFromFile(vector<string> vStr, int Index);//对vector<string>中第Index个文件名对应文件进行代码统计(-l -w -c)
	Status CountFromFileAll(vector<string> vStr, int Index);//对vector<string>中第Index个文件名对应文件进行高级代码统计(-a)
	void Display(vector<string> vStr, int Index);	//vector<string>中第Index个文件名输出统计函数
	Status EmptyCheck(string s, int pos);			//空行检查与统计
	
	void CountMain();								//统计功能入口
	void workMain(int argc, char *argv[]);			//类主功能函数入口

};















#endif