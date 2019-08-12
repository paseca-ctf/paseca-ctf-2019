int check13(char chr) // valid: 104
{
    if (((((((((chr * 3) + 90) << 5) ^ 2989) * 855) + 307) - 486) ^ 438) == 12678254)
        return 1;
    return 0;
}