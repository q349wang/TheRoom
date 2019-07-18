#include "../HelperClasses/Observer.h"
#include <iostream>
#include <string>

// Observer of Travel and Battle managers which display
// messages to stdout
class MsgDisplayManager : public Observer {

	std::ostream& _out;
	public:	
	MsgDisplayManager(std::ostream &);
	~MsgDisplayManager();

	void notify(std::string) override;
};