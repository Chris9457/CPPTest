// \brief Declaration of the class Glossary

#pragma once
#include <istream>
#include <vector>
#include <string>
#include <filesystem>
#include <optional>

namespace cpptest {

    /**
     * \brief Exception for glossary
     */
    class GlossaryException : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * \brief This class manages the glossary of a stream text
     */
    class Glossary {
    public:
        struct WordCount {
            std::string word;
            size_t count = 0;

            bool operator==(const WordCount &other) const;
        };
        using WordCounts = std::vector<WordCount>;

        Glossary(const std::filesystem::path &path);

        void extract();
        const WordCounts &getWordCounts() const;

        void exportToTable();
        void exportToReverse() const;

    private:
        static std::optional<std::string> extractWord(std::string &line);
        static std::string reverseWord(const std::string &word);

        std::filesystem::path m_path;
        WordCounts m_wordCounts;
    };
} // namespace cpptest
