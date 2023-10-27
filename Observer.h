#pragma once
class ISubject;

class IObserver
{
public:
    virtual void UpdateObserver(ISubject* _subject) {};
    virtual void UpdateObserver() {};
};

class ISubject {
public:
    virtual void Attach(IObserver* _observer) = 0;
    virtual void Detach(IObserver* _observer) = 0;
    virtual void Notify() = 0;
};

