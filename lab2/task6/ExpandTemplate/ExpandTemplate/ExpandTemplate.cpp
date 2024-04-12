# include <iostream>
# include <map>
# include <vector>
# include <string>
# include <queue>
#include <fstream>

using std::string;
using std::multimap;

class BorNode;
typedef std::map<const char, BorNode*> SufMap;

const int PARAMS_POSITION = 3;

class BorNode {
public:
    SufMap suf;
    BorNode* parent;  
    BorNode* term; 
    int out;

public:
    BorNode(BorNode* fail_node = NULL)
        : parent(fail_node)
        , term(NULL)
        , out(-1)
    { }

    BorNode* getLink(const char c) const
    {
        SufMap::const_iterator iter = suf.find(c);
        if (iter != suf.cend()) {
            return iter->second;
        }
        else {
            return NULL;
        }
    }

    bool isTerminal() const
    {
        return (out >= 0);
    }
};

class AhoCorasick
{
public:
    typedef void (*Callback) (const char* substr);
    BorNode root;
    std::vector<string> words;
    BorNode* current_state;

public:
    void addString(const string& str)
    {
        BorNode* current_node = &root;
        for (char cp : str) {
            BorNode* child_node = current_node->getLink(cp);
            if (!child_node) {
                child_node = new BorNode(&root);
                current_node->suf[cp] = child_node;
            }
            current_node = child_node;
        }
        current_node->out = words.size();
        words.push_back(str);
    }

    void init()
    {
        std::queue<BorNode*> q;
        q.push(&root);
        while (!q.empty()) {
            BorNode* current_node = q.front();
            q.pop();
            for (SufMap::const_iterator iter = current_node->suf.cbegin();
                iter != current_node->suf.cend(); ++iter)
            {
                const char symbol = iter->first;
                BorNode* child = iter->second;

                BorNode* temp_node = current_node->parent;
                while (temp_node) {
                    BorNode* fail_candidate = temp_node->getLink(symbol);
                    if (fail_candidate) {
                        child->parent = fail_candidate;
                        break;
                    }
                    temp_node = temp_node->parent;
                }

                if (child->parent->isTerminal()) {
                    child->term = child->parent;
                }
                else {
                    child->term = child->parent->term;
                }
                q.push(child);
            }
        }
    }

    void step(const char c)
    {
        while (current_state) {
            BorNode* candidate = current_state->getLink(c);
            if (candidate) {
                current_state = candidate;
                return;
            }
            current_state = current_state->parent;
        }
        current_state = &root;
    }

    bool printTermsForCurrentState(multimap<string, string>& dict, std::string& word)
    {
        string tempStr;
        if (current_state->isTerminal()) 
        {
            tempStr = words[current_state->out].c_str();
        }
        BorNode* temp_node = current_state->term;
        word = tempStr;
        while (temp_node) 
        {
            tempStr = words[temp_node->out].c_str();
            if (tempStr.size() > word.size())
            {
                word = tempStr;
            }
            temp_node = temp_node->term;
        }
        if (word.empty()) 
        {
            return false;
        }

        return true;
    }


    string search(const string& str, multimap<string, string> dict)
    {
        current_state = &root;
        string word;
        string longestWord;
        string responce;
        string temp;
        for (char c : str) {
            std::cout << c << std::endl;
            step(c);
            if ((printTermsForCurrentState(dict, word)) || word == " ")
            {
                if (longestWord.size() < word.size())
                {
                    longestWord = word;
                }
                else 
                {
                    word = c;
                    for (const auto& pair : dict)
                    {
                        if (pair.first == longestWord)
                        {
                            responce += pair.second + c;
                            longestWord = "";
                            current_state->out = 0;
                        }
                    }
                    responce += temp;
                }
            }
            else
            {
                temp += c;
            }
        }

        if (!word.empty())
        {
            for (const auto& pair : dict)
            {
                if (pair.first == word)
                {
                    responce += pair.second;
                }
            }
        }
        return responce;
    }
};


struct ConsoleArgs
{
    string inputFileName;
    string outputFileName;
    multimap<string, string> dict;
};

multimap<string, string> getParamsAndValues(int argc, const char* argv[])
{
    multimap<string, string> dict;
    try
    {
        for (int i = PARAMS_POSITION; i < argc; i += 2) 
        {
            std::string param = argv[i];
            std::string value;

            if (i + 1 < argc) 
            {
                value = argv[i + 1]; 
            }
            else
            {
                throw std::invalid_argument("Failed to get params with values.\nUsage: [<param> <value> [<param> <value> ...]");
            }

            dict.insert(std::make_pair(param, value)); 
        }
    }
    catch (const std::exception&)
    {
        throw std::invalid_argument("Failed to get params.");
    }

    return dict;
}


ConsoleArgs ParseArgs(int argc, const char* argv[])
{
    if (argc < 5)
    {
        throw std::invalid_argument("Invalid number of arguments.\nUsage: <input-file> <output-file [<param> <value> [<param> <value> …]");
    }

    ConsoleArgs args;

    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.dict = getParamsAndValues(argc, argv);

    return args;
}

void processLinesFromFile(AhoCorasick& ak, const ConsoleArgs& args)
{
    std::ifstream inputFile(args.inputFileName);
    std::ofstream outputFile(args.outputFileName);

    if (!inputFile.is_open())
    {
        throw std::runtime_error("Failed to open input file");
    }

    if (!outputFile.is_open())
    {
        throw std::runtime_error("Failed to open output file");
    }

    string str;
    string r;
    while (getline(inputFile, str))
    {
        r = ak.search(str, args.dict); // Пусть поисковик возвращает заменённую строку. Ему передать словарик.
        std::cout << r << std::endl;
        // Тут же функция записи в выходной файл.
        // Посмотреть на все фукнции ещё раз
    }

    if (!inputFile.eof())
    {
        throw std::runtime_error("Failed to read inputFile");
    }

    if (!outputFile.flush())
    {
        throw std::runtime_error("Failed save data on disk");
    }
   //    if (!(fileIn.eof))
     //  {
       //    throw std::invalid_argument("Failed to read data from file.");
       //}
    return;
}

int main(int argc, const char* argv[])
{
    try 
    {
        ConsoleArgs args = ParseArgs(argc, argv);
        AhoCorasick ak;
        for (const auto& pair : args.dict)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
            ak.addString(pair.first);
        }
        ak.init();

        processLinesFromFile(ak, args);

        return EXIT_SUCCESS;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}