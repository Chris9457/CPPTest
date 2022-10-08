// \brief Declaration of the class Glossary

#include "Glossary.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <regex>
#include <filesystem>

namespace cpptest {

    namespace {
        constexpr char WORD_DELIMITERS[] = " '-,;.!?";
        constexpr char LETTER_REGEX[]    = "[a-zA-Zéèêàâëûùîçôöü]";
    } // namespace

    /*
     * \struct Glossary::WordCount
     */
    bool Glossary::WordCount::operator==(const WordCount &other) const {
        return word == other.word && count == other.count;
    }

    /*
     * \class Glossary
     */
    Glossary::Glossary(const std::filesystem::path &path) : m_path(path) {
    }

    void Glossary::extract() {
        if (!exists(m_path)) {
            throw GlossaryException("The file " + m_path.string() + " doesn't exist");
        }

        std::ifstream is(m_path);
        std::string line;

        while (std::getline(is, line)) { // extract line
            do {
                auto const word = extractWord(line);
                if (!word.has_value()) {
                    continue;
                }

                auto const itWord = std::find_if(
                    m_wordCounts.begin(), m_wordCounts.end(), [&word](auto const wordCount) { return wordCount.word == word; });
                if (itWord == m_wordCounts.end()) {
                    m_wordCounts.push_back({ word.value(), 1 });
                } else {
                    ++(itWord->count);
                }

            } while (!line.empty());
        }

        std::sort(m_wordCounts.begin(), m_wordCounts.end(), [](auto const lhs, auto const rhs) { return lhs.count > rhs.count; });
    }

    const Glossary::WordCounts &Glossary::getWordCounts() const {
        return m_wordCounts;
    }

    void Glossary::exportToTable() {
        if (m_wordCounts.empty()) {
            extract();
        }
        if (!exists(m_path)) {
            throw GlossaryException("The file " + m_path.string() + " doesn't exist");
        }

        std::ofstream os(m_path.parent_path() / (m_path.stem().string() + ".table.txt"));
        for (auto const &wordCount : m_wordCounts) {
            os << wordCount.word << "," << wordCount.count << std::endl;
        }
    }

    void Glossary::exportToReverse() const {
        if (!exists(m_path)) {
            throw GlossaryException("The file " + m_path.string() + " doesn't exist");
        }

        std::ofstream os(m_path.parent_path() / (m_path.stem().string() + ".reverse.txt"));

        std::ifstream is(m_path);
        std::string line;
        while (std::getline(is, line)) {
            do {
                auto const pos = line.find_first_of(WORD_DELIMITERS);
                auto word{ reverseWord(line.substr(0, pos)) };
                auto delimiter = pos < line.size() ? line[pos] : '\0';

                os << word;
                if (pos != std::string::npos) {
                    os << line[pos];
                    line = line.substr(pos + 1);
                } else {
                    line.clear();
                }
            } while (!line.empty());

            os << std::endl;
        }
    }

    std::optional<std::string> Glossary::extractWord(std::string &line) {
        static std::regex wordRegEx(std::string(LETTER_REGEX) + std::string(LETTER_REGEX) + "+");

        auto const pos = line.find_first_of(WORD_DELIMITERS);
        auto word{ line.substr(0, pos) };
        if (pos != std::string::npos) {
            line = line.substr(pos + 1);
        } else {
            line.clear();
        }

        if (!std::regex_match(word, wordRegEx)) {
            return {};
        }

        return word;
    }

    std::string Glossary::reverseWord(const std::string &word) {
        std::string reverseWord;
        for (auto it = word.rbegin(); it != word.rend(); ++it) {
            reverseWord.push_back(*it);
        }

        return reverseWord;
    }
} // namespace cpptest
