#include "../include/reminder.h"


Reminder::Reminder(const string& filename){
    Rem_Tasks = loadTasksFromFile(filename);
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



void scan(){ //may check every 15 mins
    int numberofTasks = Rem_Tasks.size();


    //static int *overdue = new int[numberofTask]{0}; // initial state 
    
    if("the lock of foreground is unlocked" ){
        //lock the file from the frontground
        while(){
            for(int i=0;i<numberofTasks;i++){
             if(compareTime(Rem_Tasks[i].getReminderTime(),getCurrentTime())&&Rem_Tasks[i].overdue)
              {
                   std::cout<<Rem_Tasks[i].getId()<<Rem_Tasks[i].getName()<<Rem_Tasks[i].getReminderTime()<<std::endl;
                   tasks[i].overdue = 0;
                }
          }
    } //to check the tasklist periodically



    }
    



};



const string getCurrentTime() const{
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


bool compareTime(const string re_dueTime, const string re_currentTime){
    if(strcmp(re_dueTime,re_currentTime)==1||strcmp(re_dueTime,re_currentTime)==0) {
        return false;// the task is not overdue
    }
    else 
    {return true;} //the task is overdue
}