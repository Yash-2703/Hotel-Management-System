#include<iostream>
#include<string.h>
#include<list>
#include<fstream>
#include<conio.h>

#define max 100
using namespace std;

// Class Customer
class Customer
{
public:
    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;
};

// Class Room
class Room
{
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;

    Room() :roomNumber(0), rent(0), status(0) {}
    
    Room(int rno, char ac, char type, char stype, int rent) : roomNumber(rno), ac(ac), type(type), stype(stype), rent(rent), status(0) {}

    void displayRoom()
    {
        cout << "\nRoom Number: \t" << roomNumber;
        cout << "\nType AC/Non-AC (A/N) " << ac;
        cout << "\nType Comfort (S/N) " << type;
        cout << "\nType Size (B/S) " << stype;
        cout << "\nRent: " << rent;
    }
};

// Class Graph
class Graph
{
public:
    int count;
    list<Room> rooms;

public:
    void addRoom(int rno, char ac, char type, char stype, int rent);
    void searchRoom(int rno);
    void  deleteRoom(int rno);
    void displayRoom(int rno);

};

void Graph::addRoom(int rno, char ac, char type, char stype, int rent)
{
    Room newRoom(rno, ac, type, stype, rent);
    rooms.push_back(newRoom);
    count++;
    cout << "\nRoom Added Successfully!";
    
}

void Graph::searchRoom(int rno)
{
    int found = 0;
    list<Room>::iterator it;

    for (it = rooms.begin(); it != rooms.end(); ++it)
    {
        if (it->roomNumber == rno)
        {
            found = 1;
            break;
        }
    }

    if (found == 1)
    {
        cout << "Room Details\n";
        if (it->status == 1)
        {
            cout << "\nRoom is Reserved";
        }
        else
        {
            cout << "\nRoom is available";
        }
        it->displayRoom();
       
    }
    else
    {
        cout << "\nRoom not found";
        
    }
}



void Graph::displayRoom(int rno)
{
    int found = 0;
    list<Room>::iterator it;

    for (it = rooms.begin(); it != rooms.end();
	++it)
	{
	if (it->roomNumber == rno)
	{
	found = 1;
	break;
	}
	}
	if (found == 1)
{
    cout << "Room Details\n";
    it->displayRoom();
}
else
{
    cout << "\nRoom not found";
    
}
}



// Class HotelMgnt
class HotelMgnt
{
public:
Graph graph;

void checkIn();
void getAvailRoom();
void searchCustomer(const char *);
void checkOut(int);

void checkOutdisplay();
};

void HotelMgnt::checkIn()
{
ofstream outputFile;
outputFile.open("example.txt",ios::app);
if (!outputFile) {
        cout << "Failed to open the file." << endl;
        return ;
    }
int rno;
cout << "\nEnter Room number : ";
cin >> rno;
graph.searchRoom(rno);


list<Room>::iterator it;
for (it = graph.rooms.begin(); it != graph.rooms.end(); ++it)
{
    if (it->roomNumber == rno)
    {
        if (it->status == 1)
        {
            cout << "\nRoom is already Booked";
            
            return;
        }
      
        outputFile<<rno<<"\t\t";
        cout << "\nEnter booking id: ";
        cin >> it->cust.booking_id;
        outputFile<<it->cust.booking_id<<"\t\t";

        cout << "\nEnter Customer Name (First Name): ";
        cin >> it->cust.name;
        outputFile<<it->cust.name<<"\t\t";

        cout << "\nEnter Address (only city): ";
        cin >> it->cust.address;
        outputFile<<it->cust.address<<"\t\t";

        cout << "\nEnter Phone: ";
        cin >> it->cust.phone;
        outputFile<<it->cust.phone<<"\t\t";

        cout << "\nEnter From Date: ";
        cin >> it->cust.from_date;
        outputFile<<it->cust.from_date<<"\t\t";

        cout << "\nEnter to  Date: ";
        cin >> it->cust.to_date;
	outputFile<<it->cust.to_date<<"\t\t";
	
        cout << "\nEnter Advance Payment: ";
        cin >> it->cust.payment_advance;
        outputFile<<it->cust.payment_advance<<"\t\t\n";
       	outputFile.close();

        it->status = 1;

        cout << "\n Customer Checked-in Successfully..";
        
        return;
    }
}

cout << "\nRoom not found";
}

void HotelMgnt::getAvailRoom()
{
if (graph.rooms.empty())
{
cout << "\nAll rooms are reserved";
return;
}
list<Room>::iterator it;
for (it = graph.rooms.begin(); it != graph.rooms.end(); ++it)
{
    if (it->status == 0)
    {
        it->displayRoom();
        cout << "\n\nPress enter for next room";
    }
}
}

void HotelMgnt::searchCustomer(const char *pname)
{
int found = 0;
list<Room>::iterator it;
for (it = graph.rooms.begin(); it != graph.rooms.end(); ++it)
{
    if (it->status == 1 && strcmp(it->cust.name, pname) == 0)
    {
        cout << "\nCustomer Name\t:" << it->cust.name;
        cout << "\nAddress\t\t:" << it->cust.address;
        cout << "\nPhone\t\t:" << it->cust.phone;
        cout << "\nBooking Id\t:" << it->cust.booking_id;
        cout << "\nRoom Number\t:" << it->roomNumber;
        cout << "\nTotal Amount\t:" << it->rent;
        found = 1;
    }
}

if (found == 0)
{
    cout << "\nNo customer found with name " << pname;
}

}

void HotelMgnt::checkOut(int rno)
{
int found = 0;
list<Room>::iterator it;
for (it = graph.rooms.begin(); it != graph.rooms.end(); ++it)
{
    if (it->roomNumber == rno)
    {
        found = 1;
        break;
    }
}

	if (found == 1)
	{
    		if (it->status == 0)
    		{
        		cout << "\nRoom is already vacant";
        		//getch();
        		return;
    	}

    cout << "\nCustomer Name\t:" << it->cust.name;
    cout << "\nAddress\t\t:" << it->cust.address;
    cout << "\nPhone\t\t:" << it->cust.phone;
    cout << "\nBooking Id\t:" << it->cust.booking_id;
    cout << "\nRoom Number\t:" << it->roomNumber;
    cout << "\nTotal Amount\t:" << it->rent;
    
    
    it->status=0;
    return;
}

cout << "\nRoom not found";
}

// Main function
int main()
{
HotelMgnt hotel;

int choice;

while (1)
{
    cout << "\n\t\t\t ************";
    cout << "\n\t\t\t HOTEL MANAGEMENT ";
    cout << "\n\t\t\t ************";
    cout << "\n\n\t\t\t 1. Add Room";
    cout << "\n\t\t\t 2. Search Room";
    cout << "\n\t\t\t 3. Display Room";
    cout << "\n\t\t\t 4. Check-In Room";
    cout << "\n\t\t\t 5. Get Available Rooms";
    cout << "\n\t\t\t 6. Search Customer";
    cout << "\n\t\t\t 7. Check-Out Room";
    cout << "\n\t\t\t 8. Exit";
    cout << "\n\n\t\t\t Select Your Choice : ";

    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int rno, rent;
        char ac, type, stype;

        cout << "\nEnter Room number: ";
        cin >> rno;

        cout << "\nEnter AC/Non-AC (A/N): ";
        cin >> ac;

        cout << "\nEnter Comfort (S/N): ";
        cin >> type;

        cout << "\nEnter Size (B/S): ";
        cin >> stype;

        cout << "\nEnter Rent: ";
        cin >> rent;

        hotel.graph.addRoom(rno, ac, type, stype, rent);
        break;
    }
    case 2:
    {
        int rno;
        cout << "\nEnter Room number: ";
        cin >> rno;
        hotel.graph.searchRoom(rno);
        break;
    }
    case 3:
     {
        int rno;
        cout << "\nEnter Room number: ";
        cin >> rno;
        hotel.graph.displayRoom(rno);
        break;
    }
    
    case 4:
    	
        hotel.checkIn();
        break;
    case 5:
        hotel.getAvailRoom();
        break;
    case 6:
    {
        char pname[100];
        cout << "\nEnter Customer Name: ";
        cin >> pname;
        hotel.searchCustomer(pname);
        break;
    }
    case 7:
    {
        int rno;
        cout << "\nEnter Room number: ";
        cin >> rno;
        hotel.checkOut(rno);
        break;
    }
    case 8:
        exit(0);
    default:
        cout << "\nInvalid choice. Press enter to continue.";
        
    }
}

return 0;
}
