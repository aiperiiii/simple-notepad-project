# Notepad Simple Project

## Optional features:

### 1. Cursor line / Column indicator
Three permanent `QLabel` widgets in the status bar show live **Words**, **Lines**, and **Ln / Col**.
Connected to `textChanged` and `cursorPositionChanged` signals of `QTextEdit`.

### 2. Color picker
Opens `QColorDialog`. Works the same way as the font dialog 
applies to selection or sets the current format.

### 3. Zoom
Zoom In / Zoom Out / Reset Zoom (`Ctrl++` / `Ctrl+-` / `Ctrl+0`).
Uses `QTextEdit::zoomIn()` and `zoomOut()`.

## Required features:

### Exception handling
`notepad_exception.h` defines the hierarchy from Practice 8.
`open_file()` and `save_file()` throw and catch these exceptions, showing
`QMessageBox::critical(this, "Error", ex.what())` on failure.

### Spell checker
- `spell_checker.h` loads `data/words.txt` (370 000 words) into an `unordered_set` for O(1)
  lookup. Words are also grouped by first character for fast suggestion search.
- `spell_checker_highlighter` subclasses `QSyntaxHighlighter` and underlines misspelled words
  in red using `SpellCheckUnderline` on every keystroke.
- Right-clicking a red-underlined word shows up to 5 suggestions computed with
  Levenshtein edit distance. Clicking a suggestion replaces the word.
- Check spelling manually re-runs `rehighlight()`.
