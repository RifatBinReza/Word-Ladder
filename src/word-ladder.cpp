/*File: word-ladder.cpp
 * This program can find the shortest path of two different words, changing one letter at a time
 * but keeping all the words meaningful.
 * Uses dictionary to find meaningful words
 *
 * ====================================
 * || @author: Rifat Bin Reza        ||
 * ||                                ||
 * || Email: rifatbinreza@gmail.com  ||
 * ||                                ||
 * ====================================
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "stack.h"
#include "queue.h"
#include "set.h"

//Function Prototypes
static string getWord(Lexicon& english, string prompt);
static void playladder();
void generateLadder(Lexicon& english, string startWord, string endWord);

int main() {
    cout << "Welcome to the CS225 word ladder application!" << endl << endl;
    playladder(); //starts the playladder function which runs the game
    cout << "Thanks for playing!" << endl;
    return 0;
}

static string getWord(Lexicon& english, string prompt) { //takes words as input from the user
    while (true) {
        string response = trim(toLowerCase(getLine(prompt))); //converts the word to lower case
        if (response.empty() || english.contains(response)) return response; //takes the word
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}
//file that contains a specific list of words
static const string kEnglishLanguageDatafile = "EnglishWords.dat";

//starts the playladder() function
static void playladder() {
    Lexicon english(kEnglishLanguageDatafile); //Lexicon variable english takes the word list file as its input
    while (true) { //loops the program until the user quits
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        generateLadder(english, start, end); //generates the ladder for given two words
    }
}

/* Function void generateLadder()
 * This function figures out the 'ladder' which is the closest path of matching two different words
 */

void generateLadder(Lexicon &english, string startWord, string endWord){
    //taking a string Stack as the value of Queue and making the variable name ladder
    Queue< Stack<string> > ladder;
    //this set will contain all the words that has already been used
    Set<string> alreadyUsed;
    string alphabet = "abcdefghijklmnopqrstuvwxyz"; //list of the alphabets to use when we change the letters in a loop
    alreadyUsed.add(endWord); //end word is already in the list so we will exclude that
    Stack<string> stackOfWords;
    stackOfWords.push(endWord); //this contains the found words
    ladder.enqueue(stackOfWords); //ladder stores all the matching words

    while (!ladder.isEmpty()) //when the ladder Queue is not empty
    {
        Stack<string> stackOfWords = ladder.peek(); //copies the last element from the ladder but keeps the original there
        ladder.dequeue(); //ladder getting the words back

        string temporaryWords = stackOfWords.peek(); //this will store some temporary words
        for (int i=0;i<temporaryWords.length();i++)
        {
            string temporaryFirstWord = temporaryWords; //assigns temporaryWords to temporaryFirstWord
            for (char charecters: alphabet) //checks through all the alphabets
            {
                temporaryFirstWord[i] = charecters;
                //if the english Lexicon contains the words found
                if (english.contains(temporaryFirstWord)) {
                    if(!alreadyUsed.contains(temporaryFirstWord)) {
                        alreadyUsed.add(temporaryFirstWord);
                        if (temporaryFirstWord == startWord) {
                            //if the temporary word matches the start words then it'll be
                            //pushed into stackOfWords
                            stackOfWords.push(temporaryFirstWord);

                            cout << "A ladder from " << startWord << " to " << endWord << ":" << endl;

                            //if stackOfWords is not empty
                            while (!stackOfWords.isEmpty())
                            {
                                cout << stackOfWords.peek() << ">"; //adds one word and a > sign at a time
                                stackOfWords.pop(); //pops the next word from the stack
                            }
                            //goes the the next line
                            cout<<""<<endl;
                            return;
                        } else {
                            //if the temporary word doesn't matches the start word, make a copy of stackOfWords
                            Stack<string> clone = stackOfWords;
                            clone.push(temporaryFirstWord); //now push the temporaryFirstWord into clone
                            ladder.enqueue(clone); //put the values of clone into ladder
                        }
                    }
                }
            }
        }
    }
}
