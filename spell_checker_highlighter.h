#ifndef SPELL_CHECKER_HIGHLIGHTER_H
#define SPELL_CHECKER_HIGHLIGHTER_H

#include "spell_checker.h"

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

class spell_checker_highlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit spell_checker_highlighter(QTextDocument *parent, spell_checker *checker);

protected:
    void highlightBlock(const QString &text) override;

private:
    spell_checker *checker_;
    QTextCharFormat misspelled_format_;
};

#endif // SPELL_CHECKER_HIGHLIGHTER_H
