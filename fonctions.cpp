#include "headers.h"
#include <stdio.h>
int len_bits = 5;

t_list* creat_list() {
    t_list* new_list;
    return new_list;
}

t_cell* creat_cell(int value) {
    t_cell* new_cell;
    new_cell->value = value;
    return new_cell;
}

t_list* insert_list(t_cell* insert, t_list* list) {
    if (list->head == NULL) {
        list->head = insert;
        list->tail = insert;
    }
    else {
        insert->last = list->tail;
        list->tail->next = insert;
        list->tail = insert;
    }
    return list;
}

int transfert_str(char* tab) {
    int cpt = 0;
    for (int i = 0; i < len_bits; i++) {
        int cpt2 = 1;
        if (tab[i] == '1') {
            for (int j = 0; j < i; j++) {
                cpt2 *= 2;
            }
            cpt += cpt2;
        }
    }
    return cpt;
}

t_list* insert_all(char** tab, int len) {
    t_list* list = creat_list();
    for (int i = 0; i < len; i++) {
        t_cell* cell = creat_cell(transfert_str(tab[i]));
        list = insert_list(cell, list);
    }
    return list;
}

operateurs operation(int valeur) {
    if (valeur == 0) {
        return zero;
    }
    if (valeur == 1) {
        return un;
    }
    if (valeur == 2) {
        return deux;
    }
    if (valeur == 3) {
        return trois;
    }
    if (valeur == 4) {
        return quatre;
    }
    if (valeur == 5) {
        return cinq;
    }
    if (valeur == 6) {
        return six;
    }
    if (valeur == 7) {
        return sept;
    }
    if (valeur == 8) {
        return huit;
    }
    if (valeur == 9) {
        return neuf;
    }
    if (valeur == 10) {
        return mult;
    }
    if (valeur == 11) {
        return soustraction;
    }
    if (valeur == 12) {
        return mult;
    }
    if (valeur == 13) {
        return division;
    }
    if (valeur == 14) {
        return puissance;
    }
    if (valeur == 15) {
        return racine;
    }
}

t_list* rajoute_ope(t_list* tab) {
    t_cell* curr = tab->head;
    while (curr != tab->tail) {
        curr->opé = operation(curr->value);
    }
}

double calcul_val(t_cell* curr) {
    double val = 0;
    while (curr->value < 10 && curr->next != NULL) {
        val *= 10;
        val += curr->value;
        curr = curr->next;
    }
    return val;
}

t_ope_list* ope_list(t_cell* curr) {
    t_ope_list* ope_list;
    if (curr->value > 9) {
        t_cell* current = curr;
        ope_list->head = current;
        while (current->next->value > 9) {
            current = current->next;
        }
        ope_list->tail = current;
        current->next = NULL;
    }
    return ope_list;
}

double calcul(t_list* tab) {
    double cpt = 0;
    t_cell* curr = tab->head;
    cpt = calcul_val(curr);
    int val = 0;
    while (curr->value < 10 && curr->next != NULL) {
        curr = curr->next;
    }
    while (curr->next != NULL) {
        operateurs opé = operation(curr->value);
            if (curr->value < 10) {
                val = calcul_val(curr);
            }
            if (opé == mult) {
                t_ope_list* list_operator = ope_list(curr);
                if (list_operator->head == NULL) {
                    cpt += val;
                    val = 0;
                }
            }
            if (opé == soustraction) {
                t_ope_list* list_operator = ope_list(curr);
                if (list_operator->head == NULL) {
                    cpt -= val;
                    val = 0;
                }
            }
            if (opé == mult) {
                t_ope_list* list_operator = ope_list(curr);
                if (list_operator->head == NULL) {
                    cpt *= val;
                    val = 0;
                }
            }
            if (opé == division) {
                t_ope_list* list_operator = ope_list(curr);
                if (list_operator->head == NULL) {
                    cpt /= val;
                    val = 0;
                }
            }
            if (opé == puissance) {
                t_ope_list* list_operator = ope_list(curr);
                if (list_operator->head == NULL) {
                    if (curr->next->value > 0) {
                        for (int i = 1; i < curr->value; i++) {
                            cpt *= cpt;
                            val = 0;
                        }
                    }
                    else if (curr->next->value == 0) {
                        cpt = 1;
                        val = 0;
                    }
                    else {
                        for (int i = 1; i < curr->next->value * -1; i++) {
                            cpt *= cpt;
                        }
                        cpt = 1/cpt;
                        val = 0;
                    }
                }
                else {

                }
            }
    }
    return cpt;
}