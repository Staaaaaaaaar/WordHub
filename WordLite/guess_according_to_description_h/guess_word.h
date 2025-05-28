#ifndef GUESS_WORD_H
#define GUESS_WORD_H

#include <QProcess>
using namespace std;

class guess_word
{
private:
    QProcess *pythonprocess;
public:
    guess_word();
    void processingPython();
};

#endif // GUESS_WORD_H
