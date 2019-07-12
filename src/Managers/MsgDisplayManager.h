#include "../HelperClasses/Observer.h"
#include <iostream>

class Subject;

class MsgDisplayManager : public Observer {

	Subject * _sub;
	std::ostream& _out;
	public:	
	MsgDisplayManager(Subject *, std::ostream &);
	~MsgDisplayManager();

	void notify();
};