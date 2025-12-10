// Parker_Final.cpp
// Description: Terrance's QuickTranslate
// Author: Terrance Parker
// Date Modified: 12/10/2025

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

const int WORD_SIZE = 30;
const int MAX_WORDS = 500;
const int MAX_SENTENCE = 300;

struct WordPair
{
    char english[WORD_SIZE];
    char french[WORD_SIZE];
};

int loadVocab(WordPair vocab[]);
void saveAllVocab(WordPair vocab[], int size);
void translateSentence(WordPair vocab[], int size);
void addWord(WordPair vocab[], int &size);

int stringLength(char str[]);
bool stringsEqual(char str1[], char str2[]);
void stringCopy(char dest[], char src[]);

int main()
{
    WordPair *vocab = new WordPair[MAX_WORDS];
    int vocabSize;

    cout << "Loading vocabulary..." << endl;
    vocabSize = loadVocab(vocab);
    cout << vocabSize << " words loaded." << endl << endl;

    int choice;
    do
    {
        cout << "Terrance's QuickTranslate" << endl;
        cout << "1) Translate English to French" << endl;
        cout << "2) Add a new vocabulary word" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
            translateSentence(vocab, vocabSize);
        else if (choice == 2)
            addWord(vocab, vocabSize);

        cout << endl;
    } while (choice != 3);

    cout << "Thank you!" << endl;

    delete [] vocab;

    return 0;
}


int loadVocab(WordPair vocab[])
{
    ifstream engFile("english.txt");
    ifstream frFile("french.txt");
    int count = 0;

    while (!engFile.eof() && !frFile.eof() && count < MAX_WORDS)
    {
        engFile >> vocab[count].english;
        frFile >> vocab[count].french;

        if (!engFile.fail() && !frFile.fail())
            count++;
    }

    engFile.close();
    frFile.close();

    return count;
}

void saveAllVocab(WordPair vocab[], int size)
{
    ofstream engFile("english.txt");
    ofstream frFile("french.txt");

    for (int i = 0; i < size; i++)
    {
        engFile << vocab[i].english << endl;
        frFile << vocab[i].french << endl;
    }

    engFile.close();
    frFile.close();
}

void addWord(WordPair vocab[], int &size)
{
    char e[WORD_SIZE];
    char f[WORD_SIZE];

    cout << "Enter English word: ";
    cin.getline(e, WORD_SIZE);

    cout << "Enter French translation: ";
    cin.getline(f, WORD_SIZE);

    stringCopy(vocab[size].english, e);
    stringCopy(vocab[size].french, f);
    size++;

    saveAllVocab(vocab, size);

    cout << "Word added and saved." << endl;
}


void translateSentence(WordPair vocab[], int size)
{
    char sentence[MAX_SENTENCE];
    char word[WORD_SIZE];
    int wi = 0; // word index

    cout << "Enter a sentence to translate:" << endl;
    cin.getline(sentence, MAX_SENTENCE);

    cout << "Translation: ";

    for (int i = 0; sentence[i] != '\0'; i++)
    {
        if (isalpha(sentence[i]))
        {
            // Build up the current word, but don't overflow the buffer
            if (wi < WORD_SIZE - 1)
            {
                word[wi] = sentence[i];
                wi++;
            }
        }
        else
        {
            word[wi] = '\0';

            if (wi > 0)
            {
                bool found = false;

                // Search vocab for this word
                for (int j = 0; j < size; j++)
                {
                    if (stringsEqual(word, vocab[j].english))
                    {
                        cout << vocab[j].french;
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << word;   // unknown word stays as-is

                wi = 0; // reset for next word
            }

            cout << sentence[i];
        }
    }

    if (wi > 0)
    {
        word[wi] = '\0';
        bool found = false;

        for (int j = 0; j < size; j++)
        {
            if (stringsEqual(word, vocab[j].english))
            {
                cout << vocab[j].french;
                found = true;
                break;
            }
        }

        if (!found)
            cout << word;
    }

    cout << endl;
}


int stringLength(char str[])
{
    int c = 0;
    while (str[c] != '\0')
        c++;
    return c;
}

bool stringsEqual(char str1[], char str2[])
{
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);

    if (length1 != length2)
        return false;

    for (int i = 0; i < length1; i++)
        if (str1[i] != str2[i])
            return false;

    return true;
}

void stringCopy(char dest[], char src[])
{
    int i = 0;
    while ((dest[i] = src[i]) != '\0')
        i++;
}
