#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

//211 < x << 217 //-215

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
    std::fstream buff("tmpFile.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (!buff.good())
    {
        std::cerr << "Error creating tmp file!" << std::endl;
        f_ptr.close();
        std::exit(EXIT_FAILURE);
    }
    std::fstream buff2("tmpFile2.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (!buff.good())
    {
        std::cerr << "Error creating tmp2 file!" << std::endl;
        f_ptr.close();
        std::exit(EXIT_FAILURE);
    }
    
    int ch;
    while ( (ch=f_ptr.get()) != EOF)
    {
        buff.put(ch);
        buff2.put(ch);
    }    

    f_ptr.close();

    //gathering informations
    std::vector<char> types;
    std::map<char, std::vector<std::pair<int,int> > > points;
    buff.seekp(0, buff.beg);
    buff.seekg(0, buff.beg);
    int col_len = 1;
    while ( (ch = buff.get()) != '\n')
        col_len++;
    buff.seekg(0, buff.end);
    int rows = buff.tellg() / col_len;
    buff.seekg(0, buff.beg);
    int nodes = 0;
    while ((ch = buff.get()) != EOF)
    {
        ;
        if (ch != '.' && ch !='\n' && std::find(types.begin(),types.end(), ch) >= types.end())
            types.push_back((char)ch);
        if (ch != '.' && ch !='\n')
        {
            int len = buff.tellg();
            len += 2;
            std::pair tmp((len % col_len) - 1, (len / col_len) - 1); //(x,y) == (first,second)
            points[(char)ch].push_back(tmp);
            nodes++;
        }
    }
    buff.clear();
    //std::cout << col_len << ":" << rows << std::endl;

    //data ready to analyze
    std::vector<std::pair<int,int> > checked_uniq;
    unsigned long long result_p1 = 0;
    for (char ch : types)
    {
        for (std::pair x : points[ch])
        {
            for (std::pair y : points[ch])
            {
                if (x != y)
                {
                    int dist_x = x.first - y.first;
                    int dist_y = x.second - y.second;
                    int point_x = x.first + dist_x;
                    int point_y = x.second + dist_y;
                    if (point_x < 0 || point_x > col_len - 1)
                        continue;
                    if (point_y < 0 || point_y > rows - 1)
                        continue;
                        
                    buff.seekg(point_x + point_y*(col_len+1), buff.beg);
                    int read_ch = buff.get();
                    if (read_ch == '.')
                    {
                        buff.seekp(point_x + point_y*(col_len + 1), buff.beg);
                        buff.put('#');
                        result_p1++;
                    }
                    else if (read_ch != ch && read_ch != '#' && read_ch != '\n')
                    {
                        bool found = false;
                        for (std::pair z : checked_uniq)
                        {
                            if (z.first == point_x && z.second == point_y)
                            {
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                        {
                            checked_uniq.push_back({point_x,point_y});
                            result_p1++;
                        }
                    }
                }
            }
        }
        
    }
    //part2
    buff2.seekp(0, buff.beg);
    buff2.seekg(0, buff.beg);
    unsigned long long result_p2 = 0;
    for (char ch : types)
    {
        for (std::pair x : points[ch])
        {
            for (std::pair y : points[ch])
            {
                if ( x != y)
                {
                    bool end = false;
                    int dist_x = x.first - y.first;
                    int dist_y = x.second - y.second;
                    int point_x = x.first + dist_x;
                    int point_y = x.second + dist_y;
                    while (!end)
                    {
                        if ( (point_x < 0 || point_x > col_len - 1) || (point_y < 0 || point_y > rows - 1) )
                        {
                            end = true;
                            break;
                        }
                        buff2.seekg(point_x + point_y*(col_len+1), buff2.beg);
                        int read_ch = buff2.get();
                        if (read_ch == '.')
                        {
                            buff2.seekp(point_x + point_y*(col_len + 1), buff2.beg);
                            buff2.put('#');
                            result_p2++;
                        }
                        point_x += dist_x;
                        point_y += dist_y;
                    }
                }
            }
        }
    }

    std::cout << "Result part1: " << result_p1 << std::endl;
    std::cout << "Result part2: " << result_p2  + nodes<< std::endl;

    buff.close();
    buff2.close();
    std::remove("tmpFile.txt");
    std::remove("tmpFile2.txt");

    return 0;
}