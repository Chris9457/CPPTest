#include "Glossary.h"
#include "gtest/gtest.h"
#include <fstream>

namespace cpptest::test {

    class CPP_Test_Reverse_UnitTest : public testing::Test {
    protected:
        void SetUp() override {
            Test::SetUp();

            std::ifstream ifs(EXPECTED_TABLE_FILE);
            std::string line;
            while (std::getline(ifs, line)) {
                std::string wordCount;
                std::istringstream iss(line);

                std::getline(iss, wordCount, ',');
                auto const word = wordCount;

                std::getline(iss, wordCount);
                auto const count = std::stoul(wordCount);

                m_expectedTable.push_back({ word, count });
            }
        }

        auto getExpectedTable() const {
            return m_expectedTable;
        }

        static auto convertFileToString(const std::string &fileName) {
            std::ifstream ifs(fileName);
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            return buffer.str();
        }

    private:
        Glossary::WordCounts m_expectedTable;
    };

    TEST_F(CPP_Test_Reverse_UnitTest, extract) {
        Glossary glossary(SAMPLE_FILE);
        ASSERT_NO_THROW(glossary.extract());
        ASSERT_EQ(getExpectedTable(), glossary.getWordCounts());
    }

    TEST_F(CPP_Test_Reverse_UnitTest, extract_file_not_exists) {
        Glossary glossary(BAD_SAMPLE_FILE);
        ASSERT_THROW(glossary.extract(), GlossaryException);
    }

    TEST_F(CPP_Test_Reverse_UnitTest, exportToTable) {
        Glossary glossary(SAMPLE_FILE);
        ASSERT_NO_THROW(glossary.exportToTable());
        ASSERT_TRUE(exists(std::filesystem::path(SAMPLE_TABLE_FILE)));
        ASSERT_EQ(convertFileToString(EXPECTED_TABLE_FILE), convertFileToString(SAMPLE_TABLE_FILE));
    }

    TEST_F(CPP_Test_Reverse_UnitTest, exportToTable_file_not_exists) {
        Glossary glossary(BAD_SAMPLE_FILE);
        ASSERT_THROW(glossary.exportToTable(), GlossaryException);
    }

    TEST_F(CPP_Test_Reverse_UnitTest, exportToReverse) {
        Glossary glossary(SAMPLE_FILE);
        glossary.exportToReverse();

        ASSERT_TRUE(exists(std::filesystem::path(SAMPLE_REVERSE_FILE)));
        ASSERT_EQ(convertFileToString(EXPECTED_REVERSE_FILE), convertFileToString(SAMPLE_REVERSE_FILE));
    }

    TEST_F(CPP_Test_Reverse_UnitTest, exportToReverse_file_not_exists) {
        Glossary glossary(BAD_SAMPLE_FILE);
        ASSERT_THROW(glossary.exportToReverse(), GlossaryException);
    }
} // namespace cpptest::test
