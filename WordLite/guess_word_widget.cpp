#include "guess_word_widget.h"
#include "ui_guess_word_widget.h"
#include "guess_according_to_description_h/guess_word.h"
#include <map>
#include <QMessageBox>
using namespace std;

guess_word_widget::guess_word_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::guess_word_widget)
{
    ui->setupUi(this);
    connectSignals();
    word="";
    translation="";
    description="";
    ui->displayTextEdit->setStyleSheet(
        "QTextEdit {"
        "   font-family: '微软雅黑';"
        "   font-size: 10pt;"
        "}"
        );
    // 设置按窗口宽度自动换行（默认模式）
    ui->displayTextEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    // 单词边界换行
    ui->displayTextEdit->setWordWrapMode(QTextOption::WordWrap);
    dialog=new QMessageBox();
}

guess_word_widget::~guess_word_widget()
{
    delete ui;
}

void guess_word_widget::connectSignals()
{
    connect(ui->exitButton, &QPushButton::clicked, this, &guess_word_widget::onExitButtonClicked);
    connect(ui->ruleButton,&QPushButton::clicked,this,&guess_word_widget::onRuleButtonClicked);
    connect(ui->beginButton, &QPushButton::clicked, this, &guess_word_widget::onBeginButtonClicked);
    connect(ui->answerButton,&QPushButton::clicked,this,&guess_word_widget::onAnswerButtonClicked);
    connect(ui->commitButton,&QPushButton::clicked,this,&guess_word_widget::onCommitButtonClicked);
}

void guess_word_widget::onExitButtonClicked()
{
    emit exitRequested();
}

void guess_word_widget::onRuleButtonClicked()
{
    QString rule="本游戏由DEEPSEEK-V3对从词库中随机抽取的单词生成描述，请你根据描述猜出是哪个词，如果查看答案会显示英文单词，deepseek生成解释的翻译以及里面重点词的意思，有以下文件夹可供选择："
                   "四六级词汇合集，四级词汇，六级词汇，GRE词汇，牛津词典词汇，小学英语词汇，中考英语词汇";
    ui->displayTextEdit->setText(rule);
}

void guess_word_widget::onBeginButtonClicked()
{
    guess_word *g=new guess_word();
    map<QString,QString> result=g->processingPython();
    word=result["word"];
    translation=result["translation"];
    description=result["description"];
    ui->displayTextEdit->setText(description+"\n请在下方输入你的答案"+"\n提示：这是开头的两个字母"+word[0]+word[1]);
}

void guess_word_widget::onAnswerButtonClicked()
{
    ui->displayTextEdit->setText(word+"\n"+translation);
}

void guess_word_widget::onCommitButtonClicked()
{
    QString text=ui->answerLineEdit->text();
    if (text=="" || word=="")
    {
        dialog->setWindowTitle("错误信息");
        dialog->setText("后端未运行或用户未输入");
    }
    else
    {
        if (text==word)
        {
            ui->displayTextEdit->setText("You Win!");
            text="";
        }
        else
        {
            ui->displayTextEdit->setText("I am sorry.Please try again.");
            text="";
        }
    }
}
