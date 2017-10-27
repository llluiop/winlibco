// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int v;
	cin >> v;
	vector<int> vec;
	int tmp;
	for (int i = 0; i < v; i++)
	{
		cin >> tmp;
		vec.push_back(tmp);
	}

	auto t1 = std::find(std::begin(vec), std::end(vec), v);
	auto t2 = std::begin(vec);
	cout <<  t1 - t2;
	return 0;
}

