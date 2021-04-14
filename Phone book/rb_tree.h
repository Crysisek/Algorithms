#ifndef KSIAZKA_TELEFONICZNA_RB_TREE_H
#define KSIAZKA_TELEFONICZNA_RB_TREE_H

#include <string>

using namespace std;

typedef struct list
{
    string number;
    struct list *next;
}list;

typedef struct node
{
    bool red;
    string data[3];
    list *head;
    struct node *link[2];
}node;

class rb_tree
{
    node *root;

    static bool is_red(node *root);
    static int compare(string data1[3], string data2[3]);
    static node *single_rotation(node *root, int dir);
    static node *double_rotation(node *root, int dir);
    static node *make_node(string data[3], ifstream *file);
    static void free_tel_number(list**);

public:
    rb_tree();

    void insert(string data[3], ifstream *file);
    void search(string data[3]);
    void remove(string *data);
    void save();
    void printout();
    int test(node*, int);
};


#endif //KSIAZKA_TELEFONICZNA_RB_TREE_H
