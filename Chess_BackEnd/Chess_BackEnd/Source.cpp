/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "board.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));

	
	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	board* board1 = new board();
	
	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp########K#######################PPPPPPPPRNB#QBNR1"); // just example...
	
	board1->board_str = msgToGraphics;

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	board1->board_str = msgToGraphics;
	board1->set_board_figures();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		
		if (board1->move_figure(msgFromGraphics.substr(0,2), msgFromGraphics.substr(2, 2)))
		{
			std::cout << "nice job" << std::endl;

			if (board1->is_chess(msgFromGraphics.substr(2, 2)))
			{
				std::cout << "nice chess" << std::endl;
			}
			else
			{
				std::cout << "bad chess" << std::endl;
			}
		}
		else
		{
			std::cout << "bad job" << std::endl;
		}

		


		// YOUR CODE
		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation

		/******* JUST FOR EREZ DEBUGGING ******/
		int r = rand() % 10; // just for debugging......
		msgToGraphics[0] = (char)(1 + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/


		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}