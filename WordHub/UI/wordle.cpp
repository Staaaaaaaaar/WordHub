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
    connect(ui->exitButton, &QPushButton::clicked, this, &Wordle::onExitButtonClicked);

    // 错误：删除合并按钮的连接
    // connect(ui->gameControlButton, &QPushButton::clicked, this, &Wordle::onGameControlButtonClicked);

    // 正确：恢复对两个独立按钮的连接
    connect(ui->beginButton, &QPushButton::clicked, this, &Wordle::game);
    connect(ui->restartButton, &QPushButton::clicked, this, &Wordle::restart);

    connect(ui->commitButton, &QPushButton::clicked, this, &Wordle::getText);
    connect(ui->checkButton, &QPushButton::clicked, this, &Wordle::displayWord);
    connect(ui->getWord, &QLineEdit::returnPressed, this, &Wordle::getText);
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
            letterGrid[i][j]->setStyleSheet("background-color: #222222;");
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
    QFile file(QCoreApplication::applicationDirPath() + "/codes/wordle_base.txt");

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
    ui->beginButton->setEnabled(false); // <--- 恢复这行代码，防止在游戏中重复开始
    ui->checkButton->setEnabled(true);

    // 成就
    emit sendId(4);
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
        QString letter = letterGrid[currentCol][i]->text();
        if (letter == target_word[i])
        {
            // 位置正确：主题橙色底，白色字
            letterGrid[currentCol][i]->setStyleSheet("background-color: #e67e22; color: #ffffff;");
            all_right+=1;
        }
        else if (target_word.contains(letter))
        {
            // 单词中有但位置不对：深灰底，主题橙色字
            letterGrid[currentCol][i]->setStyleSheet("background-color: #222222; color: #e67e22;");
        }
        else
        {
            // 单词中没有：黑底，灰字
            letterGrid[currentCol][i]->setStyleSheet("background-color: #000000; color: #808086;");
        }
    }
    if (all_right==5 || attempts==6)
    {
        game_over=true;
        /*ui->winLabel->setText("WIN!!");*/
        /*修改了乱win的问题*/
        if (attempts!=6)
        {
            ui->winLabel->setText("WIN!!");
        }
        else
        {
            ui->winLabel->setText("GAME OVER!!");
        }
        ui->winLabel->setFont(*font);
        ui->getWord->setEnabled(false);
        // --- 新增代码 ---
        // 游戏结束后，也应禁用“查看答案”按钮
        ui->checkButton->setEnabled(false);
    }
}

void Wordle::restart()
{
    // 1. 重置游戏面板的视觉效果
    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<5; ++j)
        {
            letterGrid[i][j]->setStyleSheet("background-color: #222222;");
            letterGrid[i][j]->setText("");
        }
    }

    // 2. 重置所有游戏状态变量
    currentCol=0;
    text="";
    letters.clear();
    game_over=false;
    attempts=0;

    // 3. 重置UI元素（简化版）
    ui->winLabel->setText("");
    ui->getWord->setEnabled(true); // 确保输入框可用
    update();

    // 4. 立即开始一局新游戏
    // game() 函数会自动处理好所有按钮的状态
    game(); 
}

void Wordle::displayWord()
{
    ui->winLabel->setText(target_word);
    ui->winLabel->setFont(*font);

    // 禁用输入框和提交按钮，以阻止用户在查看答案后继续游戏
    ui->getWord->setEnabled(false);
    ui->commitButton->setEnabled(false);
    // --- 新增代码 ---
    // 查看答案后，也应禁用“查看答案”按钮自身
    ui->checkButton->setEnabled(false);
}


