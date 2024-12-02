#include <iostream>
#include <algorithm>
#include <vector>
//answer 373 with Dumpener

int main()
{
    int safe_cnt = 0;
    int safe_dmp_cnt = 0;
    int mistakes = 0;
    int ch;
    bool safe = true;
    while(1)
    {
        mistakes = 0;
        safe = true;
        std::vector<int> tmp_buff;
        int tmp;
        do
        {
            std::cin >> tmp;
            tmp_buff.push_back(tmp);
        }while ( (ch = std::cin.get()) != '\n' && ch != EOF);
    
        std::vector<int> test[3] = {tmp_buff , tmp_buff, tmp_buff};
        while (mistakes < 2)
        {
            
            int dir;
            int dir_now;
            safe = true;
            for (int i = 0; i < test[0].size() - 1; i++)
            {
                int last = test[0][i];
                int now = test[0][i+1];
                if (i == 0)
                {
                    dir = now - last ? (now - last > 0) ? 1 : -1 : 0; // 1 - rise, -1 - fall, 0 - the same value
                    dir_now = dir;
                }
                else
                    dir_now = now - last ? (now - last > 0) ? 1 : -1 : 0; // 1 - rise, -1 - fall, 0 - the same value
                if ( (dir < 0 && last - now >= 4) || (dir > 0 && now - last >= 4) || (0 == dir_now) || (dir_now != dir))
                {
                    test[0].erase(test[0].begin() + i);
                    test[1].erase(test[1].begin() + i + 1);
                    if (i >= 1)
                    test[2].erase(test[2].begin() + i - 1);
                    mistakes++;
                    safe = false;
                    break;
                }

            }
            if (!safe)
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < test[i].size() - 1; j++)
                    {
                        int last = test[i][j];
                        int now = test[i][j+1];
                        if (j == 0)
                        {
                            dir = now - last ? (now - last > 0) ? 1 : -1 : 0; // 1 - rise, -1 - fall, 0 - the same value
                            dir_now = dir;
                        }
                        else
                            dir_now = now - last ? (now - last > 0) ? 1 : -1 : 0; // 1 - rise, -1 - fall, 0 - the same value
                         if ( (dir < 0 && last - now >= 4) || (dir > 0 && now - last >= 4) || (0 == dir_now) || (dir_now != dir))
                        {
                            mistakes++;
                            break;
                        } 
                    }
                    if (mistakes == i + 1)
                    {
                        safe = true;
                        mistakes = 1;
                        break;
                    }
                }
            if(safe)
                 break;
        }

        if (mistakes == 0)
        {
            safe_cnt++;
            safe_dmp_cnt++;
            //std::cout << line_cnt << " safe" << std::endl;
        }
        else if (mistakes < 2)
        {
            //std::cout << line_cnt << " safe with dumpener" << std::endl;
            safe_dmp_cnt++;
        }
        if (std::cin.eof())
            break;
    }

    std::cout << "Safe reports without Dampener: " << safe_cnt << std::endl;
    std::cout << "Safe reports with Dampener: " << safe_dmp_cnt << std::endl;

    return 0;
}