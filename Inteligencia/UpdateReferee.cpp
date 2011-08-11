#include "UpdateReferee.h"

using namespace Inteligencia;

UpdateReferee::UpdateReferee(void) : Update()
{
}

UpdateReferee::UpdateReferee(char cmd, unsigned char cmd_counter, unsigned char goals_blue, unsigned char goals_yellow, unsigned short time_remaining) : Update()
{
	this->cmd = cmd;
	this->cmd_counter = cmd_counter;
	this->goals_blue = goals_blue;
	this->goals_yellow = goals_yellow;
	this->time_remaining = time_remaining;
}

UpdateReferee::~UpdateReferee(void)
{
}

void UpdateReferee::apply(Updater* u) {
	//TODO: IMPLEMENT APPLY
	/*for(size_t k=u->robots(); k>0; k--) {
		if(u->robot(k-1)->cc()==_cc) {
			u->robot(k-1)->x(_x);
			u->robot(k-1)->y(_y);
			u->robot(k-1)->angle(_angle);
		}
	}*/

	//BASE
	/*char cmd_tmp;
	rcvd_bytes_referee = e->getDados();
	cmd_tmp = (char)rcvd_bytes_referee[0];
	datareferee->cmd_counter = (unsigned char)rcvd_bytes_referee[1];
	datareferee->goals_blue = (unsigned char)rcvd_bytes_referee[2];
	datareferee->goals_yellow = (unsigned char)rcvd_bytes_referee[3];
	//time_remaining = (int)((unsigned short)rcvd_bytes_referee[4] * (unsigned short)255 + (unsigned short)rcvd_bytes[5]);
	datareferee->time_remaining = ((int)(rcvd_bytes_referee[4]) << 8)  + (int)(rcvd_bytes_referee[5]); //byte mais significativo
	
	if ( datareferee->cmd_counter != datareferee->cmd_counter_tmp ) 
	{ // se nao houver nenhum comando novo, fazer nada
		datareferee->cmd_counter_tmp = datareferee->cmd_counter;
		if (datareferee->cmd != cmd_tmp)
		{
			datareferee->cmd_prev = datareferee->cmd;
			datareferee->cmd = cmd_tmp;
		}
	}*/
}
