#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

typedef struct Node {
    double data;
    struct Node* next;
} Node;

Node* create_node(double data);
void insert_beginning(Node** head, double data);
void insert_end(Node** head, double data);
void delete_beginning(Node** head);
void delete_end(Node** head);
void display_list(Node* head);  
void delete_list(Node** head);
void search_element(Node* head, double value);  
void print_menu(int current_option);
void clear_screen();
double valid_input(const char* output);
void init_node(Node** head);

const char* menu_options[] = {
    "Инициализация списка",
    "Добавить элемент в начало",
    "Добавить элемент в конец",
    "Удалить элемент из начала",
    "Удалить элемент из конца",
    "Просмотреть список",
    "Удалить весь список",
    "Поиск элемента",
    "Выход"
};
const int MENU_ITEMS = 9;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    Node* head = NULL;
    int current_option = 0;
    int key;
    double value;
    int is_init = 0;
    
    do {
        clear_screen();
        print_menu(current_option);
        
        key = _getch();
        
        if (key == 224 || key == 0) {
            key = _getch();
            switch (key) {
                case 72:
                    current_option = (current_option - 1 + MENU_ITEMS) % MENU_ITEMS;
                    break;
                case 80:
                    current_option = (current_option + 1) % MENU_ITEMS;
                    break;
            }
        }
        else if (key == 13) {
            clear_screen();
            
            switch (current_option) {
                case 0:
                    init_node(&head);
                    is_init = 1;
                    printf("Список инициализирован.\n");
                    break;

                case 1:
                    if (is_init == 0) {
                        printf("Список не инициализирован\n");
                        break;
                    }
                    value = valid_input("Введите значение для добавления в начало: ");
                    insert_beginning(&head, value);
                    printf("Элемент добавлен!\n");
                    break;
                    
                case 2:
                    if (is_init == 0) {
                        printf("Список не инициализирован\n");
                        break;
                    }
                    value = valid_input("Введите значение для добавления в конец: ");
                    insert_end(&head, value);
                    printf("Элемент добавлен!\n");
                    break;
                    
                case 3:
                    if (is_init == 0) {
                        printf("Список не инициализирован\n");
                        break;
                    }
                    if (head != NULL) {
                        delete_beginning(&head);
                        printf("Элемент удален из начала!\n");
                    } else {
                        printf("Список пуст!\n");
                    }
                    break;
                    
                case 4:
                    if (is_init == 0) {
                        printf("Список не инициализирован\n");
                        break;
                    }
                    if (head != NULL) {
                        delete_end(&head);
                        printf("Элемент удален из конца!\n");
                    } else {
                        printf("Список пуст!\n");
                    }
                    break;
                    
                case 5:
                    if (is_init == 0) {
                        printf("Список не инициализирован\n");
                        break;
                    }
                    printf("Содержимое списка:\n");
                    display_list(head);  
                    break;
                    
                case 6:
                    if (is_init == 0) {
                        printf("Список не инициализирован\n");
                        break;
                    }
                    delete_list(&head);
                    printf("Список полностью удален!\n");
                    is_init = 0;  
                    break;

                case 7:
                    if (is_init == 0) {
                        printf("Список не инициализирован\n");
                        break;
                    }
                    value = valid_input("Введите значение для поиска: ");
                    search_element(head, value);  
                    break;
                    
                case 8:
                    delete_list(&head);
                    printf("Выход из программы...\n");
                    return 0;
            }
            
            if (current_option != 8) {
                printf("\nНажмите любую клавишу для возврата в меню...");
                _getch();
            }
        }
        
    } while (current_option != 8 || key != 13);
    
    delete_list(&head);
    return 0;
}

double valid_input(const char* output) {
    double input;
    int code_input;

    do {
        code_input = 0;
        printf("%s", output);
        
        // Читаем строку и проверяем корректность ввода
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Ошибка ввода!\n");
            code_input = 1;
            continue;
        }
        
        char *endptr;
        input = strtod(buffer, &endptr);
        
        if (endptr == buffer || *endptr != '\n') {
            printf("Вы ввели не число! Так нельзя! Повторите попытку\n");
            code_input = 1;
        }
    } while(code_input != 0);

    return input;
}

void init_node(Node** head) {
    delete_list(head);  
    *head = NULL;
}

Node* create_node(double data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_beginning(Node** head, double data) {
    Node* new_node = create_node(data);
    if (new_node != NULL) {
        new_node->next = *head;
        *head = new_node;
    }
}

void insert_end(Node** head, double data) {
    Node* new_node = create_node(data);
    if (new_node != NULL) {
        if (*head == NULL) {
            *head = new_node;
        } else {
            Node* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }
}

void delete_beginning(Node** head) {
    if (*head != NULL) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void delete_end(Node** head) {
    if (*head != NULL) {
        if ((*head)->next == NULL) {
            free(*head);
            *head = NULL;
        } else {
            Node* temp = *head;
            Node* prev = NULL;
            while (temp->next != NULL) {
                prev = temp;
                temp = temp->next;
            }
            if (prev != NULL) {
                prev->next = NULL;
            }
            free(temp);
        }
    }
}

void display_list(Node* head) {  
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }
    
    Node* temp = head;
    int position = 1;
    while (temp != NULL) {
        printf("Позиция %d: %.3lf\n", position, temp->data);
        temp = temp->next;
        position++;
    }
}

void delete_list(Node** head) {
    Node* current = *head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

void search_element(Node* head, double value) {  
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }
    
    Node* temp = head;
    int position = 1;
    int found = 0;
    
    while (temp != NULL) {
        if (fabs(temp->data - value) < 0.000001) {
            printf("Элемент %.3lf найден на позиции %d\n", value, position);
            found = 1;
        }
        temp = temp->next;
        position++;
    }
    
    if (!found) {
        printf("Элемент %.3lf не найден в списке\n", value);
    }
}

void print_menu(int current_option) {
    printf("=== Управление односвязным списком ===\n");
    printf("Используйте стрелки ВВЕРХ/ВНИЗ для навигации\n");
    printf("Нажмите ENTER для выбора пункта\n");
    printf("======================================\n\n");
    
    for (int i = 0; i < MENU_ITEMS; i++) {
        if (i == current_option) {
            printf("-> ");
        } else {
            printf("   ");
        }
        printf("%s\n", menu_options[i]);
    }
    printf("\n");
}

void clear_screen() {
    system("cls");
}
