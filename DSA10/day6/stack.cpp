#include <iostream>
using namespace std;
class Stack {
    private:
        int top;
        int size;
        int *arr;
    public:
    void initStack(int size) {
        this->top = -1;
        this->size = size;
        this->arr = (int *)malloc(size*sizeof(int));
    }
    void display() {
        if(top < 0) {
            cout << "Stack is empty" << endl;
            return;
        }
        for(int i = top; i >= 0; i--) {
            cout << arr[i] << endl;
        }
    }
    void push(int data) {
        if(top >= size-1) {
            cout << "Stack is full" << endl;
            return;
        }
        arr[++top] = data;
    }
    void pop() {
        if(top < 0) {
            cout << "Stack is empty" << endl;
            return;
        }
        int val = arr[top--];
        cout << "Popped " << val << endl;
    }

};
int main() {
    cout << "0: Init" << endl;
    cout << "1: Display" << endl;
    cout << "2: Push" << endl;
    cout << "3: Pop" << endl;
    int choice, val;
    Stack stack;
    while(1) {
        cout << "\nEnter choice: ";
        cin >> choice;
            switch(choice) {
            case 0:
                cout << "Enter max size stack: ";
                cin >> val;
                stack.initStack(val);
                break;
            case 1:
                stack.display();
                break;
            case 2:
                cout << "Enter value to be pushed: ";
                cin >> val;
                stack.push(val);
                break;
            case 3:
                stack.pop();
                break;
        }
    }
    return 0;
}