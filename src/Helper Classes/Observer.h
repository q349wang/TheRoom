#ifndef OBSERVER_H_
#define OBSERVER_H_

class Observer {
   public:
    virtual void notify() = 0;
    virtual ~Observer();
};

#endif