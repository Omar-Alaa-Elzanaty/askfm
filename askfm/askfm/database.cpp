#include <bits/stdc++.h>
#include "database.h"
#define longlong ll
#define endl "\n"
using namespace std;
database::database()
{
}

void database::dataupload(string username, string name, int pass, string email, bool an, int d) {
	ofstream file("database.txt", ios::out|ios::app);
	//file.unsetf(ios::skipws);
	if (!file.fail()) {
	file << d <<" "<< username<<" " <<" "<< pass <<" "<< name <<" "<< email <<" "<< an << "\n";
		file.close();
	}//need expetion handle for anonymous as insert 1 or two only (in plan of work)
	else cout << "fail upload";
}
void database::datadownload(){
	int i = 0;
	ifstream file("database.txt",ios::in);
	if (file.fail()) {
		cout << "faild download users data" << endl;
		return;
	}
	dat.clear();
	if (!file.fail()) {
		while (file >> obj.d >> obj.username >> obj.password >> obj.name >> obj.email >> obj.anonymous) {
			dat.push_back(obj);
		}
		file.close();
	}
	else {
		cout << "There is no data" << endl;
	}
}

int database::checklogin(string user, int pass)
{
	for (int i = 0; i < dat.size(); i++) {
		if (dat[i].username == user && dat[i].password == pass)
			return dat[i].d;
	}
	return 0;
}

bool database::checksign(string user, string mail,int pass,string nam,bool an,int id)
{
	for (int i = 0; i < dat.size(); i++) {
		if (dat[i].username == user && dat[i].email == mail) {
			return false;
		}
	}
	obj.username = user;
	obj.email = mail;
	obj.password = pass;
	obj.name = nam;
	obj.anonymous = an;	
	obj.d = ++id;
	dat.push_back(obj);
	return true;
}

bool database::askcheck(int id,int x)
{
	for (int i = 0; i < dat.size(); i++) {
		if (id == dat[i].d) {
			if (dat[i].anonymous == 0&&x==1) {
				cout << "Note: Anonymous questions are not allowed for this user" << endl;
			}
			return true;
		}
	}
	return false;
}

void database::questionupload(string s, int from,int to, int ind,int x)
{
	ob.from = from, ob.to = to, ob.in_id = ind, ob.s = s,ob.ano=x;
	que.push_back(ob);
	ofstream file("questions.txt", ios::out | ios::app);
	if (file.fail()) {
		cout << "faild upload question" << endl;
		return;
	}
	file.unsetf(ios::skipws);
	file << from << " "<<to<<" " << ind <<" "<< x << " " << s << "\n";
	file.close();
}

void database::questiondownload()
{
	que.clear();
	ifstream file("questions.txt", ios::in);
	if (file.fail()) {
		cout << "faild download the questions" << endl;
		return;
	}
	//file.unsetf(ios::skipws);
	while (file >> ob.from >>ob.to>>ob.in_id>>ob.ano,getline(file, ob.s)) {
	//	cout << ob.id << " " << ob.in_id << " " << ob.s << endl;
		que.push_back(ob);
		mxin = max(mxin, ob.in_id);
		recent();
	}
	//for (int i = 0; i < que.size();i++)cout << que[i].from<<" "<<que[i].in_id<<" "<<que[i].s << endl;
	file.close();
}

void database::questionupload()//overloading function
{
	ofstream file("questions.txt", ios::out | ios::trunc);
	if (file.fail()) {
		cout << "faild download questino data" << endl;
		return;
	}
	file.unsetf(ios::skipws);
	for (int i = 0; i < que.size(); i++) {
		file << que[i].from << " " << que[i].to << " " << que[i].in_id<<" "<<que[i].ano << " " << que[i].s << "\n";
	}
}

void database::answerupload()
{
	ofstream file("Answer.txt", ios::out | ios::trunc);
	if (file.fail()) {
		cout << "faild to upload data of answers" << endl;
		return;
	}
	file.unsetf(ios::skipws);
	for (int i = 0; i < an.size(); i++) {
		file << an[i].from << " " << an[i].to << " " << an[i].in_id << " " << an[i].s << "\n";
	}
}

int database::recent()
{
	if (mxin == -1)
		return 1;
	return mxin+1;
}

void database::answerupload(int x,int z,int y,string s,bool ok)
{
	if (ok==false) {
		ob.from = x; ob.to = z; ob.in_id = y; ob.s = s;
		an.push_back(ob);
	}
	ofstream file("Answer.txt", ios::out|ios::trunc);
	if (file.fail()) {
		cout << "faild upload answer data" << endl;
		return;
	}
	file.unsetf(ios::skipws);
	for (int i = 0; i < an.size(); i++) {
		file << x << " " << z << " " << y << " " << s << "\n";
	}
	file.close();
}

void database::answerdownload()
{
	an.clear();
	ifstream file("Answer.txt", ios::in);
	if (file.fail()) {
		cout << "faild download answer data" << endl;
		return;
	}
	while (file >> ob.from >>ob.to>> ob.in_id, getline(file, ob.s)) {
		an.push_back(ob);
	}
	file.close();
}

int database::ID()
{
	if (dat.size() == 0)return 0;
	return dat[dat.size() - 1].d;
}

void database::note()
{
	/*there is problem in database file as find space in first line automatically
	this happen when use ID function(which help to get last id)*/
}


