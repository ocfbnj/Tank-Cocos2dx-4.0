#include "AStar.h"

#include <cmath>
#include <algorithm>
#include <cstring>

void AStar::set_map(const char* map, int rows, int cols) {
	_rows = rows;
	_cols = cols;
	_map = std::make_unique<char[]>((long long)rows * cols);
	std::memcpy(_map.get(), map, (long long)rows * cols);
}

std::vector<AStar::_Result_point_t> AStar::get_route() {
	__reslove();
	std::vector<AStar::_Result_point_t> res;
	const __Position* end = _end.get();
	while (end) {
		res.push_back({ end->x, end->y });
		end = end->_prev;
	}

	std::reverse(res.begin(), res.end());

	return res;
}

AStar::AStar(_Coordinate_t x1, _Coordinate_t y1, _Coordinate_t x2, _Coordinate_t y2) :
	_begin(std::make_unique<__Position>(x1, y1)),
	_end(std::make_unique<__Position>(x2, y2)) {

	__set_H(_begin.get());
	_open_list.push_back(std::move(_begin));
}

inline void AStar::__set_H(__Position* _pos) {
	_pos->_H = std::abs(_pos->x - _end->x) + std::abs(_pos->y - _end->y);
}

bool AStar::__reslove() {
	while (!_open_list.empty()) {
		auto cur = std::max_element(_open_list.begin(), _open_list.end(),
			[](auto& left, auto& right) {
				return left->_H + left->_G > right->_H + right->_G;
			}
		);

		if (cur->get()->x == _end->x && cur->get()->y == _end->y) {
			_end = std::move(*cur);
			return true;
		}

		__explore(cur);
	}

	return false;
}

void AStar::__explore(std::list<std::unique_ptr<__Position>>::iterator& it) {
	auto p = it->release();
	_open_list.erase(it);
	_close_list.push_back(std::unique_ptr<__Position>(p));

	long long row = p->x;
	long long col = p->y;
	int g = p->_G;
	int h = p->_H;

	if (row + 1 < _rows && _map[(row + 1) * _cols + col] == '0') {
		__try_move(p, std::make_unique<__Position>(row + 1, col, g + 1));
	}

	if (row - 1 >= 0 && _map[(row - 1) * _cols + col] == '0') {
		__try_move(p, std::make_unique<__Position>(row - 1, col, g + 1));
	}

	if (col + 1 < _cols && _map[row * _cols + col + 1] == '0') {
		__try_move(p, std::make_unique<__Position>(row, col + 1, g + 1));
	}

	if (col - 1 >= 0 && _map[row * _cols + col - 1] == '0') {
		__try_move(p, std::make_unique<__Position>(row, col - 1, g + 1));
	}
}

void AStar::__try_move(__Position* prev, std::unique_ptr<__Position> cur) {
	__set_H(cur.get());
	auto pred = [&cur](auto& ptr) {
		return ptr->x == cur->x && ptr->y == cur->y;
	};

	if (std::find_if(_close_list.begin(), _close_list.end(), pred)
		!= _close_list.end()) return;

	auto it = std::find_if(_open_list.begin(), _open_list.end(), pred);
	if (it != _open_list.end()) {

		if (1 + it->get()->_H < prev->_H) {
			it->get()->_prev = prev;
		}
	}

	else {
		cur->_prev = prev;
		_open_list.push_back(std::move(cur));
	}
}

char map[5][10 + 1] = {
	"1111000111",
	"1000010001",
	"1000010001",
	"1000010001",
	"1111000111"
};
int AStar::__Position::ctor = 0;
int AStar::__Position::dtor = 0;
