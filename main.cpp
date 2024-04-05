#include <bits/stdc++.h>
using namespace std;

struct User
{
    string Name;
    int Age;
    string Contact_number;
    string Role;
    void getdetails()
    {
        cout << "Enter Name : ";
        cin >> Name;
        cout << "Age : ";
        cin >> Age;
        cout << "Contact Number : ";
        cin >> Contact_number;
        cout << "Role (admin / user) : ";
        cin >> Role;
    }
    void displaydetails()
    {
        cout << "Name : ";
        cout << Name;
        cout << "Age : ";
        cout << Age;
        cout << "Contact Number : ";
        cout << Contact_number;
        cout << "Role : ";
        cout << Role;
    }
};
struct timer
{
    int day = 0;
    int month = 0;
    bool compare(timer t)
    {
        if (t.month > month)
        {
            return true;
        }
        else if (t.month < month)
        {
            return false;
        }
        else
        {
            if (t.day >= day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};

struct conference_room
{
    string name = "default";
    bool occupied = false;
    User occupied_by;
    string meeting_title = "no_title";
    int capacity = 20;
    timer end_time;
    void putdetails()
    {
        cout << "Name : ";
        cout << name;
        cout << "Availability : ";
        if (occupied)
            cout << "BUSY\n";
        else
            cout << "FREE\n";
        cout << "\nCapacity : ";
        cout << capacity;
        cout << "\nOccupied By : ";
        cout << occupied_by.Name;
        cout << "\nMeeting Title : ";
        cout << meeting_title;
        cout << "\nEnd Time (DD MM) : ";
        cout << end_time.day << " " << end_time.month;
        cout << "\n";
    }
};

struct Floor
{
    vector<conference_room> rooms;

    Floor()
    {
        for (int i = 0; i < 1; i++)
        {
            conference_room newCR;
            rooms.push_back(newCR);
        }
    }
};

int main()
{
    map<int, Floor> Building;
    Floor emptyf;
    Building[1] = emptyf;
    Building[5] = emptyf;
    Building[10] = emptyf;

    queue<pair<int, conference_room>> RequestQueue;
    while (1)
    {
        cout << "-----------Enter Information---------------\n";
        struct User newUser;
        do
        {
            newUser.getdetails();
        } while (newUser.Role != "admin" && newUser.Role != "user");

        if (newUser.Role == "admin")
        {
            while (1)
            {
                cout << "\nSelect from option\n";
                cout << "1.Add Rooms\n";
                cout << "2.Available Rooms\n";
                cout << "3.Get Details\n";
                cout << "4.Request Queue\n";
                cout << "5.Break\n";
                int choice;
                cin >> choice;
                if (choice == 1)
                {
                    cout << "Enter FLoor No. ";
                    int f;
                    cin >> f;
                    if (f != 1 && f != 5 && f != 10)
                    {
                        cout << "Floor not allowed\n";
                        break;
                    }

                    conference_room newCR;

                    cout << "Enter Name of CR : ";
                    cin >> newCR.name;
                    cout << "\nCapacity : ";
                    cin >> newCR.capacity;
                    Building[f].rooms.push_back(newCR);
                    cout << "Room Added successfully\n";
                }
                else if (choice == 2)
                {
                    for (auto x : Building)
                    {
                        cout << "Floor No. " << x.first << "\n";
                        int count = 0;
                        cout << "Empty Rooms - ";
                        for (auto y : x.second.rooms)
                        {
                            if (!y.occupied)
                            {
                                y.putdetails();
                            }
                        }
                        cout << "Empty rooms on Floor No." << x.first << " are " << count << "\n";
                    }
                }
                else if (choice == 3)
                {
                    for (auto x : Building)
                    {
                        cout << "Floor No. " << x.first << "\n";
                        int count = 0;
                        for (auto y : x.second.rooms)
                        {
                            if (!y.occupied)
                            {
                                cout << "Conference Room : \n";
                                y.putdetails();
                            }
                        }
                        cout << "Empty rooms on Floor No." << x.first << " are " << count << "\n";
                    }
                }
                else if (choice == 4)
                {

                    queue<pair<int, conference_room>> cpy = RequestQueue;
                    while (!cpy.empty())
                    {
                        int tp = cpy.front().first;
                        conference_room newCR = cpy.front().second;
                        cpy.pop();
                        cout << "Floor No" << tp << "\n";
                        newCR.putdetails();
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            while (1)
            {
                cout << "\nSelect from option\n";
                cout << "1.Available Rooms\n";
                cout << "2.Book Rooms\n";
                cout << "3.Break\n";

                int choice;
                cin >> choice;
                if (choice == 1)
                {
                    for (auto x : Building)
                    {
                        cout << "Floor No. " << x.first << "\n";
                        int count = 0;
                        for (auto y : x.second.rooms)
                        {
                            if (!y.occupied)
                                count++;
                        }
                        cout << "Empty rooms on Floor No." << x.first << " are " << count << "\n";
                    }
                }
                else if (choice == 2)
                {
                    cout << "Enter Floor No. ";
                    int f;
                    cin >> f;
                    if (f != 1 && f != 5 && f != 10)
                    {
                        cout << "Floor not allowed\n";
                        break;
                    }

                    conference_room newCR;
                    newCR.occupied = true;
                    newCR.occupied_by = newUser;
                    cout << "\nMeeting Title : ";
                    cin >> newCR.meeting_title;
                    cout << "\nEnd Time decided : ";
                    cin >> newCR.end_time.day >> newCR.end_time.month;
                    int flag = 0;
                    for (auto &y : Building[f].rooms)
                    {
                        if (!y.occupied)
                        {
                            flag = 1;
                            y = newCR;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        RequestQueue.push({f, newCR});
                        cout << "Rooms Full\n";
                    }
                    else
                    {
                        cout << "Room Booked\n";
                    }
                }
                else
                {
                    break;
                }
            }
        }

        cout << "To break press 1";
        int x;
        cin >> x;
        if (x == 1)
            break;
    }
}