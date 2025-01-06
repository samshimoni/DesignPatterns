#pragma once
#include <string>
#include "ISubject.hpp"


class IObserver{
    public:
        virtual ~IObserver(){};
        virtual void OnNotify()=0;
};

class MailClient : public IObserver {
    public:
        explicit MailClient(ISubject& subject, int bucket, std::string fromAddres);
        ~MailClient();
        void OnNotify();

    private:
        void sendMail();
        ISubject& m_subject;
        int m_bucket;
        std::string m_address;
};

class SoundSystem : public IObserver{
    public:
        explicit SoundSystem(ISubject& subject,int bucket, std::string name);
        ~SoundSystem();
        void OnNotify();

    private:
        void playSound();
        ISubject& m_subject;  
        int m_bucket;  
        std::string m_name;
};
