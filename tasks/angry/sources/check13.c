int check13(char chr) // valid: 104
{
    if (((((((((chr * 8) + 1622) << 2) ^ 2701) * 869) + 678) - 1394) ^ 3322) == 9969863)
        return 1;
    return 0;
}