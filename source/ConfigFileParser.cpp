#ifndef CONFIG_FILE_PARSER
#define CONFIG_FILE_PARSER
    
    
#include "WOL.hpp"

#define WRITEFILE "easyWOL-config.txt"



class ConfigParser {
    private:
        std::ifstream _readFile;
        Template _tmpl; 
        //vector of strings filled with lines associated with the found alias
        std::vector<std::string> _entry;

    public:
        ConfigParser(std::string fileName, Template& tmpl) :  _readFile(fileName), _tmpl(tmpl)
        {}
        
        ConfigParser(std::string fileName, Template& tmpl, std::string find)
        :  _readFile(fileName), _tmpl(tmpl)
        {
            loadEntry(find);
        }

        //finds entry and loads it into _entry vecotr
        //findInEntry() will search through this vector

        //void functions probably in the future, in the context of the 
        //program will be booleans. 
        void loadEntry(const std::string find)
        {
            //gets the first line in the template map which will be alias
            std::string firstLine = _tmpl.firstLine();
            //|alias: | length 7
            std::string compare;
            while ( std::getline(_readFile, compare) ) {
        

                compare = compare.substr(firstLine.length(), compare.length());
                if (find == compare) {
                    //std::string temp;
                    //std::getline(_readFile, temp);
                    //std::cout << temp << '\n';
                    break;
                }   
            }

            //i is so that only the wanted entry is read and put into the vector
            //althought it wouldnt matter I suppose because those sections of the
            //vector would never be looked at as they would be longer than the template
            // length

            //@todo should only push back after the ": "
            //so the vector should not have "mac: 12:34...", only "12:34..."
            int i = 0;
            while( std::getline(_readFile, compare) && i < _tmpl.length() - 1) {
                _entry.push_back(compare);
                i++;
            }

            //perhaps not the most elegent way to see if it was found
            if (_entry.empty())  {
                std::cout << "'" << find << "' not found.\nExiting...\n";
                exit(1);
            }
        }

        void printVector()
        {
            //for (auto i = _entry.begin(); i != _entry.end(); i++)
            //    std::cout << *i;
            for (int i = 0; i < _entry.size(); i++){
                std::cout << _entry[i] << '\n';
            }
        }

        //to correspond better with the template, num 0 will be alias
        //whcih is not in the _entry vector so num will be num-- when
        //referencing the _entry vector. ie "mac" is at 0
        //
        //the perhaps complexity shouldnt be too big a deal given it is
        //more or less a private function
        //it is usually just a helper method for findInVector(std::string)
        std::string findInVector(int num, const int tempStrLen)
        {   
            if (num == 0) num = 1;
            /*
            //maybe bad practice
            if (num == 0)
                return _entry[0]; //in case of 0 wont be _entry[-1]
            

            return _entry[--num]; 
            */
            std::string str = _entry[--num];
            str = str.substr(tempStrLen, str.length());

            return str;

        }

        std::string findInVector(std::string str)
        {
            
            //std::cout << std::distance(_tmpl._map.begin(), _tmpl._map.find(str));
            
            int count = 0;
            for (templateMap::const_iterator i = _tmpl._map.begin(); i != _tmpl._map.end(); i++, count++) {
                //std::cout << i->first << "associated with index: " << count << '\n';
                if (i->first == str)
                    return findInVector(count, i->first.length());
            }
            
            return "";
        }
        //finds value associated with a keyword like "alias" or "mac"
        //deprecated.
        //Kept just in case for now
        //should be removed later
        std::string find(std::string find)
        {
            std::string temp;
            const char* str = temp.c_str();
            while ( std::getline(_readFile, temp) ) {
        
                
                const char* cmp = find.c_str();

                if ( ! strncmp(str, cmp, find.length()) )
                    return temp.substr(find.length() + 2);
            }

            return "'" + find + "' not found\n";
           
        }


};
namespace Templ {
    // accepts all inputs
    bool optional(std::string str) { return true; }

    //used when something is required but no checks on what exactly
    bool looseRequire(std::string str) 
    {
        if (str.length() > 0)
            return true;
        
        return false;
    }


    bool mac(std::string str)
    {
        if (str.length() != 17)
            return false;

        return true;
    }

    static Template myTemplate() 
    {
        static templateMap toIns;
        toIns["alias: "] = looseRequire;
        toIns["mac: "] = mac;
        return Template(toIns);
    }

    Template templ = myTemplate();

}
#endif /* CONFIG_FILE_PARSER */
/*
int main()
{
    ConfigParser test(WRITEFILE, Templ::templ, "desktop");

    std::string macAddr = test.findInVector("mac: ");

    sendPacket(macAddr.c_str());

}
*/