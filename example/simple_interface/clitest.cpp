/**
   @author Goro Yabu
   @date 2019/03/14
   @version 2.0
**/
#include <com_cli.hpp>
#include <cmdline.hpp>
using namespace com_cli;
using namespace std;

int what_your_name()
{
    string firstname = "Donkey";
    //com_cli::enable_custom_complete();
    //com_cli::set_candidates("Donkey", "Funcky");
    
    com_cli::read_value("What is your first name ?", &firstname);
    
    cout << "Your name is " << firstname << " ! " << endl;
    cout << endl;
    return 0;
}
int how_old_are_you()
{
    //com_cli::disable_custom_complete();
    int age = 37;
    com_cli::read_value("How old are you", &age);
    
    cout << "You are " << age << " years old ! " << endl;
    cout << endl;
    return 0;
}
int choose_your_food()
{
    //com_cli::enable_custom_complete();

    vector<string> list = {"BANANA", "mashroom", "eGG"};
    //com_cli::set_candidates(list);

    string answer; int ianswer = 0;
    if( com_cli::read_keyword("Choose your favourite food ?", list, &ianswer) == com_cli::CLI_OK ){
	answer = list[ianswer];
        cout << "Your choise = " << answer << endl;
        cout << "Index of choise = " << ianswer << endl;	
    }
    cout << endl;
    return 0;
}
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

int main()
{
    using namespace com_cli;
    init("DK",".cli_hist");

    //test_read_value();//read 1 int
    //test_read_value2();//read several strings with custom complete
    //test_read_keyword();
    //test_read_keyword2();
    
    what_your_name();
    how_old_are_you();
    choose_your_food();
    select_members();
    
    end();
    
    return 0;
}
