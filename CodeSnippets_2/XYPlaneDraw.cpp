#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>

//Draw a Rob Floyd traingle
/**
 * @brief This triangle will bhave equal base and height
 * 1
 * 2 3
 * 4 5 6
 * 7 8 9 10
 * 11 12 13 14 15
 * Logic:- rows and columns are same in this triangle. So there
 * should be a line break when the rows == columns. The 
 * columns are y and rows are x. Total number of elements (numbers)
 * in this triangle will be rows^2 == columns^2. So the input 
 * can be number of rows or columns
 * @return int 
 */

void DrawRFTriangle (int x){
    auto totalElements = x*x;
    int row = 1;
    int col = 1;
    for (int y=1; y<totalElements; y++){
        printf("%d", y);     
        if (col == row){
            printf("\n");
            ++row;
            col = 0;
        }
        ++col;   
    }
}

/**
 * @brief Recursive way to draw the same Rob Floyd triangle
 * Recursive functions are fetched to the stack
 * @return void
 * The output will look same
 * DrawRow will be the recursive function 
 */

void DrawRow(int x, int maxX){
    if (x==maxX){
        return;
    }else{
        printf("%d", x);
    }
    DrawRow(++x, maxX);
}

void RecursiveRFTriangle(int maxrow){
    int x = 1;
    for (int y=1; y<maxrow+2; ++y){
        DrawRow(x, x+y);
        printf("\n");
        x = x+y;
    } 
}

/**
 * @brief Draw x in a plane of 80x80
 * Logic:
 * Draw a plane of 80x80 (X x Y) axis
 * Meaning 80 rows and 80 columns
 * mark . when 
 * @return int 
 */

int PrintPattern(int xMax, int yMax){
    bool bPrint = false;
    for (int y=0; y<=yMax; ++y){
        for (int x=0; x<=xMax; ++x){
            if (x==y || x == xMax-y) {
                bPrint = true;
            }
            else{
                bPrint = false;
            }
            if (bPrint){
                printf("x");
            }else{
                printf(" ");
            }
        }
        printf("\n");  
    }
    return 1;
}

/**
 * @brief From the given string input, say "{{{[[[((((())))))]]]]}}}"
 * check if we have a missing closing brace. All open braces
 * should have a matching closing brace, else it is failure
 * Logic:- We use a stack structure here to store each types
 * of brances and when we finish searching through the string
 * the stacks should be empty, else we have missing braces
 * @param inStr 
 * @return int 
 */

int FindMissingCloseBrace(std::string inStr){
    
    std::stack<char> mbrace[4];
    bool bValid = true;
    for (auto ch : inStr)
    {
        if (ch == '(')
        {
            mbrace[0].push(ch);
            continue;
        }
        else if (ch == ')')
        {
            if (!mbrace[0].size()){
                bValid = false;
                break;
            }
            mbrace[0].pop();
            continue;
        }
        else if (ch == '{')
        {
            mbrace[1].push(ch);
            continue;
        }
        else if (ch == '}')
        {
            if (!mbrace[1].size())
            {
                bValid = false;
                break;
            }
            mbrace[1].pop();
            continue;
        }
        else if (ch == '[')
        {
            mbrace[2].push(ch);
            continue;
        }
        else if (ch == ']')
        {
            if (!mbrace[2].size())
            {
                bValid = false;
                break;
            }
            mbrace[2].pop();
            continue;
        }
        else if (ch == '<')
        {
            mbrace[3].push(ch);
            continue;
        }
        else if (ch == '>')
        {
            if (!mbrace[3].size()){
                bValid = false;
                break;
            }
            mbrace[3].pop();
            continue;
        }                        
    }

    for (int i=0; i<4; ++i)
    {
        if (mbrace[i].size())
        {
            std::cout << "Mismatching braces found " << mbrace[i].top() << std::endl;
            bValid = false;                  
        }
    }

    if (bValid)
    {
        std::cout << "The input string has valid braces !" << std::endl;
    }
    else
    {
        std::cout << "Mismatching braces found " << std::endl;
    }
    return 1;
}

/**
 * @brief Print Circle in the screen
 * 
 * @param si 
 */

void CirclePrint(int si)
{
    int Cx = si / 2; 
    int Cy = si / 2; 
    bool bPrint = false;

    for (int x = 0; x <= si; ++x)
    {
        for (int y = 0; y <= si; ++y)
        {
            int rad2 = pow((Cx - x),2) + pow((Cy - y),2); 
            bPrint = rad2 >= pow((si / 2),2);
            if (bPrint)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void menu(std::vector<std::string> menuItems){
    std::cout << "Make selection [1-" << menuItems.size() << "] or -1 to quit!" << std::endl;
    int idx = 0;
    for (auto item : menuItems){
            ++idx;
            std::cout << "[" << idx <<"] " << item << std::endl; 
    }
}

int XYPmain(){

    std::vector<std::string> strMenuItems;
    strMenuItems.insert(strMenuItems.end(), {"Draw Rob Floyd Triangle (RFT)", 
    "Recursive RFTriangle", "Pattern print X", "Find Missing Brace", "Circle Print"});

    auto selection = 0; 
    bool bQuit = false;

    while(!bQuit){
        menu(strMenuItems);
        std::cin >> selection;
        switch(selection){
            case(1):
                DrawRFTriangle(4);
                break;
            case(2):
                RecursiveRFTriangle(4);
                break;
            case(3):    
                PrintPattern(10, 10);
                break;
            case(4):
                FindMissingCloseBrace("{{{{(((([[[]]]))))}}}}()()()()()()}}}");
                break;
            case(5):
                CirclePrint(20);
                break;
            case(-1):
                bQuit = true;
                break;
            default:
                break;
            printf("Completed\n");
        }
    }

    return 1;
}
