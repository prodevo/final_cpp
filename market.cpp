#include <iostream>
#include <fstream>
#include "marketplace.h"

using namespace std;

product products[] = { {1, "noutbuk", 1250.1}, {2, "smartphon", 800.2}, {3, "navushnyky", 150.3}, {4, "klaviatura", 60.4}, {5, "mysha(nu ta, kotra dlya kompjutera)", 40.5} };
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

            cart->items[cart->size++] = { products[i], qty };
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

    ofstream out("cart.txt");

    for (int i = 0; i < cart.size; i++) {
        out << cart.items[i].product.id << " " << cart.items[i].quantity << "\n";
    }
    out.close();
    return 0;
}

int load_cart(cart* cart) {
    ifstream in("cart.txt");

    if (!in) {
        return 0;
    }

    int pid, qty;

    while (in >> pid >> qty) {

        for (int i = 0; i < product_count; i++) {

            if (products[i].id == pid) {

                if (cart->size == cart->capacity) {

                    cart->capacity *= 2;
                    cart_it* t = new cart_it[cart->capacity];
                    for (int j = 0; j < cart->size; j++) t[j] = cart->items[j];
                    delete[] cart->items;
                    cart->items = t;
                }
                cart->items[cart->size++] = { products[i], qty };
                break;
            }
        }
    }
    in.close();
    return 0;
}
