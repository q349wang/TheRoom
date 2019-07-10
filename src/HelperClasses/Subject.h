#ifndef SUBJECT_H_
#define SUBJECT_H_
#include <sstream>
#include <vector>
class Observer;

class Subject {
    std::vector<Observer*> observers;
    std::ostringstream msg;

   protected:
    void setMessageAndNotify(std::string);

   public:
    Subject();
    void attach(Observer*);
    void detach(Observer*);
    void notifyObservers();
    std::string getMsg() const;
    virtual ~Subject() = 0;
};

#endif