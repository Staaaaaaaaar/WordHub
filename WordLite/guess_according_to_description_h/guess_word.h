#ifndef GUESS_WORD_H
#define GUESS_WORD_H

#include <QProcess>
#include <map>
using namespace std;

class guess_word
{
private:
    QProcess *pythonprocess;
public:
    guess_word();
    map<QString,QString> processingPython();
};

#endif // GUESS_WORD_H
