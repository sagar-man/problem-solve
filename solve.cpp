#include <iostream>
#include <vector>

int calculateBowlingScore(const std::vector<int>& rolls)
{
    int score = 0;
    int frameIndex = 0;
    for (int frame = 0; frame < 10; ++frame)
    {
        if (rolls[frameIndex] == 10)
        {
            score += 10 + rolls[frameIndex + 1] + rolls[frameIndex + 2];
            frameIndex++;
        }
        else if (rolls[frameIndex] + rolls[frameIndex + 1] == 10)
        {
            score += 10 + rolls[frameIndex + 2];
            frameIndex += 2;
        }
        else
        {
            score += rolls[frameIndex] + rolls[frameIndex + 1];
            frameIndex += 2;
        }
    }
    return score;
}

int main()
{
    std::vector<int> rolls = {1, 4, 4, 5, 6, 4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 6, 10, 2, 6};

    int totalScore = calculateBowlingScore(rolls);
    std::cout << "Total score: " << totalScore << std::endl;

    return 0;
}
