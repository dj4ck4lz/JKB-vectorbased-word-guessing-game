/*Vector-based word guessing game*/

#include<algorithm>
#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<cctype>
#include<cstdlib>
#include<vector>
#include<iterator>
#include<random>
#include<chrono>

using std::cout;using std::cin;using std::endl;using std::vector;using std::string;

void randomizer(vector<string> &wordContent);
void wordHint(vector<string> wordContent,int i);
void wordHint2(vector<string> wordContent,int i);
void upperCase(vector<string> &wordContent, int wordSize);

int main()//start of the program
{
    string verify2;
    bool prog  = true;
    do
    {
        unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
        vector<string> words;

        string words_input, player_guess;
        int limit_input;
        int c = 1, occur = 0, word_guesses = 3;
        bool check, checking;
        string verify;

        do
        {
            cout<<"Enter the size of words you want to guess[min. 5 - max. 15]: ";
            cin>>limit_input;
            cin.clear();
            cin.ignore(10000, '\n');
        }while (limit_input<=0||limit_input>=16);

        system("cls");


        for (int i = 0;i<limit_input;i++)
        {

            occur = 0;
            cout<<"Enter the words you want to guess["<<i+1<<"/"<<limit_input<<"]: "<<endl;
            getline(cin>>std::ws, words_input);
            for (char space : words_input)
                if (space == ' ') occur++;
            while (occur>0)
            {
                occur = 0;
                cout<<"No spaces! Enter a word again:"<<endl;
                getline(cin>>std::ws, words_input);
                for (char space : words_input)
                    if (space == ' ') occur++;
            }
            words.push_back(words_input);
            cout<<c++<<".  "<<words_input<<endl;
        }
        int words_size = words.size();
        c=1;
        system("cls");
        cout<<"These are what you typed in, randomized: "<<endl;
        cout<<endl;
        upperCase(words,words_size);
        randomizer(words);
        for (auto word : words)
            cout<<c++<<".  "<<word<<endl;

        cout<<endl;
        do
        {
            c=1;
            checking = true;
            cout<<endl;
            cout<<"Randomize again? \"Y\" to do so, \"N\" to move on"<<endl;
            getline(cin>>std::ws, verify);
            system("cls");
            cout<<"These are what you typed in, randomized: "<<endl;
            cout<<endl;
            transform(verify.begin(),verify.end(),verify.begin(),tolower);
            if (verify=="y")
                {
                    randomizer(words);
                    for (auto word : words)
                        cout<<c++<<".  "<<word<<endl;
                }

            else if (verify=="n")
                checking = false;

        }while(checking==true);

        system("cls");

        cout<<"==TIME TO PLAY THE GUESSING GAME=="<<endl;


        for (int i=0;i<words_size;i++)
        {
            cout<<"The word has "<<words[i].length()<<" letters and starts with "<<words[i].at(0)<<endl;
            getline(cin>>std::ws, player_guess);
            transform(player_guess.begin(),player_guess.end(),player_guess.begin(),toupper);
            if (player_guess==words[i])
            {
                cout<<"==CORRECT=="<<endl;
                cout<<endl;
            }

            else
                word_guesses=4;
                while (player_guess!=words[i])
                {
                    word_guesses--;
                    cout<<"Not quite correct. "<<word_guesses<<" guesses left."<<endl;
                    getline(cin>>std::ws, player_guess);
                    transform(player_guess.begin(),player_guess.end(),player_guess.begin(),toupper);
                    if (player_guess==words[i])
                        {
                            cout<<"==CORRECT=="<<endl;
                            cout<<endl;
                            break;
                        }
                    else if (word_guesses==3)
                        wordHint(words,i);
                    else if (word_guesses==2)
                        wordHint2(words,i);

                    if (word_guesses==1)
                        {
                            cout<<"==WRONG=="<<endl;
                            cout<<endl;
                            break;
                        }

                }

            if (i==words_size-2&&i!=words_size-1)
                cout<<"Last word"<<endl;
            else if (i!=words_size-2&&i!=words_size-1)
                cout<<"Next word"<<endl;
        }
        cout<<endl;
        cout<<"==THANK YOU FOR PLAYING MY GAME=="<<endl;
        cout<<"Enter \"Y\" to play again, or \"N\" to quit the game"<<endl;

        getline(cin>>std::ws, verify2);
        transform(verify2.begin(),verify2.end(),verify2.begin(),toupper);

        if (verify2=="Y")
            prog==true;
        else if (verify2=="N")
            prog==false;
        system("cls");
    }while(prog==true);

    return 0;
}//end of the program

void randomizer(vector<string> &wordContent)
{
    unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(wordContent.begin(),wordContent.end(),std::default_random_engine(num));
}
void wordHint(vector<string> wordContent,int i)
{
    srand(time(0));
    unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
    int occurences = 0;
    int j = rand() % wordContent[i].length();
    char letter = wordContent[i].at(j);
    for (char l : wordContent[i])
        if (l == letter) occurences++;
    cout<<"One of the letters is \""<<letter<<"\" at placement "<<wordContent[i].find(letter)+1<<", and the letter occurs "<<occurences<<" times"<<endl;
}
void wordHint2(vector<string> wordContent,int i)
{

    if (wordContent[i].length()==1)
        cout<<"It's just one letter"<<endl;
    else
    {
        int length = wordContent[i].length();
        cout<<"Final hint: ";
        cout<<wordContent[i].front();
        for (int j=1;j<length;j++)
        {
            if (j!=1)
                cout<<" _ ";
        }
        cout<<wordContent[i].back()<<endl;
    }
}
void upperCase(vector<string> &wordContent, int wordSize)
{
    for (int i=0;i<wordSize;i++)
    {
        transform(wordContent[i].begin(),wordContent[i].end(),wordContent[i].begin(),toupper);
    }
}
