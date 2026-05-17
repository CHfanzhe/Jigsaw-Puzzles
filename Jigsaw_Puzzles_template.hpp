#pragma once
#include <type_traits>
#include <tuple>
namespace Jigsaw_Puzzles::Template {
    struct void_herit {};
    template<typename NameTag, typename Inherit = void>
    class Jigsaw_Puzzle : public std::conditional_t<std::is_same_v<Inherit, void>, void_herit, void> {
    private:
        template<typename, typename> friend struct get_name_tag;
        template<typename, typename> friend struct is_Jigsaw_Puzzle;
        template<typename, typename> friend struct has_herit;
        template<typename, typename> friend struct get_herit;
        using Tag = NameTag;
        using InheritArg = std::conditional_t<std::is_same_v<Inherit, void>, void, Inherit>;
    };

    template<typename T, typename = void>
    struct get_name_tag { using type = void; };
    template<typename T>
    struct get_name_tag<Jigsaw_Puzzle<T>> { using type = T; };
    template<typename T>
    struct get_name_tag<T, std::void_t<typename T::Tag>> {
        using type = std::conditional_t<std::is_base_of_v<Jigsaw_Puzzle<typename T::Tag>, T>, 
                        typename T::Tag, void>;
    };
    template<typename T> using get_name_tag_t = typename get_name_tag<T>::type;

    template<typename T, typename = void>
    struct is_Jigsaw_Puzzle : public std::false_type {};
    template<typename T>
    struct is_Jigsaw_Puzzle<Jigsaw_Puzzle<T>> : public std::true_type { using type = T; };
    template<typename T>
    struct is_Jigsaw_Puzzle<T, std::void_t<typename T::Tag>> : public
        std::conditional_t<std::is_base_of_v<Jigsaw_Puzzle<typename T::Tag>, T>, 
                        std::true_type, std::false_type>
    {};
    template<typename T> constexpr bool is_Jigsaw_Puzzle_v = is_Jigsaw_Puzzle<T>::value;

    template<typename, typename = void> struct has_herit : std::false_type {};
    template<typename T>
    struct has_herit<T, std::enable_if_t<is_Jigsaw_Puzzle_v<T>>> : public std::conditional_t<
    std::is_same_v<typename T::InheritArg, void>, std::true_type, std::false_type> {};
    template<typename T> constexpr bool has_herit_v = has_herit<T>::value;

    template<typename T, typename = void> struct get_herit { using type = void; };
    template<typename T> 
    struct get_herit<T, std::enable_if_t<is_Jigsaw_Puzzle_v<T>>> { using type = typename T::InheritArg; };
    template<typename T> using get_herit_t = typename get_herit<T>::type;



    struct Tuple {
    public:
        template<typename Tag, typename... Args>
        struct Search;

        template<typename Tag, typename T, typename... Args>
        struct Search<Tag, T, Args...> {
        private:
            using other_result = typename Search<Tag, Args...>::type;
            using this_result = std::conditional_t<is_Jigsaw_Puzzle_v<T>,
            std::conditional_t<std::is_same_v<get_name_tag_t<T>, Tag>, std::tuple<T>, std::tuple<>>, 
            std::tuple<>>;
        public:
            using type =
            decltype(std::tuple_cat(std::declval<this_result>(), std::declval<other_result>()));
        };

        template<typename Tag>
        struct Search<Tag> { using type = std::tuple<>; };
    };

    template<typename... Jigsaw_Puzzles>
    class Jigsaw_Puzzle_Board : protected Jigsaw_Puzzles... {
    private:
        static_assert((is_Jigsaw_Puzzle_v<Jigsaw_Puzzles> && ...),
            "All The Args Must Be Base On Jigsaw_Puzzles!");
        using Args = std::tuple<Jigsaw_Puzzles...>;
    public:
        template<typename NameTag, typename result = Tuple::Search<NameTag, Jigsaw_Puzzles...>::type>
        constexpr auto Load() noexcept 
            -> typename std::decay_t<std::tuple_element_t<0, result>> & {
            static_assert((std::tuple_size_v<result> == 1), "Load Faild: Find Zero Or More Same NameTag.");
            return static_cast<std::decay_t<std::tuple_element_t<0, result>>&>(*this);
        }
        template<typename NameTag, typename result = Tuple::Search<NameTag, Jigsaw_Puzzles...>::type>
        constexpr auto Load() const noexcept 
            -> const typename std::decay_t<std::tuple_element_t<0, result>> & {
            static_assert((std::tuple_size_v<result> == 1), "Load Faild: Find Zero Or More Same NameTag.");
            return static_cast<const std::decay_t<std::tuple_element_t<0, result>>&>(*this);
            
        }
    };


}