#include <array>
#include <iostream>
#include <gtest/gtest.h>

class BowlingGame
{
private:
    static constexpr int MAX_FRAMES = 10;  // Total number of frames in a game
    static constexpr int MAX_PINS = 10;    // Maximum pins per frame
    static constexpr int MAX_ROLLS = 21;   // Maximum possible rolls (including extra rolls in the 10th frame)
    static constexpr int STRIKE_BONUS_ROLLS = 2; // Bonus rolls after a strike
    static constexpr int SPARE_BONUS_ROLLS = 1;  // Bonus roll after a spare

    std::array<int, MAX_ROLLS> rolls{};   // Stores the number of pins knocked down in each roll
    int currentRoll = 0;                  // Tracks the current roll index

public:
    /**
     * @brief Records the number of pins knocked down in a roll.
     * @param pins The number of pins knocked down.
     */
    void roll(int pins)
    {
        if (currentRoll < MAX_ROLLS)
        {
            rolls[currentRoll++] = pins;
        }
    }

    /**
     * @brief Calculates the total score of the game based on the rolls.
     * @return The final score after all frames.
     */
    [[nodiscard]] int score() const
    {
        int totalScore = 0; // Total accumulated score
        int rollIndex = 0;  // Tracks the roll position in the rolls array

        for (int frame = 0; frame < MAX_FRAMES; ++frame)
        {
            if (isStrike(rollIndex)) // Strike
            {
                totalScore += MAX_PINS + strikeBonus(rollIndex);
                rollIndex += 1; // Move to the next frame (strike takes only one roll)
            }
            else if (isSpare(rollIndex)) // Spare
            {
                totalScore += MAX_PINS + spareBonus(rollIndex);
                rollIndex += 2; // Move to the next frame (spare takes two rolls)
            }
            else // Normal frame (not a strike or spare)
            {
                totalScore += frameScore(rollIndex);
                rollIndex += 2; // Move to the next frame (two rolls per frame)
            }
        }
        return totalScore;
    }

private:
    /**
     * @brief Checks if the current roll is a strike.
     * @param index The current roll index.
     * @return True if it's a strike, false otherwise.
     */
    [[nodiscard]] bool isStrike(int index) const
    {
        return rolls[index] == MAX_PINS;
    }

    /**
     * @brief Checks if the current frame is a spare.
     * @param index The current roll index.
     * @return True if it's a spare, false otherwise.
     */
    [[nodiscard]] bool isSpare(int index) const
    {
        return rolls[index] + rolls[index + 1] == MAX_PINS;
    }

    /**
     * @brief Calculates the strike bonus (sum of the next two rolls).
     * @param index The current roll index where the strike occurred.
     * @return The bonus points for the strike.
     */
    [[nodiscard]] int strikeBonus(int index) const
    {
        return rolls[index + 1] + rolls[index + STRIKE_BONUS_ROLLS];
    }

    /**
     * @brief Calculates the spare bonus (next roll's pins).
     * @param index The current roll index where the spare occurred.
     * @return The bonus points for the spare.
     */
    [[nodiscard]] int spareBonus(int index) const
    {
        return rolls[index + SPARE_BONUS_ROLLS + 1];
    }

    /**
     * @brief Calculates the frame score for a normal frame.
     * @param index The current roll index.
     * @return The total score for that frame.
     */
    [[nodiscard]] int frameScore(int index) const
    {
        return rolls[index] + rolls[index + 1];
    }
};

// ------------------------ UNIT TESTS USING GOOGLE TEST ------------------------

TEST(BowlingGameTest, GutterGame)
{
    BowlingGame game;
    for (int i = 0; i < 20; i++) // All rolls knock down 0 pins
    {
        game.roll(0);
    }
    ASSERT_EQ(game.score(), 0);
}

TEST(BowlingGameTest, AllOnes)
{
    BowlingGame game;
    for (int i = 0; i < 20; i++) // Each roll knocks down 1 pin
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
    game.roll(3); // Next roll (bonus for spare)
    for (int i = 0; i < 17; i++)
    {
        game.roll(0);
    }
    ASSERT_EQ(game.score(), 16);
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
    ASSERT_EQ(game.score(), 24);
}

TEST(BowlingGameTest, PerfectGame)
{
    BowlingGame game;
    for (int i = 0; i < 12; i++) // 12 consecutive strikes
    {
        game.roll(10);
    }
    ASSERT_EQ(game.score(), 300);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
