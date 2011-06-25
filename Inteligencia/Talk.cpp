#include "Talk.h"
#include <sstream>
namespace Inteligencia {
	namespace Talk {

		Client::Client() {
			_init();
			type(SIM);
		}

		Client::Client(ServerType s) {
			_init();
			type(s);
		}

		Client::~Client() {
			_clear();
		}

		void Client::_init() {
			_udpclient = NULL;
		}

		void Client::_clear() {
			if(_udpclient != NULL) delete _udpclient;
		}

		void Client::type(ServerType s) {
			_clear();
			_type = s;
			switch(_type) {
				case TX:
					_udpclient = new UDPClient("10.1.1.3", 9050);
					//_udpclient = new UDPClient("127.0.0.1", 9050);
					break;
				case SIMSSL:
					//TODO: do this right
					//this->servAddress = "127.0.0.1";
					//this->echoServPort = 10002;
					break;
				case SIM:
					_udpclient = new UDPClient("127.0.0.1", 9876);
					break;
				case REFBOX:
					//TODO: implement
					break;
				case SSL:
					//TODO: do this right
					//this->servAddress = "224.5.23.2";
					//this->echoServPort = 10002;
					break;
				default:
					break;
			}
		}

		ServerType Client::type() {
			return _type;
		}

		void Client::last_string(string s) {
			_last_string = s;
		}

		void Client::send_string(string s) {
			switch(_type) {
				case TX:
					_udpclient->setSendString(s);
					break;
				case SIMSSL:
					//TODO: do
					break;
				case SIM:
					_udpclient->setSendString(s);
					break;
				case REFBOX:
					//TODO: do
					break;
				case SSL:
					//TODO: do
					break;
				default:
					break;
			}
		}

		string Client::last_string() {
			return _last_string;
		}

		void Client::send() {
			//NOTE: send and get last string
			switch(_type) {
				case TX:
					_udpclient->service();
					last_string(_udpclient->getLastReceivedString());
					break;
				case SIMSSL:
					//TODO: do
					break;
				case SIM:
					_udpclient->service();
					last_string(_udpclient->getLastReceivedString());
					_udpclient->setSendString("5 0\n");
					_udpclient->service();
					break;
				case REFBOX:
					//TODO: do
					break;
				case SSL:
					//TODO: do
					break;
				default:
					break;
			}
		}

		///translation:
		Client* client_sim = new Client(SIM);

		//partial translation to simulator protocol
		string _to_sim(Command* c) {
			stringstream out;
			double* w = c->wheel_speed();
			double k = c->kick_speed();
			double d = c->dribble_speed();
			out << w[0] << " "
				<< w[1] << " "
				<< w[2] << " "
				<< w[3] << " "
				<< d    << " " 
				<< c;
			return out.str();
		}

		void _from_sim(){
			//TODO: do
		}

		string to_sim(Robot* r) {
			stringstream out;
			out << 13 << " "
				<< 0  << " "
				<< r->i() << " "
				<< _to_sim(r->command) << "\n";
			return out.str();
		}

		string to_sim(Team* t) {
			stringstream out;
			out << 14 << " "
				<< 0  << " ";
			t->sort();
			//for(i=1; i<=10; i
			return out.str();
		}

		void send_to_sim(int index, Robot* r) {
			client_sim->send_string(to_sim(r));		
			client_sim->send();
		}

	}
}