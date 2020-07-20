#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <Fl/fl_draw.H>
#include ".\Common\Stars.h"
#include ".\Model\Model.h"
#include <functional>
#include <memory>
class TestBox : public Fl_Box {
public:
    TestBox(int x, int y, int w, int h) :Fl_Box(x, y, w, h) {}
    std::shared_ptr<Starmat> smat;
private:
    int handle(int);
    void draw();
};
int TestBox::handle(int event) {
    if (event == FL_PUSH && Fl::event_button() == 1) {
        int x = Fl::event_x(), y = Fl::event_y();
        int bx = this->x(), by = this->y();
        printf("%d %d\n", x-bx, y-by);
        int w = 100, h = 100;
        int _c = (x - bx) / w;
        int _r = (by + this->h() - y) / h;
        printf("%d %d\n", _r, _c);
        return 1;
    }
    return 0;
}
void TestBox::draw() {
    static Fl_Color colortable[] = { FL_BLACK,FL_RED,FL_GREEN,FL_YELLOW,FL_BLUE };
    int n = smat->size();
    int m = smat->begin()->size();
    int w = 100, h = 100;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            Star s = smat->getStar(i,j);
            int _color = s.getColor(), _pickup = s.getPickup();
            if (_color == -1) return;
            int posx = this->x() + i * w;
            int posy = this->y() + this->h() - h - j * h;
            fl_rect(posx, posy, w-5, h-5, colortable[_color]);
        }
    return;
}
StarMap stm(5, 5, 5);
int main(int argc, char* argv[]) {
    //some test
    Fl_Window* window;
    TestBox* box;
    window = new  Fl_Window(1080, 768, "LittlePopStar");
    box = new TestBox(40, 34, 1000, 700);
    box->smat = stm.getStarmat();
    window->end();
    window->show(argc, argv);
    return  Fl::run();
	return 0;
}
