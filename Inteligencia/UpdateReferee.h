#pragma once

#include "Update.h"
#include "Updater.h"

namespace Inteligencia {

	class UpdateReferee : public Update
	{
	private:
		char cmd;                      // current referee command
		unsigned char cmd_counter;     // increments each time new command is set
		unsigned char goals_blue;      // current score for blue team
		unsigned char goals_yellow;    // current score for yellow team
		unsigned short time_remaining; // seconds remaining for current game stage (network byte order)
	public:
		UpdateReferee(void);
		UpdateReferee(char cmd, unsigned char cmd_counter, unsigned char goals_blue, unsigned char goals_yellow, unsigned short time_remaining);
		~UpdateReferee(void);
		void apply(Updater*);//go through the updaters list and apply the update
	};
}