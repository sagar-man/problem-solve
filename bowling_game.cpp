#include <array>
#include <iostream>
#include <gtest/gtest.h>

class BowlingGame
{
private:
    static constexpr int MAX_ROLLS = 21; // Max possible rolls in a game
    static constexpr int MAX_FRAMES = 10;
    std::array<int, MAX_ROLLS> rolls{}; // Initialize with 0s
    int currentRoll = 0;

public:
    void roll(int pins)
    {
        if (currentRoll < MAX_ROLLS)
        {
            rolls[currentRoll++] = pins;
        }
    }

    [[nodiscard]] int score() const
    {
        int totalScore = 0;
        int rollIndex = 0;

        for (int frame = 0; frame < MAX_FRAMES; ++frame)
        {
            if (isStrike(rollIndex))
            { // Strike
                totalScore += 10 + strikeBonus(rollIndex);
                rollIndex += 1;
            }
            else if (isSpare(rollIndex))
            { // Spare
                totalScore += 10 + spareBonus(rollIndex);
                rollIndex += 2;
            }
            else
            { // Normal frame
                totalScore += frameScore(rollIndex);
                rollIndex += 2;
            }
        }
        return totalScore;
    }

private:
    [[nodiscard]] bool isStrike(int index) const
    {
        return rolls[index] == 10;
    }

    [[nodiscard]] bool isSpare(int index) const
    {
        return rolls[index] + rolls[index + 1] == 10;
    }

    [[nodiscard]] int strikeBonus(int index) const
    {
        return rolls[index + 1] + rolls[index + 2];
    }

    [[nodiscard]] int spareBonus(int index) const
    {
        return rolls[index + 2];
    }

    [[nodiscard]] int frameScore(int index) const
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
