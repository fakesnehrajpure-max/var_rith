#include <iostream>
using namespace std;

struct Node {
    int data;
    struct Node *next;
};

class LinkedList {
    private:
        struct Node *head;
    public:
        void initList() {
            head = NULL;
        }
        void display() {
            if(head == NULL) {
                cout << "List is empty" << endl;
                return;
            }
            struct Node *temp = head;
            while(temp != NULL) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
        }
        void addNode(int data) {
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = data;
            newNode->next = NULL;
            if(head == NULL) {
                head = newNode;
                return;
            }
            struct Node *temp = head;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        void deleteNode() {
            if(head == NULL) {
                cout << "List is empty" << endl;
                return;
            }
            if(head->next == NULL) {
                cout << "Deleted " << head->data << endl;
                free(head);
                head = NULL;
                return;
            }
            struct Node *temp = head;
            while(temp->next->next != NULL) {
                temp = temp->next;
            }
            cout << "Deleted " << temp->next->data << endl;
            free(temp->next);
            temp->next = NULL;
        }
};

int main() {
    cout << "0: Init" << endl;
    cout << "1: Display" << endl;
    cout << "2: Add Node" << endl;
    cout << "3: Delete Node" << endl;
    int choice, val;
    LinkedList list;
    while(1) {
        cout << "\nEnter choice: ";
        cin >> choice;
        switch(choice) {
            case 0:
                list.initList();
                cout << "List initialized" << endl;
                break;
            case 1:
                list.display();
                break;
            case 2:
                cout << "Enter value to be added: ";
                cin >> val;
                list.addNode(val);
                break;
            case 3:
                list.deleteNode();
                break;
        }
    }
    return 0;
}