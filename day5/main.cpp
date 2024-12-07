#include <iostream>
#include <cstdlib>
#include <fstream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>


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

    //numbers before given int are in pair.first, numbers after are in pair.second
    std::map<int, std::pair< std::vector<int>,std::vector<int> > > rules;
    while(1)
    {
        std::pair<int,int> pair_tmp;
        f_ptr >> pair_tmp.first;
        f_ptr.get();
        f_ptr >> pair_tmp.second;
        // add rules
        rules[pair_tmp.first].second.push_back(pair_tmp.second);
        rules[pair_tmp.second].first.push_back(pair_tmp.first);
        //check if data or rules
        char ch;
        f_ptr.get();
        ch = f_ptr.get();
        if (ch == '\n')
            break;
        else
            f_ptr.unget();
    }

    long long result_p1 = 0;
    long long result_p2 = 0;
    std::vector<int> seq;
    while (!f_ptr.eof())
    {
        int tmp;
        f_ptr >> tmp;
        seq.push_back(tmp);
        if (f_ptr.get() == ',')
            continue;
        bool good_order = true;
        for (int i = 0; i < seq.size(); i++)
        {
            bool found = true;
            int checked = seq[i];
            for (int j = 0; j < i; j++)
            {
                std::vector<int>::const_iterator pos = std::find(rules[checked].second.begin(), rules[checked].second.end(), seq[j]);
                if (pos < rules[checked].second.end())
                {
                    found = false;
                    break;
                }
            }
            if (found == false && i != 0)
            {
                good_order = false;
                break;
            }
            found = true;
            for (int j = i + 1; j < seq.size();j++)
            {
                std::vector<int>::const_iterator pos = std::find(rules[checked].first.begin(), rules[checked].first.end(),seq[j]);
                if (pos < rules[checked].first.end())
                {
                    found = false;
                    break;
                }
            }
            if (found == false && i < seq.size() - 1)
            {
                good_order = false;
                break;
            }
        }
        if (good_order)
            result_p1 += seq[seq.size()/2];
        else //part2
        {
            for (int i = 0; i < seq.size(); i++)
            {
                bool changed = false;
                int checked = seq[i];
                //checks pages before checked page
                for (int j = 0; j < i; j++)
                {
                    std::vector<int>::iterator pos = std::find(rules[checked].second.begin(), rules[checked].second.end(), seq[j]);
                    if (pos < rules[checked].second.end())
                    {
                        std::vector<int>::iterator seq_pos = std::find(seq.begin(), seq.end(), *pos); //find val to change in seq
                        seq[i] = *seq_pos;
                        *seq_pos = checked;
                        changed = true;
                        break;
                    }
                }
                if (changed == true)
                {
                    i = 0;
                    continue;
                }
                //checks pages after checked page
                for (int j = i + 1; j < seq.size(); j++)
                {
                    std::vector<int>::iterator pos = std::find(rules[checked].first.begin(), rules[checked].first.end(),seq[j]);
                    if (pos < rules[checked].first.end())
                    {
                        std::vector<int>::iterator seq_pos = std::find(seq.begin(), seq.end(), *pos); //find val to change in seq
                        seq[i] = *seq_pos;
                        *seq_pos = checked;
                        changed = true;
                        break;
                    }
                }
                if (changed == true)
                {
                    i = 0;
                    continue;
                }
            }
            result_p2 += seq[seq.size()/2];
        }
        seq.erase(seq.begin(),seq.end()); //clears seq
    }

    std::cout << "Result part 1: " << result_p1 << std::endl;
    std::cout << "Result part 2: " << result_p2 << std::endl;

    f_ptr.close();

    return 0;
}