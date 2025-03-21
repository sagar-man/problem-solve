#include <iostream>
#include <vector>
#include <limits> // Required for numeric_limits

// Constants for better readability
const int FRAMES_PER_GAME = 10;
const int PINS_PER_FRAME = 10;

// Function to calculate the score of a single frame
int calculateFrameScore(const std::vector<int>& rolls, int frameIndex, int frame)
{
    if (rolls[frameIndex] == PINS_PER_FRAME) // Strike
    {
        if (frame == FRAMES_PER_GAME - 1) // 10th frame, no bonus
        {
            return PINS_PER_FRAME;
        }
        else
        {
            return PINS_PER_FRAME + rolls[frameIndex + 1] + rolls[frameIndex + 2];
        }
    }
    else if (rolls[frameIndex] + rolls[frameIndex + 1] == PINS_PER_FRAME) // Spare
    {
        if (frame == FRAMES_PER_GAME - 1) // 10th frame, no bonus
        {
            return PINS_PER_FRAME;
        }
        else
        {
            return PINS_PER_FRAME + rolls[frameIndex + 2];
        }
    }
    else // Open frame
    {
        return rolls[frameIndex] + rolls[frameIndex + 1];
    }
}

// Function to calculate the total score of a bowling game
int calculateBowlingScore(const std::vector<int>& rolls)
{
    int score = 0;
    int frameIndex = 0;
    for (int frame = 0; frame < FRAMES_PER_GAME; ++frame)
    {
        score += calculateFrameScore(rolls, frameIndex, frame);
        if (rolls[frameIndex] == PINS_PER_FRAME) // Strike
        {
            frameIndex++;
        }
        else
        {
            frameIndex += 2;
        }
    }
    return score;
}

int main()
{
    std::vector<int> rolls;
    int roll;

    std::cout << "Enter the bowling scores for each roll (enter a non-number to end):\n";
    while (std::cin >> roll)
    {
        if (roll < 0 || roll > 10)
        {
            std::cout << "Invalid input. Rolls must be between 0 and 10.  Please re-enter.\n";
            std::cin.clear(); // Clear error flags.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input.
        }
        else
        {
            rolls.push_back(roll);
        }
    }
    if (std::cin.fail())
    {
        std::cin.clear();                 // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the remaining invalid input
    }


    if (rolls.empty())
    {
        std::cout << "No rolls were entered. Exiting.\n";
        return 1;
    }

    int totalScore = calculateBowlingScore(rolls);
    std::cout << "Total score: " << totalScore << std::endl;

    return 0;
}
