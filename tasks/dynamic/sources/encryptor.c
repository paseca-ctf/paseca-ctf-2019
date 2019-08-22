#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int* encrypt(char* str, int* rand) {
    static int encrypted[46 * 2] = {0};
    int temp = 0;
    int random_blocker = 9032;

    for (int i = 0, counter = 0; counter < 46; i += 2)
    {
        temp = (int)str[counter] ^ 0x1229;
        *rand = *rand + random_blocker * (counter + 1);
        encrypted[i] = *rand;
        encrypted[i + 1] = temp - encrypted[i] - 3 ^ 0x89;
        ++counter;
        random_blocker += 1290;
    }

    for (int i = 0; i < 46; ++i)
    {
        if (i % 2 == 0) 
        {
            temp = encrypted[i];
            encrypted[i] = encrypted[46 * 2 - 1 - i] ^ 1229;
            encrypted[46 * 2 - 1- i] = temp;
        } else 
        {
            continue;
        }
    }

/*    for (int i = 0; i < 46 * 2; i += 2)
    {
        printf("%d, %d\n", encrypted[i], encrypted[i + 1]);
    }
*/
    return encrypted;
}


char* decrypt(int * encrypted) {
    static char decrypted[46];
    int counter = 0;
    int temp = 0;

    for (int i = 0; i < 46; ++i)
    {
        if (i % 2 == 0) 
        {
            temp = *(encrypted + i);
            *(encrypted + i) = *(encrypted + 46 * 2 - 1 - i);
            *(encrypted + 46 * 2 - 1 - i) = temp ^ 1229;
        } else 
        {
            continue;
        }
    }   

    for (int i = 0; i < 46 * 2 - 1; i += 2)
    {
        temp = *(encrypted + i) + (*(encrypted + i + 1) ^ 0x89) + 3;
        temp ^= 0x1229;
        decrypted[counter] = temp;
        ++counter;
    }

    return decrypted;
}

int check(int* encrypted_flag_usr, int* encrypted_first, int* encrypted_second) {
    for (int i = 0, counter = 0; counter < 46; i += 2)
    {
        if (*(encrypted_flag_usr + i) == *(encrypted_first + counter) && *(encrypted_flag_usr + i + 1) == *(encrypted_second + counter))
        {
            ++counter;
            continue;
        } else
        {
            return 0;
        }
        return 1;
    }
}

int main(int argc, char** argv) {

    int encrypted_first[]  = {-51597032, -48509288, -45548437, -42712532, -39992226, -37393557, -34907710, -32534081, -30267946, -28111061, -26060610, -24110159, -22258737, -20504407, -18841898, -17273422, -15795705, -14400268, -13091010, -11862872, -10713262, -9639964, -8642230, 8645937, 9645737, 10719069, 11868513, 13096649, 14406057, 15799317, 17279009, 18847713, 20508009, 22262477, 24113697, 26064249, 28116713, 30273669, 32537697, 34911377, 37397289, 39998013, 42716129, 45554217, 48514857, 51600629};
    int encrypted_second[] = {-6522, -27166, -61989, -113875, -184590, -277701, -395161, -539613, -713581, -920304, -1161284, -1440173, -1758876, -2119761, -2526373, -2980536, -3484717, -4042080, -4655081, -5325641, -6057085, -6852076, -7712323, 7717089, 6856613, 6061929, 5330457, 4659617, 4046829, 3489513, 2985089, 2530977, 2124597, 1763369, 1444713, 1166049, 924797, 718377, 544209, 399713, 282309, 189417, 118457, 66849, 32013, 11369};

    char flag[] = "paseca{s3lf_mut4ble_pr0grams_aren1t_that_ev1l}";
    int rand = 2337;
    int* encrypted = encrypt(flag, &rand);
    for (int i = 0; i < 46 * 2;)
    {
        printf("%d, ", encrypted[i]);
        i += 2;
    }
    puts("");
    for (int i = 1; i < 46 * 2;)
    {
        printf("%d, ", encrypted[i]);
        i += 2;
    }
    // char* decrypted = decrypt(encrypted);

    if (check(encrypted, encrypted_first, encrypted_second)) {
        printf("Wow\n");
    } else 
    {
        printf("Nope...\n");
    }

    // printf("%s\n", decrypted);
    return 0;
}
