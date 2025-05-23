#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "marketplace.h"

using namespace std;

int main() {
    cart cart;
    initialize_cart(&cart);

    int choice;
    do {
        cout << "=== Marketplace Menu ===\n";
        cout << "1. pokazaty producty\n";
        cout << "2. dodaty do koshyka\n";
        cout << "3. pokazaty koshyk\n";
        cout << "4. zberegty koshyk\n";
        cout << "5. zavantazhyty koshyk\n";
        cout << "0. VYHID\n> ";
        cin >> choice;

        switch (choice) {
        case 1:
            show_products();
            break;

        case 2:
            add_to_cart(&cart);
            break;

        case 3:
            show_cart(cart);
            break;


        case 4:
            save_cart(cart);
            break;

        case 5:
            load_cart(&cart);
            break;

        case 0:
            break;

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 0);

    delete_cart(&cart);
    return 0;
} 
