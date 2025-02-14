#include <stdio.h>
#include <string.h>
// Function to check if an email is valid
int is_valid_email(const char *email)
{
    int at_index = -1, dot_index = -1;
    int length = strlen(email);
    int i;
    for (i = 0; i < length; i++)
    {
        if (email[i] == '@')
        {
            if (at_index != -1)
                return 0; // More than one '@'
            at_index = i;
        }
        else if (email[i] == '.' && at_index != -1)
        {
            dot_index = i;
        }
    }
    return (at_index > 0 && dot_index > at_index + 1 && dot_index < length - 1);
}
// Function to check if a website URL is valid
int is_valid_website(const char *website)
{
    int length = strlen(website);
    if (length < 5)
        return 0;
    // Check for valid domain suffix
    const char *valid_suffixes[] = {".com", ".org", ".net", ".edu", ".gov", ".io"};
    int suffix_count = sizeof(valid_suffixes) / sizeof(valid_suffixes[0]);
    int i;
    for (i = 0; i < suffix_count; i++)
    {
        int suffix_len = strlen(valid_suffixes[i]);
        if (length > suffix_len && strcmp(website + length - suffix_len, valid_suffixes[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    char email[100], website[100];
    // Taking input
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter website: ");
    scanf("%s", website);
    // Validate email and website
    int valid_email = is_valid_email(email);
    int valid_website = is_valid_website(website);
    // Output based on validation
    if (valid_email && valid_website)
    {
        printf("Email, 1\nWeb, 2\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}
