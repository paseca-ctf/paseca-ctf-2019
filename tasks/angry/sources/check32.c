int check32(char chr) // valid: 110
{
    if (((((((((chr * 4) + 1183) << 5) ^ 2938) * 24) + 789) - 512) ^ 1133) == 1188840)
        return 1;
    return 0;
}