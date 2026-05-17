#include "Jigsaw_Puzzles_template.hpp"
#include <iostream>

namespace Tags{
    struct PRINT{};
    struct LifeReporter{};
}

struct LifeReporter : public Jigsaw_Puzzles::Template::Jigsaw_Puzzle<Tags::LifeReporter>
{
    LifeReporter() {
        std :: cout << "LifeReporter Was Build!\n";
    }
    ~LifeReporter(){
        std :: cout << "LifeReporter Was Destory!\n";
    }
};

struct Print : public Jigsaw_Puzzles::Template::Jigsaw_Puzzle<Tags::PRINT> {
    inline void PrintFunc(const std::string& msg) noexcept {
        std :: cout << msg;
    }
};

struct PrintV2 : Print {
    inline void PrintFuncln(const std::string& msg) noexcept {
        std :: cout << msg << std::endl;
    }
    inline void PrintFunc(const std::string& msg) noexcept {
        std :: cout << msg;
    }
};

int main(){
    Jigsaw_Puzzles::Template::Jigsaw_Puzzle_Board<LifeReporter, PrintV2> test;
    PrintV2& a = test.Load<Tags::PRINT>();
    a.PrintFunc("Hello, World!!!!!\n");
    a.PrintFuncln("1234567890");

    std :: cout << "Hello, World!" << std :: endl;
    std :: cin.get();
    return 0;
}