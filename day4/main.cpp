#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>

bool XMAS_check(const std::string & s)
{
    std::string check(s.begin(),s.begin()+4);
    return check == "XMAS" || check == "SMAX" ? true : false;
}

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
    f_ptr.seekg(0, f_ptr.end);
    int f_rows = f_ptr.tellg();
    f_ptr.seekg(0, f_ptr.beg);

    char ch;
    std::string str_buff[4];
    for (int i = 0; i< 3;i++)
        std::getline(f_ptr,str_buff[i]);
    int f_col = str_buff[0].size();
    f_rows /= f_col + 1;
    
    long long result_p1 = 0;
    long long result_p2 = 0;
    int i = 0;
    for (; i < f_rows; i++)
    {
        std::getline(f_ptr,str_buff[(i+3)%4]);
        //horizontal search
        std::size_t pos = 0;
        while (1)
        {
            pos = str_buff[i % 4].find("XMAS", pos);
            if (pos < f_col)
            {
                pos += 4;
                result_p1++;
            }
            else
                break;
        }
        pos = 0;
        while (1)
        {
            pos = str_buff[i % 4].find("SAMX",pos);
            if (pos < f_col)
            {
                pos += 4;
                result_p1++;
            }
            else
                break;
        }
        //vertical search
        if (i < f_rows - 3)
        {
            for (int j = 0; j < f_col; j++)
            {
                if (str_buff[i % 4][j] == 'X' && str_buff[(i+1) % 4][j] == 'M'
                && str_buff[(i+2) % 4][j] == 'A' && str_buff[(i+3) % 4][j] == 'S')
                    result_p1++;
                if (str_buff[i % 4][j] == 'S' && str_buff[(i+1) % 4][j] == 'A'
                && str_buff[(i+2) % 4][j] == 'M' && str_buff[(i+3) % 4][j] == 'X')
                    result_p1++;
            }
            //diagonal search from word left to right
            for (int j = 0; j < f_col-3; j++)
            {
                if (str_buff[i % 4][j] == 'X' && str_buff[(i+1) % 4][j+1] == 'M'
                && str_buff[(i+2) % 4][j+2] == 'A' && str_buff[(i+3) % 4][j+3] == 'S')
                    result_p1++;
                else if (str_buff[i % 4][j] == 'S' && str_buff[(i+1) % 4][j+1] == 'A'
                && str_buff[(i+2) % 4][j+2] == 'M' && str_buff[(i+3) % 4][j+3] == 'X')
                    result_p1++;
            }
            //diagonal search from word right to left 
            for (int j = 0; j < f_col-3; j++)
            {
                if (str_buff[i % 4][j+3] == 'X' && str_buff[(i+1) % 4][j+2] == 'M'
                && str_buff[(i+2) % 4][j+1] == 'A' && str_buff[(i+3) % 4][j] == 'S')
                    result_p1++;
                else if (str_buff[i % 4][j+3] == 'S' && str_buff[(i+1) % 4][j+2] == 'A'
                && str_buff[(i+2) % 4][j+1] == 'M' && str_buff[(i+3) % 4][j] == 'X')
                    result_p1++;
            }
        }
        if ( i < f_rows - 2)
        {
            for (int j = 0; j < f_col - 2; j++)
            {
                if (str_buff[(i+1) % 4][j+1] == 'A')
                {
                    if (str_buff[i % 4][j] == 'M' && str_buff[i % 4][j+2] == 'S'
                    && str_buff[(i+2) % 4][j] == 'M' && str_buff[(i+2) % 4][j+2] == 'S')
                        result_p2++;
                    else if (str_buff[i % 4][j] == 'M' && str_buff[i % 4][j+2] == 'M'
                    && str_buff[(i+2) % 4][j] == 'S' && str_buff[(i+2) % 4][j+2] == 'S')
                        result_p2++;
                    else if (str_buff[i % 4][j] == 'S' && str_buff[i % 4][j+2] == 'S'
                    && str_buff[(i+2) % 4][j] == 'M' && str_buff[(i+2) % 4][j+2] == 'M')
                        result_p2++;
                    else if (str_buff[i % 4][j] == 'S' && str_buff[i % 4][j+2] == 'M'
                    && str_buff[(i+2) % 4][j] == 'S' && str_buff[(i+2) % 4][j+2] == 'M')
                        result_p2++;
                    
                }
            }
        }

    }
    
    std::cout << "result part2: " << result_p2 << std::endl;
    std::cout << "result part1: " << result_p1 << std::endl;

    f_ptr.close();

    return 0;
}