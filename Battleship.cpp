//
//  Battleship.cpp
//
//
//  Mobolurin Chibudom Edun,
//  
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Ship
{
public:
    string type;
    int size;
    int hits;

    Ship() {}
    Ship(string type, int size)
    {
        this->type = type;
        this->size = size;
        hits = 0;
    }

    bool isSunk()
    {
        if (hits == size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int getSize()
    {
        return size;
    }

    string getType()
    {
        return type;
    }

    void hit()
    {
        if (hits < size)
        {
            hits += 1;
        }
    }
};

class BattleshipSquare
{
public:
    Ship* ship;
    bool isFired;

    BattleshipSquare()
    {
        ship = NULL;
        isFired = false;
    }

    void reset()
    {
        ship = NULL;
        isFired = false;
    }

    void addShip(Ship* ship)
    {
        this->ship = ship;
    }

    char getStatus()
    {
        if (!ship)
        {
            if (isFired)
            {
                return 'M';
            }
            else
            {
                return ' ';
            }
        }
        else
        {
            if (isFired)
            {
                return 'H';
            }
            else
            {
                return 'S';
            }
        }
    }

    void fire()
    {
        char status = getStatus();
        if (status == 'S' && !isFired)
        {
            ship->hit();
            isFired = true;
        }
    }
};

class Point
{
public:
    char x;
    char y;
    Point() {}
    Point(char x, char y)
    {
        this->x = x;
        this->y = y;
    }
};

class Orientation
{
public:
    Point p;
    char d;
    Orientation() {}
    Orientation(Point p, char d)
    {
        this->p = p;
        this->d = d;
    }
};

class Board
{
public:
    BattleshipSquare squares[8][8];

    Board()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                squares[i][j] = BattleshipSquare();
            }
        }
    }

    void displayBoard()
    {
        cout << string(3, ' ') << "A--B--C--D--E--F--G--H " << endl;
        cout << string(26, '-') << endl;
        cout << "1| ";
        for (int i = 0; i < 8; i++)
            cout << squares[0][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << "2| ";
        for (int i = 0; i < 8; i++)
            cout << squares[1][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << "3| ";
        for (int i = 0; i < 8; i++)
            cout << squares[2][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << "4| ";
        for (int i = 0; i < 8; i++)
            cout << squares[3][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << "5| ";
        for (int i = 0; i < 8; i++)
            cout << squares[4][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << "6| ";
        for (int i = 0; i < 8; i++)
            cout << squares[5][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << "7| ";
        for (int i = 0; i < 8; i++)
            cout << squares[6][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << "8| ";
        for (int i = 0; i < 8; i++)
            cout << squares[7][i].getStatus() << string(2, ' ');
        cout << endl;
        cout << string(26, '-') << endl;
    }

    char getSquareState(Point p)
    {
        return squares[p.y - 49][p.x - 65].getStatus();
    }

    bool placeShip(Orientation o, Ship* ship)
    {
        Point startLoc = o.p;
        Point endLoc = o.p;
        int arrX = startLoc.x - 65;
        int arrY = startLoc.y - 49;
        int tmp = 0;

        //Check for spillage
        if (o.d == 'N' && ((int)startLoc.y - ship->size + 1) < 49)
        {
            cout << "Invalid entry! Please try again" << endl;
            return false;
        }
        else if (o.d == 'S' && ((int)startLoc.y + ship->size - 1) > 56)
        {
            cout << "Invalid entry! Please try again" << endl;
            return false;
        }
        else if (o.d == 'E' && ((int)startLoc.x + ship->size - 1) > 72)
        {
            cout << "Invalid entry! Please try again" << endl;
            return false;
        }
        else if (o.d == 'W' && ((int)startLoc.x - ship->size + 1) < 65)
        {
            cout << "Invalid entry! Please try again" << endl;
            return false;
        }

        //Check for overlap
        if (o.d == 'N')
        {
            for (int i = arrY - ship->size + 1; i <= arrY; i++)
            {
                if (squares[i][arrX].getStatus() == 'S')
                {
                    cout << "Invalid entry! Please try again" << endl;
                    return false;
                }
            }
        }
        else if (o.d == 'S')
        {
            for (int i = arrY; i <= arrY + ship->size - 1; i++)
            {
                if (squares[i][arrX].getStatus() == 'S')
                {
                    cout << "Invalid entry! Please try again" << endl;
                    return false;
                }
            }
        }
        else if (o.d == 'E')
        {
            for (int i = arrX; i <= arrX + ship->size - 1; i++)
            {
                if (squares[arrY][i].getStatus() == 'S')
                {
                    cout << "Invalid entry! Please try again" << endl;
                    return false;
                }
            }
        }
        else
        {
            for (int i = arrX - ship->size + 1; i <= arrX; i++)
            {
                if (squares[arrY][i].getStatus() == 'S')
                {
                    cout << "Invalid entry! Please try agian" << endl;
                    return false;
                }
            }
        }

        // add ships if not returned
        if (o.d == 'N')
        {
            endLoc.y = (char)startLoc.y - ship->size + 1;
            tmp = arrY;
            arrY = endLoc.y - 49;
            for (int i = arrY; i <= tmp; i++)
                squares[i][arrX].addShip(ship);
        }
        else if (o.d == 'S')
        {
            endLoc.y = startLoc.y + ship->size - 1;
            tmp = arrY;
            arrY = endLoc.y - 49;
            for (int i = tmp; i <= arrY; i++)
                squares[i][arrX].addShip(ship);
        }
        else if (o.d == 'E')
        {
            endLoc.x = startLoc.x + ship->size - 1;
            tmp = arrX;
            arrX = endLoc.x - 65;
            for (int i = tmp; i <= arrX; i++)
                squares[arrY][i].addShip(ship);
        }
        else
        {
            endLoc.x = startLoc.x - ship->size + 1;
            tmp = arrX;
            arrX = endLoc.x - 65;
            for (int i = arrX; i <= tmp; i++)
                squares[arrY][i].addShip(ship);
        }
        return true;
    }

    bool fireAtSquare(Point& p)
    {
        bool isValid = false;

        //check if x coordinate is valid or not
        while (!isValid)
        {
            cout << "Enter the x coordinate (A-H): ";
            cin >> p.x;
            if (p.x >= 65 && p.x <= 72)
                isValid = true;
            if (!isValid)
                cout << "Invalid entry! Please try again." << endl;
        }

        //similarly, check if y coordinate is valid or not
        isValid = false;
        while (!isValid)
        {
            cout << "Enter the y coordinate (1-8): ";
            cin >> p.y;
            if (p.y >= 49 && p.y <= 56)
                isValid = true;
            if (!isValid)
                cout << "Invalid entry! Please try again." << endl;
        }

        //check for hit or miss
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (squares[p.y - 49][p.x - 65].getStatus() == 'S')
                {
                    cout << "It's a hit!" << endl;
                    squares[p.y - 49][p.x - 65].fire();
                    return true;
                }
                else
                {
                    cout << "It's a miss!" << endl;
                    squares[p.y - 49][p.x - 65].fire();
                    return false;
                }
            }
        }
    }

    void resetBoard()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                squares[i][j] = BattleshipSquare();
            }
        }
    }

    // void updateBoard(Point p, bool isHit) // IS THIS NECESSARY?
    // {
    //     if (isHit)
    //     {
    //         squares[p.y - 49][p.x - 65].isFired = true;
    //     }
    //     else
    //     {
    //         squares[p.y - 49][p.x - 65] = 'M';
    //     }
    // }
};

class Player
{
public:
    string name;
    Board shipBoard;
    Board fireBoard;
    Ship* ships[5] = { new Ship, new Ship, new Ship, new Ship, new Ship };

    Player()
    {
        ships[0]->type = "Destroyer";
        ships[1]->type = "Submarine";
        ships[2]->type = "Cruiser";
        ships[3]->type = "Battleship";
        ships[4]->type = "Carrier";

        ships[0]->size = 2;
        ships[1]->size = 3;
        ships[2]->size = 3;
        ships[3]->size = 4;
        ships[4]->size = 5;
    }

    void displayBoard(char type)
    {
        if (type == 's')
        {
            shipBoard.displayBoard();
        }
        else
        {
            fireBoard.displayBoard();
        }
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getName(int count)
    {
        cout << "** Enter player " << count << " name: ";
        getline(cin, name);
        return name;
    }

    bool fire(Point p)
    {
        bool isHit = shipBoard.fireAtSquare(p);
        return isHit;
    }

    Ship* getShip(int index)
    {
        return ships[index];
    }

    bool placeShip(Orientation o, int index)
    {
        Ship* shipPlace = getShip(index);
        bool isValid = shipBoard.placeShip(o, shipPlace);
        return isValid;
    }

    bool checkLost()
    {
        for (int i = 0; i < 5; i++)
        {
            if (!ships[i]->isSunk())
            {
                return false;
            }
        }
        return true;
    }

    // void updateBoard(Point p, bool isHit) 
    // {
    //     fireBoard.updateBoard(p, isHit);
    // }
};

bool mainMenu(bool& exit);
void clearScreen();
void addShips(Player& playerX);
void enterToContinue();

int main()
{
    Player player1;
    Player player2;
    Player* pointer1 = &player1;
    Player* pointer2 = &player2;
    Point p;
    int turn = 1;
    bool exit = false;
    bool isHit = false;
    bool isWin = false;
    bool option = mainMenu(exit);
    if (option)
        return 0;
    else
    {
        string name = player1.getName(1);
        player1.setName(name);
        name = player2.getName(2);
        player2.setName(name);
        addShips(player1);
        addShips(player2);
        while (!isWin)
        {
            cout << "Turn: " << turn << endl;
            cout << pointer1->name << " enter coordinates to fire" << endl;
            pointer1->displayBoard('f');
            isHit = pointer2->fire(p);
            enterToContinue();
            isWin = pointer1->checkLost();
            if (isWin)
                break;
            turn++;
            swap(*pointer1, *pointer2);
        }
        cout << pointer1->name << " you won!" << endl;
        pointer1->displayBoard('f');
    }
    return 0;
}

void clearScreen()
{
    cout << "\x1B[2J\x1B[H";
}

bool mainMenu(bool& exit)
{
    string csc;
    string menuSelection = "0";
    //Option given to clear console or not
    cout << "Would you like to clear the console screen (y/n)?: ";
    getline(cin, csc);
    if (csc == "y" || csc == "Y")
        clearScreen();

    //Print loading screen and options
    cout << string(30, '-') << endl;
    cout << string(8, ' ') << "Battleships" << endl;
    cout << string(8, ' ') << "Main Menu" << endl;
    cout << string(30, '-') << endl;
    cout << string(8, ' ') << "1. Start Game" << endl;
    cout << string(8, ' ') << "2. Exit Game" << endl
        << '\n';

    // Obtain option to either start or exit game from the user
    while (menuSelection != "1" && menuSelection != "2")
    {
        cout << "Enter menu selection (1-2): ";
        getline(cin, menuSelection);
        if (menuSelection != "1" && menuSelection != "2")
            cout << "Invalid entry! Plese try again." << endl;
        else if (menuSelection == "2")
        {
            cout << "Goodbye!" << endl;
            return true;
        }
    }
    return false;
}

void addShips(Player& playerX)
{
    char dArray[4] = { 'N', 'S', 'E', 'W' };
    Orientation initShip;
    int i = 0;
    bool isValid;
    bool shipValid = false;

    // Display ship details
    cout << string(30, '-') << endl;
    cout << string(11, ' ') << "Add Ship" << endl;
    cout << string(30, '-') << endl;
    cout << string(8, ' ') << "No Name" << string(6, ' ') << "Squares" << endl;
    cout << string(8, ' ') << '1' << string(2, ' ') << "Carrier" << string(6, ' ') << '5' << endl;
    cout << string(8, ' ') << '1' << string(2, ' ') << "Battleship" << string(3, ' ') << '4' << endl;
    cout << string(8, ' ') << '1' << string(2, ' ') << "Cruiser" << string(6, ' ') << '3' << endl;
    cout << string(8, ' ') << '1' << string(2, ' ') << "Submarine" << string(4, ' ') << '3' << endl;
    cout << string(8, ' ') << '1' << string(2, ' ') << "Destroyer" << string(4, ' ') << '2' << endl;
    cout << string(30, '-') << endl;

    while (i < 5)
    {
        while (!shipValid)
        {
            // Add ship
            cout << playerX.name << " add a " << playerX.ships[i]->type << " of size: " << playerX.ships[i]->size << endl;
            //Check if ship x coordinate is valid
            isValid = false;
            while (!isValid)
            {
                cout << "Enter the x coordinate (A-H): ";
                cin >> initShip.p.x;
                if (initShip.p.x >= 65 && initShip.p.x <= 72)
                    isValid = true;
                if (!isValid)
                    cout << "Invalid entry! Please try again." << endl;
            }
            //check if ship y coordinate is valid
            isValid = false;
            while (!isValid)
            {
                cout << "Enter the y coordinate (1-8): ";
                cin >> initShip.p.y;
                if (initShip.p.y >= 49 && initShip.p.y <= 56)
                    isValid = true;
                if (!isValid)
                    cout << "Invalid entry! Please try again." << endl;
            }
            //check if ship direction is valid
            isValid = false;
            while (!isValid)
            {
                cout << "Enter the direction (N/E/S/W): ";
                cin >> initShip.d;
                for (int i = 0; i < 4; i++)
                {
                    if (initShip.d == dArray[i])
                        isValid = true;
                }
                if (!isValid)
                    cout << "Invalid entry! Please try again." << endl;
            }
            shipValid = playerX.placeShip(initShip, i);
            playerX.displayBoard('s');
        }
        if (i < 5)
        {
            shipValid = false;
            i++;
        }
    }
    cout << "All ships are added!" << endl;
    enterToContinue();
}

void enterToContinue()
{
    cout << "Press enter to continue! ";
    cin.clear();
    cin.ignore(50, '\n');
    cin.get();
}
