#include <iostream>
#include <type_traits>
#include "pack.h"

int main() {
    // Test 1: Pack with several types
    using MyPack = Pack<int, double, char>;

    // Check size
    static_assert(MyPack::size == 3);
    std::cout << "Test 1 passed size\n";

    // Check index -> type
    static_assert(std::is_same_v<MyPack::type<0>, int>);
    static_assert(std::is_same_v<MyPack::type<1>, double>);
    static_assert(std::is_same_v<MyPack::type<2>, char>);
    std::cout << "Test 2 passed index to type\n";

    // Check type -> index
    static_assert(MyPack::index<int> == 0);
    static_assert(MyPack::index<double> == 1);
    static_assert(MyPack::index<char> == 2);
    std::cout << "Test 3 passed type to index\n";

    // Test 2: Type not found
    static_assert(MyPack::index<float> == -1);
    std::cout << "Test 4 passed missing type\n";

    // Test 3: Empty pack
    using EmptyPack = Pack<>;
    static_assert(EmptyPack::size == 0);
    static_assert(EmptyPack::index<int> == -1);
    std::cout << "Test 5 passed empty pack\n";

    // Test 4: One-type pack
    using SinglePack = Pack<bool>;
    static_assert(SinglePack::size == 1);
    static_assert(std::is_same_v<SinglePack::type<0>, bool>);
    static_assert(SinglePack::index<bool> == 0);
    std::cout << "Test 6 passed single-type pack\n";

    // Test 5: Duplicate types
    using DuplicatePack = Pack<int, char, int>;
    static_assert(DuplicatePack::size == 3);
    static_assert(DuplicatePack::index<int> == 0);
    static_assert(std::is_same_v<DuplicatePack::type<2>, int>);
    std::cout << "Test 7 passed duplicate types\n";

    std::cout << "All passed\n";
    return 0;
}
