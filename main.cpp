#include "JigsawPuzzles/JigsawPuzzles.hpp"
#include <iostream>

namespace Tags{
    struct PRINT{};
    struct LifeReporter{};
}

struct LifeReporter : public JigsawPuzzles::Template::JigsawPuzzle<Tags::LifeReporter>
{
    LifeReporter() {
        std :: cout << "LifeReporter Was Build!\n";
    }
    ~LifeReporter(){
        std :: cout << "LifeReporter Was Destory!\n";
    }
};

struct Print : public JigsawPuzzles::Template::JigsawPuzzle<Tags::PRINT> {
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
    JigsawPuzzles::Template::JigsawPuzzle_Board<LifeReporter, PrintV2> test;
    PrintV2& a = test.Load<Tags::PRINT>();
    a.PrintFunc("Hello, World!!!!!\n");
    a.PrintFuncln("1234567890");

    std :: cout << "Hello, World!" << std :: endl;
    std :: cin.get();
    return 0;
}