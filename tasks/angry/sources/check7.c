int check7(char chr) // valid: 123
{
    if (((((((((chr * 9) + 621) << 2) ^ 778) * 506) + 782) - 1409) ^ 18) == 3113283)
        return 1;
    return 0;
}