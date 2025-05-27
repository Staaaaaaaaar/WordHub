# include "../back_head/utils.h"

QDebug operator<<(QDebug o,const Word& w)
{
    o<<"__________________\n";
    o<<w.word<<"\n";
    o<<"id:"<<w.id<<"\n";
    o<<"meaning:"<<w.meaning<<"\n";
    o<<"pronunciation:"<<w.pronunciation<<"\n";
    o<<"example:"<<w.example<<"\n";
    o<<"difficulty:"<<w.difficulty<<"\n";
    o<<"reviewCount:"<<w.reviewCount<<"\n";
    o<<"lastReviewed:"<<w.lastReviewed<<"\n";
    o<<"__________________"<<"\n";
    return o;
}

QDebug operator<<(QDebug o,const Category c)
{
    o<<"__________________\n";
    o<<c.name<<"\n";
    o<<"id:"<<c.id<<"\n";
    o<<"description:"<<c.description<<"\n";
    o<<"__________________"<<"\n";
    return o;
}