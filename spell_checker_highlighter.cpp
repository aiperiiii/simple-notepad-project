#include "spell_checker_highlighter.h"

#include <QRegularExpression>

spell_checker_highlighter::spell_checker_highlighter(QTextDocument *parent, spell_checker *checker)
    : QSyntaxHighlighter(parent)
      , checker_(checker) {
    misspelled_format_.setUnderlineColor(Qt::red);
    misspelled_format_.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
}

void spell_checker_highlighter::highlightBlock(const QString &text) {
    if (!checker_) return;

    static const QRegularExpression word_pattern("\\b[A-Za-z']+\\b");
    auto it = word_pattern.globalMatch(text);

    while (it.hasNext()) {
        const auto match = it.next();
        if (!checker_->is_correct(match.captured().toStdString())) {
            setFormat(match.capturedStart(), match.capturedLength(), misspelled_format_);
        }
    }
}
