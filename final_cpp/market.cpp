#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "marketplace.h"

using namespace std;

product products[] = { {1, "noutbuk", 1250.1f}, {2, "smartphon", 800.2f}, {3, "navushnyky", 150.3f}, {4, "klaviatura", 60.4f}, {5, "mysha(nu ta, kotra dlya kompjutera)", 40.5f} };
int product_count = sizeof(products) / sizeof(product);

int initialize_cart(cart* cart) {
    cart->capacity = 5;
    cart->size = 0;
    cart->items = new cart_it[cart->capacity];
    return 0;
}

int delete_cart(cart* cart) {
    delete[] cart->items;
    cart->items = nullptr;
    cart->size = 0;
    cart->capacity = 0;
    return 0;
}

int show_products() {
    for (int i = 0; i < product_count; i++) {
        cout << products[i].id << ". " << products[i].name << " - " << products[i].price << "$\n";
    }
    return 0;
}

int add_to_cart(cart* cart) {

    int pid, qty;
    cout << "vvedit ID produktu ta kilkist: ";
    cin >> pid >> qty;

    for (int i = 0; i < product_count; i++) {

        if (products[i].id == pid) {

            if (cart->size == cart->capacity) {

                cart->capacity *= 2;
                cart_it* t = new cart_it[cart->capacity];

                for (int s = 0; s < cart->size; s++) {
                    t[s] = cart->items[s];
                }

                delete[] cart->items;
                cart->items = t;
            }

            cart->items[cart->size].product = products[i];
            cart->items[cart->size].quantity = qty;
            cart->size++;
            return 0;
        }
    }
    cout << "Product ne znaideno((\n";
    return 0;
}

int show_cart(const cart& cart) {

    float total = 0;

    for (int i = 0; i < cart.size; i++) {
        const cart_it& item = cart.items[i];
        cout << item.product.name << " x" << item.quantity << " = " << item.product.price * item.quantity << "$\n";
        total += item.product.price * item.quantity;
    }
    cout << "Vsogo: " << total << "$\n";
    return 0;
}

int save_cart(const cart& cart) {

    FILE* file;
    fopen_s(&file, "cart.txt", "w");

    if (file == nullptr) {
        perror("ERROR");
        return 0;
    }

    for (int i = 0; i < cart.size; i++) {
        fprintf(file, "%d %d\n", cart.items[i].product.id, cart.items[i].quantity);
    }

    fclose(file);
    return 0;
}

int load_cart(cart* cart) {

    FILE* file;
    fopen_s(&file, "cart.txt", "w");

    int pid, qty;

    if (file == nullptr) {
        perror("ERROR");
        return 0;
    }

    while (fscanf_s(file, "%d %d",  &pid, &qty) == 2) {

        for (int i = 0; i < product_count; i++) {

            if (products[i].id == pid) {

                if (cart->size == cart->capacity) {

                    cart->capacity *= 2;
                    cart_it* t = new cart_it[cart->capacity];
                    for (int j = 0; j < cart->size; j++) t[j] = cart->items[j];
                    delete[] cart->items;
                    cart->items = t;
                }
                cart->items[cart->size].product = products[i];
                cart->items[cart->size].quantity = qty;
                cart->size++;
                break;
            }
        }
    }

    fclose(file);
    return 0;
}
