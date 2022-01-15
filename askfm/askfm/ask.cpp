#include <bits/stdc++.h>
#include "ask.h"
//#include <fstream>
using namespace std;
#define endl "\n"
ask::ask()
{
	cout << "                                                      Welcome in AskFm" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}
ask::ask(string x, int i, string y, string k, bool o) :username(x), password(i), name(y), email(k), anonymous(o) {};
int ask::id = 0;
int ask::in_id = 0;
void ask::start()
{
	cout << "Menu:" << endl;
	cout << "        1: Login" << endl;
	cout << "        2: Sing Up" << endl << endl;
	cout << "Enter number in range 1 - 2: ";
	datadownload();
	id = ID();
}

bool ask::login()
{
	cout << "Enter User name & password : "; cin >> username >> password;
	recent_id = checklogin(username, password);
	if (recent_id) {
		questiondownload();
		answerdownload();
		return true;
	}
	cout << "couldn't find this account " << endl;
	return false;
}

void ask::menulog()
{
	cout << "Menu:" << endl;
	cout << "           1: Print Questions To Me" << endl;
	cout << "           2: Print Questions From Me" << endl;
	cout << "           3: Answer Question" << endl;
	cout << "           4: Delete Question" << endl;
	cout << "           5: Ask Question" << endl;
	cout << "           6: List System Users" << endl;
	cout << "           7: Feed" << endl;
	cout << "           8: Logout" << endl;
	cout << "           9: close program" << endl<<endl;
	cout << "Enter number in range 1 - 9: ";
}

void ask::sinup()
{
	int x;
	cout << "Enter new user name doesn't used before: "; cin >> username;
	cout << "Enter your first :  "; cin >> name;
	cout << "Enter password not less than 4 digits: "; cin >> password;
	cout << "Enter your Email: "; cin >> email;
	cout << "Allow anonymous Questions?: ( 0 , 1 ) "; cin >> x;
	if (x)anonymous = true;
	else anonymous = false;
	if (checksign(username, name, password, email, anonymous,id)) {
		cout << "successfull operation :" << endl;
		id++;
		dataupload(username,name,password,email,anonymous,id);
	}
	else {
		cout << "this account already exist" << endl;
	}
}

void ask::askquestion()
{
	cout << "Enter User id or -1 to cancel: "; cin >> identifi;
	cout << endl;
	if (identifi != -1) {
		string s;
		if (askcheck(identifi)) {
			cout << "Enter question text: ";
			cin.ignore();
			getline(cin, s);
			questionupload(s, recent_id,identifi,in_id);
			//questiondownload();
			in_id++;
		}
		else 
			cout << "this account doesn't exist" << endl;
	}
}

void ask::answer()
{
	string ans;
	int queid,x;
	bool ok = false,change=false;
	cout << "Enter Question id or -1 to cancel: "; cin >> queid;
	if (queid != -1) {
		for (int i = 0; i < que.size(); i++) {
			if (queid == que[i].in_id&&recent_id!=que[i].from) {
				cout << "question Id (" << queid << ") from user id(" << que[i].from << ")" << endl;
				cout << que[i].s << endl;
				cout << "Answer: "; cin.ignore();
				getline(cin, ans);
				for (int i = 0; i < an.size(); i++) {
					if (queid == an[i].in_id) {
						cout << "keep warning this question maybe answered before press 1 to confirm or 0 to cancel: ";
						cin >> x;
						if (x) {
							an[i].s = ans;//from to idque ans
							change = 1;
						}
						else return;
					}
				}
				answerupload(recent_id, que[i].from, que[i].in_id, ans,change);
				//answerdownload();
				ok = true;
				break;
			}
		}
		if (!ok)
			cout << "no user with this id ask Before" << endl;
	}
}

const void ask::print_from_me()//questions i send and if some 
{
	/*for (int i = 0; i < que.size(); i++)cout << que[i].to << " "; cout << endl;
	for (int i = 0; i < an.size(); i++)cout << an[i].from << " ";*/
	for (int i = 0; i < que.size(); i++) {
		if (que[i].from == recent_id) {
			cout << "Question Id (" << que[i].in_id << ") from user id(" << que[i].from << ")\n";
			cout << "Question: " << que[i].s << endl;
			for (int j = 0; j < an.size(); j++) {
				if (recent_id == an[j].to) {
					cout << "Answer: " << an[j].s << endl;
					return;
				}
			}
			cout << "NO Answer yet" <<endl;
		}
	}
}

const void ask::print_to_me()
{
	for (int i = 0; i < que.size(); i++) {
		if (que[i].to == recent_id) {
			cout << "Question Id (" << que[i].in_id << ") from user id(" << que[i].from << ")\n";
			cout << "Question: " << que[i].s << endl;
			for (int j = 0; j < an.size(); j++) {
				if (recent_id == an[j].from) {
					cout << "Answer: " << an[j].s << endl;
				}
			}
		}
	}
}

void ask::system()
{
	for (auto i : dat) {
		cout << "ID: " << i.d << "        Name: " << i.name << endl;
	}
}

void ask::Delete()
{
	int x;
	cout << "Enter number of the question" << endl; cin >> x;
	bool ok = true;
	int i = 0;
	for (; i < que.size(); i++) {
		if (que[i].in_id == x) {
			if (que[i].to != recent_id)
				ok = 0;
			break;
		}
	}
	if (ok) {
		que.erase(que.begin()+i);

		for (int i = 0; i < an.size(); i++) {
			if (an[i].in_id = x) {
				an.erase(an.begin() + i);
			}
		}
	}
	else cout << "You can delete this question or may be this number is not found" << endl;
}

void ask::feed()
{
	bool ok = 0;
	for (int i = 0; i < que.size(); i++) {
		cout << "Question Id (" << que[i].in_id << ") from user id(" << que[i].from << ") To user id(" << que[i].to << ")" << endl;
		cout << que[i].s << endl;
		for (int j = 0; j < an.size(); j++) {
			if (que[i].in_id == an[j].in_id) {
				cout << "Answer: " << an[j].s << endl;
			}
		}
		ok = true;
	}
	if (!ok)cout << "There is no Questions";
	cout << endl;
}

ask::~ask()
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                                Hope to be enjoyed" << endl;
	cout << "AskFm made by Omar Alaa" << endl;
	cout << "Student At Sohag University" << endl<<endl;
}



