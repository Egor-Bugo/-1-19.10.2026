#include <iostream>
#include "Keeper.h"
#include "ListQueue.h"
#include "StackQueue.h"
#include "DequeQueue.h"
#include "MyException.h"

void showMenu() {
    std::cout << "\n=== MENU (Variant 11: Queue-based Containers) ===\n";
    std::cout << "1. Add List\n";
    std::cout << "2. Add Stack\n";
    std::cout << "3. Add Deque\n";
    std::cout << "4. Show all containers\n";
    std::cout << "5. Remove container by index\n";
    std::cout << "6. Interact with a specific container (Push/Pop/Print)\n";
    std::cout << "7. Save to file\n";
    std::cout << "8. Load from file\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Keeper keeper;
    int choice = -1;

    while (choice != 0) {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        try {
            switch (choice) {
            case 1: {
                keeper.add(new ListQueue());
                std::cout << "List added successfully.\n";
                break;
            }
            case 2: {
                keeper.add(new StackQueue());
                std::cout << "Stack added successfully.\n";
                break;
            }
            case 3: {
                keeper.add(new DequeQueue());
                std::cout << "Deque added successfully.\n";
                break;
            }
            case 4: {
                keeper.printAll();
                break;
            }
            case 5: {
                int idx;
                std::cout << "Enter index to remove: ";
                std::cin >> idx;
                keeper.remove(idx);
                std::cout << "Container removed.\n";
                break;
            }
            case 6: {
                int idx;
                std::cout << "Enter container index: ";
                std::cin >> idx;
                Base* obj = keeper.get(idx);

                int subChoice = -1;
                while (subChoice != 0) {
                    std::cout << "\n--- Container [" << idx << "] (" << obj->getType() << ") ---\n";
                    std::cout << "1. Print elements\n";
                    std::cout << "2. Push element\n";
                    std::cout << "3. Pop element\n";
                    if (std::strcmp(obj->getType(), "Deque") == 0) {
                        std::cout << "4. Push Front (Deque specific)\n";
                        std::cout << "5. Pop Back (Deque specific)\n";
                    }
                    std::cout << "0. Back to main menu\n";
                    std::cout << "Choice: ";
                    std::cin >> subChoice;

                    if (subChoice == 1) {
                        obj->print();
                    }
                    else if (subChoice == 2) {
                        int val;
                        std::cout << "Enter value to push: ";
                        std::cin >> val;
                        obj->push(val);
                    }
                    else if (subChoice == 3) {
                        int val = obj->pop();
                        std::cout << "Popped value: " << val << "\n";
                    }
                    else if (subChoice == 4 && std::strcmp(obj->getType(), "Deque") == 0) {
                        int val;
                        std::cout << "Enter value to push front: ";
                        std::cin >> val;
                        static_cast<DequeQueue*>(obj)->pushFront(val);
                    }
                    else if (subChoice == 5 && std::strcmp(obj->getType(), "Deque") == 0) {
                        int val = static_cast<DequeQueue*>(obj)->popBack();
                        std::cout << "Popped back value: " << val << "\n";
                    }
                }
                break;
            }
            case 7: {
                char filename[100];
                std::cout << "Enter filename to save (e.g., data.txt): ";
                std::cin >> filename;
                keeper.saveToFile(filename);
                break;
            }
            case 8: {
                char filename[100];
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                keeper.loadFromFile(filename);
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Unknown choice!\n";
            }
        }
        catch (const MyException& ex) {
            std::cout << "[EXCEPTION CAUGHT]: " << ex.getMessage() << "\n";
        }
        catch (...) {
            std::cout << "[UNKNOWN EXCEPTION CAUGHT]\n";
        }
    }

    return 0;
}