#include "mvc/rgapplication.h"

int main()
{
//    std::cout << "main" << std::endl;
    rg::Application app;

    if(app.run()) exit(0);
    return 0;
}
