// test.cpp : 定义控制台应用程序的入口点。
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

	int ret = create(&co, &attr, func);
	
	cout << "continue" << endl;

	resume(co);

	cout << "run ends" << endl;
	return 0;
}

