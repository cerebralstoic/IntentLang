#include <stdio.h>
#include <string.h>

int main() {
    int marks;
    char result[10];
    scanf("%d", &marks);
    if (marks < 40) strcpy(result, "fail");
    else if (marks >= 85) strcpy(result, "A");
    else if (marks >= 70) strcpy(result, "B");
    else strcpy(result, "C");
    printf("%s", result);
    return 0;
}
