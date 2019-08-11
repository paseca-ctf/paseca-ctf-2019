int check34(char chr) // valid: 114
{
    if (((((((((chr * 5) + 747) << 4) ^ 334) * 761) + 1093) - 229) ^ 1766) == 16191848)
        return 1;
    return 0;
}