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