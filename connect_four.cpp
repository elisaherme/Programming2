#include <iostream>

using namespace std;

void Xenters(char a[6][7]);
void Oenters(char b[6][7]);
void show(char c[6][7]);
int win(char w[6][7]);

int main()
{
    int counter = 0;
    char board[6][7];
    
    //Initializing matrix with empty spaces
    for(int x=0; x<6; x++)
    {
        for(int y=0; y<7; y++)
        {
            board[x][y] = ' ';
        }
    }
    
    cout << "Connect Four game" << endl;
    
    show(board);
    
    cout << endl;
    
    //counter variable corresponds to the returned value of 'a' from the win function, if it returns a value of 5 or 43, then the loop ends and the game is over
    while (counter < 5)
    {
        Xenters(board);
        cout << endl;
        show(board);
        cout << endl;
        counter = win(board);
        if(counter == 5)
        {
            break;
        }
        Oenters(board);
        cout << endl;
        show(board);
        cout << endl;
        counter = win(board);
    }
    
    return 0;
}


//Function for player X entering a column
void Xenters(char a[6][7])
{
    int n = 0, m = 5;
    int s = 0;
    
    cout << "Player X, enter a column: ";
    cin >> n;
    
    //Checks if the column entered is a valid number between 1 and 7
    while ((n < 1) || (n > 7))
    {
        cout << "That column cannot be entered" << endl;
        cout << "Player X, enter a column between 1 and 7: ";
        cin >> n;
        
    }
    n = n - 1;
    //Enters X in the right place into the matrix
    while (s == 0)
    {
        if (m >= 0)
        {
            if ((a[m][n] == 'X') || (a[m][n] == 'O'))
            {
                //If that space of the matrix is not empty, it checks the next row
                m = m - 1;
                s = 0;
            }
            else
            {
                a[m][n] = 'X';
                s = 1;
            }
        }
        
        //If the column entered is full, it asks the player to enter another column
        else
        {
            cout << "That column is full, player X enter another column: ";
            cin >> n;
            while ((n < 1) || (n > 7))
            {
                cout << "That column cannot be entered" << endl;
                cout << "Player X, enter a column between 1 and 7: ";
                cin >> n;
                
            }
            s = 0;
            m = 5;
            n = n - 1;
        }
    }
}


//Function for player O entering a column
void Oenters(char b[6][7])
{
    int n = 0, m = 5;
    int s = 0;
    
    cout << "Player O, enter a column: ";
    cin >> n;
    
    //Checks if the column entered is a valid number between 1 and 7
    while ((n < 1) || (n > 7))
    {
        cout << "That column cannot be entered" << endl;
        cout << "Player O, enter a column between 1 and 7: ";
        cin >> n;
        
    }
    n = n - 1;
    //Enters O in the right place into the matrix
    while (s == 0)
    {
        if (m >= 0)
        {
            if ((b[m][n] == 'X') || (b[m][n] == 'O'))
            {
                //If that space of the matrix is not empty, it checks the next row
                m = m - 1;
                s = 0;
            }
            else
            {
                b[m][n] = 'O';
                s = 1;
            }
        }
        
        //If the column entered is full, it asks the player to enter another column
        else
        {
            cout << "That column is full, player O enter another column: ";
            cin >> n;
            while ((n < 1) || (n > 7))
            {
                cout << "That column cannot be entered" << endl;
                cout << "Player O, enter a column between 1 and 7: ";
                cin >> n;
                
            }
            s = 0;
            m = 5;
            n = n - 1;
        }
    }
}


//Function for showing the matrix within the grid
void show(char c[6][7])
{
    cout << "   1   2   3   4   5   6   7 " << endl;
    for(int x=0; x<6; x++)
    {
        for(int y=0; y<7; y++)
        {
            cout << " | " << c[x][y];
        }
        cout << " |" << endl;
        cout << " |---|---|---|---|---|---|---|" << endl;
    }
}


//Function for checking if someone has won the game or if the game is over
int win(char w[6][7])
{
    int a = 0, p = 0;
    
    for(int i = 5; i >= 0; i--)
    {
        for(int j = 0; j < 7; j++)
        {
            //Checks horizontal X
            while ((a < 5) && (p == 0))
            {
                if(w[i][j + a] == 'X')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player X wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    j = j + 1;
                    if (j == 7)
                    {
                        i = i -1;
                        j = 0;
                        if (i == -1)
                        {
                            i = 5;
                            j = 0;
                            p = 1;
                        }
                    }
                    a = 0;
                }
            }
            
            //Checks horizontal O
            while ((a < 5) && (p == 1))
            {
                if(w[i][j + a] == 'O')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player O wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    j = j + 1;
                    if (j == 7)
                    {
                        i = i - 1;
                        j = 0;
                        if (i == -1)
                        {
                            i = 5;
                            j = 0;
                            p = 2;
                        }
                    }
                    a = 0;
                }
            }
            
            //Checks vertical X
            while ((a < 5) && (p == 2))
            {
                if(w[i - a][j] == 'X')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player X wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    i = i - 1;
                    if (i == -1)
                    {
                        j = j + 1;
                        i = 5;
                        if (j == 7)
                        {
                            i = 5;
                            j = 0;
                            p = 3;
                        }
                    }
                    a = 0;
                }
            }
            
            //Checks vertical O
            while ((a < 5) && (p == 3))
            {
                if(w[i - a][j] == 'O')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player O wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    i = i - 1;
                    if (i == -1)
                    {
                        j = j + 1;
                        i = 5;
                        if (j == 7)
                        {
                            i = 5;
                            j = 0;
                            p = 4;
                        }
                    }
                    a = 0;
                }
            }
            
            // Checks diagonal up X
            while ((a < 5) && (p == 4))
            {
                if(w[i - a][j + a] == 'X')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player X wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    j = j + 1;
                    if (j == 7)
                    {
                        i = i -1;
                        j = 0;
                        if (i == -1)
                        {
                            i = 5;
                            j = 0;
                            p = 5;
                        }
                    }
                    a = 0;
                }
            }
            
            // Checks diagonal up O
            while ((a < 5) && (p == 5))
            {
                if(w[i - a][j + a] == 'O')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player O wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    j = j + 1;
                    if (j == 7)
                    {
                        i = i -1;
                        j = 0;
                        if (i == -1)
                        {
                            i = 5;
                            j = 0;
                            p = 6;
                        }
                    }
                    a = 0;
                }
            }
        }
    }
    p = 6;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            // Checks diagonal down X
            while ((a < 5) && (p == 6))
            {
                if(w[i + a][j + a] == 'X')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player X wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    j = j + 1;
                    if (j == 7)
                    {
                        i = i + 1;
                        j = 0;
                        if (i == 6)
                        {
                            i = 5;
                            j = 0;
                            p = 7;
                        }
                    }
                    a = 0;
                }
            }
            
            // Checks diagonal down O
            while ((a < 5) && (p == 7))
            {
                if(w[i + a][j + a] == 'O')
                {
                    a = a + 1;
                    if(a == 4)
                    {
                        cout << "Player O wins!" << endl;
                        a = 5;
                        return a;
                    }
                }
                else
                {
                    j = j + 1;
                    if (j == 7)
                    {
                        i = i -1;
                        j = 0;
                        if (i == -1)
                        {
                            i = 5;
                            j = 0;
                            p = 8;
                        }
                    }
                    a = 0;
                }
            }
        }
    }
    
    //Checks if the matrix is completely full with X and O and therefore the game is over and no one wins
    for(int i = 5; i >= 0; i--)
    {
        for(int j = 0; j < 7; j++)
        {
            //There are 42 spaces in the matrix, so 'a' must be less than 43
            while ((a < 43) && (p == 8))
            {
                if((w[i][j] == 'X') || (w[i][j] == 'O'))
                {
                    a = a + 1;
                    j = j + 1;
                    if (j == 7)
                    {
                        i = i - 1;
                        j = 0;
                        if (i == -1)
                        {
                            i = 5;
                            j = 0;
                            p = 9;
                        }
                    }
                    
                    if(a == 42)
                    {
                        cout << "Draw. Game over" << endl;
                        a = 43;
                        return a;
                    }
                }
                else
                {
                    a = 0;
                    p = 9;
                }
            }
        }
    }
    cout << "Continue playing" << endl;
    return a;
}
