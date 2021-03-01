#include <iostream>
#include "cell.h"
#include "board.h"
#include "specialEffects.h"
#include "blockList.h"
#include "window.h"
#include <string.h>
#include <sstream>
using namespace std;


void drawRow(const string &row, int column, Xwindow *xw, const string &prevrow) {
    for (int i = 0; i < 27; ++i) {
	if ((prevrow == "") || (prevrow[i] != row[i]))
        {
	if (row[i] == 'L') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Orange);
        }
        else if (row[i] == 'J') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Blue);
        }
        else if (row[i] == 'I') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Cyan);
        }
        else if (row[i] == 'O') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Yellow);
        }
        else if (row[i] == 'S') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Green);
        }
        else if (row[i] == 'Z') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Red);
        }
        else if (row[i] == 'T') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Magenta);
        }
        else if (row[i] == '*') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Brown);
        }
        else if (row[i] == '-') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->White);
        }
        else if (row[i] == '?') {
            xw->fillRectangle (i*25+21, column+1, 24, 24, xw->Black);
        }
	}
   }
}

void  drawBoard (const string &board, Xwindow *xw, string &prevboard) {
    int counter = 0;
    string row = "";
    string prevrow = "";
    for (int j = 0; j < 18; ++j) {
        while (board[counter] != '\n') {
            row += board[counter];
            if (prevboard != "") {
                prevrow += prevboard[counter];
            }
	    ++counter;
        } 
    if (row != prevrow) {
    	drawRow (row, j*25+20, xw, prevrow);
    } //check for changes
    row = "";
    prevrow = "";
    ++counter;
    xw->flush();
    }
}

string printBoard (Board *b1, Board *b2, bool graphics, Xwindow *xw, string &prevboard) { //this can be sent to graphics
    string retval = "";
    for (int i = 0; i < 18; ++i) {
        retval += b1->printrow(i) + "    " + b2->printrow(i) + "\n";
    }
    if (graphics) {
        drawBoard(retval, xw, prevboard);
    }
    prevboard = retval;
    return retval;
}

void graphicsNext (int x, string next, Xwindow *xw) {
    if (next == "O") {
       xw->fillRectangle (x, 545, 50, 50, xw->Yellow); 
    }
    else if (next == "L") {
       xw->fillRectangle(x+50, 545, 25, 25, xw->Orange); 
       xw->fillRectangle(x, 545+25, 75, 25, xw->Orange); 
    }
    else if (next == "J") {
       xw->fillRectangle (x, 545, 25, 25, xw->Blue); 
       xw->fillRectangle (x, 545+25, 75, 25, xw->Blue); 
    }
    else if (next == "I") {
       xw->fillRectangle (x, 545, 100, 25, xw->Cyan); 
    }
    else if (next == "T") {
      xw->fillRectangle (x, 545, 75, 25, xw->Magenta); 
      xw->fillRectangle (x+25, 545+25, 25, 25, xw->Magenta); 
    }
    else if (next == "Z") {
      xw->fillRectangle (x, 545, 50, 25, xw->Red); 
      xw->fillRectangle (x+25, 545+25, 50, 25, xw->Red); 
    }
    else if (next == "S") {
      xw->fillRectangle (x + 25, 545, 50, 25, xw->Green); 
      xw->fillRectangle (x, 545 + 25, 50, 25, xw->Green); 
   }
}

void printGame (Board *b1, Board *b2, bool graphics, Xwindow* xw, string &prevboard) {
    if (graphics) {
	xw->fillRectangle(0, 500, 1000, 1000);
        xw->drawString (20, 510, "score: ", xw->White);
        xw->drawString (275, 510, to_string (b1->getScore()), xw->Red);
        xw->drawString (395, 510, "score: ", xw->White);
        xw->drawString (650, 510, to_string (b2->getScore()), xw->Red);
        xw->drawString (20, 525, "level: ", xw->White);
        xw->drawString (275, 525, to_string (b1->getLevel()), xw->Red);
        xw->drawString (395, 525, "level: ", xw->White);
        xw->drawString (650, 525, to_string (b2->getLevel()), xw->Red);
        xw->drawString (20, 540, "next: ", xw->White);
        xw->drawString (395, 540, "next: ", xw->White);
        int xcoord = 20; 
        string next = b1->printNext();
        graphicsNext(xcoord, next, xw);
        next = b2->printNext(); 
        xcoord = 395; 
        graphicsNext(xcoord, next, xw); 
    }
    cout << "score:   " << b1->getScore() << "     score:   " << b2->getScore() << endl;
    cout << "level:   " << b1->getLevel() << "     level:   " << b2->getLevel() << endl;
    cout << printBoard (b1, b2, graphics, xw, prevboard);
    cout << "next:          next:      "<<endl;
    cout <<b1->printNext(0)<<"    "<<b2->printNext(0)<<endl;
    cout <<b1->printNext(1)<<"    "<<b2->printNext(1)<<endl;
}


//returns true when restart is entered
//when d is entered, this is activated to start next round
void dropCase(Board **curboard, Board *player, Board **otherboard, Board *player1, Board *player2) {
    (*curboard)->endAction(); //end all special effects
    player->blockDrop(); //drop current block

    player->clearLine(); //clear full lines
    player->scoreBlock(); //update scores after clearing
    player->nextRound(); //set up next round blocks

    //swap boards
    Board* temp = *curboard;
    *curboard = *otherboard;
    *otherboard = temp;

    if (player->getSpecial()) {
        cout << "You have cleared two or more lines"<<endl;
        cout << "you can choose a special action that will be applied to your opponent in the next round:"<<endl;
        cout << "heavy - Every time your opponent moves a block left or right, the block automatically falls by two rows"<<endl;
        cout << "blind - Your opponent's board, from columns 3-9, and from rows 3-12, will be covered with question marks"<<endl;
        cout << "force - Change the opponent's current block to be one of your choosing"<<endl;
        string type;
        while (cin >> type) {
            cout << "Please enter: heavy, blind, force"<<endl;
            if (type == "blind") {
                (*curboard) = new Blind {*curboard};
                break;
            }
            else if (type == "heavy") {
                (*curboard) = new Heavy {*curboard};
                break;
            }
            else if (type == "force") {
                    cout <<"Enter block type: I, T, O, S, Z, L, J"<< endl;
                while (cin >> type) {
                    if (type == "I" || type == "J" || type == "L" || type == "S" ||
                        type == "Z" || type == "O" || type == "T") {
                            (*curboard) = new Force {*curboard, type};
                            break;
                    }
                    cout <<"Enter block type: I, T, O, S, Z, L, J"<< endl;
                }
                break;
            }
        }
        player->turnoffSpecial(); //turn off after adding an effect
    }
}

template <typename T>
void remove(T* ptr)
{
	shared_ptr<T> i (ptr);
}

bool play (int argc, char* argv[]) {
    //boards
    Board* player1 = new Board;
    Board* player2 = new Board;

    Board *curboard = player1;
    Board *otherboard = player2;

    //starting levels
    int p1level = 0;
    int p2level = 0;

    //files
    string file1 = "sequence1.txt";
    string file2 = "sequence2.txt";

    bool graphics = true;

    int counter = 1;
    string input;

    while (counter < argc) {
        input = argv[counter];
        if (input == "-text")  {
            graphics = false;
        }
        else if(input == "-seed")  {
            ++counter;
            srand(atoi(argv[counter]));
        }
        else if(input == "-scriptfile1")  {
            ++counter;
            file1 = argv[counter];
        }
        else if(input == "-scriptfile2")  {
            ++counter;
            file2 = argv[counter];
        }
        else if(input == "-startlevel")  {
            ++counter;
	    string level = argv[counter];
	    istringstream ss {level};
	    ss >> p1level;
            p2level = p1level;
        }
        ++counter;
    }
    Xwindow *xw = nullptr;
    if (graphics) {
        xw = new Xwindow{690, 600};
        xw->fillRectangle (0, 0, 690, 600);
        xw->drawString (20, 495, "Player 1", xw->White);
        xw->drawString (395, 495, "Player 2", xw->White);
    }

    player1->setFile(file1);
    player2->setFile(file2);

    player1->changeLevel(p1level);
    player2->changeLevel(p2level);

    //start the beginning blocks
    player1->nextRound();
    player2->nextRound();

    //pointer for current player
    Board *player = nullptr;

    //print beginning game board
    string prevboard = "";
    printGame(player1, player2, graphics, xw, prevboard);

    string command;

    int multiplier;
    int loc;
    char c;
    while (cin >> command) {
        //getting command multiplier
        multiplier = 0;
        loc = 0;
        c = command.at(loc);
        while (c >= '0' && c <= '9') {
            multiplier *= 10;
            multiplier += c - '0';
            loc ++;
            c = command.at(loc);
        }
        //adjusting for 0 multiplier command
        if (multiplier == 0){
            ++multiplier;
        }
        //get command
        command = command.substr(loc);

        player = curboard->getBoard();
        if (player->getGameEnd()) { //check game end
            cout <<"game over!"<<endl;
            break;
        }
        if (player->getEndRound()) { //if heavy results in next round, next round starts
            dropCase (&curboard, player, &otherboard, player1, player2);
            player->turnOffEndRound();
        }
        if (command == "I" || command == "J" || command == "L" || command == "S" ||
            command == "Z" || command == "O" || command == "T"|| command == "*") { //manually change pieces
            player->checkEnd(command); //check if the piece fits
            if (player->getGameEnd()) {
                cout <<"game over!"<<endl;
                break;
            }
            player->resetBlock(command);
        }
        else if (command == "c") {
            player->blockRotateC(multiplier);
        }
        else if (command == "cc") {
            player->blockRotateCC(multiplier);
        }
        else if (command == "d") {
            dropCase (&curboard, player, &otherboard, player1, player2);
        }
        else if (command == "sl") {
            player->blockShiftL(multiplier);
        }
        else if (command == "sr") {
            player->blockShiftR(multiplier);
        }
        else if (command == "sd") {
            player->blockShiftD(multiplier);
        }
	    else if (command == "lu") {
            player->levelUp(multiplier);
	    }
	    else if (command == "ld") {
            player->levelDown(multiplier);
	    }
	    else if (command == "restart") {
            remove(curboard);
            remove(otherboard);
            remove(xw);
            return true;
	    }
        //!system("clear");
        printGame(player1, player2, graphics, xw, prevboard);
       }
        remove(curboard);
        remove(otherboard);
    return false;
}


int main (int argc, char *argv[]) {
    while (play(argc, argv)) {} //continue playing
}
