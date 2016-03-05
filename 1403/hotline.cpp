#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <sstream>

using namespace std;

struct event_t{
	event_t():everybody(false), nobody(false), somebody(false), not_somebody(false){}
	bool everybody, nobody,
	     somebody, not_somebody;
	vector<pair<string, bool>> subjects;

	bool add(string subject, bool does){
		if (subject == "everybody" && not_somebody)
			return false;
		if (subject == "nobody" && somebody)
			return false;
		if (everybody && !does)
			return false;
		if (nobody && does)
			return false;

		if (subject == "everybody")
			everybody = somebody = true;
		if (subject == "nobody")
			nobody = not_somebody = true;
		if (does && subject != "nobody")
			somebody = true;
		else
			not_somebody = true;
		subjects.push_back(make_pair(subject, does));
		return true;
	}
};

struct subject_t{
	vector<pair<string, bool>> events;
	bool add(string event, bool does){
		for (int i = 0; i < events.size(); i++)
			if (events[i].first == event && events[i].second != does)
				return false;

		events.push_back(make_pair(event, does));
		return true;
	}
	int check(string event){
		for (int i = 0; i < events.size(); i++)
			if (events[i].first == event)
				return events[i].second ? 1 : 0;
		return -1;
	}
};

void print_e(const pair<string, bool>& event, string does){
	if (event.second){
		int index = event.first.find(" ");
		if (index == string::npos)
			index = event.first.size();
		string predicate = event.first.substr(0, index), object = "";
		if (index != event.first.size())
			object = event.first.substr(index);
		if (does == "doesn\'t")
			cout << predicate << "s" << object;
		else
			cout << predicate << object;
	}else
			cout << does << " " << event.first;
}

int main(){
	int T;
	scanf("%d\n", &T);
	for (int dialog_no = 0; dialog_no < T; dialog_no++){
		printf("Dialogue #%d:\n", dialog_no + 1);
		
		map<string, event_t> events;
		map<string, subject_t> subjects;
		subjects.insert(make_pair("everybody", subject_t()));

		bool abroad = false;
		string line;
		while (getline(cin, line) && line[line.size() - 1] != '!'){
			if (line[line.size() - 1] == '.'){ 
				line = line.substr(0, line.size() - 1);
				istringstream sin(line);
				string subject, predicate, object;
				bool does = true;
				sin >> subject;
				if (subject == "I")
					subject = "you";
				else if (subject == "you")
					subject = "I";	
				sin >> predicate;
				if (predicate == "don\'t" || predicate == "doesn\'t"){
					does = false;
					sin >> predicate;
				}
				if (subject != "I" && subject != "you" && does && predicate[predicate.size() - 1] == 's')
					predicate = predicate.substr(0, predicate.size() - 1);
				getline(sin, object);
				if (!events[predicate + object].add(subject, does))
					abroad = true;


				if (subjects.find(subject) == subjects.end())
					subjects[subject].events = subjects["everybody"].events;

				if (subject == "everybody"){
					for (map<string, subject_t>::iterator it = subjects.begin(); it != subjects.end(); it++)
						if(!(*it).second.add(predicate + object, does))
							abroad = true;
				}else if (subject == "nobody"){
					for (map<string, subject_t>::iterator it = subjects.begin(); it != subjects.end(); it++)	
						if (!(*it).second.add(predicate + object, !does))
							abroad = true;
				}else
					if (!subjects[subject].add(predicate + object, does))
						abroad = true;

			}
			else{
				cout << line << "\n";
				if (abroad){
					cout << "I am abroad.\n\n";
					continue;
				}

				if (line[0] == 'd'){
					line = line.substr(0, line.size() - 1);
					istringstream sin(line);
					string subject, predicate, object, does;
					sin >> does >> subject >> predicate;
					getline(sin, object);
					if (subject == "I")
						subject = "you";
					else if (subject == "you")
						subject = "I";
					int code = -1;
					event_t& event = events[predicate + object];
					if (event.everybody)
						code = 1;
					else if (event.nobody)
						code = 0;
					if (code == -1)
						code = subjects[subject].check(predicate + object);
					
					if (code == 1){
						if (does == "does")
						 predicate += 's';
						cout << "yes, " << subject << " " << predicate << object << ".\n";
					}
					else if (code == 0){
						if (does == "do")
							does = "don\'t";
						else
							does = "doesn\'t";
						cout << "no, " << subject << " " << does << " " << predicate << object << ".\n";
					}else
						cout << "maybe.\n";
				}else if (line.substr(0,3) == "who"){
					line = line.substr(0, line.size() - 1);
					istringstream sin(line);
					string subject, predicate, object;
					sin >> subject >> predicate;
					getline(sin, object);
					predicate = predicate.substr(0, predicate.size() - 1);
					
					event_t& event = events[predicate + object];
				
					if (event.nobody)
						cout << "nobody " << predicate << "s" << object << ".\n";
					else if (event.everybody)
						cout << "everybody " << predicate << "s" << object <<".\n";
					else{
						vector<string> subs;

						for (int i = 0; i < event.subjects.size(); i++)
							if (event.subjects[i].second)
								subs.push_back(event.subjects[i].first);
						if (subs.empty())
							cout << "I don\'t know.\n";
						else{
							cout << subs[0];
							for (int i = 1; i < subs.size() - 1; i++)
								cout << ", " << subs[i];
							if (subs.size() >= 2)
								cout << " and " << subs[subs.size() - 1];
							if (subs.size() == 1 && subs[0] != "I" && subs[0] != "you")
								predicate += 's';
							cout << " " << predicate << object << ".\n";
						}
					}
				}else{
					line = line.substr(5, line.size() - 1);
					istringstream sin(line);
					string does, subject;
					sin >> does >> subject;
					
					if (subject == "I")
						subject = "you";
					else if (subject == "you")
						subject = "I";

					if (subjects.find(subject) == subjects.end())
						subjects[subject].events = subjects["everybody"].events;

					if (does == "does")
						does = "doesn\'t";
					else
						does = "don\'t";

					subject_t& sub = subjects[subject];
					if (sub.events.empty())
						cout << "I don\'t know.\n";
					else{
						cout << subject << " ";
						print_e(sub.events[0], does);
						for (int i = 1; i < sub.events.size() - 1; i++){
							cout << ", ";
							print_e(sub.events[i], does);
						}
						if (sub.events.size() >= 2){
							cout << ", and ";
							print_e(sub.events[sub.events.size() - 1], does);
						}
						cout << ".\n";
					}
				}
				cout << "\n";
			}
		}
		cout << line << "\n\n";
	}
	return 0;
}
