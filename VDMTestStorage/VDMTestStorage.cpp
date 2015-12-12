// VDMTestStorage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace VDMaster;

int main()
{
	BCBuffer<char> buf = BCBuffer<char>();
	BCBuffer<char> pushBuf = BCBuffer<char>(ptrCpy<char>("!!", 2), 2, null);
	BCBuffer<char> popBuf = BCBuffer<char>();
	buf.setBuffer(ptrCpy<char>("Hello!", 6));
	buf.push(&pushBuf);
	cout << &buf[0] << endl;
	system("pause");
    return 0;
}

