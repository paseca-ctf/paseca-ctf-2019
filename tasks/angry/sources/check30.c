int check30(char chr) // valid: 95
{
    if (((((((((chr * 6) + 245) << 5) ^ 1312) * 429) + 1079) - 282) ^ 1366) == 10625419)
        return 1;
    return 0;
}