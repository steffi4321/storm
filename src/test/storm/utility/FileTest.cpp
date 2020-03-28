#include "test/storm_gtest.h"
#include "storm-config.h"

#include "storm/utility/file.h"

TEST(FileTest, GetLine) {
    std::stringstream stream;
    stream << "Hello world" << std::endl << "This is a test with n\nThis is a test with rn\r\n\nMore tests";

    std::string str;
    int i = 0;
    std::string expected[] = {"Hello world", "This is a test with n", "This is a test with rn", "", "More tests"};
    while (storm::utility::getline(stream, str)) {
        EXPECT_EQ(str, expected[i]);
        ++i;
    }
}


TEST(FileTest, GetLineEmpty) {
    std::stringstream stream;
    std::string str;
    EXPECT_FALSE(storm::utility::getline(stream, str));
}
