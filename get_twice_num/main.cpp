#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <functional>
#include <chrono>

/**
 * Retrieves elements that are met twice in input.
 *
 * Maximum performance is a goal.
 *
 * Current complexity: Log(N) + N
 */
template<typename T>
static void get_twice_numbers(std::vector<T>& input, std::vector<T>& output) noexcept {
    //Using in-place modification of output vector may be less efficient
    //due to constant re-allocations when erasing element not at the end.
    std::vector<T> temp(input);

    //Log(N)
    std::sort(temp.begin(), temp.end());

    //N
    size_t oc = 1;
    auto prev = temp.cbegin();
    for (auto it = prev + 1; it != temp.cend(); ++it) {
        if (*prev == *it) {
            oc++;
        }
        else {
            if (oc == 2) output.push_back(*prev);
            prev = it;
            oc = 1;
        }
    }
}

template<typename T>
static std::vector<T> random_vector(size_t size) {
    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());
    std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

    std::vector<T> result(size);
    std::generate(result.begin(), result.end(), std::bind(dist, mersenne_engine));

    return result;
}

template<typename T>
static void verify(std::function<void(std::vector<T>&, std::vector<T>&)> get_twice_numbers) {
    std::vector<T> a = {1, 2, 300, 2, 3, 3, 3};
    std::vector<T> result;

    get_twice_numbers(a, result);

    assert(result.size() == 1);
    assert(result[0] == 2);
}

template<typename T>
static void measure(std::function<void(std::vector<T>&, std::vector<T>&)> get_twice_numbers, size_t size) {
    std::vector<T> result;

    auto input = random_vector<T>(size);
    auto start = std::chrono::system_clock::now();
    get_twice_numbers(input, result);
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << size << " elements required " << elapsed.count() << "ms\n";
}

int main(int, char**) {
    std::cout << "Sorting in a temp vector:\n";
    verify<long>(get_twice_numbers<long>);
    measure<long>(get_twice_numbers<long>, 500000);

    return 0;
}
