#include <forward_list>
#include <map>

#pragma once

class IObserver;

class ISubject{
    public:
        ISubject();
        virtual ~ISubject();

        virtual void AddObserver(int bucket, IObserver* observer);
        virtual void RemoveObserver(int bucket, IObserver* observer);

        virtual void NotifyAll();
        virtual void Notify(int bucket);

    private:
        typedef std::forward_list<IObserver*> ObserversList;
        typedef std::map<int, ObserversList> ObserversMap;

        ObserversMap m_observers;
};


class FTPServer : public ISubject{
    public:
        enum BucketsTypes{SOUND, COMMUNICATION, LOG};
};