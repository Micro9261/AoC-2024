#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <list>

#include <algorithm>

int digits(unsigned long long num)
{
    int dig = 1;
    while (num /= 10)
        dig++;
    return dig;
}

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        std::cerr << "How to use: " << argv[0] << " [input file] [blinks num]" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::ifstream f_ptr(argv[1]);
    if (!f_ptr.good())
    {
        std::cerr << "Error opening file " << argv[1] << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::list<unsigned long long> stones;
    while (!f_ptr.eof())
    {
        unsigned long long tmp;
        f_ptr >> tmp;
        stones.push_back(tmp);
    }
    f_ptr.close();

    int blinks = std::atoi(argv[2]);

    std::for_each(stones.begin(), stones.end(), [](unsigned long long x){std::cout << x << " "; });
    std::cout << std::endl;
    unsigned long long result_p1 = 0;
    for (int i = 0; i < blinks; i++)
    {
        std::list<unsigned long long>::iterator it = stones.begin();
        while (it != stones.end())
        {
            int dig = digits(*it);
            if (*it == 0)
                *it = 1;
            else if (dig % 2 == 0 )
            {
                unsigned long long base = 1;
                int half_dig = dig/2;
                while (half_dig--)
                    base *= 10;
                unsigned long long tmp = *it / base;
                *it %= base;
                stones.push_front(tmp);
            }
            else
                *it *= 2024;

            it++;
        }
        //std::cout << "Iteration: " << i + 1 << std::endl;
        //std::for_each(stones.begin(), stones.end(), [](unsigned long long x){std::cout << x << " "; });
        //std::cout << std::endl;
    }
    


    std::cout << "Result part1: " << stones.size() << std::endl;
    std::cout << "Result part2: " << std::endl;

    return 0;
}