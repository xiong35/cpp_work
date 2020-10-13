
#include "menu.h"

int showMainMenu(Lists& lists) {
    system(CLEAR);

    printf("=================================================\n");
    printf("|      Availiable Mutations On Linearlist       |\n");
    printf("=================================================\n");
    printf("|             1. show all lists' names          |\n");
    printf("|             2. add a new list                 |\n");
    printf("|             3. select a list(and mutate it)   |\n");
    printf("|             4. save a list                    |\n");
    printf("|             5. load a list                    |\n");
    printf("|             0. exit                           |\n");
    printf("=================================================\n");

    int mutation = 0;
    while (1) {
        printf("Your choice is[0~5]: ");
        scanf("%d", &mutation);
        if (mutation > 5 || mutation < 0)
            printf("please enter a num between 0 and 5\n");
        else
            break;
    }
    char name[30];

    switch (mutation) {
        case 0:
            printf("Thanks for using!");
            return 0;

        case 1:
            if (lists.length == 0)
                printf("There is no list now.\n");
            else
                showListsNames(lists);
            break;

        case 2:
            printf("Please enter list name: ");
            scanf("%s", name);
            if (AddList(lists, name) == OK)
                printf("success!\n");
            else
                printf("fail!\n");
            break;

        case 3:
            if (lists.length == 0)
                printf("There is no list now.\n");
            else
                mutateList(lists);
            break;

        case 4:
            if (lists.length == 0)
                printf("There is no list now.\n");
            else {
                int ind = getIndByName(lists);
                if (SaveList(lists.lists[ind - 1], FILE_NAME) == OK)
                    printf("success!\n");
                else
                    printf("fail!\n");
            }
            break;

        case 5:;
            if (LoadList(lists.lists[lists.length++], FILE_NAME) == OK) {
                lists.names[lists.length - 1][0] = 'l';
                lists.names[lists.length - 1][1] = 'o';
                lists.names[lists.length - 1][2] = 'a';
                lists.names[lists.length - 1][3] = 'd';
                lists.names[lists.length - 1][4] = 0;
                printf("success!\n");
            } else
                printf("fail!\n");
            break;

        default:
            return 0;
    }

    return 1;
}

int getIndByName(const Lists& lists) {
    char name[30];
    int ind = 0;
    while (1) {
        showListsNames(lists);
        printf("Please enter the list's name: ");
        scanf("%s", name);
        ind = LocateList(lists, name);
        if (ind)
            return ind;
        else
            printf("No such list, try again\n");
    }
}

void mutateList(Lists& lists) {
    printf("Please enter a name: \n");
    printf("Availiable names are: \n");
    int ind = getIndByName(lists);
    LinkList& L = lists.lists[ind - 1];
    while (1) {
        int mutation;

        system(CLEAR);
        printf("================================================\n");
        printf("|      Availiable Mutations On %-10s      |\n",
               lists.names[ind - 1]);
        printf("================================================\n");
        printf("|            1.  clear this list               |\n");
        printf("|            2.  destroy this list             |\n");
        printf("|            3.  show list length              |\n");
        printf("|            4.  get an element                |\n");
        printf("|            5.  locate an element             |\n");
        printf("|            6.  get the prior lists            |\n");
        printf("|            7.  get the next lists             |\n");
        printf("|            8.  insert an element             |\n");
        printf("|            9.  delete an element             |\n");
        printf("|            10. traverse this list            |\n");
        printf("|            0.  exit                          |\n");
        printf("================================================\n");

        while (1) {
            printf("Your choice is[0~10]: ");
            scanf("%d", &mutation);
            if (mutation > 10 || mutation < 0)
                printf("Invalid mutation, please try again");
            else
                break;
        }
        ElemType e;
        int res;
        ElemType target;

        switch (mutation) {
            case 0:
                return;
            case 1:
                ClearList(L);
                break;
            case 2:
                DestroyList(L);
                for (int i = ind; i < lists.length; i++) {
                    lists.lists[i - 1] = lists.lists[i];
                }
                lists.length--;
                return;
            case 3:
                printf("list length is: %d\n", ListLength(L));
                break;
            case 4:
                printf("Enter the index of the element: ");
                scanf("%d", &ind);
                res = GetElem(L, ind, e);
                if (res == OK)
                    printf("The element is: %d\n", e);
                else
                    printf("No such element\n");
                break;

            case 5:
                printf("Enter the value of the element: ");
                scanf("%d", &e);
                res = LocateElem(L, e);
                if (res > 0)
                    printf("The element index is: %d\n", res);
                else
                    printf("No such element\n");
                break;

            case 6:
                printf("Enter the value of the element: ");
                scanf("%d", &e);
                res = PriorElem(L, e, target);
                if (res == OK)
                    printf("The prior element is: %d\n", target);
                else
                    printf("No such element\n");
                break;

            case 7:
                printf("Enter the value of the element: ");
                scanf("%d", &e);
                res = NextElem(L, e, target);
                if (res == OK)
                    printf("The next element is: %d\n", target);
                else
                    printf("No such element\n");
                break;

            case 8:
                printf("Enter the value of the new element: ");
                scanf("%d", &e);
                printf("Enter the index of the new element: ");
                scanf("%d", &ind);
                res = ListInsert(L, ind, e);
                if (res == OK)
                    printf("success\n");
                else
                    printf("fail\n");
                break;

            case 9:
                printf("Enter the index of the element you want to del: ");
                scanf("%d", &ind);
                res = ListDelete(L, ind, e);
                if (res == OK)
                    printf("successfuly del %d at %d\n", e, ind);
                else
                    printf("fail\n");
                break;

            case 10:
                printf("the list is:\n");
                ListTraverse(L);
                printf("\n");
                break;

            default:
                break;
        }

        getchar();
        printf("\n## press Enter to continue ##\n");
        getchar();
    }
}

void showListsNames(const Lists& lists) {
    for (int i = 0; i < lists.length; i++) {
        printf("%d.  %s\n", i + 1, lists.names[i]);
    }
}
