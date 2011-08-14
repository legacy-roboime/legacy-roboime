#include "UpdateReferee.h"
#include <iostream>

using namespace Inteligencia;

UpdateReferee::UpdateReferee(char cmd, unsigned char cmd_counter, unsigned char goals_blue, unsigned char goals_yellow, int time_remaining) : Update() {
	this->cmd = cmd;
	this->cmd_counter = cmd_counter;
	this->goals_blue = goals_blue;
	this->goals_yellow = goals_yellow;
	this->time_remaining = time_remaining;
}

UpdateReferee::~UpdateReferee(void) {}

void UpdateReferee::apply(Updater* u) {
	cout << to_string() << endl;
	//TODO: IMPLEMENT APPLY
	/*for(size_t k=u->robots(); k>0; k--) {
		if(u->robot(k-1)->cc()==_cc) {
			u->robot(k-1)->x(_x);
			u->robot(k-1)->y(_y);
			u->robot(k-1)->angle(_angle);
		}
	}*/
}

string UpdateReferee::to_string() {
	stringstream out;
	out << "UpdateReferee [" << cmd << cmd_counter << goals_blue << goals_yellow << time_remaining << "]";
	return out.str();
}
