int check14(char chr) // valid: 49
{
    if (((((((((chr * 1) + 1135) << 3) ^ 2916) * 364) + 582) - 753) ^ 343) == 4322514)
        return 1;
    return 0;
}