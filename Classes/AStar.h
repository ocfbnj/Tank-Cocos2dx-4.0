#ifndef _ASTAR_H_
#define _ASTAR_H_

#include <memory>
#include <list>
#include <vector>
#include <utility>

class AStar {
public:
    using _Coordinate_t = int;
    using _G_value_t = int;
    using _H_value_t = int;
    using _Result_point_t = std::pair<_Coordinate_t, _Coordinate_t>;

    struct __Position {
        __Position(AStar::_Coordinate_t _x = 0, AStar::_Coordinate_t _y = 0, AStar::_G_value_t G = 0) :
            x(_x), y(_y), _G(G), _H() {
            ctor++;
        }

        ~__Position() { dtor++; }

        _Coordinate_t x;
        _Coordinate_t y;

        _G_value_t _G;
        _H_value_t _H;

        __Position* _prev = nullptr;

        static int ctor;
        static int dtor;
    };

public:
    AStar(_Coordinate_t x1, _Coordinate_t y1, _Coordinate_t x2, _Coordinate_t y2);

    void set_map(const char* map, int rows, int cols);
    [[nodiscard]] std::vector<_Result_point_t> get_route();

private:
    std::unique_ptr<__Position> _begin;
    std::unique_ptr<__Position> _end;

    std::list<std::unique_ptr<__Position>> _open_list;
    std::list<std::unique_ptr<__Position>> _close_list;

    std::unique_ptr<char[]> _map;

    long long _rows{};
    long long _cols{};

    void __set_H(__Position* _pos);
    bool __reslove();
    void __explore(std::list<std::unique_ptr<__Position>>::iterator& it);
    void __try_move(__Position* prev, std::unique_ptr<__Position> cur);
};

#endif
