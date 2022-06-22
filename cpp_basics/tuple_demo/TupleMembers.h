#pragma once

template <typename ...Types>
class TupleMembers {
public:
    TupleMembers(
        Types...                aArguments
    ) :
        myMembers(std::forward<Types>(aArguments)...)
        //myMembers(std::make_tuple<Types...>(std::forward<Types>(aArguments)...))
    {
    }

    template<typename FunctionType>
    void
    CallFirstArg(FunctionType aFunction)
    {
        aFunction(std::get<0>(myMembers));
    }

    template<typename FunctionType, std::size_t ...I>
    inline void
    PrivCallHelper(FunctionType aFunction, std::index_sequence<I...>)
    {
        aFunction(std::get<I>(myMembers)...);
    }

    template<typename FunctionType>
    void
    CallWithHelper(FunctionType aFunction)
    {
        PrivCallHelper(aFunction, std::index_sequence_for<Types...>{});
    }

    std::tuple<Types...>        myMembers;
};

