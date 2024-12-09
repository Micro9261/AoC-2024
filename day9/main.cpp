#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <list>
#include <utility>
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

    std::vector<std::pair<unsigned int, int> > block_seq;
    std::vector<int> free_sp_seq;
    std::list<std::pair<int, int> > part2_buff;
    char ch;
    unsigned long iter = 0;
    unsigned int id = 0;
    unsigned long pos_to_check = 0;
    //unsigned long free_pos = 0;
    while (!f_ptr.eof())
    {
        f_ptr.get(ch);
        ch -= 0x30; //ASCII to intiger
        if (iter % 2 == 0)
        {
            std::pair tmp(id, ch);
            block_seq.push_back(tmp);
            part2_buff.push_back(tmp);
            pos_to_check += ch;
            id++;
        }
        else
        {
            free_sp_seq.push_back(ch);
            part2_buff.push_back(std::pair(-1,ch));
        }
        iter++;
    }

    

    std::vector<std::pair<unsigned int, int> > good_seq;
    unsigned int pos = 0;
    unsigned int free_pos = 0;
    int vec_sel = 0;
    unsigned int block_iter = 0;
    unsigned int b_end_iter = block_seq.size() - 1;
    while (pos  < pos_to_check)
    {
        if (vec_sel == 0)
        {
            int pos_write;
            if (block_seq[block_iter].second + pos > pos_to_check)
                pos_write = pos_to_check - pos;
            else
                pos_write = block_seq[block_iter].second;

            good_seq.push_back( std::pair(block_seq[block_iter].first,pos_write) );
            pos += pos_write;
            vec_sel++;
        }
        else if (vec_sel == 1)
        {
            if (free_pos == 0)
                free_pos = free_sp_seq[block_iter];
            if (free_pos + pos > pos_to_check)
                free_pos = pos_to_check - pos;
            if (free_pos < block_seq[b_end_iter].second && free_pos > 0) //less free space
            {
                block_seq[b_end_iter].second -= free_pos;
                good_seq.push_back( std::pair(block_seq[b_end_iter].first,free_pos) );
                pos += free_pos;
                free_pos = 0;

            }
            else if (free_pos >= block_seq[b_end_iter].second) // more space or equal
            {
                good_seq.push_back(block_seq[b_end_iter]);
                free_pos -= block_seq[b_end_iter].second;
                pos += block_seq[b_end_iter--].second;
            }

            if (free_pos == 0)
            {
                block_iter++;
                vec_sel--;
            }
        }
    }


    //checks checksum
    unsigned long long result_p1 =0 ;
    iter = 0;
    pos = 0;
    id = 0;
    for (unsigned int i = 0; i < pos_to_check; i++)
    {
        if (pos == 0)
        {
            pos = good_seq[iter].second;
            id = good_seq[iter].first;
            iter++;
        }
        result_p1 += id * i;
        pos--;
    }

    //part2
    std::vector<int> moved_files;
    std::list<std::pair<int,int> >::iterator i = part2_buff.end();
    for (i--; i !=  part2_buff.begin(); i--)
    {
        if (i->first != -1)
        {
            bool check = true;
            for (int x : moved_files)
            {
                if (i->first == x)
                {
                    check = false;
                    break;
                }
            }
            if (check == false)
                continue;
            moved_files.push_back(i->first);

            for (std::list<std::pair<int,int> >::iterator x = part2_buff.begin(); x != i ; x++)
            {
                if (x->first == -1 && x->second == i->second)
                {
                    std::pair swap_tmp = *x;
                    *x = *i;
                    *i = swap_tmp;
                    break;
                }
                else if (x->first == -1 && x->second > i->second)
                {
                    std::pair<int,int> tmp(-1,x->second - i->second );
                    x->second = i->second;
                    std::pair swap_tmp = *x;
                    *x = *i;
                    *i = swap_tmp;
                    x++;
                    part2_buff.emplace(x, tmp);
                    break;
                }
            }
        }
    }

    //checks part2 checksum
    unsigned long long result_p2 =0 ;
    iter = 0;
    pos = 0;
    int id_p2 = 0;
    std::list<std::pair<int,int> >::iterator x = part2_buff.begin();
    while ( x != part2_buff.end())
    {
        if (pos == 0)
        {
            do
            {
                pos = x->second;
                id_p2 = x->first;
                x++;
            } while (pos == 0);
        }
        if (id_p2 != -1)
            result_p2 += id_p2 * iter;
        pos--;
        iter++;
    }


    std::cout << "Result part1: " << result_p1 << std::endl;
    std::cout << "Result part2: " << result_p2 << std::endl;

    f_ptr.close();

    return 0;
}