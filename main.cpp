#include "JigsawPuzzles/JigsawPuzzles_t.hpp"
#include <iostream>
#include <string>

struct Life : public JP::Public::Puzzle<struct LifeTag> {
    Life(){
        std :: cout << "Life Constructed!" << std :: endl;
    }
    ~Life() {
        std :: cout << "Life Destructed!" << std :: endl;
    }
};

struct Print : public JP::Public::Puzzle<struct PrintTag> {
    inline void println(const std::string& str) const {
        std :: cout << str << std :: endl;
    }
};

int main() {
    JP::Template::TemplateBoard<Life, Print> board;
    board.Load<PrintTag>().println("Hello, world!");
    return 0;
}