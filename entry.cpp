#include <sstream>
#include <iomanip>
#include <sstream>
#include "entry.h"
#include "prompt.h"
#include "menu.h"

using namespace std;
using Prompt::natural_num;

namespace Tome {
//|----------Constructor--------------
Book::Book(void)
{
    author = " ";
    title = " ";
    isbn = " ";
    number = 0;
    stocks = 0;
    price = 0.00;
}
//|------Ctor user initialized arguments----------------
Book::Book(int n, int s, double p, string au,
             string tt, string ibn,
             vector<string> gen)
    : number(n), stocks(s), price(p),           //initialize the values
      author(au), title(tt), isbn(ibn), genres(gen) 
{
}

//|-------- OPERATOR OVERLOAD --------------
ostream& operator <<(ostream& ost, const Book& b)
{
    
    //printing all books in the archives
        ost << "-> ["      << b.number << "]" 
             << " Title:  "  << b.title << "\n "
             << " \tAuthor: " << b.author << "\n ";
        ost << " \tGenres: "; 

   //for each  word found in the genre
     for(auto& w : b.genres) ost << w << ". ";

        ost << "\n \tISBN:   "    << b.isbn << "\n "
             << " \tStocks: "     << b.stocks << "\n " 
             << fixed             << setprecision(2)
             << " \tPrice:  "     << b.price << "\n\n";

     return ost;
}

ofstream& operator <<(ofstream& out, const Book& b)
{   
    out  << "{ " << '"' << b.title << "\" \"" << b.author << '"'; 

    for(auto& w : b.genres)
        out << '"' << w << '"';

    out << " , " << b.number << " , " << b.isbn << " , " 
        << b.stocks << " , " << fixed << setprecision(2) 
        << b.price << " }" << endl;

    return out;
}

//|-------Member  Functions-----------
void Book::insert(const int n)
{
    const double TAX = 0.12;
    string s; 

    //taking the inputs
    cout << "Title:\t";
    getline(cin, title);
    cout << "Author:\t";
    getline(cin, author);

    cout << "\nEnter in delimited by space eg. action drama...\n";
    cout << "Genres: ";
    getline(cin, s);

    stringstream ss(s); //break the words
    for(string word; ss >> word;) 
        genres.push_back(word); //vector handles the words

    cout << "ISBN:\t";
    getline(cin, isbn);

    //take input until its a number
    stocks = Prompt::prompt("Stocks:\t");
    price = Prompt::prompt("Price:\t");    

    //tax calculation
    //TO DO: fix error prone of price
    price = (TAX * price) + price;
    number = n;
}

// args passed will be change by reference
void Book::revise(void)
{
    Menu::update_book(stocks, price);
}

// arg passed is by user found in computation function
int Book::min_stocks(int& n)
{
    enum {OUT, MIN, SUCCESS};
    if(stocks == 0)         //check the remaining stocks
    {
      cout << "\nOut of stocks...\n";
      return OUT;
    }
    double dummy = stocks - n;            //compute stocks if valid
    if(natural_num(dummy) == false)
    {
      cout << "\nInvalid amount of quantity...\n";
      return MIN; //will be prompt again to insert valid n
    }

    stocks -= n;
    return SUCCESS;
}

//****************** UTILITY FUNCTIONS *********************
double Book::get_price(void)
{
    return price;
}
int Book::get_stocks(void)
{
    return stocks;
}
int Book::get_no(void) const
{
    return number;
}
string Book::get_title(void) const
{
    return title;
}

vector<string> split(const string& text, const string& delims)
    //will split the strings
{
    vector<string> tokens;

    //continously find the delims
    size_t start = text.find_first_not_of(delims),
           end = 0;
    //read until the end
    while((end = text.find_first_of(delims, start)) != string::npos)
      {
        tokens.push_back(text.substr(start, end - start)); //n + end take string
        start = text.find_first_not_of(delims, end);  //find another delim
      }
    if(start != string::npos)       //take the remaining strings
     tokens.push_back(text.substr(start));

    return tokens;
}

}
