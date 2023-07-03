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
    User(const string& username, const string& password, int uid)
    {
        m_username = username;
        m_passwordHash = password;
        m_uid=uid;
    }
    User(const string& username, const string& password){
        m_username = username;
        m_passwordHash = password;
        m_uid=s_nextuid;
        s_nextuid++;
    }
    const string& getUsername() const { return m_username; }
    const string& getPasswordHash() const { return m_passwordHash; }
    bool checkPassword(const string& password) const {
        return m_passwordHash == encryptPassword(password);
    }

private:
    string m_username;
    string m_passwordHash;

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
    int m_uid;
    static int s_nextuid;
};

//vector<User> loadTasksFromFile(const string& filename);
//bool saveTasksToFile(const vector<User>& tasks, const string& filename);
bool userLogin();
bool userLogout();
void saveUserToFile(vector<User>& ulist);
void loadUserFromFile(vector<User>& ulist);

#endif // USER_H