#ifndef marketplace_h
#define marketplace_h
#define _CRT_SECURE_NO_WARNINGS 1

struct product {
    int id;
    const char* name;
    float price;
};

struct cart_it {
    product product;
    int quantity;
};

struct cart {
    cart_it* items;
    int size;
    int capacity;
};

int initialize_cart(cart* cart);
int delete_cart(cart* cart);
int show_products();
int add_to_cart(cart* cart);
int show_cart(const cart& cart);
int save_cart(const cart& cart);
int load_cart(cart* cart);

#endif
