#include "Model.h"
#include <queue>

StarMap::StarMap(int _row, int _col,unsigned int _colorNum) :starMap(_row, _col),row(_row),col(_col),colorNum(_colorNum) {
	initStars();
	//puts("StarMap construct"); system("pause");
	sendNotification = [](int x) {
		puts("initialize notification");
		return x;
	};
}

void StarMap::initStars() {
	for (int i = 0; i < row; i++) 
		for (int j = 0; j < col; j++) {
			starMap.setStar(i, j, Star(rand() % colorNum + 1, false));
		}
}


bool StarMap::pickupStar(int _row, int _col) {
	printf("pickup %d %d\n",_row,_col);//debug information

	if (_row >= row || _col >= col) {
		throw "no this star";
		return false;
	}
	std::queue<std::pair<int, int> > que;
	while (!que.empty()) que.pop();
	que.push(std::make_pair(_row, _col));
	Star cur = starMap.getStar(_row, _col);
	bool flag = cur.getPickup();
	cur.setPickup(!flag);
	starMap.setStar(_row, _col, cur);
	unsigned int curColor = cur.getColor();
	while (!que.empty()) {
		std::pair<int, int> c = que.front(), t;
		que.pop();
		for (int i = 0; i < 4; i++) {
			t = c;
			switch (i) {
			case 0: t.first--; break;
			case 1: t.first++; break;
			case 2: t.second--; break;
			case 3: t.second++; break;
			}
			if (t.first >= 0 && t.first < row && t.second >= 0 && t.second < col) {
				Star tmp = starMap.getStar(t.first, t.second);
				if (tmp.getPickup()!=flag || tmp.getColor()!=curColor) continue;
				tmp.setPickup(!flag);
				starMap.setStar(t.first, t.second, tmp);//!!
				que.push(t);
			}
		}

	}
	sendNotification(0);
	return true;
}

bool StarMap::pickupStar(int _num) {
	if (_num > row * col) {
		throw "no this star";
		return false;
	}
	return pickupStar(_num / col, _num % col);
}

void StarMap::attachNotification(std::function<void(int)>&& _notification_func) {
	sendNotification = std::move(_notification_func);
}

/*void StarMap::detachNotification() {
	sendNotification = std::function<void(int)>();
}*/

std::shared_ptr<Starmat> StarMap::getStarmat() {
	return std::make_shared<Starmat>(starMap);
}
