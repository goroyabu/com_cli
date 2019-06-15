/**
   @author Goro Yabu
   @date 2019/03/14
   @version 2.0
**/
#include <com_cli.hpp>
#include <cmdline.hpp>
using namespace std;
int test_read_value()
{
    string name = "Donkey";
    com_cli::read_value("What is your name", &name);
    
    int age = 37;
    com_cli::read_value("How old are you", &age);

    cout << endl;
    cout << "Your name is " << name << " ! " << endl;
    cout << "You are " << age << " years old ! " << endl;
    cout << endl;
    return 0;
}
int test_read_keyword()
{
    string answer; int ianswer = 0;
    vector<string> list = {"Sunday", "monday", "TUESDAY", "WEDnesday"};
    
    if( com_cli::read_keyword("Choose your favourite day ?", list, &ianswer) == com_cli::CLI_OK ){
	answer = list[ianswer];
        cout << "Your choise = " << answer << endl;
        cout << "Index of choise = " << ianswer << endl;	
    }
    else{
	com_cli::cli_error(1, "test_read_keyword", "Your input is not valid");
    }
    cout << endl;
    return 0;
}
/*
int select_members()
{
    vector<string> name = {"Mario", "bowser", "toad", "luigi"};
    vector<double> level = {10.0, 99.0, 5.0, 1.03};
    
    vector<int> answer;
    com_cli::read_keyword("DK *** Select Character ***", name, -1, &answer);
    cout << "YOUR TEAM" << endl;
    for(int index : answer) cout << name[index] << endl;
    cout << endl;
    
    com_cli::read_value<double>("*** Modify Parameter ***", name, &level);
    for(auto i : level) cout << i << endl;
    
    return 0;
}
*/
int main()
{
    com_cli::init("",".cli_hist");

    test_read_value();
    test_read_keyword();
    
    com_cli::end();
    
    return 0;
}
