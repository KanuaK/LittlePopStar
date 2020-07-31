#include "./App/App.h"
#include <ctime>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 
int main(int argc, char* argv[]) {
    srand(time(NULL));
    std::unique_ptr<GameApp> _App(new GameApp);
    //bool t = _App->Init();
    return _App->Run();
}
