int check27(char chr) // valid: 121
{
    if (((((((((chr * 10) + 1715) << 5) ^ 670) * 91) + 1925) - 1757) ^ 3509) == 8553991)
        return 1;
    return 0;
}