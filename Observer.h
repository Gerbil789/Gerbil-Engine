#pragma once

class IObserver
{
public:
	virtual void UpdateObserver() = 0;
};

class ISubject {
public:
    virtual void Attach(IObserver* _observer) = 0;
    virtual void Detach(IObserver* _observer) = 0;
    virtual void Notify() = 0;
};

