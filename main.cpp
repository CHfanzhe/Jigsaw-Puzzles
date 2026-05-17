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

struct PrintV3 : PrintV2 {
    inline void PrintFuncln(const std::string& msg) noexcept {
        std :: cout << msg << std::endl;
    }
    inline void PrintFunc(const std::string& msg) noexcept {
        std :: cout << msg;
    }
    inline void PrintFuncHello() noexcept {
        std :: cout << "Hello, world!" << std :: endl;
    }
};

int main(){
    JigsawPuzzles::Template::JigsawPuzzleBoard<LifeReporter, PrintV3> test;
    PrintV3& a = test.Load<Tags::PRINT>();
    a.PrintFunc("Hello, World!!!!!\n");
    a.PrintFuncln("1234567890");
    a.PrintFuncHello();

    std :: cout << "Hello, World!" << std :: endl;
    std :: cin.get();
    return 0;
}