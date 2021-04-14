#include "rb_tree.h"
#include <iostream>
#include <fstream>
#include <queue>


rb_tree::rb_tree()
{
    root = nullptr;
}

bool rb_tree::is_red(node *root)
{
    return root && root->red;
}

int rb_tree::compare(string *data1, string *data2)
{
    for(int i = 0; i < 3; i++)
    {
        if (!(data1[i] == data2[i]))
            return data1[i].compare(data2[i]);
    }
    return 0;
}

node *rb_tree::single_rotation(node *root, int dir)
{
    node *save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    root->red = true;
    save->red = false;

    return save;
}

node *rb_tree::double_rotation(node *n, int dir)
{
    n->link[!dir] = single_rotation(n->link[!dir], !dir);

    return single_rotation(n, dir);
}

node *rb_tree::make_node(string data[3], ifstream *file)
{
    node *rn = new node;


    for(int i = 0; i < 3; i++)
        rn->data[i] = data[i];
    rn->red = true;
    rn->link[0] = nullptr;
    rn->link[1] = nullptr;
    rn->head = nullptr;

    if(file)
    {
        list *tmp;
        list *x = new list;
        size_t len;
        char *temp;
        for(;;)
        {
            file->read((char*)& len, sizeof(size_t));
            temp = new char[len+1];
            file->read(temp, len);
            temp[len] = '\0';
            x->number = temp;
            delete temp;
            if(x->number == "end")
                break;
            else
            {
                list *new_element = new list;
                new_element->number = x->number;
                new_element->next = nullptr;

                if (!rn->head)
                {
                    rn->head = new_element;
                    tmp = rn->head;
                } else
                {
                    tmp->next = new_element;
                    tmp = tmp->next;
                }
            }
        }
    }
    else
    {
        cout << "Teraz prosze podac numery telefonu adresata. (gdy chcesz skonczyc napisz '-')." << endl;
        string number;
        list *tmp;
        for (;;)
        {
            cin >> number;
            if (number == "-")
            {
                break;
            }

            list *new_element = new list;
            new_element->number = number;
            new_element->next = nullptr;

            if (!rn->head)
            {
                rn->head = new_element;
                tmp = rn->head;
            } else
            {
                tmp->next = new_element;
                tmp = tmp->next;
            }
        }
    }

    return rn;
}

void rb_tree::insert(string *data, ifstream *file)
{
    if(!root)   // puste drzewo
    {
        root = make_node(data, file);
    }
    else
    {
        node head = {0};                // aby nie było specjalnych przypadków, tworzymy fałszywy korzeń

        node *great_grand, *grand;      // pradziadek i dziadek
        node *parent, *current;         // ojciec i aktualny węzeł
        int dir = 0, last;

        great_grand = &head;
        grand = parent = nullptr;
        current = great_grand->link[1] = root;

        for(;;)
        {
            /* jeżeli jesteśmy w wolnym miejscu, dołącz węzeł */
            if(!current)
            {
                parent->link[dir] = current = make_node(data, file);
            }

            else if(is_red(current->link[0]) && is_red(current->link[1]))       // przekoloryzowanie
            {
                current->red = true;
                current->link[0]->red = false;
                current->link[1]->red = false;
            }

            if(is_red(current) && is_red(parent))       // jezeli syn i ojciec są czerwoni, napraw
            {
                int dir2 = great_grand->link[1] == grand;       // jezeli dziadek jest prawym synem pradziadka zwróć 1, inaczej 0

                if(current == parent->link[last])
                {
                    great_grand->link[dir2] = single_rotation(grand, !last);
                }
                else
                {
                    great_grand->link[dir2] = double_rotation(grand, !last);
                }
            }

            if(!compare(current->data, data))       // jeżeli znaleziono danego abonenta skoncz
            {
                break;
            }

            last = dir;
            dir = compare(current->data, data) < 0;     // w którą stronę drzewa dalej

            if(grand)
            {
                great_grand = grand;     // pradziadek przyjmuje wartosc dziadka
            }

            grand = parent;             // dziadek ojca
            parent = current;           // ojciec obecnego węzła
            current = current->link[dir];   // obecny swojego syna
        }
        root = head.link[1];
    }
    root->red = false;
}

void rb_tree::search(string *data)
{
    if(!root)
    {
        cout << "Baza danych jest pusta." << endl;
        return;
    }

    node *tmp = root;
    int i = 1;
    int c = compare(tmp->data, data);

    while(c)
    {
        if (c < 0 && tmp->link[1])
        {
            tmp = tmp->link[1];
            c = compare(tmp->data, data);
        } else if (c > 0 && tmp->link[0])
        {
            tmp = tmp->link[0];
            c = compare(tmp->data, data);
        }
        else
        {
            cout << "Brak abonenta ";
            for(int k = 0; k < 3; k++)
                cout << data[k] << " ";
            cout << endl;
            return;
        }
    }

    while (tmp->head)
    {
        cout << i++ << ". " << tmp->head->number << endl;
        tmp->head = tmp->head->next;
    }
}

void rb_tree::free_tel_number(list **head)
{
    list *current = *head;
    list *next;
    while(current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = nullptr;
}

void rb_tree::remove(string *data)
{
    if(root)
    {
        node head = {0};                    // fałszywy korzeń, aby uniknąć specjalnych przypadków
        node *current, *parent, *grand;     // obecny węzeł, ojcieć i dziadek
        node *found = nullptr;
        int dir = 1;

        current = &head;
        grand = parent = nullptr;
        current->link[1] = root;

        while(current->link[dir])   // dopoki nie znaleźliśmy poprzednika
        {
            int last = dir;

            grand = parent;     // dziadek przyjmuje wartosc ojca
            parent = current;   // ojciec obecnego wezła
            current = current->link[dir];   // obecny swojego syna
            dir = compare(current->data, data) < 0;

            if(!compare(current->data, data))   // sprawdzamy czy znaleźliśmy węzeł do usunięcia
            {
                found = current;
            }

            if(!is_red(current) && !is_red(current->link[dir]))     // "pchanie" czerwonego węzła w dół drzewa, gdy następują po sobie 2 węzły czarne
            {
                if(is_red(current->link[!dir]))                // jeżeli drugie dziecko jest węzłem czerwonym, zrób rotacje
                    parent = parent->link[last] = single_rotation(current, dir);
                else if(!is_red(current->link[!dir]))
                {
                    node *save = parent->link[!last];

                    if(save)    // sprawdzenie czy nasz kuzyn istnieje
                    {
                        if(!is_red(save->link[!last]) && !is_red(save->link[last]))     // jeżeli jego synowie są czarni, przekoloruj
                        {
                            parent->red = false;
                            save->red = true;
                            current->red = true;
                        }
                        else
                        {
                            int dir2 = grand->link[1] == parent;        // jeżeli ojciec jest prawym synem dziadka, ustaw wartość na 1, inaczej 0

                            if(is_red(save->link[last]))
                                grand->link[dir2] = double_rotation(parent, last);
                            else if(is_red(save->link[!last]))
                                grand->link[dir2] = single_rotation(parent, last);

                            /* przekolorowanie węzłów */
                            current->red = grand->link[dir2]->red = true;
                            grand->link[dir2]->link[0]->red = false;
                            grand->link[dir2]->link[1]->red = false;
                        }
                    }
                }
            }
        }

        if(found)
        {
            for(int i = 0; i < 3; i++)
                found->data[i] = current->data[i];
            free_tel_number(&found->head);
            found->head = current->head;
            parent->link[parent->link[1] == current] = current->link[current->link[0] == nullptr];
            delete current;
            cout << "Usunieto." << endl;
        }

        root = head.link[1];

        if(root)
            root->red = false;
    }
}

void rb_tree::save()
{
    ofstream out("ksiunszka.bin", ios::out | ios::binary | ios:: trunc);
    node *tmp = root;
    list *tmp_list;
    queue<node*> queue;
    size_t len;
    queue.push(tmp);
    while(!queue.empty())
    {
        tmp = queue.front();
        tmp_list = tmp->head;
        queue.pop();
        for(int i = 0; i < 3; i++)
        {
            len = tmp->data[i].size();
            out.write((char*)& len, sizeof(size_t));
            out.write(tmp->data[i].c_str(), len);
        }

        while(tmp_list)
        {
            len = tmp_list->number.size();
            out.write((char*)& len, sizeof(size_t));
            out.write(tmp_list->number.c_str(), len);
            tmp_list = tmp_list->next;
        }
        string end = "end";
        len = end.size();
        out.write((char*)& len, sizeof(size_t));
        out.write(end.c_str(), len);

        if(tmp->link[0])
            queue.push(tmp->link[0]);
        if(tmp->link[1])
            queue.push(tmp->link[1]);
    }
    out.close();
}

void rb_tree::printout()
{
    if(!root)
    {
        cout << "Drzewo puste." << endl;
        return;
    }
    node *tmp = root;
    list *tmp_list;
    queue<node*> queue;
    queue.push(tmp);
    int x = 0;
    while(!queue.empty())
    {
        tmp = queue.front();
        tmp_list = tmp->head;
        queue.pop();
        cout << ++x << ". ";
        for(int i = 0; i < 3; i++)
        {
           cout << tmp->data[i] << " ";
        }

        while(tmp_list)
        {
            cout << tmp_list->number << " ";
            tmp_list = tmp_list->next;
        }
        cout << endl;

        if(tmp->link[0])
            queue.push(tmp->link[0]);
        if(tmp->link[1])
            queue.push(tmp->link[1]);
    }
}

int rb_tree::test(node *n, int r)
{
    if(r)
        n = root;

    int lh, rh;

    if(!n)
        return 1;
    else
    {
        node *ln = n->link[0];
        node *rn = n->link[1];

        if(is_red(n))
        {
            if(is_red(ln) || is_red(rn))
            {
                cout << "Red violation";
                return 0;
            }
        }
        lh = test(ln, 0);
        rh = test(rn, 0);

        if((ln && compare(ln->data, n->data) >= 0) || (rn && compare(rn->data, n->data) <= 0))
        {
            cout << "Binary tree violation";
            return 0;
        }

        if(lh && rh && lh != rh)
        {
            cout << "Black violation";
            return 0;
        }

        if(lh && rh)
            return is_red(n) ? lh : lh + 1;
        else
            return 0;
    }
}