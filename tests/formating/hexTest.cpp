#include<gtest/gtest.h>
#include<include/formating/hex.hpp>
TEST(HexTest,HexTest)
{
    hexFormating* hex = new hexFormating();
    std::vector<unsigned char> vctr = {72, 4, 5, 156, 229, 228, 36, 120, 68, 209, 239, 30, 71, 181, 240, 241, 64, 188, 179, 66, 168, 107, 37, 89, 39, 156, 133, 139, 120, 220, 192, 100};
    std::string str = hex->unsignedCharToHex(vctr);
    std::vector<unsigned char> res = hex->hexToUnsignedChar("4804059ce5e4247844d1ef1e47b5f0f140bcb342a86b2559279c858b78dcc064");
    EXPECT_EQ(str,"4804059ce5e4247844d1ef1e47b5f0f140bcb342a86b2559279c858b78dcc064");
    EXPECT_EQ(vctr,res);
}