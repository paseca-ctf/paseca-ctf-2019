int check6(char chr) // valid: 97
{
    if (((((((((chr * 10) + 62) << 4) ^ 1824) * 1691) + 1552) - 175) ^ 343) == 31007254)
        return 1;
    return 0;
}