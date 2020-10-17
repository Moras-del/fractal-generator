#include <string>
using namespace std;

class CliManager
{
    private:
        int count;
        char** args;
    public:
        CliManager(int count, char** args);
        bool getFloat(float& var, string longVal, string shortVal);

};

CliManager::CliManager(int count, char** args)
{
    this->count = count;
    this->args = args;
}

bool CliManager::getFloat(float& var, string longVal, string shortVal)
{
    for(int i = 0; i < count; i++){
        string arg = args[i];
        if(arg.rfind(shortVal, 0) == 0 || arg.rfind(longVal, 0) == 0)
        {
            int index = arg.find("=")+1;
            string number = arg.substr(index, arg.size());
            var = stof(number);
            return true;
        }
    }
    return false;
}