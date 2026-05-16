#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class spell_checker {
public:
    explicit spell_checker(const std::string &word_list_path) {
        std::ifstream file(word_list_path);
        std::string word;

        while (std::getline(file, word)) {
            if (!word.empty()) {
                words_.insert(word);
                by_first_[word[0]].push_back(word);
            }
        }
    }

    [[nodiscard]] bool is_correct(const std::string &word) const {
        const std::string norm = normalize(word);
        if (norm.empty()) return true;
        return words_.count(norm) > 0;
    }

    [[nodiscard]] std::vector<std::string> suggestions(const std::string &word, int max = 5) const {
        const std::string norm = normalize(word);
        if (norm.empty()) return {};

        const char first = norm[0];
        auto it = by_first_.find(first);
        if (it == by_first_.end()) return {};

        const int target_len = static_cast<int>(norm.size());
        std::vector<std::string> result;

        for (const auto &candidate: it->second) {
            const int len_diff = std::abs(static_cast<int>(candidate.size()) - target_len);
            if (len_diff > 2) continue;
            if (edit_distance(norm, candidate) <= 2) {
                result.push_back(candidate);
                if (static_cast<int>(result.size()) >= max) break;
            }
        }

        return result;
    }

private:
    std::unordered_set<std::string> words_;
    std::unordered_map<char, std::vector<std::string> > by_first_;

    [[nodiscard]] static std::string normalize(const std::string &word) {
        std::string result;
        for (const unsigned char c: word) {
            if (std::isalpha(c)) {
                result += static_cast<char>(std::tolower(c));
            }
        }
        return result;
    }

    [[nodiscard]] static int edit_distance(const std::string &a, const std::string &b) {
        const int m = static_cast<int>(a.size());
        const int n = static_cast<int>(b.size());
        std::vector<std::vector<int> > dp(m + 1, std::vector<int>(n + 1));

        for (int i = 0; i <= m; ++i) dp[i][0] = i;
        for (int j = 0; j <= n; ++j) dp[0][j] = j;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = (a[i - 1] == b[j - 1])
                               ? dp[i - 1][j - 1]
                               : 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }

        return dp[m][n];
    }
};

#endif // SPELL_CHECKER_H
