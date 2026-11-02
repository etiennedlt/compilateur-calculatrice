#ifndef CAL_HEADERS_H
#define CAL_HEADERS_H

typedef enum {
    plus,
    soustraction,
    mult,
    division,
    racine,
    puissance,
    zero,
    un,
    deux,
    trois,
    quatre,
    cinq,
    six,
    sept,
    huit,
    neuf,
} operateurs;

typedef struct s_cell {
    s_cell* last;
    int value;
    operateurs opé;
    s_cell* next;
} t_cell;

typedef struct s_list {
    t_cell* head;
    t_cell* tail;
} t_list;

typedef struct s_ope_list {
    t_cell* head;
    t_cell* tail;
} t_ope_list;

t_cell* creat_cell(int value);

t_list* insert_list(t_cell* insert, t_list* list);

int transfert_str(char* tab);

t_list* creat_list();

void rajoute_ope(t_list* tab);

t_ope_list* ope_list(t_cell* &curr);

double calcul(t_list* tab);

#endif //CAL_HEADERS_H