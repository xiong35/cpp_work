
#include "menu.h"

int showMainMenu(Trees& trees) {
    system(CLEAR);

    printf("=================================================\n");
    printf("|      Availiable Mutations On BinaryTree       |\n");
    printf("=================================================\n");
    printf("|             1. show all trees' names          |\n");
    printf("|             2. load a tree                    |\n");
    printf("|             3. select a tree(and mutate it)   |\n");
    printf("|             4. save a tree                    |\n");
    printf("|             0. exit                           |\n");
    printf("=================================================\n");

    int mutation = 0;
    while (1) {
        printf("Your choice is[0~4]: ");
        scanf("%d", &mutation);
        if (mutation > 4 || mutation < 0)
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
            if (trees.length == 0)
                printf("There is no tree now.\n");
            else
                showTreesNames(trees);
            break;

        case 2:
            printf("Please enter file name: ");
            scanf("%s", name);
            if (trees.length < MAX_TREES &&
                LoadBiTree(trees.trees[trees.length], name) == OK) {
                strcpy(trees.names[trees.length++], name);
                printf("success!\n");
            } else
                printf("fail!\n");
            break;

        case 3:
            if (trees.length == 0)
                printf("There is no tree now.\n");
            else
                mutateTree(trees);
            break;

        case 4:
            if (trees.length == 0)
                printf("There is no tree now.\n");
            else {
                printf("enter the file name: ");
                scanf("%s", name);
                int ind = getIndByName(trees);
                if (SaveBiTree(trees.trees[ind], name) == OK)
                    printf("success!\n");
                else
                    printf("fail!\n");
            }
            break;
        default:
            return 0;
    }

    return 1;
}

int getIndByName(const Trees& trees) {
    char name[30];
    int ind = 0;
    while (1) {
        showTreesNames(trees);
        printf("Please enter the tree's name: ");
        scanf("%s", name);
        for (int i = 0; i < trees.length; i++) {
            if (strcmp(trees.names[i], name) == 0)
                return i;
        }
        printf("No such tree, try again\n");
    }
}

void visit(BiTree t) {
    printf("key: %d\tname: %s\n", t->data.key, t->data.others);
}

void mutateTree(Trees& trees) {
    printf("Please enter a name: \n");
    printf("Availiable names are: \n");
    int ind = getIndByName(trees);
    BiTree& curTree = trees.trees[ind];
    while (1) {
        int mutation;

        system(CLEAR);
        printf("================================================\n");
        printf("|      Availiable Mutations On %-10s      |\n",
               trees.names[ind]);
        printf("================================================\n");
        printf("|            1.  clear this tree               |\n");
        printf("|            2.  insert a node                 |\n");
        printf("|            3.  show tree depth               |\n");
        printf("|            4.  locate a node                 |\n");
        printf("|            5.  assign value to an node       |\n");
        printf("|            6.  get the sibling               |\n");
        printf("|            7.  deleate a node                |\n");
        printf("|            8.  pre order traverse            |\n");
        printf("|            9.  in order traverse             |\n");
        printf("|            10. postorder traverse            |\n");
        printf("|            11. level order traverse          |\n");
        printf("|            0.  exit                          |\n");
        printf("================================================\n");

        while (1) {
            printf("Your choice is[0~11]: ");
            scanf("%d", &mutation);
            if (mutation > 11 || mutation < 0)
                printf("Invalid mutation, please try again");
            else
                break;
        }
        KeyType e;
        TElemType c;
        BiTree target;
        int res, LR;

        switch (mutation) {
            case 0:
                return;
            case 1:
                ClearBiTree(curTree);
                for (int i = ind; i < trees.length; i++) {
                    strcpy(trees.names[i], trees.names[i + 1]);
                    trees.trees[i] = trees.trees[i + 1];
                }
                trees.length--;
                return;
            case 2:
                printf(
                    "please enter the parent key, LR, elem key and elem "
                    "name: ");
                scanf("%d %d %d %s", &e, &LR, &c.key, &c.others);
                res = InsertNode(trees.trees[ind], e, LR, c);
                if (res == OK)
                    printf("success\n");
                else
                    printf("fail!\n");
                break;
            case 3:
                printf("tree depth is: %d\n", BiTreeDepth(curTree));
                break;
            case 4:
                printf("Enter the key of the node: ");
                scanf("%d", &e);
                target = LocateNode(curTree, e);
                if (target)
                    printf("The node name is: %s\t\n", target->data.others);
                else
                    printf("No such node\n");
                break;

            case 5:
                printf(
                    "Enter the old key, new key and new name of the target: ");
                scanf("%d %d %s", &e, &c.key, &c.others);
                res = Assign(curTree, e, c);
                if (res == OK)
                    printf("success!\n");
                else
                    printf("fail!\n");
                break;

            case 6:
                printf("Enter the key of the node: ");
                scanf("%d", &e);
                target = GetSibling(curTree, e);
                if (target)
                    printf("The sibling name is: %s\n", target->data.others);
                else
                    printf("No such node\n");
                break;

            case 7:
                printf("Enter the key of the node: ");
                scanf("%d", &e);
                res = DeleteNode(curTree, e);
                if (res == OK)
                    printf("success!\n");
                else
                    printf("fail!\n");
                break;

            case 8:
                res = PreOrderTraverse(curTree, visit);
                if (res == OK)
                    printf("success\n");
                else
                    printf("fail\n");
                break;

            case 9:
                res = InOrderTraverse(curTree, visit);
                if (res == OK)
                    printf("success\n");
                else
                    printf("fail\n");
                break;

            case 10:
                res = PostOrderTraverse(curTree, visit);
                if (res == OK)
                    printf("success\n");
                else
                    printf("fail\n");
                break;
            case 11:
                res = LevelOrderTraverse(curTree, visit);
                if (res == OK)
                    printf("success\n");
                else
                    printf("fail\n");
                break;
            default:
                break;
        }

        getchar();
        printf("\n## press Enter to continue ##\n");
        getchar();
    }
}

void showTreesNames(const Trees& trees) {
    for (int i = 0; i < trees.length; i++) {
        printf("%d.  %s\n", i + 1, trees.names[i]);
    }
}
