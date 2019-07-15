#ifndef SUBJECT_H_
#define SUBJECT_H_
#include <vector>

class Observer;

class Subject {
	std::vector<Observer*> observers;
	public:
	Subject();
	void attach(Observer*);
	void detach(Observer*);
	void notifyObservers();
	virtual ~Subject() =0;
};

#endif