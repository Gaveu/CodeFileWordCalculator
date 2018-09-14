#include"WChead.h"



//class_WordCal 方法集

void class_WordCal::Option(int argc, char *argv[])		////功能选择函数
{
	int i;
	for (i = 1; i < argc; ++i)
	{
		string s = argv[i];
		if (s == "-l")
		{
			bOpLine = true;
		}
		else if (s == "-w")
		{
			bOpWord = true;
		}
		else if (s == "-c")
		{
			bOpChar = true;
		}
		else if (s == "-s")
		{
			bOpRecursion = true;
		}
		else if (s == "-a")
		{
			bOpAll = true;
		}
		else
		{
			vStrFileOrDirName.push_back(s);
		}
	}
}

void class_WordCal::Display(int Index)
{
	if (bOpChar)
	{
		cout << "The Num of chars: " << iNumOfChar << "  " << vStrFileOrDirName[Index] << endl;
	}
	if (bOpWord)
	{
		cout << "The Num of words: " << iNumOfWord << "  " << vStrFileOrDirName[Index] << endl;
	}
	if (bOpLine)
	{
		cout << "The Num of Lines: " << iNumOfLine << "  " << vStrFileOrDirName[Index] << endl;
	}
	if (bOpAll)
	{
		cout << "The Num of Effective lines: " << iNumOfEffectiveLine << "  " << vStrFileOrDirName[Index] << endl;
		cout << "The Num of Empty lines: " << iNumOfEmptyLine << "  " << vStrFileOrDirName[Index] << endl;
		cout << "The Num of Comment lines: " << iNumOfCommentLine << "  " << vStrFileOrDirName[Index] << endl;
	}

}

void class_WordCal::Display(vector<string> vStr, int Index)	//vector<string>中第Index个文件名输出统计函数
{

	if (bOpChar)
	{
		cout << "The Num of chars: " << iNumOfChar << "  " << vStr[Index] << endl;
	}
	if (bOpWord)
	{
		cout << "The Num of words: " << iNumOfWord << "  " << vStr[Index] << endl;
	}
	if (bOpLine)
	{
		cout << "The Num of Lines: " << iNumOfLine << "  " << vStr[Index] << endl;
	}
	if (bOpAll)
	{
		cout << "The Num of Effective lines: " << iNumOfEffectiveLine << "  " << vStr[Index] << endl;
		cout << "The Num of Empty lines: " << iNumOfEmptyLine << "  " << vStr[Index] << endl;
		cout << "The Num of Comment lines: " << iNumOfCommentLine << "  " << vStr[Index] << endl;
	}
}

void class_WordCal::StringSkip(string s, int &pos)				//当s中存在' ' '\t' '\n' '\r'时，将pos置于该字符之后
{
	if (pos > s.size() || pos < 0)
	{
		cout << "Function_StringSkip:Input pos error!" << endl;
		cout << "pos " << pos << endl;
		cout << "s.size() " << s.size() << endl;
		return;
	}
	while ('\t' == s[pos]
		|| '\r' == s[pos]
		|| '\n' == s[pos]
		|| ' ' == s[pos])
	{
		pos++;
		if (pos >= s.size())
		{
			return;
		}
	}
}

void class_WordCal::myFileFind(string DirPath)	//对vector<string>中第Index个目录下的所有代码文件(.c .cpp .h) 录入至 vStrCodeFilePath 中
{
	int i;
	vector<string> vDirPath;
	string tmpPath;
	DirList(vDirPath, DirPath + "\\*");
	
	if (DirPath.back() == '\\')		//此处判断仅为了使路径统一，将DirPath的最后字节置为空，使得路径的“\”能够统一。
	{
		DirPath.erase(DirPath.size()-1);
	}

	for (i = 0; i < vDirPath.size(); ++i)
	{
		tmpPath = DirPath + "\\" + vDirPath[i];
		myFileFind(tmpPath);
	}
}

void class_WordCal::DirList(vector<string> &vStr, string strPath)	//从strPath指定的路径中递归查找代码文件，并录入至vStrCodeFilePath中
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
		tmp.erase(tmp.size() - 1, 1);
		do
		{
			string FileOrDirName(fileDir.name);
			if (FileOrDirName.find('.') == -1)	//目录则传入vStrTmp中
			{
				vStrTmp.push_back(fileDir.name);
			}
			else if(
					((tmpPos = FileOrDirName.find(".cpp")) != -1 && FileOrDirName[tmpPos + 4] == '\0')	//精确匹配.cpp字串
				||	((tmpPos = FileOrDirName.find(".c")) != -1  && FileOrDirName[tmpPos + 2] == '\0')	//精确匹配.c字串
				|| ((tmpPos = FileOrDirName.find(".h")) != -1 && FileOrDirName[tmpPos + 2] == '\0')		//精确匹配.h字串
				)//代码文件则将其路径传入vStrCodeFilePath中
			{
				vStrCodeFilePath.push_back(tmp + FileOrDirName);
			}
		} while (_findnext(lfDir, &fileDir) == 0);
	}
	_findclose(lfDir);
	vStr = vStrTmp;
}

int class_WordCal::getword(FILE *fp)
{
	if (!fp || feof(fp))
	{
		return 0;
	}
	int c;
	int word = 0;
	while ((c = getc(fp)) != EOF)
	{
		if (isalpha(c))
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
	while (c != EOF)
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

	return c != EOF;
}

Status class_WordCal::SetIfstream(vector<string> vStr, int Index)								//设置打开文件的文件读操作类
{
	const char *FileName = vStr[Index].c_str();
	tmpifs.open(FileName);
	if (!tmpifs)
	{
		cout << "File "<< FileName << " isn't existed." << endl;
		return en_nullptr;
	}
	return en_success;
}

//Status class_WordCal::CountFromFile(int Index)	//(旧代码，不兼容-s统计功能)对vStrFileOrDirName中第Index个文件名对应文件进行代码统计(-l -w -c)
/*{
	if (Index < 0 ||Index >= vStrFileOrDirName.size())
	{
		return en_fail;
	}
	const char *FileName = vStrFileOrDirName[Index].c_str();
	FILE *fp = fopen(FileName, "r");

	if (!fp)
	{
		cout << "Can't open the file " << FileName << endl;
		return en_fail;
	}

	iNumOfChar = iNumOfLine = iNumOfWord = 0;
	while (getword(fp));
	fclose(fp);
	return en_success;
}*/

Status class_WordCal::CountFromFile(vector<string> vStr, int Index)		//获取当前记录文件中的字符数
{
	if (Index < 0 || Index >= vStr.size())
	{
		return en_fail;
	}

	const char *FileName = vStr[Index].c_str();
	FILE *fp = fopen(FileName, "r");

	if (!fp)
	{
		cout << "Can't open the file " << FileName << endl;
		return en_fail;
	}

	iNumOfChar = iNumOfLine = iNumOfWord = 0;
	while (getword(fp));
	fclose(fp);
	return en_success;
}

//Status class_WordCal::CountFromFileAll(int Index)	//(旧代码，不兼容-s统计功能)对vStrFileOrDirName中第Index个文件名对应文件进行高级代码统计(-a)
/*{
	if (Index < 0 || Index >= vStrFileOrDirName.size() || en_success != SetIfstream(vStrFileOrDirName,Index))
	{
		return en_fail;
	}
	int pos;
	Status tmpStatus;
	allStatus.bComm1 = allStatus.bComm2 = allStatus.bEffective = allStatus.bEmpty = false;	//高级统计状态机初始化
	iNumOfEffectiveLine = iNumOfEmptyLine = iNumOfCommentLine = 0;	//代码行数、空行数、注释行数置零初始化
	while (!tmpifs.eof())
	{
		pos = 0;
		allStatus.bEffective = allStatus.bComm1 = false;	
		getline(tmpifs, strTmpRowStr);	//读取文件中的一行代码
		if (allStatus.bComm2 == true)	//存在	"/*"	的注释状态
		{
			allStatus.bComm1 = true;
		}
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
				&&	'/' == strTmpRowStr[pos + 1])	//读取到"//"的情况
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
				allStatus.bComm1 = true;
				continue;
			}
			if (true == allStatus.bComm2)	//	"/*"的过滤处理
			{
				if ('*' == strTmpRowStr[pos] && '/' == strTmpRowStr[pos + 1])	//读到"/*"注释结束时的状态处理
				{
					pos++;
					allStatus.bComm2 = false;
				}
				else if ('\0' == strTmpRowStr[pos])	//读取至行末时的处理
				{
					if (true == allStatus.bEffective)	//若此时为有效代码状态，则代码行数++。例如 printf("hello\n"); /*this is a hello print*/
					/*
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
}*/

Status class_WordCal::CountFromFileAll(vector<string> vStr, int Index)	//对vector<string>中第Index个文件名对应文件进行高级代码统计(-a)
{
	if (Index < 0 || Index >= vStr.size() || en_success != SetIfstream(vStr,Index))
	{
		return en_fail;
	}
	int pos;
	Status tmpStatus;
	allStatus.bComm1 = allStatus.bComm2 = allStatus.bEffective = allStatus.bEmpty = false;	//高级统计状态机初始化
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

Status class_WordCal::CountFromDir(int Index)	//对目录下的所有代码文件进行递归统计(-s)
{
	if (Index < 0 || Index >= vStrFileOrDirName.size())
	{
		return en_fail;
	}
	myFileFind(vStrFileOrDirName[Index]);
	cout << "list_size: " << vStrCodeFilePath.size() << endl;
	for (int i = 0; i < vStrCodeFilePath.size(); ++i)
	{
		if (bOpChar == true || bOpWord == true || bOpLine == true || bOpAll == true)
		{
			cout << "No." << i << "  " << vStrCodeFilePath[i] << ": " << endl;
			CountFromFile(vStrCodeFilePath, i);
			if (bOpAll == true)
			{
				CountFromFileAll(vStrCodeFilePath, i);
			}
			Display(vStrCodeFilePath, i);
			cout << endl;
		}
	}
	return en_success;

}

Status class_WordCal::EmptyCheck(string s, int pos)	////空行检查与统计
{
	if (pos > s.size() || pos < 0)
	{
		cout << "Function_EmptyCheck:Input pos error!" << endl;
		return en_fail;
	}
	if (false == allStatus.bComm2 && (	'\0' == s[pos] 
										|| ('{' == s[pos] && '\0' == s[pos + 1])
										|| ('}' == s[pos] && '\0' == s[pos + 1])
									)
		)
	{
		iNumOfEmptyLine++;
		return en_true;
	}
	return en_false;
}

void class_WordCal::CountMain()	//统计功能入口
{
	if (bOpRecursion == true)
	{
		int i;
		for (i = 0; i < vStrFileOrDirName.size(); ++i)
		{
			CountFromDir(i);
			vStrCodeFilePath.clear();
			
		}
	}
	else if (bOpChar == true || bOpWord == true || bOpLine == true || bOpAll == true)
	{
		int i;
		for (i = 0; i < vStrFileOrDirName.size(); ++i)
		{
			if (bOpChar == true || bOpWord == true || bOpLine == true)
			{
				CountFromFile(vStrFileOrDirName,i);
			}
			if (bOpAll == true)
			{
				CountFromFileAll(vStrFileOrDirName,i);
			}
			Display(i);
			cout << endl;
		}
	}
}

void class_WordCal::workMain(int argc, char *argv[])	//功能主函数
{
	Option(argc, argv);
	CountMain();

}

