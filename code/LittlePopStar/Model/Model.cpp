#include "Model.h"
#include <queue>
#include <iostream>
#include <fstream>

static const Star emptyStar = Star(0, false);
static const int bonusScore[] = { 50,40,30,25,20,15,12,9,6,3,1 };

StarMap::StarMap(int _row, int _col,unsigned int _colorNum) :starMap(_row, _col),row(_row),col(_col),colorNum(_colorNum) {
	initStars();
	//puts("StarMap construct"); system("pause");
}

void StarMap::initStars() {
	starMap = Starmat(row, col);
	for (int i = 0; i < row; i++) 
		for (int j = 0; j < col; j++) {
			starMap.setStar(i, j)= Star(rand() % colorNum + 1, false);
		}
	score = 0;
	if (sendNotification != nullptr) sendNotification(-1);
}


bool StarMap::pickupStar(int _row, int _col) {
	printf("pickup %d %d\n",_row,_col);//debug information

	if (_row >= row || _col >= col) {
		throw "no this star";
		return false;
	}
	if (checkGameOver()) {
		sendNotification(1);
		return true;
	}
	const Star& cur = starMap.getStar(_row, _col);
	if (cur.getPickup()) 
		return popStar();

	pickdownStar();
	if (!cur.getColor()) {
		sendNotification(0);
		return true;
	}
	std::queue<std::pair<int, int> > que;
	while (!que.empty()) que.pop();
	que.push(std::make_pair(_row, _col));
	bool flag = cur.getPickup();
	starMap.setStar(_row, _col).setPickup(!flag);
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
				const Star &tmp = starMap.getStar(t.first, t.second);
				if (tmp.getPickup()!=flag || tmp.getColor()!=curColor) continue;
				starMap.setStar(t.first, t.second).setPickup(!flag);
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

void StarMap::pickdownStar() {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			starMap.setStar(i, j).setPickup(false);
}

bool StarMap::checkGameOver() {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++) {
			unsigned int col = starMap.getStar(i, j).getColor();
			if (col == 0) continue;
			if (i && col == starMap.getStar(i - 1, j).getColor()) return false;
			if (j && col == starMap.getStar(i, j - 1).getColor()) return false;
		}
	puts("GameOver");
	return true;
}

bool StarMap::popStar() {
	int cnt = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (starMap.getStar(i, j).getPickup()) cnt++;
	if (cnt <= 1) {
		sendNotification(0);
		return true;
	}
	score += cnt * (cnt + 1) / 2;
	int l = 0;
	for (int j = 0; j < col; j++) {
		int k = row-1;
		for (int i = row - 1; i >= 0; i--) {
			const Star &tmp = starMap.getStar(i, j);
			if (tmp.getPickup()) {
				popVec.push_back(std::make_pair(i * col + j, tmp.getColor()));
				starMap.setStar(i, j) = emptyStar;
			}
			if (tmp.getColor()) {
				starMap.setStar(k--, j) = tmp;
			}
		}
		for (; k >= 0; k--) starMap.setStar(k, j) = emptyStar;
		if (starMap.getStar(row - 1, j).getColor()) {
			for (int i = 0; i < row; i++)
				starMap.setStar(i, l) = starMap.getStar(i, j);
			l++;
		}
	}
	for (; l < col; l++)
		for (int i = 0; i < row; i++)
			starMap.setStar(i, l) = emptyStar;
	if (checkGameOver()) {
		int cnt = 0;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				if (starMap.getStar(i, j).getColor()) cnt++;
		if (cnt > 10) cnt = 10;
		sendNotification(score+bonusScore[cnt]);
	}
	sendNotification(0);
	//popVec.clear();
	return true;
}

void StarMap::attachNotification(std::function<void(int)>&& _notification_func) {
	sendNotification = std::move(_notification_func);
}

bool StarMap::load(const std::string& file_name) {
	std::fstream in(file_name.c_str(), std::ios_base::in);
	if (in.is_open()) {
		int _row, _col, _colorNum;
		in >> _row >> _col >> _colorNum;
		if (_row == 0 || _col == 0 || _colorNum==0) {
			in.close();
			return false;
		}
		row = _row; col = _col; colorNum = _colorNum;
		printf("load: %d %d %d\n", row, col, colorNum);
		starMap = Starmat(row, col);
		int color;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (in.eof()) {
					initStars();
					throw "Error: Incomplete file!";
					return false;
				}
				in >> color;
				if (color > colorNum || color <= 0) {
					throw "Error: Wrong color!";
					return false;
				}
				starMap.setStar(i, j).setColor(color);
				starMap.setStar(i, j).setPickup(false);
			}
		}
		score = 0;
		if (sendNotification != nullptr) sendNotification(-1);
		return true;
	}
	else {
		return false;
	}
}

/*void StarMap::detachNotification() {
	sendNotification = std::function<void(int)>();
}*/

std::function<Starmat* ()> StarMap::getStarmatFunc() {
	return [this]()->Starmat* {
		return &starMap;
	};
}

std::function<std::vector<std::pair<int, int>>* ()> StarMap::getPopVecFunc() {
	return [this]()->std::vector<std::pair<int, int>>* {
		return &popVec;
	};
}

int* StarMap::getScore() {
	return &score;
}

Starmat* StarMap::getStarmat() {
	return &starMap;
}
