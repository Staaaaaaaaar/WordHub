# include "../back_head/utils.h"

QDebug operator<<(QDebug o, const Word& w) {
    o << "\n------------------------ Word Information ------------------------\n";

    // 基本信息
    o << "Word: " << w.word << "\n";
    o << "ID: " << w.id << "\n";
    o << "Last Reviewed: " << w.lastReviewed.toString("yyyy-MM-dd hh:mm:ss") << "\n";
    o << "Review Count: " << w.reviewCount << "\n";
    o << "Difficulty: " << w.difficulty << "\n";

    // 音标信息（非空时显示）
    if (!w.phonetics.isEmpty()) {
        o << "\nPhonetics (" << w.phonetics.size() << " items):\n";
        for (const Phonetic& ph : w.phonetics) {
            o << "  Text: " << ph.text << "\n";
            if (!ph.audio.isEmpty()) {
                o << "    Audio: " << ph.audio << "\n";
            }
        }
    }

    // 释义信息（非空时显示，Qt 6 QMap遍历）
    if (!w.meanings.isEmpty()) {
        o << "\nMeanings (" << w.meanings.size() << " parts of speech):\n";
        int posIdx = 1;
        // 遍历QMap的键值对（Qt 6兼容）
        for (auto it = w.meanings.begin(); it != w.meanings.end(); ++it, ++posIdx) {
            const QString& pos = it.key();
            const QVector<Definition>& defs = it.value();

            o << posIdx << ". Part of Speech: " << pos << "\n";
            o << "  Definitions (" << defs.size() << " items):\n";

            int defIdx = 1;
            for (const Definition& def : defs) {
                o << "    " << defIdx++ << ". Definition: " << def.definition << "\n";

                // 示例（非空时显示）
                if (!def.example.isEmpty()) {
                    o << "      Example: " << def.example << "\n";
                }
                // 同义词（非空时显示）
                if (!def.synonyms.isEmpty()) {
                    o << "      Synonyms: " << def.synonyms.join(", ") << "\n";
                }
                // 反义词（非空时显示）
                if (!def.antonyms.isEmpty()) {
                    o << "      Antonyms: " << def.antonyms.join(", ") << "\n";
                }
            }
        }
    }

    o << "--------------------------------------------------------------\n";
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

QString Word::getoneMeaning()
{
    QStringList res;
    for (auto it = meanings.constBegin(); it != meanings.constEnd(); ++it) {
        QString kind = it.key();
        QString meaning= it.value()[0].definition;
        res.append(kind+":"+meaning);
    }
    int total=res.size();
    int index=rand()%total;
    return res[index];
}














