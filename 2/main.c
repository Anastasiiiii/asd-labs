#include <stdio.h>
#include <stdlib.h>

            typedef struct list {
            int field;
            struct list *next;
             }list;
            //Инициализация списка
            struct list *list_init(int a) {
            struct list * lst;
            lst = (struct list*) malloc (sizeof (struct list));
            lst -> field = a;
            lst -> next = NULL;
            return lst;
            }
            //получение последнего элемента
            list* getLast(list *lst) {
            if (lst == NULL) {
            return NULL;
            }

             while (lst->next)
            { lst = lst->next; }
            return lst;
            }
            //Добавляет элемент

            list * add_list(list *lst, int item){
            struct list *node_p ;
            node_p = malloc(sizeof(struct list));
            node_p->field = item;
            node_p->next = lst;
            return node_p;
          }
          //вывод списка
            void listprint(list *lst)
            {
            struct list *p;
            p = lst;
            do {
            printf("%c ", p -> field);
            p = p -> next;
            }
            while (p != NULL);
            printf("\n");
            }
          //Удаление
          list *deletea(list *lst)
          {
              struct list *temp;
              temp = lst ->next;
              free(lst);
              return temp; 
          }
            int main() {
            char k[] = "a, e, i, o, u, y";
            char m[] = "b, c, d, f, g, h, j, k, l, m, n, p, q, r, s, c, t, v, z, w";
            printf("%c %c %c %c %c %c\n", k[0], k[1], k[2], k[3], k[4], k[5]);
            printf("%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15], m[16], m[17], m[18], m[19]);

             struct list* MyList = list_init(0);
             int n; char a;
             printf("Input n:");
             scanf("%d", &n); n = n*2;
             printf("Input a:\n");

             while (n--)
                { scanf("%c", &a);
             add_list(MyList, a); }
            MyList = deletea(MyList);
             printf("Unsorted list:\n");
             listprint(MyList);
             int *firstelement, *secondelement;
              int i, j;
              for (i = 0; i < 6; i++){
                for (j = 0; j < 20; j++){
                    if (a == i){
                        a = *firstelement;
                    } else if (a == j) {
                    a = *secondelement;
                    }
                }
              }

              printf("\nSorted list:\n", *firstelement, *secondelement);
               listprint(MyList);
               return 0;
            }
