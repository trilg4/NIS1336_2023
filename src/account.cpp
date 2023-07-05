#include "../include/account.h"
#include "../include/task.h"

using namespace std;
int User::s_nextuid = 1;

bool saveUserToFile(vector<User>& ulist) {
    ofstream outputfile ("../data/userinfo.txt");
    if(outputfile.is_open()){
        for(const auto& tmp : ulist){
            outputfile
            << tmp.getUsername() << " "
            << tmp.getPasswordHash() << " "
            << tmp.getUid()<<" "
            <<endl;
        }
        outputfile.close();
        return true;
    }
    return false;
}

void loadUserFromFile(vector<User>& ulist) {
    ifstream infile("../data/userinfo.txt");
    if(!infile){
       ofstream outputfile("../data/userinfo.txt");
       return;

    }
    int tmp_uid;
    string tmp_userName;
    string tmp_passwordHash;
    
    
    while(infile >> tmp_userName>> tmp_passwordHash >> tmp_uid ){
        User tmp(tmp_userName, tmp_passwordHash, tmp_uid);
        ulist.push_back(tmp);
    }
    sort_by_uid(ulist);
    setNextUid((*(ulist.end()-1)).getUid()+1);
}

bool uid_compare(User a, User b){
    return a.getUid() < b.getUid();
}

void sort_by_uid(vector<User>& ulist) {
    sort(ulist.begin(), ulist.end(), uid_compare);
}

void setNextUid(const int next_id) {
    User::s_nextuid = next_id;
}

int userLogin() {
    vector<User> ulist;
    loadUserFromFile(ulist);
    cout<<"quit? 0 for NO ;1 for YES; "<<endl;
    int quit;
    cin>>quit;
    if(quit==1){
        saveUserToFile(ulist);
        exit(0);
    }
    cout<<"if you want to create a new account ,please input the username and the password directly;"<<endl;
    while(true){
        cout<<"username: "<<endl;
        string username;
        cin>>username;
        cout<<"password: "<<endl;
        string password;
        cin>>password;
        User tmp_user(username, password, -1);
        for(auto it = ulist.begin() ; it < ulist.end() ; it++){
            if(username == (*it).getUsername() && tmp_user.getPasswordHash() == (*it).getPasswordHash()){
                return (*it).getUid();
            }
        }
    //not found
        while(1) {
            cout<<"user not found\n option: 0.return to the login interface\n 1.create a new account \n";
            int option;
            cin>>option;
            if(option==0) break;
            else if(option==1){
                User new_user(username,password);
                ulist.push_back(new_user);
                saveUserToFile(ulist);
                return new_user.getUid();
            }
        }
    }
}

int userLogin(string username, string password){
    vector<User> ulist;
    loadUserFromFile(ulist);
    User tmp_user(username, password, -1);
    for(auto it = ulist.begin() ; it < ulist.end() ; it++){
        if(username == (*it).getUsername() && tmp_user.getPasswordHash() == (*it).getPasswordHash()){
            return (*it).getUid();
        }
    }
    return -1;
}