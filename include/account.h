#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <openssl/md5.h>
#include <cstring>
#include <sstream>
using namespace std;

class User {
public:
    //to load users
    User(const string& username, const string& passwordHash, int uid)
    {
        m_username = username;
        m_passwordHash = passwordHash;
        m_uid=uid;
    }
    //to create new user
    User(const string& username, const string& password){
        m_username = username;
        m_passwordHash = encryptPassword(password);
        m_uid=s_nextuid;
        s_nextuid++;
    }
    const string& getUsername() const { return m_username; }
    const string& getPasswordHash() const { return m_passwordHash; }
    const int getUid() const {return m_uid;}
    bool checkPassword(const string& password) const {
        return m_passwordHash == encryptPassword(password);
    }
    friend void setNextUid(const int next_id);
    string encryptPassword(const string& password) const {
        // TODO: Implement password encryption or hashing algorithm here
        unsigned char digest[MD5_DIGEST_LENGTH];
        MD5(reinterpret_cast<const unsigned char*>(password.c_str()),password.length(),digest);
        std::stringstream ss;
        for(int i=0;i<MD5_DIGEST_LENGTH;++i) {
            ss<<hex<<setw(2)<<setfill('0')<<static_cast<int>(digest[i]);
        }
        return ss.str();
    }
private:
    string m_username;
    string m_passwordHash;

    
    int m_uid;
    static int s_nextuid;
};
//vector<User> loadTasksFromFile(const string& filename);
//bool saveTasksToFile(const vector<User>& tasks, const string& filename);
int userLogin();
bool saveUserToFile(vector<User>& ulist);
void loadUserFromFile(vector<User>& ulist);
void sort_by_uid(vector<User>& ulist);
void setNextUid(const int next_id);
string toEncrypt(const string& password);
#endif // USER_H