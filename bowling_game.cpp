#include <iostream>
#include <vector>
#include <gtest/gtest.h>

class BowlingGame
{
private:
    std::vector<int> rolls;

public:
    void roll(int pins)
    {
        rolls.push_back(pins);
    }

    int score()
    {
        int totalScore = 0;
        int rollIndex = 0;

        for (int frame = 0; frame < 10; ++frame)
        {
            if (isStrike(rollIndex))
            { // Strike case
                totalScore += 10 + strikeBonus(rollIndex);
                rollIndex += 1; // Strike moves to next frame
            }
            else if (isSpare(rollIndex))
            { // Spare case
                totalScore += 10 + spareBonus(rollIndex);
                rollIndex += 2;
            }
            else
            { // Open frame
                totalScore += frameScore(rollIndex);
                rollIndex += 2;
            }
        }
        return totalScore;
    }

private:
    bool isStrike(int index)
    {
        return rolls[index] == 10;
    }

    bool isSpare(int index)
    {
        return rolls[index] + rolls[index + 1] == 10;
    }

    int strikeBonus(int index)
    {
        return rolls[index + 1] + rolls[index + 2];
    }

    int spareBonus(int index)
    {
        return rolls[index + 2];
    }

    int frameScore(int index)
    {
        return rolls[index] + rolls[index + 1];
    }
};

// Google Test Cases
TEST(BowlingGameTest, GutterGame)
{
    BowlingGame game;
    for (int i = 0; i < 20; i++)
    {
        game.roll(0);
    }
    ASSERT_EQ(game.score(), 0);
}

TEST(BowlingGameTest, AllOnes)
{
    BowlingGame game;
    for (int i = 0; i < 20; i++)
    {
        game.roll(1);
    }
    ASSERT_EQ(game.score(), 20);
}

TEST(BowlingGameTest, OneSpare)
{
    BowlingGame game;
    game.roll(5);
    game.roll(5); // Spare
    game.roll(3);
    for (int i = 0; i < 17; i++)
    {
        game.roll(0);
    }
    ASSERT_EQ(game.score(), 16); // 10 + 3 + 3 = 16
}

TEST(BowlingGameTest, OneStrike)
{
    BowlingGame game;
    game.roll(10); // Strike
    game.roll(3);
    game.roll(4);
    for (int i = 0; i < 16; i++)
    {
        game.roll(0);
    }
    ASSERT_EQ(game.score(), 24); // 10 + (3+4) + 3 + 4 = 24
}

TEST(BowlingGameTest, PerfectGame)
{
    BowlingGame game;
    for (int i = 0; i < 12; i++)
    {
        game.roll(10); // 12 strikes for a perfect game
    }
    ASSERT_EQ(game.score(), 300);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
