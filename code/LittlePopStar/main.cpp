#include "./App/App.h"
#include <ctime>
int main(int argc, char* argv[]) {
    srand(time(NULL));
    std::unique_ptr<GameApp> _App(new GameApp);
    //bool t = _App->Init();
    return _App->Run();
}
