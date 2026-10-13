#ifndef PACK_H
#define PACK_H

#include <type_traits>

namespace pack_detail {
    // 1. Count the number of types
    template <typename... Args>
    constexpr int packSize = static_cast<int>(sizeof...(Args));

    // 2. Index to type: Recursively unpack the types until we reach the desired index
    // Primary template: required declaration
    template <int QueryIndex, typename... Args>
    struct _packIndexToType {
        static_assert(sizeof...(Args) > 0 && QueryIndex >= 0, "Index out of range");
    };

    // Base case when Index is 0 return the first type
    template <typename First, typename... Rest>
    struct _packIndexToType<0, First, Rest...> {
        using type = First;
    };
    // Recursive case: If the index isn't zero, skip the first type and decrease the index
    template <int QueryIndex, typename First, typename... Rest>
    struct _packIndexToType<QueryIndex, First, Rest...> {
        using type = typename _packIndexToType<QueryIndex - 1, Rest...>::type;
    };

    // the required _packIndexToType template for convenience
    template <int QueryIndex, typename... Args>
    using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;   

    // 3. Type to index: Recursively unpack the types until we find the desired type
    // Primary: empty pack -> not found
    template <int Accumulated, typename QueryType, typename... Args>
    constexpr int _packTypeToIndex = -1;

    // Partial specialization: at least one type left
    template <int Accumulated, typename QueryType, typename First, typename... Rest>
    // If the first type matches the query type, return the accumulated index
    // Otherwise, continue searching in the rest of the types, incrementing the accumulated index
    constexpr int _packTypeToIndex<Accumulated, QueryType, First, Rest...> =
        std::is_same_v<QueryType, First>
            ? Accumulated
            : _packTypeToIndex<Accumulated + 1, QueryType, Rest...>;

    template <typename QueryType, typename... Args>
    constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

}
template <typename... Args>
struct Pack {
    // 4. Size
    static constexpr int size = pack_detail::packSize<Args...>;

    // 5. Index to type
    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    // 6. Type to index
    template <typename QueryType>
    static constexpr int index = pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif  // PACK_H
