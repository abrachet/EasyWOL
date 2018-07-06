/**
 * easyWOL
 * 
 * 
 * Alex Brachet-Mialot
 * 
 * 
 */ 

#include "ConfigFileParser.cpp"

int commandLineCalls(const char*, const char*);

int main( const int argc, const char** argv )
{
    for (int i = 1; i < argc; i++)
        i += commandLineCalls(argv[i], argv[i + 1]);
    
}

int commandLineCalls(const char* arg, const char* arg2)
{
    bool null = (arg2 == NULL);
    
    if ( std::strcmp(arg, "wake") == 0 
      || std::strcmp(arg, "-w") == 0 ) {
        
        if (null) {
            std::cout << "No target for wake\n";
            return 0;
        } 

        ConfigParser test(WRITEFILE, Templ::templ, arg2);
        std::string macAddr = test.findInVector("mac: ");
        sendPacket(macAddr.c_str());
        return 1;
        

    } else if ( std::strcmp(arg, "version") == 0
             || std::strcmp(arg, "-v") == 0) {

        std::cout << "easyWOL Version 1.0\n";
        std::cout << "Alex Brachet\n";
        return 1;
    
    } else {
        std::cout << "Unrecognized command '" << arg << "' \nExiting...\n";
        return 0;
        //exit(1);
    }

    return 0;

}