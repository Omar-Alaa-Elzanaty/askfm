#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#include "database.h"
class ask : private database
{
private:
	int password,recent_id;
	string name, email,username;
	bool anonymous;
	static int id,in_id;
	int identifi;
public:
	ask();
	ask(string,int, string,string,bool);
	void sinup();
	void start();
	bool login();
	void menulog();
	void askquestion();
	void print_to_me();
	void answer();
	~ask();
};
