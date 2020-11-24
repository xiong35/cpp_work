
#include "menu.h"

void visit(VertexType v) {
    printf(" %d %s", v.key, v.others);
}

int showMainMenu(ALGraph& graph) {
    system(CLEAR);

    printf("================================================\n");
    printf("|        Availiable Mutations On Graph         |\n");
    printf("================================================\n");
    printf("|            1.  LocateVex                     |\n");
    printf("|            2.  PutVex                        |\n");
    printf("|            3.  FirstAdjVex                   |\n");
    printf("|            4.  NextAdjVex                    |\n");
    printf("|            5.  InsertVex                     |\n");
    printf("|            6.  DeleteVex                     |\n");
    printf("|            7.  InsertArc                     |\n");
    printf("|            8.  DeleteArc                     |\n");
    printf("|            9.  DFSTraverse                   |\n");
    printf("|            10. BFSTraverse                   |\n");
    printf("|            11. SaveGraph                     |\n");
    printf("|            12. LoadGraph                     |\n");
    printf("|            0.  exit                          |\n");
    printf("================================================\n");

    int mutation = 0;
    while (1) {
        printf("Your choice is[0~13]: ");
        scanf("%d", &mutation);
        if (mutation > 13 || mutation < 0)
            printf("please enter a num between 0 and 5\n");
        else
            break;
    }

    KeyType m, n;
    VertexType v;
    int res;

    switch (mutation) {
        case 0:
            printf("Thanks for using!");
            return 0;

        case 1:
            printf("Enter the key: ");
            scanf("%d", &m);
            res = LocateVex(graph, m);
            if (res == -1)
                printf("could not locate");
            else
                printf("others: %s", graph.vertices[res].data.others);
            break;

        case 2:
            printf("key, new key, new others: ");
            scanf("%d %d %s", &m, &v.key, &v.others);
            if (PutVex(graph, m, v) == OK)
                printf("OK\n");
            else
                printf("FAIL\n");
            break;

        case 3:
            printf("Enter the key: ");

            scanf("%d", &m);
            res = FirstAdjVex(graph, m);
            if (res == -1)
                printf("FAIL\n");
            else
                printf("others: %s\n", graph.vertices[res].data.others);
            break;

        case 4:
            printf("Enter two keys: ");

            scanf("%d %d", &m, &n);
            res = NextAdjVex(graph, m, n);
            if (res == -1)
                printf("FAIL\n");
            else
                printf("others: %s\n", graph.vertices[res].data.others);
            break;

        case 5:
            printf("Enter the key and others: ");

            scanf("%d %s", &v.key, &v.others);
            if (InsertVex(graph, v) == OK)
                printf("OK\n");
            else
                printf("FAIL\n");
            break;

        case 6:
            printf("Enter the key: ");

            scanf("%d", &v.key);
            if (DeleteVex(graph, v.key) == OK)
                printf("OK\n");
            else
                printf("FAIL\n");
            break;

        case 7:
            printf("Enter two keys: ");

            scanf("%d %d", &m, &n);
            if (InsertArc(graph, m, n) == OK)
                printf("OK\n");
            else
                printf("FAIL\n");
            break;

        case 8:
            printf("Enter two keys: ");

            scanf("%d %d", &m, &n);
            if (DeleteArc(graph, m, n) == OK)
                printf("OK\n");
            else
                printf("FAIL\n");
            break;

        case 9:
            DFSTraverse(graph, visit);
            break;

        case 10:
            BFSTraverse(graph, visit);
            break;

        case 11:
            SaveGraph(graph, "g2.txt");
            printf("OK\n");
            break;

        case 12:
            LoadGraph(graph, "g.txt");
            printf("OK\n");
            break;

        default:
            return 0;
    }

    return 1;
}
