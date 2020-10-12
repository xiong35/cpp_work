#include <iostream>
class NODE
{
    char *data;
    NODE *left, *right;

public:
    NODE(const char *dataIn);
    NODE(char *dataIn);
    NODE(const char *dataIn, NODE *leftone, NODE *rightone);
    NODE(char *dataIn, NODE *leftone, NODE *rightone);
    ~NODE();
    void preOrder(NODE *node);
    void midOrder(NODE *node);
    void find(const char *target, NODE *node, NODE *&e);
    char *getData();
};
NODE::NODE(const char *dataIn)
{
    int i, cnt = 0;
    for (int j = 0; dataIn[j] != '\0'; j++)
    {
        cnt++;
    }
    data = new char[cnt + 1];
    for (i = 0; dataIn[i] != '\0'; i++)
    {
        data[i] = dataIn[i];
    }
    data[i] = '\0';
    left = nullptr;
    right = nullptr;
}
NODE::NODE(char *dataIn)
{
    int i, cnt = 0;
    for (int j = 0; dataIn[j] != '\0'; j++)
    {
        cnt++;
    }
    data = new char[cnt + 1];
    for (i = 0; dataIn[i] != '\0'; i++)
    {
        data[i] = dataIn[i];
    }
    data[i] = '\0';
    left = nullptr;
    right = nullptr;
}
NODE::NODE(const char *dataIn, NODE *leftone, NODE *rightone)
{
    int i, cnt = 0;
    for (int j = 0; dataIn[j] != '\0'; j++)
    {
        cnt++;
    }
    data = new char[cnt + 1];
    for (i = 0; dataIn[i] != '\0'; i++)
    {
        data[i] = dataIn[i];
    }
    data[i] = '\0';
    left = leftone;
    right = rightone;
}
NODE::NODE(char *dataIn, NODE *leftone, NODE *rightone)
{
    int i, cnt = 0;
    for (int j = 0; dataIn[j] != '\0'; j++)
    {
        cnt++;
    }
    data = new char[cnt + 1];
    for (i = 0; dataIn[i] != '\0'; i++)
    {
        data[i] = dataIn[i];
    }
    data[i] = '\0';
    left = leftone;
    right = rightone;
}
NODE::~NODE()
{
    delete left;
    delete right;
    std::cout << data << std::endl;
    delete data;
}
void NODE::preOrder(NODE *node)
{
    if (node)
    {
        std::cout << node->getData() << std::endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}
void NODE::midOrder(NODE *node)
{
    if (node)
    {
        midOrder(node->left);
        std::cout << node->getData() << std::endl;
        midOrder(node->right);
    }
}
void NODE::find(const char *target, NODE *node, NODE *&e)
{
    int flag = 0;
    if (node)
    {
        for (int i = 0; target[i] != '\0'; i++)
        {
            if (node->data[i] != target[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            e = node;
        }
        find(target, node->left, e);
        find(target, node->right, e);
    }
}
char *NODE::getData()
{
    return data;
}