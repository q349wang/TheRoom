#ifndef OBSERVER_H_
#define OBSERVER_H_
#include <string>

class Observer {
   public:
    virtual void notify(std::string) = 0;
    virtual ~Observer();
};

#endif