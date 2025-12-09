// ELEC2645 Circuit Analyzer - Main File
// Student style but fully working

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"

static void main_menu(void);
static void print_main_menu(void);
static int  get_user_input(void);
static void select_menu_item(int input);
static int  is_integer(const char *s);

int main(void)
{
    while(1)
    {
        main_menu();
    }
    return 0;
}

static void main_menu(void)
{
    print_main_menu();
    int input = get_user_input();
    select_menu_item(input);
}

static int get_user_input(void)
{
    enum { MENU_ITEMS = 8 };
    char buf[50];
    int value;

    while(1)
    {
        printf("\nSelect option: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;

        if(is_integer(buf))
        {
            value = atoi(buf);

            if(value >= 1 && value <= MENU_ITEMS)
                return value;
        }

        printf("Invalid choice, try again.\n");
    }
}

static void select_menu_item(int input)
{
    switch(input)
    {
        case 1:
            menu_item_1(); // Voltage
            break;
        case 2:
            menu_item_2(); // Current
            break;
        case 3:
            menu_item_3(); // Resistance
            break;
        case 4:
            menu_item_4(); // Series
            break;
        case 5:
            menu_item_5(); // Parallel
            break;
        case 6:
            menu_item_6(); // Mixed
            break;
        case 7:
            menu_item_7(); // Power
            break;
        case 8:
            printf("Program closed.\n");
            exit(0);
    }
}

static void print_main_menu(void)
{
    printf("\n=========== MAIN MENU ===========\n");
    printf("1 - Voltage Calculation\n");
    printf("2 - Current Calculation\n");
    printf("3 - Resistance Calculation\n");
    printf("4 - Series Circuit\n");
    printf("5 - Parallel Circuit\n");
    printf("6 - Mixed Circuit\n");
    printf("7 - Power Calculation\n");
    printf("8 - Exit\n");
    printf("========================================\n");
}

static int is_integer(const char *s)
{
    if(!s || !*s) return 0;

    if(*s == '-' || *s == '+') s++;

    while(*s)
    {
        if(!isdigit(*s))
            return 0;
        s++;
    }
    return 1;
}
