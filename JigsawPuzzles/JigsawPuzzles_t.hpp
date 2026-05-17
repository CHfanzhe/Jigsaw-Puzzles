#pragma once
#include "JigsawPuzzles_Public.hpp"
#include <type_traits>
#include <tuple>

//JigsawPuzzles -> JP
namespace JP::Template {
    template<typename... JPs>
    class TemplateBoard : protected JPs... {
        static_assert((Public::PuzzleTools::is_Puzzle_v<JPs> && ...),
            "JigsawPuzzles Must Be Puzzle!");
        static_assert((std::is_default_constructible_v<JPs> && ...), 
            "JigsawPuzzles Must Has Default Constructible!");
    private:
    public:
        struct TupleOperator {
            template<typename PuzzleTag, typename... Args>
            struct search_PuzzleTag;



            template<typename PuzzleTag, typename T, typename... Args>
            struct search_PuzzleTag<PuzzleTag, T, Args...> {
            private:
                using other_result = typename search_PuzzleTag<PuzzleTag, Args...>::type;
                using this_result = std::conditional_t<
                    Public::PuzzleTools::is_Puzzle_v<T>, 
                        std::conditional_t<
                            Public::PuzzleTools::has_same_PuzzleTag_v<T, Public::Puzzle<PuzzleTag>>,
                                std::tuple<T>, std::tuple<>
                        >, std::tuple<>
                >;
            public:
                using type = decltype(
                    std::tuple_cat(std::declval<this_result>(), std::declval<other_result>())
                );
            };
            template<typename PuzzleTag>
            struct search_PuzzleTag<PuzzleTag> { using type = std::tuple<>; };
            template<typename PuzzleTag, typename... Args>
            using search_PuzzleTag_t = typename search_PuzzleTag<PuzzleTag, Args...>::type;
        };



        template<typename PuzzleTag>
        constexpr auto Load() noexcept {
            using result = typename TupleOperator::template search_PuzzleTag_t<PuzzleTag, JPs...>;
            static_assert((std::tuple_size_v<result> == 1), "Found Zero or Over One Puzzle!");
            using type = std::tuple_element_t<0, result>;
            return static_cast<type&>(*this);
        };
        template<typename PuzzleTag>
        constexpr auto Load() const noexcept {
            using result = typename TupleOperator::template search_PuzzleTag_t<PuzzleTag, JPs...>;
            static_assert((std::tuple_size_v<result> == 1), "Found Zero or Over One Puzzle!");
            using type = std::tuple_element_t<0, result>;
            return static_cast<const type&>(*this);
        };
    };
}