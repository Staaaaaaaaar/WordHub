#include "wordle.h"
#include "ui_wordle.h"
#include <random>
#include <QFile>
#include <vector>
#include <QLabel>
#include <QDebug>
#include <QFont>
using namespace std;

Wordle::Wordle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Wordle)
{
    ui->setupUi(this);
    connect(ui->exitButton,&QPushButton::clicked,this,&Wordle::onExitButtonClicked);
    connect(ui->beginButton,&QPushButton::clicked,this,&Wordle::game);
    connect(ui->commitButton,&QPushButton::clicked,this,&Wordle::getText);
    connect(ui->restartButton,&QPushButton::clicked,this,&Wordle::restart);
    connect(ui->checkButton,&QPushButton::clicked,this,&Wordle::displayWord);
    loadWord();
    letterGrid.resize(6);
    letterGrid[0]={ui->a11,ui->a12,ui->a13,ui->a14,ui->a15};
    letterGrid[1]={ui->a21,ui->a22,ui->a23,ui->a24,ui->a25};
    letterGrid[2]={ui->a31,ui->a32,ui->a33,ui->a34,ui->a35};
    letterGrid[3]={ui->a41,ui->a42,ui->a43,ui->a44,ui->a45};
    letterGrid[4]={ui->a51,ui->a52,ui->a53,ui->a54,ui->a55};
    letterGrid[5]={ui->a61,ui->a62,ui->a63,ui->a64,ui->a65};
    for (int i=0;i<6;++i)
    {
        for (int j=0;j<5;++j)
        {
            letterGrid[i][j]->setStyleSheet("background-color: white; color: black;");
        }
    }
    currentCol=0;
    attempts=0;
    ui->commitButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    font=new QFont("Arial", 16, QFont::Bold);
}

Wordle::~Wordle()
{
    delete ui;
}

void Wordle::onExitButtonClicked()
{
    emit exitSignals();
}

void Wordle::loadWord()
{
    QFile file("D:\\vocabulary_learning\\WordLite\\wordle_base.txt"); // 如果放在资源文件中

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开单词文件：" << file.errorString();
        // 添加默认单词防止崩溃
        wordbase = {"APPLE", "GRAPE", "LEMON", "MELON", "PEACH"};
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed().toUpper();
        if (line.length() >= 5) {
            wordbase.push_back(line.left(5));
        }
    }
    file.close();

    qDebug() << "加载单词数量：" << wordbase.size();
}

void Wordle::selectRandomWord()
{
    std::random_device rd;

    // 2. 使用 Mersenne Twister 引擎（高质量随机数生成器）
    std::mt19937 gen(rd());

    // 3. 定义均匀整数分布 [1, 1000]
    std::uniform_int_distribution<int> dist(5, 1800);

    // 4. 生成随机数
    int random_num = dist(gen);
    target_word=wordbase[random_num];
    for (int i=0;i<5;++i)
    {
        letters.insert(target_word[i]);
    }

    qDebug()<<target_word;
}

void Wordle::game()
{
    selectRandomWord();
    ui->commitButton->setEnabled(true);
    ui->beginButton->setEnabled(false);
    ui->checkButton->setEnabled(true);
}

void Wordle::getText()
{
    text=ui->getWord->text().toUpper();
    ui->getWord->setText("");
    if (text.length()==5)
    {
        for (int i=0;i<5;++i)
        {
            letterGrid[currentCol][i]->setText(text[i]);
            letterGrid[currentCol][i]->setFont(*font);
        }
        attempts+=1;
        setColor();
        currentCol+=1;
        update();
    }
}

void Wordle::setColor()
{
    int all_right=0;
    for (int i=0;i<5;++i)
    {
        if (letterGrid[currentCol][i]->text()==target_word[i])
        {
            letterGrid[currentCol][i]->setStyleSheet("background-color: green; color: red;");
            all_right+=1;
        }
        else if (letters.contains(letterGrid[currentCol][i]->text()))
        {
            letterGrid[currentCol][i]->setStyleSheet("background-color: yellow; color: purple;");
        }
        else
        {
            letterGrid[currentCol][i]->setStyleSheet("background-color: white; color: black;");
        }
    }
    if (all_right==5 || attempts==6)
    {
        game_over=true;
        ui->winLabel->setText("WIN!!");
        ui->winLabel->setFont(*font);
        ui->getWord->setEnabled(false);
    }
}

void Wordle::restart()
{
    for (int i=0;i<6;++i)
    {
        for (int j=0;j<5;++j)
        {
            letterGrid[i][j]->setStyleSheet("background-color: white; color: black;");
            letterGrid[i][j]->setText("");
        }
    }
    currentCol=0;
    text="";
    letters.clear();
    game_over=false;
    attempts=0;
    ui->commitButton->setEnabled(false);
    ui->beginButton->setEnabled(true);
    ui->checkButton->setEnabled(false);
    ui->getWord->setEnabled(true);
    ui->winLabel->setText("");
    update();
}

void Wordle::displayWord()
{
    ui->winLabel->setText(target_word);
    ui->winLabel->setFont(*font);
}
