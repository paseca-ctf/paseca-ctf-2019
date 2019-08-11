int check12(char chr) // valid: 116
{
    if (((((((((chr * 9) + 1132) << 4) ^ 1867) * 1588) + 1506) - 1963) ^ 1147) == 58253064)
        return 1;
    return 0;
}