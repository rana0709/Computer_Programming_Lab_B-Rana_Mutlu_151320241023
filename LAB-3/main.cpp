#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;
};

void visit(Page* &head, Page* &current, string url, string title, int h, int m, int s) {
    Page* p = new Page();
    p->url = url;
    p->title = title;
    p->accessTime[0] = h;
    p->accessTime[1] = m;
    p->accessTime[2] = s;
    p->next = nullptr;
    p->prev = nullptr;

    if (head == nullptr) {
        head = p;
        current = p;
        return;
    }

    Page* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = p;
    p->prev = last;
    current = p;
}

void goBack(Page* &current) {
    if (current != nullptr && current->prev != nullptr) {
        current = current->prev;
        cout << "Back to: " << current->title << endl;
    } else {
        cout << "Can't go back!" << endl;
    }
}

void goForward(Page* &current) {
    if (current != nullptr && current->next != nullptr) {
        current = current->next;
        cout << "Forward to: " << current->title << endl;
    } else {
        cout << "Can't go forward!" << endl;
    }
}

void deleteEntry(Page* &head, Page* &current) {
    if (current == nullptr) return;

    Page* target = current;

    if (current == head) {
        head = current->next;
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    if (current->prev != nullptr) {
        current = current->prev;
    } else {
        current = current->next;
    }

    delete target;
    cout << "Page deleted." << endl;
}

void displayHistory(Page* head, Page* current) {
    cout << "\n--- History ---" << endl;
    Page* temp = head;

    while (temp != nullptr) {
        if (temp == current) {
            cout << "-> ";
        } else {
            cout << "   ";
        }

        cout << temp->title << " (" << temp->url << ") ";

        for (int i = 0; i < 3; i++) {
            if (temp->accessTime[i] < 10) cout << "0";
            cout << temp->accessTime[i];
            if (i < 2) cout << ":";
        }
        cout << endl;

        temp = temp->next;
    }
    cout << "---------------\n" << endl;
}

void clearHistory(Page* &head) {
    Page* temp = head;
    while (temp != nullptr) {
        Page* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
}

int main() {
    Page* head = nullptr;
    Page* current = nullptr;

    visit(head, current, "a.com", "Site A", 14, 30, 0);
    visit(head, current, "b.com", "Site B", 14, 35, 12);
    visit(head, current, "c.com", "Site C", 14, 40, 55);

    displayHistory(head, current);

    goBack(current);
    displayHistory(head, current);

    deleteEntry(head, current);
    displayHistory(head, current);

    goForward(current);
    displayHistory(head, current);

    clearHistory(head);

    return 0;
}
