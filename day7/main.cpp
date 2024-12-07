#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>



bool check_equ(std::vector<int> & v, int elem, unsigned long long res, unsigned long long equ);

bool check_equ_3operators(std::vector<int> & v, int elem, unsigned long long equ);
int base10(int num);

int main(int argc, char ** argv)
{
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
    
    int line_cnt = 0;
    unsigned long long result_p1 = 0;
    unsigned long long result_p2 = 0;
    while (!f_ptr.eof())
    {
        std::vector<int> seq;
        unsigned long long equ;
        f_ptr >> equ;
        while(f_ptr.get() != '\n' && !f_ptr.eof())
        {
            int tmp;
            f_ptr >> tmp;
            seq.push_back(tmp);
        }
        line_cnt++;
        if (check_equ(seq,1,seq[0],equ))
            result_p1 += equ;
        else if(check_equ_3operators(seq,seq.size(),equ))
        {
            result_p2 += equ;
        }

    }

    std::cout << "Result part1: " << result_p1 << std::endl;
    std::cout << "Result part2: " << result_p2 + result_p1<< std::endl;

    f_ptr.close();

    return 0;
}

bool check_equ(std::vector<int> & v, int elem, unsigned long long res, unsigned long long equ)
{
    bool right = false, left = false;
    if (elem == 0)
    {
        left = right = check_equ(v, elem + 1, v[elem],equ);
    }
    else if (elem < v.size() && res < equ)
    {
        left = check_equ(v, elem + 1, res * v[elem],equ);
        right = check_equ(v, elem + 1, res + v[elem],equ);
    }
    else
        return res == equ;

    return left | right;
}

bool check_equ_3operators(std::vector<int> & v, int elem, unsigned long long equ)
{
    int iter = elem - 1;
    bool mul = false, add = false, con = false;
    if (iter > 1 && equ > v[iter])
    {
        if (equ % v[iter] == 0)
            mul = check_equ_3operators(v, iter, equ / v[iter]);
        add = check_equ_3operators(v, iter, equ - v[iter]);
        int digit = base10(v[iter]);
        equ -= v[iter];
        int base = 1;
        while (digit > 0)
        {
            digit--;
            base *= 10;
        }
        if (equ % base == 0)
            con = check_equ_3operators(v, iter, equ / base);
    }
    else
    {
        if (equ % v[iter] == 0)
            mul = equ / v[iter] == v[0];
        add = equ - v[iter] == v[0];
        int digit = base10(v[iter]);
        equ -= v[iter];
        while (digit > 0)
        {
            if (equ % 10 != 0)
                break;
            equ /= 10;
            digit--;
        }
        con = equ == v[0];
    }

    return mul | add | con;
}

int base10(int num)
{
    int digits = 0;
    while (num > 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}