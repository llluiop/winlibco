// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../libco/libco.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
using namespace std;

void func()
{
	cout << "this is a test:" << this_thread::get_id()<<endl;
}

int main() {
	CoRoutine* co = nullptr;
	RoutineAttr attr = { 1024 * 128 };
	int i = 0x01020304;
	int ret = create(&co, &attr, func);
	
	cout << "continue" << endl;
	cout << &((CoRoutine*)0)->coctx;
	resume(co);

	cout << "run ends" << endl;
	return 0;
}

