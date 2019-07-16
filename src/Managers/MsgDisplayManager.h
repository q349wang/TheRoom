#include "../HelperClasses/Observer.h"
#include <iostream>

class Subject;

// Observer of Travel and Battle managers which display
// messages to stdout
class MsgDisplayManager : public Observer {

	Subject * _sub;
	std::ostream& _out;
	public:	
	MsgDisplayManager(Subject *, std::ostream &);
	~MsgDisplayManager();

	void notify() override;
};