#ifndef VERSION3
#define VERSION3

#include <iostream>
#include <map>
#include <vector>
#include <fstream>

typedef std::function<bool(const std::string&)> funct;
typedef std::map<std::string, funct> templateMap; 

class Entry;
class ConfigParser;

/**
 * @brief provides a template for for Entry and ConfigParser
 *        to use for creation and parsing. 
 * 
 * 
 * 
 * 
 * @todo Template::addToMap() to add to the map of an already init'd Template
 *       Similarly, it will make 
 */ 
class Template {
    friend class Entry;
    friend class ConfigParser;

    private:

        templateMap _map; //make private later and implement iterator

        
    public:
        //Template() : _map() {}

        Template(const templateMap& map) : _map(map)
        {}

        int length() const { return _map.size(); }

        void print() const
        {
            for (templateMap::const_iterator i = _map.begin(); i != _map.end(); i++)
                std::cout << i->first << '\n';
            
        }

        //void addToMap(templateMap) {}

        // templateMap::iterator begin() 
        // {
        //     //not currently used
        //     return _map.begin();
        // }

        std::string firstLine() const
        {
            return _map.begin()->first;
        }

        int numLines() const
        {
            return _map.size();
        }
};

class Entry {
    private:
        Template& _templ;
        std::vector<std::string> _vector;

    public:
        Entry(Template& templ) : _templ(templ)
        {}

        void AddEntry()
        {
            //bad, very bad, terrible even
            for (templateMap::const_iterator i = _templ._map.begin(); i != _templ._map.end(); i++) {
                std::cout << i->first;

                std::string returnStr = i->first;

                std::string in;
                std::cin >> in;

                //checks if entry is valid with the templates bool function
                if ( ! i->second(in)) {
                    std::cout << "incorrect " << i->first.substr(0, i->first.length() - 2) << "\n";
                    i--;
                } else {
                    returnStr += in + '\n';
                    _vector.push_back(returnStr);
                }
            }
        }
 
        void print() const
        {
            for (int i = 0; i < _vector.size(); i++)
                std::cout << _vector[i];
        }

        void writeToFile(std::ofstream& writeFile) const
        {
            std::cout << "Writing to writeFile. \n";
            for (int i = 0; i < _vector.size(); i++)
                //+build ignore              
                writeFile << _vector[i];
        }
};
#endif /* VERSION3 */