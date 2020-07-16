#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include ".\Common\Stars.h"
#include <functional>
Starmat smat;
class Model {
public:
    std::function<bool(int)> sendNotification;
    void changeData(){
        //do something
        sendNotification(3);
    }
};
class ViewModel {
public:
    int val;
    ViewModel():val(0) {}
    bool receiveNotification(int _val) {
        this->val = _val;
        return true;
    }
};
int main(int argc, char* argv[]) {
    //some test
    //smat = Starmat(5, 5);
    Model _m;
    ViewModel _vm;
    _m.sendNotification = std::bind(&ViewModel::receiveNotification, &_vm, std::placeholders::_1);
    printf("%d\n", _vm.val);
    _m.changeData();
    printf("%d\n", _vm.val);
    
    //Hello World
    Fl_Window* window;
    Fl_Box* box;
    window = new  Fl_Window(450, 330, "First App!");
    box = new Fl_Box(20, 40, 360, 200, "Hello World");
    box->box(FL_FLAT_BOX);
    box->labelsize(36);
    box->labelfont(FL_BOLD + FL_ITALIC);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);
    return  Fl::run();
	return 0;
}
