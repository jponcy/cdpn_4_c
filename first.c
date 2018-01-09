#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void empty_stream(FILE* stream) {
    char buffer[100];
    int arrayLength = sizeof(buffer) / sizeof(char);

    fflush(stdin);
    fgets(buffer, arrayLength, stdin);
}

void tp_scan() {
    char name1[21] = "", name2[21] = "";
    int nb1, nb2;

    printf("Saisir nom perso 1 : ");
    scanf(" %20[a-zA-Z]", name1);

    printf("Saisir nom perso 2 : ");
    scanf(" %20[a-zA-Z]", name2);

    printf("Nombre de pommes de %s : ", name1);
    scanf(" %d", &nb1);
    printf("Nombre de pommes de %s : ", name2);
    scanf(" %d", &nb2);

    printf("\n%s a %d pommes\n", name1, nb1);
    printf(  "%s a %d pommes\n", name2, nb2);
    printf("Pour un total de %d pommes\n", (nb1 + nb2));
}

void tp_io() {
        char name[31] = "";
    int choice;
    char letter;
    int limit = 0;

    printf("Saisir votre nom : ");
    scanf(" %30s", name);

    printf("Que souhaitez-vous faire :\n\t1) nom avec espaces\n\t2) nom a l'envers\n\t3) nom diminue\nChoix : ");

    while (scanf("%d", &choice) == 0 || choice < 0 || choice > 3) {
        empty_stream(stdin);
        printf("Erreur, faire une saisie [1-3] : ");
    }

    switch (choice) {
        case 1: // Name with spaces.
            for (int i = 0, letter = name[0]; letter != '\0'; ++ i, letter = name[i]) {
                printf("%c ", letter);
            }
            break;
        case 2: // Reverse name.
            // Find index of last letter.
            while (name[++limit] != '\0');

            // Print.
            for (int i = limit, letter = name[limit]; i >= 0; -- i, letter = name[i]) {
                printf("%c", letter);
            }

            break;
        case 3:
            for (int i = 0, letter = name[0]; letter != '\0'; ++ i, letter = name[i]) {
                if (i % 2 == 1) continue;
                printf("%c", letter);
            }
    }

    printf("\n");
}








typedef unsigned int uint;

typedef struct employee {
    char* lastname;
    char* firstname;
    short age;
    struct employee* next;
} employee;

/*
 * Faire d'employee une liste chain&eacute;e.
 * Faire des fonctions d'utilisation :
 * - void add_item(employee* employees, employee blue)
 * - employee create_employee(char* lastname, char* firstname, short age)
 * - void create_add_employee(employee* employees, char* lastname, char* firstname, short age)
 * - employee* get_employee(employee* employees, unsigned int index)
 * - void print_employee(const employee* e)
 * - void print_employees(const employee* employees)
 */

employee* add_item(employee** employees, employee* blue) {
    employee* elt = *employees;

    if (*employees == NULL) {
        *employees = blue;
    } else {
        while (elt->next != NULL)
        { elt = elt->next; }

        elt->next = blue;
    }

    return *employees;
}

employee* create_employee(char* lastname, char* firstname, short age) {
    employee* e = (employee*) malloc(sizeof(employee));

    e->lastname = lastname;
    e->firstname = firstname;
    e->age = age;
    e->next = NULL;

    return e;
}

employee* create_add_employee(employee** employees, char* lastname, char* firstname, short age) {
    return add_item(employees, create_employee(lastname, firstname, age));
}

employee* get_employee(employee* employees, unsigned int index) {
    employee* elt = employees;

    for (int i = 0; i < index && elt != NULL; ++ i)
    { elt = elt->next; }

    return elt;
}

void print_employee(const employee* e) {
    if (e == NULL) return;
    printf("%s %s is %d", e->lastname, e->firstname, e->age);
}

void print_employees(const employee* employees) {
    employee* elt = employees;

    while (elt != NULL) {
        printf("\t- ");
        print_employee(elt);
        printf("\n");
        elt = elt->next;
    }
}

int count(employee* employees) {
    int i = 0;
    employee* elt = employees;

    while (elt != NULL) {
        elt = elt->next;
        i++;
    }

    // for (employee* elt = employees; elt != NULL; elt = elt->next, i++);

    return i;
}

int main() {
    employee* root = NULL;

    create_add_employee(&root, "Mit", "Francois", 98);
    create_add_employee(&root, "R", "Gautier", 25);
    root = create_add_employee(&root, "Pasr", "Gwenole", 25);

    printf("Second employee was: ");
    print_employee(get_employee(root, 1));

    printf("\n\n----------------\n\nEmployees:\n");
    print_employees(root);

    return 0;
}
