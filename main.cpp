// GDENG03_CPlusPlus3D.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AppWindow.h"

int main()
{
    AppWindow app;
    try {
        if (!app.init())
            return -1;

        while (app.isRunning())
        {
            app.broadcast();
        }

    } catch (const std::exception& err)
    {
	    std::cout << err.what();
        return -1;
    }

    app.onDestroy();

    return 0;
}
