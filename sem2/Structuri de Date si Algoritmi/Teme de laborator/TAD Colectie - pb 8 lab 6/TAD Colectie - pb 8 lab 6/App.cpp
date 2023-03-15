#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
using namespace std;


int main() {
	clock_t time;
	time = clock();
	testAll();
	test_intersectie();
	testAllExtins();
	cout << "End";
	time = clock() - time;
	cout << "\nFinished in " << (float)time / CLOCKS_PER_SEC << " seconds (" << (float)time / CLOCKS_PER_SEC / 60 << " minutes).";
}