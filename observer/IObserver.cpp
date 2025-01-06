#include "IObserver.hpp"
#include <iostream>

SoundSystem::SoundSystem(ISubject& subject, int bucket, const std::string name) :
    m_subject(subject),
    m_bucket(bucket),
    m_name(name)
    {
        m_subject.AddObserver(m_bucket, this);
    }

SoundSystem::~SoundSystem(){
    m_subject.RemoveObserver(m_bucket, this);
}

void SoundSystem::OnNotify(){
    playSound();
}

void SoundSystem::playSound(){
    std::cout << m_name << " Playing Sound " <<  std::endl;
}



MailClient::MailClient(ISubject& subject, int bucket ,std::string fromAddres) : 
    m_subject(subject), m_bucket(bucket), m_address(fromAddres){
    m_subject.AddObserver(m_bucket, this);
}
void MailClient::OnNotify(){
    MailClient::sendMail();
}

MailClient::~MailClient(){
    m_subject.RemoveObserver(m_bucket, this);
}

void MailClient::sendMail(){
    std::cout << "sending mail from " << m_address << std::endl;
}



