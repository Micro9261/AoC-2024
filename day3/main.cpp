#include <iostream>
#include <cstdlib>
#include <fstream>

int main(int argc, char ** argv)
{
    long long result_p1 = 0;
    long long result_p2 = 0;
    char ch;

    int state_mul = 0;
    int state_enable = 0;
    int state_disable = 0;

    const char pattern[4] = {'m', 'u', 'l', '('};
    const char mul_enable_p[4] = {'d', 'o', '(', ')'};
    const char mul_disable_p[7] = {'d', 'o', 'n', '\'', 't', '(', ')'};
    bool mul_en = true;

    if (argc < 2)
    {
        std::cerr << "How to use: " << argv[0] << " [input file] " << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::ifstream f_ptr(argv[1]);
    if (!f_ptr.good())
    {
        std::cerr << "Error opening file " << argv[1] << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while ( (ch = f_ptr.get()) != EOF)
    {
        if ( ch == pattern[state_mul] && state_mul != 4)
        {
            state_mul++;
        }
        else if (state_mul != 4)
            state_mul = 0;
        
        if ( ch == mul_disable_p[state_disable] && state_disable != 7)
            state_disable++;
        else if (state_disable == 7)
        {
            mul_en = false;
            state_disable = 0;
        }
        else if (state_disable != 7)
            state_disable = 0;

        if ( ch == mul_enable_p[state_enable] && state_enable != 4)
            state_enable++;
        else if (state_enable == 4)
        {
            mul_en = true;
            state_enable = 0;
        }
        else if (state_enable != 4)
            state_enable = 0;

        if (state_mul != 4)
            continue;

        // after 'mul(' detected
        state_mul = 0;
        int x;
        int y = 0;
        if (!(f_ptr >> x))
        {
            f_ptr.clear();
            continue;
        }
 
        ch = f_ptr.get();
        if (ch == EOF)
            break;
        else if (ch != ',')
            continue;

        if ( !(f_ptr >> y) )
        {
            f_ptr.clear();
            continue;
        }

        ch = f_ptr.get();
        if (ch == EOF)
            break;
        else if (ch != ')')
            continue;

        int num = x * y;
        //std::cout << "Added: " << num << std::endl;
        if (mul_en)
            result_p2 += num;
        result_p1 += num;
    }


    std::cout << "Part 1 result: " << result_p1 << std::endl;
    std::cout << "Part 2 result: " << result_p2 << std::endl;

    f_ptr.close();

    return 0;
}