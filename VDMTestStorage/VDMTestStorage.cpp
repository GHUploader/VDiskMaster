// VDMTestStorage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace VDMaster;

int main()
{
	BCBuffer<char> buf = BCBuffer<char>();
	BCBuffer<char> pushBuf = BCBuffer<char>(ptrCpy<char>("!!!!", 4), 4, null);
	BCBuffer<char>* popBuf;

	buf.setBuffer(ptrCpy<char>("Hello", 5));
	buf.push(&pushBuf);
	popBuf = buf.pop(3);
	cout << "Push/pop test:" << endl;
	cout << &buf[0] << endl;
	cout << &(*popBuf)[0] << endl;

	cout << "SCopy() test:" << endl;
	BCBuffer<char>* sCpy = popBuf->SCopy();
	delete popBuf;
	cout << &(*sCpy)[0] << endl;

	cout << "pushFront() test:" << endl;
	sCpy->pushFront(&buf);
	cout << &(*sCpy)[0] << endl;

	cout << "popFront() test:" << endl;
	BCBuffer<char>* pfBuf = sCpy->popFront(5);
	cout << &(*sCpy)[0] << endl;
	cout << &(*pfBuf)[0] << endl;

	cout << "= operator test:" << endl;
	BCBuffer<char> cpy;
	cpy = *pfBuf;
	BCBuffer<char> ssCpy = (*sCpy);
	cout << &cpy.begin()[0] << endl;
	cout << &ssCpy.begin()[0] << endl;

	delete pfBuf;
	delete sCpy;

	cout << "Allocation Test:" << endl;
	BCBuffer<char> allocTest = BCBuffer<char>(ptrCpy<char>("Hi", 2), 2, null);
	char* largeBuf = new char[5000 + 2];
	for (int i = 0; i < 5000; i++)
	{
		largeBuf[i] = '!';
	}
	largeBuf[5000] = null;
	pushBuf.setBuffer(largeBuf, 5000, null);
	allocTest.push(&pushBuf);
	cout << &allocTest.begin()[0] << endl;

	cout << "Deallocation Test:" << endl;
	allocTest.setSize(2);
	cout << &allocTest.begin()[0] << endl;

	system("pause");
    return 0;
}



