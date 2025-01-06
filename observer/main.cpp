#include <iostream>
#include <string>
#include <forward_list>
#include "IObserver.hpp"
#include "ISubject.hpp"



int main(void){
    FTPServer ftpserver;

    MailClient mail_client(ftpserver, FTPServer::COMMUNICATION, "Samshimoni@gmail.com");
    MailClient mail_client2(ftpserver, FTPServer::COMMUNICATION, "michalrotenberg1@gmail.com");

    {
        SoundSystem SoundSystem(ftpserver, FTPServer::SOUND, "Sonos"); 
        ftpserver.Notify(FTPServer::SOUND);
    }

    ftpserver.NotifyAll();

    std::cout << std::endl;

    ftpserver.Notify(FTPServer::COMMUNICATION);

    return 0;
}

//TODO
//using smart ponters
//uing enum class instead of int.
//using vector instead of forward_list (map / unordered_map ?)
//or maybe implementing the storage of observers in a linked list
 
