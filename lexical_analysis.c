#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 100
#define MAX_TOKENS 500
int i;

// Global arrays to hold distinct tokens in each category.
char keywordsTable[MAX_TOKENS][MAX_TOKEN_LEN];
int keywordsCount = 0;

char identifiersTable[MAX_TOKENS][MAX_TOKEN_LEN];
int identifiersCount = 0;

char mathOpsTable[MAX_TOKENS][MAX_TOKEN_LEN];
int mathOpsCount = 0;

char logicalOpsTable[MAX_TOKENS][MAX_TOKEN_LEN];
int logicalOpsCount = 0;

char numericalTable[MAX_TOKENS][MAX_TOKEN_LEN];
int numericalCount = 0;

char othersTable[MAX_TOKENS][MAX_TOKEN_LEN];
int othersCount = 0;

// --- Helper Functions to add distinct tokens ---

// Check if token already exists in table.

int tokenExists(char table[][MAX_TOKEN_LEN], int count, const char *token)
{
    for (i = 0; i < count; i++)
    {
        if (strcmp(table[i], token) == 0)
            return 1;
    }
    return 0;
}

void addToken(char table[][MAX_TOKEN_LEN], int *count, const char *token)
{
    if (!tokenExists(table, *count, token))
    {
        strcpy(table[*count], token);
        (*count)++;
    }
}

// --- Classification Functions ---

// For this assignment, we only consider these four keywords.
int isKeyword(const char *token)
{
    return (strcmp(token, "int") == 0 ||
            strcmp(token, "float") == 0 ||
            strcmp(token, "if") == 0 ||
            strcmp(token, "else") == 0);
}

// A valid identifier starts with a letter or underscore and then letters, digits, or underscores.
int isValidIdentifier(const char *token)
{
    if (!isalpha(token[0]) && token[0] != '_')
        return 0;
    for (i = 1; token[i] != '\0'; i++)
    {
        if (!isalnum(token[i]) && token[i] != '_')
            return 0;
    }
    return 1;
}

// Checks if the token is a number (only digits for this example).
int isNumber(const char *token)
{
    if (token[0] == '\0')
        return 0;
    for (i = 0; token[i] != '\0'; i++)
    {
        if (!isdigit(token[i]))
            return 0;
    }
    return 1;
}

// --- Category check for single-character tokens ---

// Math operators (for our sample: =, ., -, +)
int isMathOperatorChar(char ch)
{
    return (ch == '=' || ch == '.' || ch == '-' || ch == '+');
}

// Logical operators (for our sample: <, >)
int isLogicalOperatorChar(char ch)
{
    return (ch == '<' || ch == '>');
}

// Others (punctuation: ;, (, ), {, }, ,)
int isOtherChar(char ch)
{
    return (ch == ';' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == ',');
}

// --- Processing token buffer (accumulated token from letters/digits) ---
void processTokenBuffer(char *buffer)
{
    if (buffer[0] == '\0')
        return;
    // First, check if token is a keyword.
    if (isKeyword(buffer))
    {
        addToken(keywordsTable, &keywordsCount, buffer);
    }
    // Then check if it is a number.
    else if (isNumber(buffer))
    {
        addToken(numericalTable, &numericalCount, buffer);
    }
    // Then if it is a valid identifier.
    else if (isValidIdentifier(buffer))
    {
        addToken(identifiersTable, &identifiersCount, buffer);
    }
    // Otherwise, ignore.
}

// --- Main function ---
int main(void)
{
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    char tokenBuffer[MAX_TOKEN_LEN];
    int bufIndex = 0;

    // Process file character by character.
    while ((ch = fgetc(fp)) != EOF)
    {
        // If whitespace, finish the current token.
        if (isspace(ch))
        {
            tokenBuffer[bufIndex] = '\0';
            processTokenBuffer(tokenBuffer);
            bufIndex = 0;
            continue;
        }

        // If ch is one of our operator or punctuation characters,
        // first finish the token in the buffer.
        if (isMathOperatorChar(ch) || isLogicalOperatorChar(ch) 
        || isOtherChar(ch))
        {
            tokenBuffer[bufIndex] = '\0';
            processTokenBuffer(tokenBuffer);
            bufIndex = 0;

            // Now process the current character separately.
            char op[2] = {ch, '\0'};
            if (isMathOperatorChar(ch))
                addToken(mathOpsTable, &mathOpsCount, op);
            else if (isLogicalOperatorChar(ch))
                addToken(logicalOpsTable, &logicalOpsCount, op);
            else if (isOtherChar(ch))
                addToken(othersTable, &othersCount, op);
            continue;
        }

        // Otherwise, accumulate the character.
        if (bufIndex < MAX_TOKEN_LEN - 1)
        {
            tokenBuffer[bufIndex++] = ch;
        }
    }

    // Process any token remaining in the buffer.
    tokenBuffer[bufIndex] = '\0';
    processTokenBuffer(tokenBuffer);

    fclose(fp);
    // Keywords:
    printf("Keywords: ");
    for (i = 0; i < keywordsCount; i++)
    {
        printf("%s", keywordsTable[i]);
        if (i < keywordsCount - 1)
            printf(", ");
    }
    printf("\n");

    // Identifiers:
    printf("Identifiers: ");
    for (i = 0; i < identifiersCount; i++)
    {
        printf("%s", identifiersTable[i]);
        if (i < identifiersCount - 1)
            printf(", ");
    }
    printf("\n");

    // Math Operators:
    printf("Math Operators: ");
    for ( i = 0; i < mathOpsCount; i++)
    {
        printf("%s", mathOpsTable[i]);
        if (i < mathOpsCount - 1)
            printf(", ");
    }
    printf("\n");

    // Logical Operators:
    printf("Logical Operators: ");
    for ( i = 0; i < logicalOpsCount; i++)
    {
        printf("%s", logicalOpsTable[i]);
        if (i < logicalOpsCount - 1)
            printf(", ");
    }
    printf("\n");

    // Numerical Values:
    printf("Numerical Values: ");
    for ( i = 0; i < numericalCount; i++)
    {
        printf("%s", numericalTable[i]);
        if (i < numericalCount - 1)
            printf(", ");
    }
    printf("\n");

    // Others:
    printf("Others: ");
    for (i = 0; i < othersCount; i++)
    {
        printf("%s", othersTable[i]);
        if (i < othersCount - 1)
            printf(", ");
    }
    printf("\n");

    return 0;
}
