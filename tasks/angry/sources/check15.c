int check15(char chr) // valid: 115
{
    if (((((((((chr * 1) + 1600) << 3) ^ 3529) * 103) + 1199) - 839) ^ 3850) == 1484533)
        return 1;
    return 0;
}