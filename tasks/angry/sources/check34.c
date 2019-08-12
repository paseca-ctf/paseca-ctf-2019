int check34(char chr) // valid: 114
{
    if (((((((((chr * 8) + 5) << 3) ^ 1381) * 639) + 958) - 626) ^ 1570) == 4219357)
        return 1;
    return 0;
}