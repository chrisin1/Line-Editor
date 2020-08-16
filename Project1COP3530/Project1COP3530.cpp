// Project1COP3530.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LinkedList.h"
#include <string>
using namespace std;

class LineEditor
{
private:
	LinkedList<string> document;
public:
	void insertEnd(string text);
	void insert(int index, string text);
	void deleteLine(int index);
	void edit(int index, string text);
	void print();
	void search(string text);
	string parseText(string& command, string type);

};

void LineEditor::insertEnd(string text)
{
	string newText = text;
	while (newText.length() > 80)
	{
		document.AddTail(newText.substr(0, 80));
		newText = newText.substr(80, newText.length());
	}

	if (newText.length() <= 80)
	{
		document.AddTail(newText);
	}

}

void LineEditor::insert(int index, string text)
{
	string newText = text;
	int startIndex = index - 1; //index is one-indexed
	if (startIndex <= document.NodeCount())
	{
		while (newText.length() > 80)   //cuts up long string into smaller pieces
		{
			document.InsertAt(newText.substr(0, 80), startIndex);
			newText = newText.substr(80, newText.length());
			startIndex++;
		}

		if (newText.length() <= 80)
		{
			document.InsertAt(newText, startIndex);
		}
	}
	
}

void LineEditor::deleteLine(int index)
{
	document.RemoveAt(index - 1);  //index is one-indexed
}

void LineEditor::edit(int index, string text)
{
	deleteLine(index);              //"editing" is the same as deleting it, and adding the new edit in its place
	insert(index, text);
}

void LineEditor::print()
{
	document.PrintForward();
}

void LineEditor::search(string text)
{
	bool found = false;
	int searchFactor = (int)((text.length() / 80.0) + 1); // used to determine how to group Nodes to be searched based on input size. 80 or less = search one node at a time. 81-160 = search two at a time. 
	LinkedList<string>::Node* ptr = document.Head();
	if (searchFactor > document.NodeCount()) //edge case, search item cannot be found if it is larger than the whole document
	{
		cout << "not found" << endl;
		return;
	}
	else if (searchFactor == 1)
	{	
		for (unsigned int i = 0; i < document.NodeCount(); i++)
		{
			if (ptr->data.find(text) != std::string::npos)
			{
				cout << (i + 1) << " " << ptr->data << endl;
				found = true;
			}
				
			ptr = ptr->next;
		}

	}
	else 
	{	
		LinkedList<string>::Node* upperBound = ptr;
		for (int i = 0; i < searchFactor - 1; i++) //initialize upperBound for grouping purposes
		{
			upperBound = upperBound->next;
		}
		for (unsigned int i = 0; i < document.NodeCount() && upperBound != nullptr; i++)
		{
			string combinedText = ""; //combined text from multiple lines
			LinkedList<string>::Node* addPtr = ptr;  //pointer that is used to traverse ahead and add strings to the big combined string
			LinkedList<string> currLines; //contains current lines being searched, for printing purposes

			for (int j = 0; j < searchFactor; j++) //assemble and store current group of searched lines in currLines
			{
				combinedText += addPtr->data;
				currLines.AddTail(addPtr->data);
				addPtr = addPtr->next;
			}

			if (combinedText.find(text) != std::string::npos)
			{
				int j = i + 1;
				for (LinkedList<string>::Node* curr = currLines.Head(); curr != nullptr; curr = curr->next, j++)
				{
					cout << j << " " << curr->data << endl;
				}

				found = true;
			}
			
			ptr = ptr->next;
			upperBound = upperBound->next;
		}
	}

	if (!found)
	{
		cout << "not found" << endl;
	}
}

string LineEditor::parseText(string& command, string type)
{
	string result = "";
	if (type.compare("text") == 0)
	{
		result = command.substr(command.find("\"") + 1, command.length());  //text starts after index of quotation
		result = result.substr(0, result.length() - 1); //exculde last quotation mark
	}
	else if (type.compare("line number") == 0)
	{
		int numStart = command.find(" ") + 1;
		result = command.substr(numStart, (command.find(" ", numStart)) - numStart);  //substring from first digit to last digit
	}

	return result;
}



int main()
{
	LineEditor doc;
	string command = "";
	do {
		getline(cin, command);
		if (command.find("insertEnd") != std::string::npos)
		{
			string parsedText = doc.parseText(command, "text");
			doc.insertEnd(parsedText);
		}
		else if (command.find("insert") != std::string::npos)
		{
			string parsedInt = doc.parseText(command, "line number");
			int index = stoi(parsedInt);
			string parsedText = doc.parseText(command, "text");
			doc.insert(index, parsedText);
		}
		else if (command.find("delete") != std::string::npos)
		{
			string parsedInt = doc.parseText(command, "line number");
			int index = stoi(parsedInt);
			doc.deleteLine(index);
		}
		else if (command.find("edit") != std::string::npos)
		{
			string parsedInt = doc.parseText(command, "line number");
			int index = stoi(parsedInt);
			string parsedText = doc.parseText(command, "text");
			doc.edit(index, parsedText);

		}
		else if (command.find("print") != std::string::npos)
		{
			doc.print();
		}
		else if (command.find("search") != std::string::npos)
		{
			string parsedText = doc.parseText(command, "text");
			doc.search(parsedText);
		}
	} while (command.compare("quit") != 0);
	
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
