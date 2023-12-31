#include <array>
#include <chrono>
#include <iostream>
#include <string_view>
#include <type_traits>

class StopWatch
{
public:
    StopWatch()
    {
        m_startPoint = std::chrono::high_resolution_clock::now();
    }

    std::chrono::duration<double> Stop() const
    {
        auto endPoint = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::duration<double>>(endPoint - m_startPoint);
    }

private:
    std::chrono::high_resolution_clock::time_point m_startPoint;
};

constexpr std::array<std::string_view, 6> string_view_array{ "Hello", "World", "Guten", "Morgen", "Dobro", "jutro" };

static constexpr size_t repeat{ 500'000 };
static constexpr size_t loops{ 500 };

std::pair<double, char> ReturnByValue()
{
    char c = 127;

    std::chrono::duration<double> minDuration = std::chrono::duration<double>::max();

    for (size_t r = 0; r < repeat; ++r)
    {
        StopWatch sw;

        for (size_t l = 0; l < loops; ++l)
        {
            for (auto s : string_view_array)
            {
                c %= s[c % 4];
                c += 15;
            }
        }

        if (const auto duration = sw.Stop(); duration < minDuration)
        {
            minDuration = duration;
        }

    }
    return { minDuration.count(), c };
}

std::pair<double, char> ReturnByConstRef()
{
    char c = 127;

    std::chrono::duration<double> minDuration = std::chrono::duration<double>::max();

    for (size_t r = 0; r < repeat; ++r)
    {
        StopWatch sw;

        for (size_t l = 0; l < loops; ++l)
        {
            for (const auto& s : string_view_array)
            {
                c %= s[c % 4];
                c += 15;
            }
        }

        if (const auto duration = sw.Stop(); duration < minDuration)
        {
            minDuration = duration;
        }

    }
    return { minDuration.count(), c };
}

int main()
{
    auto [duration1, c1] = ReturnByValue();
    std::cout << duration1 << std::endl;
    std::cout << c1 << std::endl;

    auto [duration2, c2] = ReturnByConstRef();
    std::cout << duration2 << std::endl;
    std::cout << c2 << std::endl;
}
