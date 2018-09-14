[TOC]



---

# MyWCprj.exe

[Github仓库地址](https://github.com/Gaveu/CodeFileWordCalculator)

[博客地址]()

## 1. What is MyWCprj.exe?

`wc`是linux下一个非常好用的代码统计小工具，可以通过 `-c` 、`-w` 、`-l`等选项分别进行对指定文件的代码字符数、词组数、行数统计。应学校软件工程课程的PSP个人项目开发实践需要，特此尝试自己写一个用c++实现的`wc`(`MyWCprj.exe`)，该程序仅能确保统计.c .cpp .h文件代码数的正确性。

### 语法

```
MyWCprj.exe [parameter] [fileOrDir_name1] [fileOrDir_name2] ……
```

### 功能参照

```
 //输出文件 file.c 的字符数
MyWCprj.exe -c file.c   

 //输出文件 file.c 的词的数目  
MyWCprj.exe -w file.c   

//输出文件 file.c 的行数
MyWCprj.exe -l file.c    

//输出文件 file.c
MyWCprj.exe -a file.c 	 

//递归处理目录fileDir及其子目录中代码文件，无其他参数时仅列举目录fileDir及其子目录中代码文件(.c .cpp .h),可配合一个或多个 -c -w -l -a 一起处理。
MyWCprj.exe -s fileDir  

//输出file1.c、file2.c、file3.c的行数
MyWCprj.exe -l file1.c file2.c file3.c	

//递归输出DirPath1、DirPath2、DirPath3目录及其子目录下所有代码文件的行数
MyWCprj.exe -s -l DirPath1 DirPath2 DirPath3 


```

### 测试示例

参考中典型的源代码文件 CommonSrcCode.cpp：

```C
#include"WChead.h"


int main(int argc,char *argv[])
{
	/*cout << "ar num=" << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "No." << i << " ";
		cout << "ar =" << argv[i] << endl;
	}
	system("PAUSE");*/

	if (argc < 2)
	{
		cout << "" << endl;
		return -1;
	}

	class_WordCal myWC;
	myWC.workMain(argc, argv);

	//system("PAUSE");
	return 0;
}
```

测试：

```powershell
# 运行环境：windows 10 pro,ver 1803,powershell
# 使用 dir 命令，可看出 I:\TmpCode 下的示例代码文件
PS ..\MyWCprj\Debug> dir I:\TmpCode
Directory: I:\TmpCode
Mode                LastWriteTime         Length Name

------
#典型的源代码文件 CommonSrcCode.cpp	
-a----        9/14/2018   9:34 AM            384 CommonSrcCode.cpp	
#空代码文件 EmptyCode.cpp
-a----        9/14/2018   7:29 PM              0 EmptyCode.cpp	
#仅有字符'a'的代码文件 Onechar.cpp
-a----        9/14/2018   7:32 PM              1 Onechar.cpp	
#仅有字符串“#pragma once”的代码文件 Oneline.cpp	
-a----        9/14/2018   7:34 PM             12 Oneline.cpp
#仅有字符串“#define” 的代码文件 Oneword.cpp	
-a----        9/14/2018   7:32 PM              7 Oneword.cpp	

# 使用 .\MyWCprj.exe -s -w -c -l -a I:\TmpCode 组合
# 可看出 MyWCprj.exe 递归输出当前目录下的代码文件对应信息
PS ..\MyWCprj\Debug> .\MyWCprj.exe -s -w -c -l -a I:\TmpCode
list_size: 5
No.0  I:\TmpCode\CommonSrcCode.cpp:
The Num of chars: 360  I:\TmpCode\CommonSrcCode.cpp
The Num of words: 45  I:\TmpCode\CommonSrcCode.cpp
The Num of Lines: 24  I:\TmpCode\CommonSrcCode.cpp
The Num of Effective lines: 8  I:\TmpCode\CommonSrcCode.cpp
The Num of Empty lines: 9  I:\TmpCode\CommonSrcCode.cpp
The Num of Comment lines: 8  I:\TmpCode\CommonSrcCode.cpp

No.1  I:\TmpCode\EmptyCode.cpp:
The Num of chars: 0  I:\TmpCode\EmptyCode.cpp
The Num of words: 0  I:\TmpCode\EmptyCode.cpp
The Num of Lines: 0  I:\TmpCode\EmptyCode.cpp
The Num of Effective lines: 0  I:\TmpCode\EmptyCode.cpp
The Num of Empty lines: 1  I:\TmpCode\EmptyCode.cpp
The Num of Comment lines: 0  I:\TmpCode\EmptyCode.cpp

No.2  I:\TmpCode\Onechar.cpp:
The Num of chars: 1  I:\TmpCode\Onechar.cpp
The Num of words: 1  I:\TmpCode\Onechar.cpp
The Num of Lines: 0  I:\TmpCode\Onechar.cpp
The Num of Effective lines: 1  I:\TmpCode\Onechar.cpp
The Num of Empty lines: 0  I:\TmpCode\Onechar.cpp
The Num of Comment lines: 0  I:\TmpCode\Onechar.cpp

No.3  I:\TmpCode\Oneline.cpp:
The Num of chars: 12  I:\TmpCode\Oneline.cpp
The Num of words: 2  I:\TmpCode\Oneline.cpp
The Num of Lines: 0  I:\TmpCode\Oneline.cpp
The Num of Effective lines: 1  I:\TmpCode\Oneline.cpp
The Num of Empty lines: 0  I:\TmpCode\Oneline.cpp
The Num of Comment lines: 0  I:\TmpCode\Oneline.cpp

No.4  I:\TmpCode\Oneword.cpp:
The Num of chars: 7  I:\TmpCode\Oneword.cpp
The Num of words: 1  I:\TmpCode\Oneword.cpp
The Num of Lines: 0  I:\TmpCode\Oneword.cpp
The Num of Effective lines: 1  I:\TmpCode\Oneword.cpp
The Num of Empty lines: 0  I:\TmpCode\Oneword.cpp
The Num of Comment lines: 0  I:\TmpCode\Oneword.cpp

```



## 2. PSP实践

PSP2.1表格

| PSP2.1                                | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟） |
| ------------------------------------- | --------------------------------------- | ---------------- | ---------------- |
| Planning                              | 计划                                    | 430              | 120              |
| Estimate                              | 估计这个任务需要多少时间                | 30               | 15               |
| Development                           | 开发                                    | 400              | 300              |
| Analysis                              | 需求分析 (包括学习新技术)               | 150              | 45               |
| Design Spec                           | 生成设计文档                            | 20               | 40               |
| Design Review                         | 设计复审 (和同事审核设计文档)           | 20               | 60               |
| Coding Standard                       | 代码规范 (为目前的开发制定合适的规范)划 | 10               | 85               |
| Design                                | 具体设计                                | 30               | 120              |
| Code Review                           | 代码复审                                | 30               | 60               |
| Test                                  | 测试（自我测试，修改代码，提交修改）    | 30               | 120              |
| PReporting                            | 报告                                    | 110              | 50               |
| Test Report                           | 测试报告                                | 30               | 60               |
| Size Measurement                      | 计算工作量                              | 20               | 40               |
| Postmortem & Process Improvement Plan | 事后总结, 并提出过程改进计划            | 60               | 70               |
| 合计                                  | 计划                                    | 430              | 680              |



## 3.分析思路

由于曾经有过在linux上逆向分析二进制程序的经验，对于`ltrace` 、`wc`、`objdump`、`ptrace`、`gdb`等二进制分析与调试工具有一定的了解与使用经历，所以对于`wc`功能也有一定的了解。

于是乎，去`GNU`找`WC`命令行工具的[C源码](https://www.gnu.org/software/cflow/manual/html_node/Source-of-wc-command.html)，简洁且优雅，在性能与可读性上有非常好的平衡。据其分析之，于是就以C++的方式实现了`-c`、`-w`、`-l`的功能，并初步封装入c++自定义的类`class_WordCal`中。

对于`-a`功能，要求分析出待统计代码文件的空行、注释行、有效代码行。先是与室友沟通，结果很天马行空，基于字符判断的分析模式利用代码实现很困难且可读性不佳，于是在google中查阅与编译原理、代码预处理相关的网页与资料，结果在csdn论坛中获得启发。[依然是源码注释行统计.请进来看看，感谢之至！](https://bbs.csdn.net/topics/380106995)。可利用状态机的思想:

```实现举个最简单的例子：/**/注释，不考虑其他的C语法。
假定一开始是非注释状态，读入一个字符，如果不是/，保持非注释状态继续读入字符，
如果字符是/，读入下一个字符，如果不是*，保持非注释状态，如果是*，进入注释状态；
在注释状态，类似的读入字符，如果不是*，保持注释状态继续读入字符，
如果字符是*，读入下一个字符，如果不是/，保持注释状态，如果是/，退出注释状态进入非字符状态。
```

于是自己依据该思想创建了一个结构体：

```c++
typedef struct {	
	bool bEffective;		//有效行标识
	bool bComm1;			//	"//"	注释行标识
	bool bComm2;			//	"/**/"	注释行标识
}AllStatus;	//高级统计状态标识结构体
```

具体的功能思路的代码实现见Github代码有。

至于`-s`功能，由于对windows的文件操作不算太熟悉，于是在网上查找目录递归遍历的思路，基本上就是调用诸如`_findfirst` 、`_findnext`的库函数，逐个获取目录下的子目录或文件的路径并存之于对应的`string`类的`vector`，遇到子目录则对子目录路径进行递归遍历。如此反复，最终可获得一个关于所有子目录路径的`vector<string>`,和关于所有代码文件路径的`vector<string>`。然后根据每一个代码文件路径实现指定的分析与信息输出功能即可。难点在于如何实现递归遍历上，这对于提升编程能力与启发编程思想来说是一个很好的实践。



## 4.大体设计

1. 高级统计(-a)状态结构体` AllStatus`:

   ```c++
   typedef struct {
   	bool bEffective;		//有效行标识
   	bool bComm1;			//	"//"	注释行标识
   	bool bComm2;			//	"/**/"	注释行标识
   }AllStatus;	//高级统计状态标识结构体
   ```

2. 数据统计类 `class_data`:

```c++
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
		allStatus.bEmpty = false;
	}

	~class_Data()
	{

	}

};

```

3. 总功能类设计class_WordCal:

```c++
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
```



## 关键功能伪码

1. `-c` 、`-w` 、`-l`：

   ```c++
   wc_basic_function(FileName)
   {
       File *fp = fopen(FileName, "r");
       char c;
       bool bEnd = false;
       while(bEnd != true)
       {
           while ((c = getc(fp)) != EOF)
           {
               if (isalpha(c))	//调用stdarg.h中的isalpha(),判断是否为词组，是则词组数++；
               {
                   iNumOfWord++;
                   break;
               }
               iNumOfChar++;
               if ((c) == '\n')
               {
                   iNumOfLine++;
               }
           }
           while (c != EOF)	//由于词组判断完后上一个循环结束，此循环将继续统计行数及字符数。
           {
               iNumOfChar++;
               if ((c) == '\n')
               {
                   iNumOfLine++;
               }
               if (!isalpha(c))
               {
                   break;
               }
               c = getc(fp);
           }
           bEnd = (c != EOF);
       }
   }
   ```

2. `-a`:

```c++
function_GetFileAllInfo()
{
	Status tmpStatus;
	allStatus.bComm1 = allStatus.bComm2 = allStatus.bEffective = false;	//高级统计状态机初始化
	iNumOfEffectiveLine = iNumOfEmptyLine = iNumOfCommentLine = 0;	//代码行数、空行数、注释行数置零初始化
	while (!tmpifs.eof())
	{
		pos = 0;
		allStatus.bEffective  = false;
		getline(tmpifs, strTmpRowStr);	//读取文件中的一行代码

		StringSkip(strTmpRowStr, pos);

		tmpStatus = EmptyCheck(strTmpRowStr, pos);	//空行检查与统计
		if (en_true == tmpStatus)
		{
			continue;
		}
		else if (en_fail == tmpStatus)
		{
			return en_fail;
		}

		while (1)
		{
			if (false == allStatus.bComm2
				&&	'/' == strTmpRowStr[pos]
				&& '/' == strTmpRowStr[pos + 1])	//读取到"//"的情况
			{
				if (false == allStatus.bEffective)
				{
					iNumOfCommentLine++;
				}
				else
				{
					iNumOfEffectiveLine++;
				}
				break;
			}

			if (false == allStatus.bComm2
				&&	'}' == strTmpRowStr[pos]
				&& '/' == strTmpRowStr[pos + 1]
				&& '/' == strTmpRowStr[pos + 2])	//读取到"}//"的情况
			{
				if (false == allStatus.bEffective)
				{
					iNumOfCommentLine++;
				}
				else
				{
					iNumOfEffectiveLine++;
				}
				break;
			}

			if (false == allStatus.bComm2
				&&	'/' == strTmpRowStr[pos]
				&& '*' == strTmpRowStr[pos + 1])	//读取到"/*"的情况
			{
				pos += 2;
				allStatus.bComm2 = true;
				continue;
			}
			if (true == allStatus.bComm2)	//	"/**/"的过滤处理
			{
				if ('*' == strTmpRowStr[pos] && '/' == strTmpRowStr[pos + 1])	//读到"*/"时的状态处理
				{
					pos++;
					allStatus.bComm2 = false;
					iNumOfCommentLine++;
				}
				else if ('\0' == strTmpRowStr[pos])	//读取至行末时的处理
				{
					if (true == allStatus.bEffective)	//若此时为有效代码状态，则代码行数++。例如 printf("hello\n"); /*this is a hello print*/
					{
						iNumOfEffectiveLine++;
					}
					else	//否则，此处代表纯注释行，则注释行数++
					{
						iNumOfCommentLine++;
					}
					break;
				}
				pos++;
				continue;
			}


			if ('\0' == strTmpRowStr[pos])	//运行至行末
			{
				if (allStatus.bEffective == false)
				{
					if (allStatus.bComm1 || allStatus.bComm2)	//纯注释行
					{
						++iNumOfCommentLine;
					}
				}
				else if (allStatus.bEffective == true)
				{
					++iNumOfEffectiveLine;
				}
				break;
			}
			pos++;
			allStatus.bEffective = true;
		}
	}
	tmpifs.close();
}
```





3. `-s`:

   递归算法伪码：

```c++
class cal{
    ...
    vector<string> vFilePath;
    vector<string> vDirPath;
	...
    wc_GetFile_main(string strDirPath)	//递归遍历目录，并将所有代码文件路径传入FilePath中
    {
        string tmpStr;
        DirList(vDirPath, strDirPath + "\\*");	//从strDirPath + "\\*"指定的路径中递归查找代码文件，并录入至vFilePath中；将strDirPath的子目录名传入vDirPath中。
        for (i = 0; i < vDirPath.size(); ++i)
        {
            tmpPath = strDirPath + "\\" + vDirPath[i];	//子目录路径拼接。
            myFileFind(tmpPath);	//对子目录进行递归操作。
        }
    }

    DirList(verctor<string> &vStr,string strPath)	//获取当前目录下的子目录名与代码文件路径，分别录入到vStr与vFilePath中。
    {
        vector<string> vStrTmp;
        _finddata_t fileDir;
        long lfDir = _findfirst(strPath.c_str(), &fileDir);
        int tmpPos;

        if (-1l == lfDir)	//尚未实现具体的文件类型识别，仅进行_findfirst是否成功的判断
        {
            cout << "DirList: "<< strPath <<"   File or dir not found!" << endl;
        }
        else
        {
            string tmp = strPath;
            tmp.erase(tmp.size() - 1, 1);//去除路径中的'*'
            do
            {
                string FileOrDirName(fileDir.name);
                if (FileOrDirName.find('.') == -1)	//目录则将目录名传入vStrTmp中
                {
                    vDirPath.push_back(fileDir.name);
                }
                else if(
                        ((tmpPos = FileOrDirName.find(".cpp")) != -1 && FileOrDirName[tmpPos + 4] == '\0')	//精确匹配.cpp字串
                    ||	((tmpPos = FileOrDirName.find(".c")) != -1  && FileOrDirName[tmpPos + 2] == '\0')	//精确匹配.c字串
                    || ((tmpPos = FileOrDirName.find(".h")) != -1 && FileOrDirName[tmpPos + 2] == '\0')		//精确匹配.h字串
                    )//代码文件则将其路径传入vStrCodeFilePath中
                {
                    vFilePath.push_back(tmp + FileOrDirName);
                }
            } while (_findnext(lfDir, &fileDir) == 0);
        }
        _findclose(lfDir);
        vStr = vStrTmp;    
    }
    ...
};


```

在获得到所有代码文件路径的vector<string> vFilePath后，逐一对vFilePath内各个路径进行代码统计与信息输出即可，简单的迭代就可以实现。



## 总结

1. 前期的准备工作非常重要，知识学习与储备、类似的程序框架的参考、算法的评估、按需求设计功能模块等等，都是为中期代码开发提供方向与实现基础的，不重视前期工作的话在中期代码开发与后期的测试、文档撰写方面要吃很大的亏，代码体现的思路与实现方式也难以简洁优雅。这次实践中我就是吃了这个亏，导致在具体代码实现时做了很多前期需要做的工作，流程很乱，效率不高。
2. 注意待统计代码文件的编码类型，utf-8在此程序中表现良好。曾在测试环节中遇到对unicode编码的文件进行统计，算法失败地一塌糊涂，统计结果与实际也相差甚远。在接近有一个半小时的时间里都是在debug，试图在算法上找错误的根源，无果。最终发现是unicode编码下宽字符串的问题，换用utf-8后表现良好。
3. 此次的时间较赶，感觉代码质量还不高，找机会整理好思路，按PSP的流程进行代码重构。





