#include "reminder.h"
#include <thread>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <cerrno>

Reminder::Reminder(const string& filename){
    Rem_Tasks = loadTasksFromFile(filename);
    string re_filename = filename;
};


void Reminder::reminderbyDuetime(){
    sort_by_reminderTime(Rem_Tasks);
    int numberofRem_Tasks = Rem_Tasks.size();
    for(int i =0;i<numberofRem_Tasks;i++){
        std::cout<<Rem_Tasks[i].getReminderTime()<<std::endl;
    }
}    
    
void Reminder::reminderbyId(){
    sort_by_id(Rem_Tasks);
    int numberofRem_Tasks = Rem_Tasks.size();
    for(int i = 0;i<numberofRem_Tasks;i++){
        std::cout<<Rem_Tasks[i].getId()<<std::endl;
    }
}



void Reminder::scan(){ //may check every 15 minutes
    
 
 while(true){
    while(isFileLocked(re_filename) ){
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }        //to check the tasklist periodically


    //open the file    
    int fd = open("example.txt", O_RDWR);
    if (fd == -1) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    //lock the file
    if (flock(fd, LOCK_EX) == -1) {
        std::cerr << "Failed to acquire the lock." << std::endl;
        close(fd);
        return 1;
    }


    if(isFileLocked(re_filename)){
        Rem_Tasks = loadTasksFromFile(re_filename);
            int numberofTasks = Rem_Tasks.size();
            for(int i=0;i<numberofTasks;i++){
             if(compareTime(Rem_Tasks[i].getReminderTime(),getCurrentTime())&&!Rem_Tasks[i].isReminded())
                {
                   std::cout<<Rem_Tasks[i].getId()<<" "<<Rem_Tasks[i].getName()<<" "<<Rem_Tasks[i].getReminderTime()<<std::endl;
                   Rem_Tasks[i].setReminded(true);
                }
            }
        if (flock(fd, LOCK_UN) == -1) {
            std::cerr << "Failed to release the lock." << std::endl;
            } 
        else {
        std::cout << "File unlocked successfully!" << std::endl;
        }
        close(fd);

    } 
 }  

};



const string Reminder::getCurrentTime() const{
    // Get the current system time
    std::time_t currentTime = std::time(nullptr);

    // Convert the system time to local time
    std::tm* localTime = std::localtime(&currentTime);

    // Format the time as MM/DD/hh/mm
    char formattedTime[20];
    std::strftime(formattedTime, sizeof(formattedTime), "%m/%d/%H/%M", localTime);

    // Print the formatted time
    return formattedTime.c_str(); 
};


bool Reminder::compareTime(const string re_dueTime, const string re_currentTime){
    if(strcmp(re_dueTime,re_currentTime)==1||strcmp(re_dueTime,re_currentTime)==0) {
        return false;// the task is not overdue
    }
    else 
    {return true;} //the task is overdue
}

bool isFileLocked(const std::string& filePath) {
    int fd = open(filePath, O_RDWR);
    if (fd == -1) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    // Attempt to acquire a non-blocking exclusive write lock
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            // The file is already locked
            close(fd);
            return true;
        } else {
            // An error occurred while acquiring the lock
            std::cerr << "Failed to acquire the lock." << std::endl;
            close(fd);
            return false;
        }
    }

    // Release the lock
    if (flock(fd, LOCK_UN) == -1) {
        std::cerr << "Failed to release the lock." << std::endl;
    }

    close(fd);
    return false;
}