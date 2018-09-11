#ifndef __WCHEAD_H__
#define __WCHEAD_H__

#include<iostream>
#include<string>
using namespace std;

typedef enum{en_success,en_fail,en_true,en_false,en_nullptr} Status;

class class_Data
{
private:
	int itNumOfChar;			//存储当前文件的字符数
	int	itNumOfWord;			//存储当前文件的单词数
	int itNumOfRow;				//存储当前文件的行数
	string strTmpRowStr;		//临时存储刚从文件读入的一行代码


public:
	int GetNumOfChar();			//获取类中已记录的字符数
	int GetNumOfWord();			//获取类中已记录的单词数
	int GetNumOfRow();			//获取类中已记录的行数
	string GetTmpRowStr();		//获取类中存储的临时行代码字符串

};

class class_WordCal : public class_Data
{
private:
	string strFileName;					//存储当前文件名
	string strFileDirPath;				//存储当前文件所在路径

public:
	Status GetCharFormFile();
	Status GetWordFormFile();
	Status GetRowFormFile();



};















#endif