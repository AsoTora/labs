#include <iostream>

using namespace std;

struct node{
    int data;
    node *next = nullptr;
};

class list{ // last in first out
private:
    node *head, *tail;
public:
    list(){head = nullptr; tail=nullptr;} // конструктор
    ~list() = default; // деструктор
    void push(int );
    void pop();  // удаление верхнего эл-та
    void append(int);  // insert at the begining
    void insert(int);
    void display();
    void clear();
    void del();
    // void qsort();  // quicksort
    void bubblesort();
    void search(int);
    void reverse();
    void rec_display(node *);
    void taskB();
    bool is_empty(){return head == nullptr;};  // extra
    node *gethead(){return head;}; // для рекурсивного прохода
    node *gettail();  // для случая стека без указателя на tail
};

void list::push(int value) {
    node *tmp = new node;
    tmp->data = value;
    tmp->next = nullptr;

    if (head == nullptr){  // список пустой
        head = tmp;
        tail = tmp;
    }else{
        tmp->next  = head; // новая нода вставляется сверху
        head = tmp; // теперь она в head
    }
}

void list::pop(){
    if(this->is_empty()){
        cout << "The list is empty!"<<endl;
        return;
    }
    node *old = head;
    head = old->next;
    delete old;
}

void list::append(int value) {  // немного нарушает принцип стека, но не односвязного списка
    node *tmp = new node;
    tmp->data = value;
    tmp->next = nullptr;

    if(head == nullptr){
        head = tmp;
        tail = tmp;
    }else{
        tail->next = tmp;
        tail = tmp;
    }
    /* Реализация без tail в самом списке
    node *tail = head;
    while(tail->next != nullptr)
        tail = tail->next;
    tail->next = tmp;
    */
}

void list::insert(int value) {
    int pos, c=0;
    node *tmp = new node;
    tmp->data = value;
    tmp->next = nullptr;
    cout << "Enter position of node to insert after (starts with 0): ";
    cin >> pos;

    if (pos == 0){
        if (this->is_empty()){
            head = tmp;
            tail = tmp;
        }else{
            tmp->next = head->next;
            head->next = tmp;
            tail = tmp;
        }
    }else{
        node *tmp2 = head;
        while(c != pos){
            tmp2 = tmp2->next;
            c++;
        }
        if (c == pos){
            tmp->next = tmp2->next;
            tmp2->next = tmp;
        }else{
            cout << "Unregistered position!" << endl;
        }
    }
}

void list::display(){
    node *tmp = head;
    if (is_empty())
        cout << "List is empty." << endl;
    else{
        cout << "Current list: ";
        while(tmp != nullptr){
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
}

void list::clear(){
    while(head != nullptr){
        this->pop();
    }
    cout << "List is emptyed" << endl;
}

void list::del(){
    int pos, c=1;
    cout << "Enter position of node to delete (starts with 0): ";
    cin >> pos;
    node *tmp = head;
    if (pos == 0 && head == tail){  // if there is only 1 node
        head = nullptr;
        tail = nullptr;
        cout << "The list is emptied." << endl;
    }else{
        while(c != pos){
            tmp = tmp->next;
            c++;
        }
        tmp->next = tmp->next->next;
        cout << pos << "'s node successfully deleted." << endl;
    }


}

void list::search(int value) {  // обычный линейный поиск
    int pos=0; node *tmp = head;

    if (this->is_empty()){
        cout << "List is empty.";
    }else{
        while (tmp != nullptr) {
            if (tmp->data == value){
                cout << "Your data is on the " << pos <<"'s position" << endl;
                return;
            }
            tmp = tmp->next; pos++;
        }
        cout << "There is no such data" << endl;
    }
}

void list::reverse() {
    node *curr = head;
    node *prev= nullptr, *next;

    do{
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }while(curr != nullptr);

    tail = head;
    head = prev;
}

void list::rec_display(node *tmp){
    if(tmp == nullptr){
        cout << "nullptr" << endl;
    }
    else{
        cout << tmp->data << " ";
        rec_display(tmp->next);
    }
}

node* list::gettail() {
    node *tmp=head;
    while(tmp->next != nullptr)
        tmp = tmp->next;
    return tmp;
}

void list::bubblesort() {
    struct node *tmp, *next;

    if (this->is_empty()){
        cout<<"The List is empty"<<endl;
        return;
    }

    tmp = head;
    while (tmp != nullptr){  // сортировка выбором
        for (next = tmp->next; next != nullptr; next = next->next){  // поставит на 0,1,2... позицию минимальный эл-т
            if (tmp->data > next->data){
                swap(tmp->data, next->data);
            }

        }
        tmp = tmp->next;  // переход на следующую поз.
    }
    cout << "List is sorted." << endl;
}

void list::taskB(){
    if (this->is_empty()) {return;}
    if (head == tail && head->data < 0) {
        this->pop(); cout << "Task successfully completed." << endl; return;
    } // для случая одной ноды


    node *tmp = head, *prev=tmp;
    while(tmp != nullptr){
        if (tmp == head && tmp->data < 0) {
            tmp = tmp->next;
            prev = tmp;
            this->pop();
        }

        if (tmp->data < 0){
            prev->next = tmp->next;
            tmp = tmp->next;
        }else{
            prev = tmp;
            tmp = tmp->next;
        }
    }
    cout << "Task successfully completed." << endl;
}

char menu() {
    char choice;
    cout << endl << endl << " ***** Single linked list(LIFO) by aso *****" << endl;
    cout << "1. Push element" << endl;
    cout << "2. Pop elemet" << endl;
    cout << "3. Append list" << endl;
    cout << "4. Insert value" << endl;
    cout << "5. Display list" << endl;
    cout << "6. Delete a node" << endl;
    cout << "7. Clear list" << endl;
    cout << "8. Sort list" << endl;
    cout << "9. Search by value" << endl;
    cout << "r. Reverse" << endl;
    cout << "B. Выполнить задание лабораторной работы: 'удалить из стека все нечетные числа'." << endl;
    cout << "0. Exit" << endl;

    cout << endl << "Choice: ";
    cin >> choice;
    return choice;

}

int main(){
    char choice;
    int data;
    list st;

    do{
        choice = menu();
        switch(choice){
            case '1':{
                cout << "Enter value:"; cin >> data;
                st.push(data); break;
            }
            case '2': st.pop(); break;
            case '3': {
                cout << "Enter value:"; cin >> data;
                st.append(data); break;
            }
            case '4': {
                cout << "Enter value:"; cin >> data;
                st.append(data); break;
            }
            case '5': st.display(); break;
            case '6': st.del(); break;
            case '7': st.clear(); break;
            case '9': {
                cout << "Enter value:"; cin >> data;
                st.search(data); break;
            }
            case '8': st.bubblesort(); break;
            case 'r': st.reverse(); break;
            case 'B': st.taskB(); st.display(); break;
            case '0': cout << "exit."; break;
            default: cout << "Wrong choice. Try again." << endl;
        }
    }while(choice != '0');

    return 0;
}

/*
node *partition(node *head, node *tail, node *newhead, node *newtail){
    node *pivot = tail; // посл нода
    node *prev = nullptr, *curr = head, *end = pivot;

    while(curr != pivot){
        if (curr->data < pivot->data){
            if (newhead == nullptr)  // в newhead теперь эл-т < pivot:
                newhead = curr;

            prev = curr;
            curr = curr->next;
        }else{
            if (prev)
                prev->next = curr->next;
            node *tmp = curr->next;
            curr->next = nullptr;
            end->next = curr;
            end = curr;
            curr = tmp;
        }
    }

    if (newhead == nullptr)
        newhead = pivot; // значит выбрали самый маленьнкий эл-т, надо поставить его в head
    newtail = end;

    return pivot;
}

node *quicksort(node *head, node *tail){
    if (head == tail)  // если одна нода
        return head;

    node *newhead= nullptr, *newtail= nullptr;
    node *pivot = partition(head, tail, newhead, newtail);

    if (newhead != pivot){  // если pivot дошел до начала, значит список отсортирован
        node *tmp = newhead;
        while(tmp->next != pivot){ tmp = tmp->next;}
        newhead = quicksort(newhead, tmp); // сортировка левой части, т.е. до pivot-1
    }

    pivot->next = quicksort(pivot->next, newtail);  // сортировка правой части от pivot+1;
    return newhead;
}

void list::qsort() {
    if (!this->is_empty())
        head = quicksort(head, tail);
}

 */