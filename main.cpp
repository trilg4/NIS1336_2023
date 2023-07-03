#include <iostream>
#include "account.h"
#include "task.h"
#include "reminder.h"
#include "ui.h"
using namespace std;

int main(int argc, char* argv[]) {
    UI ui;
    ui.run();
    return 0;
}