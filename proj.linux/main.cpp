#include "../Classes/AppDelegate.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

int main(int argc, char **argv)
{
    AppDelegate app;
    return Application::getInstance()->run();
}
