#include <bits/stdc++.h>
using namespace std;
#define long long ll
class database
{
protected:
	struct data{
		int password,d;
		string name, email, username;
		bool anonymous;
	};
	struct dq {
		int from,to, in_id;
		string s;
		int ano;
	};
	vector<data>dat;
	vector<dq>que;
	vector<dq>an;
	data obj;
	dq ob;
	int d, mxin;
public:
	database();
	void dataupload(string, string, int, string, bool, int);
	void datadownload();
	int checklogin(string user,int pass);
	bool checksign(string,string,int,string,bool,int);
	bool askcheck(int,int);
	void answerupload(int,int,int,string,bool);
	void answerdownload();
	void questionupload(string,int,int,int,int);
	void questiondownload();
	void questionupload();
	void answerupload();
	int recent();
	int ID();
	void note();
};

