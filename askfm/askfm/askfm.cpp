#include <bits/stdc++.h>
#include "ask.h"
using namespace std;
#define endl "\n"

int main()
{
	int x;
	string k;
	ask prog;
	while (true) {
		prog.start();
		cin >> k;
		if (k == "1") {
			if (prog.login()) {//log in
				x = 1;
				while (true) {
					prog.menulog();
					cin >> x;
					if (x <  1|| x>9)
					{
						cout << "invalid number.....try again" << endl;
						x = 1;
					}
					else {
						if (x == 1)prog.print_to_me();
						else if (x == 2)prog.print_from_me();
						else if (x == 3)prog.answer();
						else if (x == 4)prog.Delete();
						else if (x == 5)prog.askquestion();
						else if (x == 6)prog.system();
						else if (x == 7)prog.feed();
						else if (x == 8)break;
						else if (x == 9) return 0;
					}
				}
			}
		}
		else if (k == "2") {
			prog.sinup();
		}
		else cout<<"try again" << endl;
	}
}

