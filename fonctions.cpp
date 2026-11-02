#include "headers.h"
#include <stdio.h>

int len_bits = 5;

t_list* creat_list() {
    t_list* new_list = new t_list();
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}

t_cell* creat_cell(int value) {
    t_cell* new_cell = new t_cell();
    new_cell->value = value;
    new_cell->last = NULL;
    new_cell->next = NULL;
    return new_cell;
}

t_list* insert_list(t_cell* insert, t_list* list) {
    if (list->head == NULL) {
        list->head = insert;
        list->tail = insert;
    } else {
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
    if (valeur == 10) return plus;
    if (valeur == 11) return soustraction;
    if (valeur == 12) return mult;
    if (valeur == 13) return division;
    if (valeur == 14) return puissance;
    if (valeur == 15) return racine;
    return zero;
}

void rajoute_ope(t_list* tab) {
    t_cell* curr = tab->head;
    while (curr != NULL) {
        if (curr->value > 9) {
            curr->opé = operation(curr->value);
        }
        curr = curr->next;
    }
}

double calcul_val(t_cell* &curr) {
    double val = 0;
    while (curr != NULL && curr->value < 10) {
        val = val * 10 + curr->value;
        curr = curr->next;
    }
    return val;
}

t_ope_list* ope_list(t_cell* &curr) {
    t_ope_list* op_list = new t_ope_list();
    op_list->head = NULL;
    op_list->tail = NULL;

    if (curr != NULL && curr->value > 9) {
        op_list->head = curr;
        t_cell* current = curr;
        while (current->next != NULL && current->next->value > 9) {
            current = current->next;
        }
        op_list->tail = current;
        curr = current->next;
    }
    return op_list;
}

// Fonction de calcul prenant en compte les opérateurs multiples
double calcul(t_list* tab) {
    t_cell* curr = tab->head;
    if (curr == NULL) return 0;
    double cpt = calcul_val(curr);
    while (curr != NULL) {
        // Récupérer un ou plusieurs opérateurs à la suite
        t_ope_list* list_operator = ope_list(curr);
        if (curr == NULL) break;
        double val = calcul_val(curr);
        // Cas : un seul opérateur
        if (list_operator->head == list_operator->tail && list_operator->head != NULL) {
            operateurs opé = operation(list_operator->head->value);
            if (opé == plus) {
                cpt += val;
            } else if (opé == soustraction) {
                cpt -= val;
            } else if (opé == mult) {
                cpt *= val;
            } else if (opé == division) {
                if (val != 0) cpt /= val;
            } else if (opé == puissance) {
                double base = cpt;
                for (int i = 1; i < val; i++) {
                    cpt *= base;
                }
            }
        }
        // Cas : PLUSIEURS opérateurs à la suite (ex: * et +, ou --, etc.)
        else if (list_operator->head != NULL) {
            // Exemple de stratégie pour plusieurs opérateurs :
            // On applique le dernier opérateur de la chaîne, ou on gère les signes consécutifs.
            // Ici, on récupère le dernier opérateur valide de la séquence :
            operateurs dernier_ope = operation(list_operator->tail->value);
            if (dernier_ope == plus) {
                cpt += val;
            }
            else if (dernier_ope == soustraction) {
                cpt -= val;
            }
            else if (dernier_ope == mult) {
                cpt *= val;
            }
            else if (dernier_ope == division && val != 0) {
                cpt /= val;
            }
        }
    }
    return cpt;
}