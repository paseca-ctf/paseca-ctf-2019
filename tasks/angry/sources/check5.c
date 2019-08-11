int check5(char chr) // valid: 99
{
    if (((((((((chr * 8) + 1921) << 3) ^ 4078) * 1844) + 13) - 340) ^ 3455) == 43024654)
        return 1;
    return 0;
}