#include "Talk.h"
namespace Inteligencia {
	namespace Talk {

		UDPClientIntSim* server = new UDPClientIntSim();

		string to_sim(Command command) {
			stringstream out;
			//out << command.get_type();
			//TODO: finish writing the out
			return out.str();
		}

		void send(int index, Command command) {
			server->setSendString(to_sim(command));		
			server->func1();
		}

	}
}