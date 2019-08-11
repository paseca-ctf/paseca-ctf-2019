int check10(char chr) // valid: 100
{
    if (((((((((chr * 8) + 84) << 4) ^ 2047) * 725) + 1466) - 662) ^ 3621) == 9051690)
        return 1;
    return 0;
}