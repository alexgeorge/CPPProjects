#include <iostream>
/**
 * @brief Draw isoscelus triangle in 80x80 matrix apex at 40 
 * The logic here is print is active only when the row and column
 * conditions met. The condition is J is the row and i is the column
 * when j = maxJ/2 and i = 0 we seed the process. It progresses with
 * next row (i) and make the print true for range j = maxJ-i and j = max+j
 * This continues will we reach maxI
 */

//max rows and columns
static const int maxJ = 80;
static const int maxI = 80;

void DrawTriangle()
{
    bool bPrint = false;
    int startRow = maxJ/2;
    for (int j= 0; j<maxJ/2; ++j){
        for (int i=0; i<maxI; ++i){
            bPrint = i >= startRow-j && i <= startRow+j && j < startRow;
            if (bPrint) {
                std::cout << "*";
            }
            else{
                std::cout << " "; 
            }
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "Drawing Isoscelus Triangle \n";
    DrawTriangle();
    return 0;
}