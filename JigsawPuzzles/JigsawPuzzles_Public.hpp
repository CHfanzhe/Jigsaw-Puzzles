#pragma once
#include <type_traits>
// JigsawPuzzle -> JP
namespace JP::Public {
    struct empty_inherit {};
    template<typename PuzzleTag, typename PuzzleInherit = empty_inherit>
    class Puzzle : public PuzzleInherit {
    private:
        friend struct PuzzleTools;
        using Tag       = PuzzleTag;
        using Inherit   = PuzzleInherit;
    public: using PuzzleInherit::PuzzleInherit;
    };

    struct PuzzleTools {
        template<typename T, typename = void>                   
            struct is_Puzzle : public std::false_type {};
        template<typename PuzzleTag, typename PuzzleInherit>
            struct is_Puzzle<Puzzle<PuzzleTag, PuzzleInherit>> : public std::true_type {};
        template<typename T>
            struct is_Puzzle<T, std::void_t<typename T::Tag, typename T::Inherit>> 
            : public std::conditional_t<
                std::is_base_of_v<Puzzle<typename T::Tag, typename T::Inherit>, T>,
                std::true_type, std::false_type> {};
        template<typename T> static constexpr bool is_Puzzle_v = is_Puzzle<T>::value;


        template<typename T, typename = std::enable_if_t<is_Puzzle_v<T>>>
            struct get_PuzzleTag {
                using type = typename T::Tag;
            };
        template<typename T> using get_PuzzleTag_t = get_PuzzleTag<T>::type;
        

        template<typename T, typename = std::enable_if_t<is_Puzzle_v<T>>>
            struct get_PuzzleInherit { using type = T::Inherit; };
        template<typename T> using get_PuzzleInherit_t = get_PuzzleInherit<T>::type;


        template<typename T1, typename T2, typename = 
            std::enable_if_t<is_Puzzle_v<T1> && is_Puzzle_v<T2>>>
            struct has_same_PuzzleTag 
                : public std::conditional_t<
                    std::is_same_v<get_PuzzleTag_t<T1>, get_PuzzleTag_t<T2>>,
                    std::true_type, std::false_type> {};
        template<typename T1, typename T2> 
            static constexpr bool has_same_PuzzleTag_v = has_same_PuzzleTag<T1, T2>::value;
        

        template<typename T1, typename T2, typename = 
            std::enable_if_t<is_Puzzle_v<T1> && is_Puzzle_v<T2>>>
            struct has_same_PuzzleInherit 
                : public std::conditional_t<
                    std::is_same_v<get_PuzzleInherit_t<T1>, get_PuzzleInherit_t<T2>>,
                    std::true_type, std::false_type> {};
        template<typename T1, typename T2> 
            static constexpr bool has_same_PuzzleInherit_v = has_same_PuzzleInherit<T1, T2>::value;



        template<typename T1, typename T2, typename = 
            std::enable_if_t<is_Puzzle_v<T1> && is_Puzzle_v<T2>>>
            struct completely_same 
                : public std::conditional_t<
                    (has_same_PuzzleInherit_v<T1, T2> && has_same_PuzzleTag_v<T1, T2>),
                    std::true_type, std::false_type
                > {};
        template<typename T1, typename T2>
            static constexpr bool completely_same_v = completely_same<T1, T2>::value;
    };
}