int check33(char chr) // valid: 103
{
    if (((((((((chr * 9) + 93) << 1) ^ 1869) * 658) + 1124) - 701) ^ 227) == 119298)
        return 1;
    return 0;
}