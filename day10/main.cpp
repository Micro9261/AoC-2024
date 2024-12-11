#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <utility>

int rec_search(const std::pair<int,int> & p, std::vector<std::string> & v, char val);
int rec_search2(const std::pair<int,int> & p,const std::vector<std::string> & v, char val);
bool up(std::pair<int,int> & p);
bool down(std::pair<int,int> & p, int max_row);
bool left(std::pair<int,int> & p);
bool right(std::pair<int,int> & p, int max_col);


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

    std::vector<std::string> buff;
    std::string tmp = "";
    int ch;
    while (!f_ptr.eof())
    {
        ch = f_ptr.get();
        if (ch == '\n')
        {
            buff.push_back(tmp);
            tmp = "";
        }
        else    
            tmp += (char)ch;
    }
    buff.push_back(tmp);
    f_ptr.close();

    unsigned long result_p1 = 0;
    unsigned long result_p2 = 0;
    for (int i = 0 ; i < buff.size(); i++)
        for (int j = 0; j < buff[i].size(); j++)
        {
            if ( buff[i][j] == '0')
            {
                std::pair<int,int> pos(j,i);
                std::vector<std::string> tmp(buff);
                result_p1 += rec_search(pos, tmp, '0');
                result_p2 += rec_search2(pos,buff, '0');
            }
        }


    std::cout << "Result part1: " << result_p1 << std::endl;
    std::cout << "Result part2: " << result_p2 << std::endl;

    return 0;
}

int rec_search(const std::pair<int,int> & p, std::vector<std::string> & v, char val)
{
    int ret = 0;
    std::pair<int,int> tmp[4] = {p,p,p,p};
    bool truth_tab[4] = {false};
    truth_tab[0] = up(tmp[0]);
    truth_tab[1] = down(tmp[1], v.size());
    truth_tab[2] = left(tmp[2]);
    truth_tab[3] = right(tmp[3], v[0].size());
    for (int i = 0; i < 4; i++)
    {
        if (truth_tab[i] && v.at(tmp[i].second).at(tmp[i].first) == val + 1)
        {
            if (val == '8')
            {
                ret++;
                v.at(tmp[i].second).at(tmp[i].first) = '#';
            }
            else if (val < '8')
                ret += rec_search(tmp[i],v , val + 1);
        }
    }

    return ret;
}

int rec_search2(const std::pair<int,int> & p,const std::vector<std::string> & v, char val)
{
    int ret = 0;
    std::pair<int,int> tmp[4] = {p,p,p,p};
    bool truth_tab[4] = {false};
    truth_tab[0] = up(tmp[0]);
    truth_tab[1] = down(tmp[1], v.size());
    truth_tab[2] = left(tmp[2]);
    truth_tab[3] = right(tmp[3], v[0].size());
    for (int i = 0; i < 4; i++)
    {
        if (truth_tab[i] && v.at(tmp[i].second).at(tmp[i].first) == val + 1)
        {
            if (val == '8')
            {
                ret++;
            }
            else if (val < '8')
                ret += rec_search2(tmp[i],v , val + 1);
        }
    }

    return ret;
}

bool up(std::pair<int,int> & p)
{
    bool able = true;
    if (p.second > 0)
        p.second--;
    else
        able = false;

    return able;
}

bool down(std::pair<int,int> & p, int max_row)
{
    bool able = true;
    if (p.second < max_row - 1)
        p.second++;
    else
        able = false;

    return able;
}

bool left(std::pair<int,int> & p)
{
    bool able = true;
    if (p.first > 0)
        p.first--;
    else
        able = false;

    return able;
}

bool right(std::pair<int,int> & p, int max_col)
{
    bool able = true;
    if (p.first < max_col - 1)
        p.first++;
    else
        able = false;
    
    return able;
}
