#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>

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

    std::vector<int> left_l, right_l;
    while (1)
    {
        int tmp;
        f_ptr >> tmp;
        if (!f_ptr)
            break;
        left_l.push_back(tmp);
        f_ptr >> tmp;
        right_l.push_back(tmp);
    }

    std::sort(left_l.begin(), left_l.end());
    std::sort(right_l.begin(), right_l.end());

    //first part
    {
    long long total_sum = 0;
    
    std::vector<int>::iterator left_ptr = left_l.begin();
    for (int i = 0; left_ptr < left_l.end(); i++, left_ptr++)
    {
        if (left_l[i] < right_l[i])
            total_sum += right_l[i] - left_l[i];
        else
            total_sum += left_l[i] - right_l[i];
    }
    
    std::cout << "Sum of distance: " << total_sum << std::endl;
    } //end of first part

    //second part
    long long total_sum = 0;
    int cnt_l = 0; //count the same number in left list
    int cnt_r = 0; //count the same number in right list
    int val = 0;
    std::vector<int>::iterator right_ptr = right_l.begin();
    std::vector<int>::iterator left_ptr = left_l.begin();
    while ( left_ptr < left_l.end() )
    {
        val = *left_ptr;
        //count how many
        while ( left_ptr < left_l.end() && (*left_ptr) == val)
        {
            cnt_l++;
            left_ptr++;
        }
        while ( right_ptr < right_l.end() && *right_ptr < val)
            right_ptr++;

        while ( right_ptr < right_l.end() && (*right_ptr) == val )
        {
            cnt_r++;
            right_ptr++;
        }
        total_sum += val * cnt_r * cnt_l;
        cnt_l = cnt_r = 0;
    }

    std::cout << "Sum of similarity score: " << total_sum << std::endl;

    f_ptr.close();

    return 0;
}