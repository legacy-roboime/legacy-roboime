public class Component {

private:
	//fields:
	bool active, working;

public:
	//methods:
	bool is_broken();
	bool is_working();
	bool is_active();
	bool is_inactive();
	void activate();
	void deactivate();
	void repair();
	void break_down();

};