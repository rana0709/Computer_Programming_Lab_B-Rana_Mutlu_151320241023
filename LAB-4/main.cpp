#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string customerName;
    string transactionType;
};

const int QUEUE_SIZE = 5;

struct CustomerQueue {
    Customer customers[QUEUE_SIZE];
    int front = -1;
    int rear = -1;
    int count = 0;
};

bool isQueueFull(CustomerQueue& q) {
    return q.count == QUEUE_SIZE;
}

bool isQueueEmpty(CustomerQueue& q) {
    return q.count == 0;
}

void enqueue(CustomerQueue& q, string name, string type) {
    if (isQueueFull(q)) {
        cout << "Queue is full!\n";
        return;
    }
    if (isQueueEmpty(q)) {
        q.front = 0;
        q.rear = 0;
    }
    else {
        q.rear = (q.rear + 1) % QUEUE_SIZE;
    }
    q.customers[q.rear].customerName = name;
    q.customers[q.rear].transactionType = type;
    q.count++;
}

void dequeue(CustomerQueue& q, Customer& servedCustomer) {
    if (isQueueEmpty(q)) {
        cout << "Queue is empty!\n";
        return;
    }
    servedCustomer = q.customers[q.front];
    if (q.front == q.rear) {
        q.front = -1;
        q.rear = -1;
    }
    else {
        q.front = (q.front + 1) % QUEUE_SIZE;
    }
    q.count--;
}

void push(MoneyBundle*& top, string serial, string currency, int b100, int b50, int b20) {
    MoneyBundle* newBundle = new MoneyBundle();
    newBundle->serialNumber = serial;
    newBundle->currencyType = currency;
    newBundle->billCounts[0] = b100;
    newBundle->billCounts[1] = b50;
    newBundle->billCounts[2] = b20;
    newBundle->next = top;
    top = newBundle;
}

bool isStackEmpty(MoneyBundle* top) {
    return top == nullptr;
}

void pop(MoneyBundle*& top, MoneyBundle*& poppedBundle) {
    if (isStackEmpty(top)) {
        poppedBundle = nullptr;
        return;
    }
    poppedBundle = top;
    top = top->next;
}

void processTransaction(CustomerQueue& q, MoneyBundle*& top) {
    if (isQueueEmpty(q)) {
        cout << "No customers waiting.\n";
        return;
    }
    if (isStackEmpty(top)) {
        cout << "No money in the safe.\n";
        return;
    }

    Customer servedCustomer;
    dequeue(q, servedCustomer);

    MoneyBundle* usedBundle;
    pop(top, usedBundle);

    cout << "Transaction Processed:\n";
    cout << "Customer: " << servedCustomer.customerName << " (" << servedCustomer.transactionType << ")\n";
    cout << "Money Bundle Given: " << usedBundle->serialNumber << " [" << usedBundle->currencyType << "]\n";
    cout << "Bills - 100s: " << usedBundle->billCounts[0]
        << " | 50s: " << usedBundle->billCounts[1]
        << " | 20s: " << usedBundle->billCounts[2] << "\n\n";

    delete usedBundle;
}

void display(CustomerQueue& q, MoneyBundle* top) {
    cout << "\n--- Money Safe (Stack) ---\n";
    if (isStackEmpty(top)) {
        cout << "Safe is empty.\n";
    }
    else {
        MoneyBundle* temp = top;
        while (temp != nullptr) {
            cout << "Bundle: " << temp->serialNumber << " [" << temp->currencyType << "] -> "
                << "100s: " << temp->billCounts[0] << ", "
                << "50s: " << temp->billCounts[1] << ", "
                << "20s: " << temp->billCounts[2] << "\n";
            temp = temp->next;
        }
    }

    cout << "\n--- Customer Line (Queue) ---\n";
    if (isQueueEmpty(q)) {
        cout << "No customers waiting.\n";
    }
    else {
        int i = q.front;
        for (int c = 0; c < q.count; c++) {
            cout << c + 1 << ". " << q.customers[i].customerName << " - " << q.customers[i].transactionType << "\n";
            i = (i + 1) % QUEUE_SIZE;
        }
    }
    cout << "------------------------------\n\n";
}

int main() {
    CustomerQueue queue;
    MoneyBundle* safeTop = nullptr;

    push(safeTop, "1", "USD", 10, 5, 0);
    push(safeTop, "2", "TL", 50, 20, 10);
    push(safeTop, "3", "EUR", 5, 10, 20);

    enqueue(queue, "A", "getcash");
    enqueue(queue, "B", "putcash");
    enqueue(queue, "C", "getcash");
    enqueue(queue, "D", "putcash");

    display(queue, safeTop);

    processTransaction(queue, safeTop);

    display(queue, safeTop);

    processTransaction(queue, safeTop);
    processTransaction(queue, safeTop);

    display(queue, safeTop);

    return 0;
}