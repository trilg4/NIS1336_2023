#include <iostream>
#include "./include/account.h"
#include "./include/task.h"
#include "./include/reminder.h"
#include "./include/ui.h"
std::mutex filemutex;
vector<Task> t_list;
using namespace std;

int main(int argc, char* argv[]) {
    UI ui;
    ui.run();
}