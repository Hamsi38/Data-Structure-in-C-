#include <iostream>
#include <string>
#include <stdbool.h>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

#define CYAN "\033[1;36m"
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"


using namespace std;

struct Library
{
    string book_name;
    string author;
    int page;
    double price;
    bool available;
    bool borrowed;
};

struct Library book;
vector <Library> V;

//* this part is for resgister of books for library
void menu();
void add_book(string price_str, string page_str);
void get_name();
void author_read();
void page_read(string page_str);
void book_price(string price_str);


//* display of all books
void display_all_books();
string lower_string(string must_lower);

//* verification for book's details like page number title author are int or not etc.
bool is_name_valid(const string& str);
bool is_choice_digit(const string & str); //? this is also is page int and the price double or int 
bool is_book_price(const string & str);

//* this part is for searching book
void search_book(string search_str);
bool is_book_avaible(const string & search_str);

//* borrow book part
bool is_book_borrowed(string & search_str);
void borrow_book(string  borrow_book_str);

//*update book
void update_book();

//* deleting book
bool delete_book(string str);
void delete_print();

//* returning a book
void return_menu();

//* all borrowed bokos display
void all_borrowed_books();

int main(){

    int choice;
    string choice_str,page_str, price_str,search_str,borrow_book_str;
    bool start_stop = true;

    while (start_stop)
    {
        menu();
        getline(cin,choice_str);
        if (is_choice_digit(choice_str)) 
        {
            choice = stoi(choice_str);
            switch (choice)
            {
            case 1:
                add_book(price_str, page_str);
                break;
            case 2:
                display_all_books();
                break;
            case 3:
                search_book(search_str);
                break;
            case 4:
                update_book();
                break;
            case 5:
                borrow_book(borrow_book_str);
                break;
            case 6:
                delete_print();
                break;
            case 7:
                return_menu();
                break;
            case 9:
                all_borrowed_books();
                break;
            case 0:
                cout<<RED<<"Thanks for using my application"<<RESET<<endl;
                start_stop = false;
                break;
            default:
                cout<<RED<<"INVALID NUMBER PLEASE TRY AGAIN"<<RESET<<endl;
                break;
            }
        }
        else
        {
            cout<<RED<<"Invalid number please try again!!!"<<RESET<<endl;
            cout<<GREEN;
        }
    }
    
    


    return 0;
}


void add_book(string price_str, string page_str)
{
    
    cout<<GREEN;
    get_name();
    author_read();
    page_read(page_str);
    book_price(price_str);
    book.available = true;
    book.borrowed = false;
    V.push_back(book);
}

void display_all_books()
{
    if (V.empty())
    {
        cout<<RED<<"Library is empyt "<<RESET<<endl;
    }
    else
    {
        cout<<YELLOW;
        for (int i = 0; i < V.size(); i++)
        {
            cout<<"Book's name = "<<V[i].book_name<<endl;
            cout<<"Author = "<<V[i].author<<endl;
            cout<<"Number of Pages = "<<V[i].page<<endl;
            cout<<"Price = "<<V[i].price<<endl;
            cout<<"Situation = "<< ((V[i].available) ? "In Stock " : "Not in Stock")<<endl;
            cout<<"Borrow = "<< (V[i].borrowed ? "Borrowed" : "Not Borrowed")<<endl;
            cout<<"\n\n";
        }
        cout<<RESET;
    }
}

void get_name()
{
    cout<<"Enter Book's Name --> ";
    getline(cin, book.book_name);
    book.book_name = lower_string(book.book_name);
    if (book.book_name.empty())
    {
        cout<<endl;
        cout<<RED<<"Every Book has a name!!!!"<<endl;
        cout<<"Enter the Name Again Please!!!"<<RESET<<endl;
        cout<<GREEN;
        get_name();
    }
}

void author_read()
{
    cout<<endl<<"Author --> ";
    getline(cin, book.author);
    if (book.author.empty())
    {
        cout<<endl;
        cout<<RED<<"Every book has an author!!"<<endl;
        cout<<"Enter the Author's name Again Please!!!"<<RESET<<endl;
        author_read();
        cout<<GREEN;
    }
    else if (!is_name_valid(book.author))
    {
        cout<<RED<<"Author's name only can contain :"<<endl;
        cout<<"* A-Z, a-z "<<"Spaces "<<" Period (.) "<<"Apostrophe (') "<<"Hypen (-)"<<RESET<<endl;
        cout<<GREEN;
        author_read();
    }
    
}

bool is_name_valid(const string & str) // for author
{
    for(char ch : str)
    {
        if (!isalpha(ch) && !isspace(ch) && ch!='.' && ch!='\'' && ch!='-') return false;
    }
    return true;
}

bool is_choice_digit(const string&  str)
{
    if(str.empty()) return false;
    for(char ch : str)
    {
        if(!isdigit(ch)) return false;
    }
    return true;
}

void menu()
{
        cout<<CYAN<<"========================================"<<endl;
        cout<<"             WELCOME TO THE"<<endl;
        cout<<"         LIBRARY MANAGEMENT SYSTEM"<<endl;
        cout<<"========================================"<<RESET<<endl;

        cout<<WHITE<<"=========== Library Management System ==========="<<endl;
        cout<<"1. Add Book"<<endl;
        cout<<"2. Display All Books"<<endl;
        cout<<"3. Search Book"<<endl;
        cout<<"4. Update Book"<<endl;
        cout<<"5. Borrow Book"<<endl;
        cout<<"6. Delete Book"<<endl;
        cout<<"7. Return Book"<<endl;
        cout<<"8. Display All Available Books"<<endl;
        cout<<"9. Display Borrowed Books"<<endl;
        cout<<"10. Sort Books"<<endl;
        cout<<"11. Library Statics"<<endl;
        cout<<"12. Save Data"<<endl;
        cout<<"13. Load Data"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"==============================================="<<endl;
        cout<<"Enter your choice is here --> "<<RESET;
}

void page_read(string page_str)
{
    cout<<endl<<"Page --> ";
    getline(cin,page_str);
    if (is_choice_digit(page_str))
    {
        book.page = stoi(page_str);
    }
    else
    {
        cout<<RED<<"Please enter a valid number"<<RESET<<endl;
        cout<<GREEN;
        page_read(page_str);
    }
}

void book_price(string price_str)
{
    cout<<endl<<"Price --> ";
    getline(cin,price_str);
    if (is_book_price(price_str))
    {
        book.price = stod(price_str);
    }
    else
    {
        cout<<RED<<"Please enter a valid number!!!"<<RESET;
        cout<<endl<<GREEN;
        book_price(price_str);
    }
    
}

bool is_book_price(const string & str)
{
    int dot = 0;
    if(str.empty()) return false;
    for(char ch : str)
    {
        if(ch=='.') dot++;
        if(!isdigit(ch) && ch != '.') return false;
        if(dot > 1) return false;
    }
    return true;
}

void search_book(string search_str)
{
    cout<<CYAN<<"Enter book's name to see is it in Library and available!!! --> ";
    getline(cin,search_str);
    search_str = lower_string(search_str);
    if (search_str.empty())
    {
        cout<<RED<<"Please enter book's name --> "<<RESET<<endl;
        search_book(search_str);
    }
    else
    {
        bool temp_avaible = is_book_avaible(search_str);
        bool temp_borrow = is_book_borrowed(search_str);
        if (temp_avaible && temp_borrow==false)
        {
            cout<<endl;
            cout<<CYAN"Yes the book you search in Library and not borrowed by someone"<<RESET<<endl<<endl;
        }
        else if (temp_avaible && temp_borrow==true)
        {
            cout<<endl;
            cout<<CYAN<<"WE have the book but right now it is borrowed by someone!!!"<<RESET<<endl;
        }
        else
        {
            cout<<CYAN<<"The book your looking for right now it is not available"<<RESET<<endl<<endl;
        }
    }
}

bool is_book_avaible(const string & search_str)
{
    for (int i = 0; i < V.size(); i++)
    {
        if(V[i].book_name == search_str)
        {
            return true;
        }
    }
    return false;
}

void borrow_book(string  borrow_book_str)
{
    cout<<YELLOW<<"Enter the book's name you want to borrow --> ";
    getline(cin,borrow_book_str);
    cout<<endl;
    if (borrow_book_str.empty())
    {
        cout<<"Please enter a valid name --> ";
        borrow_book(borrow_book_str);
    }
    else if (is_book_borrowed(borrow_book_str)==true)
    {
        cout<<"The book your looking is borrowed by someone sorry!!!"<<endl;
        return;
    }
    else 
    {
        if (is_book_avaible(borrow_book_str) && is_book_borrowed(borrow_book_str)==false)
        {
            string answer_ys;// answer for yes no if user wants to borrow a book
            cout<<"Do you want to borrow this book ? (type --> Yes/No)";
            getline(cin,answer_ys);
            answer_ys = lower_string(answer_ys);
            if (answer_ys=="yes")
            {
                for(int i = 0; i < V.size(); i++)
                {
                    if(V[i].book_name==borrow_book_str)
                    {
                        V[i].borrowed = true;
                        break;
                    }
                }
                cout<<"you borrowed it"<<endl;
            }
            else if (answer_ys=="no") return; 
            else
            {
                cout<<"Please type a valid answer!!!"<<endl;
                borrow_book(borrow_book_str);
            }   
        }
        else
        {
            cout<<"Please enter a valid book name!!!"<<endl;
            return;
        }
    }
}

bool is_book_borrowed(string & borrow_book_str)
{
    borrow_book_str = lower_string(borrow_book_str);
    for (int i = 0; i < V.size(); i++)
    {
        if (V[i].book_name== borrow_book_str)
        {
            if (V[i].borrowed==false) return false;
            else return true;
        }
    }
    return true;
}

void update_book()
{
    string update_book_name,update_answer,new_data;
    while (1)
    {
        cout<<BLUE<<"what book do you want to update ? ";
        getline(cin,update_book_name);
        if(update_book_name.empty()) return;
        cout<<endl<<"Type 1 for change book's name "<<endl;
        cout<<"Type 2 for change book's author "<<endl;
        cout<<"Type 3 for chagne book's page "<<endl;
        cout<<"Type 4 for change book's price"<<endl;
        cout<<endl<<"and What do you want to change ? ";
        cout<<endl<<"Enter Here ";
        getline(cin,update_answer);
        cout<<endl;
        cout<<"Enter here new data --> ";
        getline(cin,new_data);
        if(update_answer.empty() )
        {
            cout<<"Please type something!!!"<<endl;
            return;
        }
        else
        {
            for (int i = 0; i < V.size(); i++)
            {
                if(update_book_name == V[i].book_name)
                {
                    if (update_answer=="1")
                    {
                        V[i].book_name = new_data;
                        cout<<"Book's name changed successful"<<endl;
                        return;
                    }
                    else if (update_answer=="2")
                    {
                        V[i].author = new_data;
                        cout<<"Author's name changed successful"<<endl;
                        return;
                    }
                    else if (is_choice_digit(update_answer) && update_answer=="3")
                    {
                        if (is_choice_digit(new_data))
                        {
                            V[i].page = stoi(new_data);
                            cout<<"Book's page has changed successful"<<endl;
                            return;
                        }
                        else
                        {
                            cout<<"Please enter a valid integer number!!!"<<endl;
                            return;
                        }
                        
                    }
                    else if (is_book_price(new_data) && update_answer=="4")
                    {
                        V[i].price = stod(new_data);
                        cout<<"Book's price has changed successful"<<endl;
                        return;
                    }
                    else
                    {
                        cout<<"Plase enter a valid input"<<endl;
                        return;
                    }
                }
                else 
                {
                    cout<<"The book you typied it is not in library!!!"<<endl;
                    cout<<"maybe you wrote wrong try again!!!"<<endl;
                    return;
                }
            }
        }
    }
}


string lower_string(string must_lower)
{
    transform(must_lower.begin(), must_lower.end(), must_lower.begin(), ::tolower);
    return must_lower;
}

bool delete_book(string str)
{
    for (int i = 0; i < V.size(); i++)
    {
        if(V[i].book_name==str)
        {
            V.erase(V.begin() + i);
            return true;
        }
    }
    return false;
}

void delete_print()
{
    string str;
    cout<<BLUE<<"Enter your answer here --> ";
    getline(cin,str);
    cout<<endl;
    if (delete_book(str))
    {
        cout<<str<<" deleted successfully."<<endl;
    }
    else cout<<"No such book."<<RESET<<endl;
}

void return_menu()
{
    string str;
    cout<<RED<<"Enter the Book's name --> ";
    getline(cin,str);
    cout<<endl;
    str = lower_string(str);
    if (is_book_avaible(str))
    {
        if (is_book_borrowed(str)==true)
        {
            for (size_t i = 0; i < V.size(); i++)
            {
                if (V[i].book_name==str)
                {
                    if(V[i].borrowed==true)
                    {
                        V[i].borrowed=false;
                        cout<<BLUE<<"it is returned successfully!!!"<<RESET<<endl;
                        return;
                    }
                }
            }
        }
        else if (is_book_borrowed(str)==false)
        {
            cout<<BLUE<<"It is not borrowed you can't return it"<<RESET<<endl;
        }
        else
        {
            cout<<BLUE<<"Error please try again!!!"<<endl;
        }
        cout<<RESET<<endl;
    }
    else
    {
        cout<<BLUE<<"It is not in stock sorry!!!"<<endl;
    }
}

void all_borrowed_books()
{
    cout<<YELLOW<<endl;
    cout<<"All borrowed books here!!!"<<endl;
    for (size_t i = 0; i < V.size(); i++)
    {
        if (V[i].borrowed==true)
        {
            cout<<V[i].book_name<<" "<<V[i].borrowed<<endl;
        }
    }
    cout<<RESET<<endl;
}
