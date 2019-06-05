#include "cmdline.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
using namespace cmdline;
int define_args()
{
    set_program_name("mkarginit");
    add_option("force", 'f', "Force to overwrite.");
    add_option<string>("progname", 'n', "Programe name.", false, "\0");
    add_option<string>("out", 'o', "Output file name.", false, "main.cpp");
    //add_option<double>("energy", 's', "Energy of the gamma-ray \n incidented the material", false, 2);
    add_option("version", '\0', "Print the version and exit.");
    add_option("author", '\0', "Print the author and exit.");    
    return 0;
}
int print_version()
{
    cout << "mkinit 1.0.0" << endl;
    return 0;
}
int print_init()
{
    ofstream ofs(get_option<string>("out"));
    stringstream ss;
    ss << "/**" << endl;
    ss << "" << endl;
    ss << "**/" << endl;
    ss << "int main(int argc, char* argv[])" << endl;
    ss << "{" << endl;
    ss << "    return 0;" << endl;
    ss << "}" << endl;
    ofs << ss.str();
    return 0;
}
int main(int argc, char *argv[])
{
    define_args();
    parse_check(argc, argv);
    
    if(exist_option("version")) return print_version();    
    return print_init();
    
    return 0;
}
