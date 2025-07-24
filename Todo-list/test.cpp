#include "TodoList.h"
int main()
{
    TaskManager manager("my_tasks.txt");
    manager.run();
    return 0;
}