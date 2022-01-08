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
		in_id=questiondownload();
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
	cout << "Enter new name :  "; cin >> name;
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
			in_id++;
		}
		else 
			cout << "this account doesn't exist" << endl;
	}
}

void ask::answer()
{
	string ans;
	int sender,quenum,pos,x;
	bool ok = false;
	cout << "Enter Question id or -1 to cancel: "; cin >> sender;
	if (sender != -1) {
		for (int i = 0; i < que.size(); i++) {
			if (sender == que[i].from) {
				quenum = que[i].in_id;
				pos = i;
				ok = true;
				break;
			}
		}
		if (ok) {
			cout << "question Id (" << quenum << ") from user id(" << sender << ")" << endl;
			cout << que[pos].s << endl;
			cout << "Answer: "; cin.ignore();
			getline(cin, ans);
			for (int i = 0; i < an.size(); i++) {
				if (recent_id == an[i].from && quenum == an[i].in_id, sender == an[i].to) {
					cout << "keep warning this question maybe answered before press 1 to confirm or 0 to cancel: ";
					cin >> x;
					if (x) {
						answerupload(recent_id, sender, quenum, ans);//from to idque ans
					}
					else return;
				}
			}
			answerupload(recent_id, sender, quenum, ans);
			answerdownload();
		}
		else cout << "no user with this id ask Before" << endl;
	}
}

void ask::print_to_me()//questions i get
{
	bool ok = false;
	/*for (int i = 0; i < que.size(); i++)cout << que[i].to << " "; cout << endl;
	for (int i = 0; i < an.size(); i++)cout << an[i].from << " ";*/
	for (int i = 0; i < que.size(); i++) {
		if (que[i].to == recent_id) {
			for (int j = 0; j < an.size(); j++) {
				if (recent_id == an[j].from) {
					cout << "Question Id (" << que[i].in_id << ") from user id(" << que[i].from << ")\n";
					cout <<"Question: "<< que[i].s << endl;
					cout << "Answer: " << an[j].s << endl;
					ok = true;
				}
			}
		}
	}
	if (ok == false)cout << "NO Questions" << endl;
}

ask::~ask()
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                                Hope to be enjoyed" << endl;
	cout << "AskFm made by Omar Alaa" << endl;
	cout << "Student At Sohag University";
}



