#include <iostream>
#include <string>

using namespace std;

struct Node {
    string songTitle;
    Node* next;
};

void addSong(Node*& head, string title) {
    Node* newNode = new Node();
    newNode->songTitle = title;
    newNode->next = head;
    head = newNode;
}

void searchSong(Node* head, string title) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->songTitle == title) {
            cout << "Found: " << title << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Not Found." << endl;
}

void listSongs(Node* head) {
    if (head == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }

    Node* temp = head;
    int order = 1;
    while (temp != nullptr) {
        cout << order << ". " << temp->songTitle << endl;
        temp = temp->next;
        order++;
    }
}

int main() {
    Node* head = nullptr;
    int choice;
    string songName;

    while (true) {
        cout << "\n1. Add\n2. Search\n3. List\n4. Exit\nEnter choice: ";
        if (!(cin >> choice)) break;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter song title: ";
            getline(cin, songName);
            addSong(head, songName);
        }
        else if (choice == 2) {
            cout << "Enter song to search: ";
            getline(cin, songName);
            searchSong(head, songName);
        }
        else if (choice == 3) {
            listSongs(head);
        }
        else if (choice == 4) {
            break;
        }
    }

    return 0;
}
