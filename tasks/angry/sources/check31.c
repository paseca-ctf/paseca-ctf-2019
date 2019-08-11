int check31(char chr) // valid: 97
{
    if (((((((((chr * 4) + 1148) << 3) ^ 1102) * 791) + 444) - 1194) ^ 3493) == 10590129)
        return 1;
    return 0;
}