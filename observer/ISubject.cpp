#include "ISubject.hpp"
#include "IObserver.hpp"
#include <iostream>

ISubject::ISubject(){}
ISubject::~ISubject() {}

void ISubject::AddObserver(int bucket, IObserver* observer){
    auto it = m_observers.find(bucket);
    if (it == m_observers.end()){
        m_observers[bucket] = ObserversList();
    }
    
    m_observers[bucket].push_front(observer);
}

void ISubject::RemoveObserver(int bucket, IObserver* observer){

    m_observers[bucket].remove(observer);
}

void ISubject::NotifyAll(){
    for (ObserversMap::iterator it = m_observers.begin();
                                it != m_observers.end();
                                it++){
        for (auto& o: m_observers[it->first]){
            o->OnNotify();
        }                       
    }
}

void ISubject::Notify(int bucket){
    for (auto o:m_observers[bucket]){
        o->OnNotify();
    }
}