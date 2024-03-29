#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "archive.h"
#include "menu.h"  //use by updt_book function to display update prompts
#include "prompt.h" //using the prompt(string) to take numbers


/*
 * Created: 10/6/2022
 *
 * Class Functions mainly
 * for Inserting books in the archive*/

using std::cout;
using std::cin;
using std::endl;
using std::ws;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::getline;
using std::string;

Archive *find_entry(Archive *head, const int &n)
{
    Archive *p = head;

    cout << "Finding...\n" ;
    for(;
        p != nullptr && n > p->number;
        p = p->next)
        ;

    if (p != nullptr && n == p->number)
    {
       return p; //number ay nakita na
    }
    else
        return nullptr; //number does not exist in archive list
}

Archive *entry_datas(Archive *node)
{
    Archive *p = node;

    cout << "Title:\t";
    std::getline(cin >> ws, p->title);

    cout << "Author:\t";
    std::getline(cin >> ws, p->author);

    cout << "ISBN:\t";
    std::getline(cin >> ws, p->isbn);

    p->stocks = Prompt::prompt("Stocks:\t");

    p->price = Prompt::prompt("Price:\t");    

    return p;
}

//inserting entry 
void Book::insertArch(void)
{
    Archive *cur, *prev;
    Archive *new_node = new Archive;

    if(new_node == NULL)
    {
        std::cerr << "Memory full: ";
        return;
    }

    cout << "Entry number: ";
    cin >> new_node->number;
    
    //will sort the entry number from low to high
    for(cur = head, prev = nullptr;
        cur != nullptr && new_node->number > cur->number;
        prev = cur, cur = cur->next)
        ;
    
    if(cur != nullptr && new_node->number == cur->number)
    {
        cout << "Entry number already exist\n";
        delete(new_node);
        return;
    }
    
    new_node = entry_datas(new_node);
    new_node->next = cur; 
    if(prev == nullptr)
        head = new_node; //entry will be insert
                         //in the lowest number
    else
        prev->next = new_node; //insert the entry num
                               //after the low num
}

//searching through a parameter archive
void Book::search(void)
{
    int n;
    Archive *p = head;
    cout << "Find Entry Number: ";
    cin >> n;

    p = find_entry(p, n);
    if(p != nullptr)
    {
        cout << "\t=======\tBook Details\t======\n"
             << "\tTitle " << " Author\n"
             << "\t" << p->title << "  " << p->author
             << endl; 
    }
    else
        cout << "Entry doesn't exist in the archive\n"; 
}

void Book::update(void)
{
    int n;
    double num;

    Archive *p = head; //aayusin ko to soon ok...

    cout << "Find Entry Number: ";
    cin >> n;

    p = find_entry(p, n);
    if(p != NULL)
    {
       cout << "Changing " << p->title << " data...\n";
       Menu::update_book(p->stocks, p->price); //updating the books informations
       head = p;
    }
    else
        cout << "Entry doesn't exist in the archive\n";
}

void Book::show(void)
{
    Archive *p;
    static int line_len = 150;
    
    string bk_det[] = { "Code", "Title", "Author",
                        "ISBN", "Stocks", "Price"};
    for(size_t i = 0; i < sizeof(bk_det) / sizeof(bk_det[0]);
            i++)
        cout << " " << bk_det[i] << "\t\t\t\t";
      
    cout << "\n\n" << setfill('=') << setw(line_len) 
         << "\n";
    for(p = head; p != nullptr; p = p->next)
    {
             cout << " "  << p->number  << "\t\t|\t"
             << p->title << "\t\t\t "
             << p->author << "\t\t "
             << p->isbn << "\t\t"
             << p->stocks << "\t\t\t"
             << p->price << "\t\t\t\n";
    }
}

