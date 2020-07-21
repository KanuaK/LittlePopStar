#include "./App/App.h"
int main(int argc, char* argv[]) {
    std::unique_ptr<GameApp> _App(new GameApp);
    //bool t = _App->Init();
    return _App->Run();
}
