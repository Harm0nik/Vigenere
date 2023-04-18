#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * readLetters(FILE * inFile, int * input);
char * readCipher(char * fileName);
char * padPlaintext(char * plaintext);
char * encrypt(char * plaintext, char * key);
void format(char * string);

#define MAX_SIZE 512

// Function to read a plaintext file and return a string with no spaces and converts uppercase letters to lowercase
char * readLetters(FILE * inFile, int * input)
{
    char * res = (char *) malloc(sizeof(char) * (MAX_SIZE + 1));
    char character = '\0';
    res[0] = '\0';

    while ((character = fgetc(inFile)) != EOF)
    { 
        if (!isalpha(character))
        {
            continue;
        }

        // use tolower function to convert uppercase letters to lowercase
        character = tolower(character);
        res[(*input)++] = character;
        res[* input] = '\0';

        if ((* input) == MAX_SIZE) 
        {
            return res;
        }
    }
    return res; 
}

// Function that reads in a cipher file, calls readLetters to strip non-alphabetical characters, and convert uppercase to lowercase
char * readCipher (char * fileName)
{ 
        FILE * cipherFile = NULL;
        char * key = NULL;
        int i = 0;

        cipherFile = fopen(fileName, "r");

        if (!(cipherFile = fopen(fileName, "r"))) 
        {
            return NULL;
        }
        key = readLetters(cipherFile, &i);

        key[i] = '\0';

        return key;
}

// Function to take in a plaintext file after using readLetters function and pad with x
char * padPlaintext(char * plaintext)
{
        FILE * myFile = NULL;
        char * ans = NULL;
        int i = 0;

        myFile = fopen(plaintext, "r"); 

        if (!(myFile = fopen(plaintext, "r"))) 
        {
            return NULL;
        }

        ans = readLetters(myFile, &i);

        // pad with x until there are 512 characters (bits)
        while (i < MAX_SIZE)
        {
                ans[i++] = 'x';
        }

        // place null terminator at the final index
        ans[i] = '\0';

        return ans;
}

// Function to encrpyt after taking in a plaintext file and a key
char * encrypt(char * plaintextKey, char * key)
{
        int i, x, plaintextIndex, keyIndex, insertVal;

        // assign memory for array, max bit size + 1 for the null terminator
        char * cipher = malloc(sizeof(char) * (MAX_SIZE + 1));

        for (i = x = 0; i < MAX_SIZE; i++)
        {
            if (key[x] == '\0') 
            {
                x = 0;
            }

            keyIndex = key[x] - 'a';
            plaintextIndex = plaintextKey[i] - 'a';

            // modulo operation of the size of the alphabet to get the new character
            insertVal = (keyIndex + plaintextIndex) % 26; 

            // call tolower function to convert character to lowercase
            cipher[i] = tolower('a' + insertVal);

            x++;
        }

        return cipher;
}

// Function to format a string to be in rows of 80 characters
void format(char * string)
{
        int i = 0;
        int j = 0;

        // keep iterating until the end of the string, the null terminator
        while (string[i] != '\0')
        {
                // if string has reached 80 characters, print a new line
                if (j == 80)
                {
                        j = 0;
                        printf("\n");
                }

                printf("%c", string[i]);
                i++;
                j++;
        }
        printf("\n");
}

// arguments to read in files as shown by McAlpin
int main(int argc, char **argv)
{
        int i;
        
        // arrays for the plaintext, vigenere key, and the output text
        char * plaintext = NULL;
        char * key = NULL;
        char * cipherText = NULL;

        // print out vignere key in the row format requested
        printf("\n\nVigenere Key:\n\n");
        if (!(key = readCipher(argv[1]))) 
        {
            return 0;
        }
        format(key);

        // print out plaintext in the row format requested
        printf("\n\nPlaintext:\n\n");
        if (!(key = padPlaintext(argv[2]))) 
        {
            return 0;
        }

        format(plaintext);

        // pass plaintext file and key to encryption function
        cipherText = encrypt(plaintext, key);

        // print final cipher text output
        printf("\n\nCiphertext:\n\n");
        format(cipherText);

        return 0;
}