#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char customerName[50];
    char email[50];
    char address[100];
} Customer;

typedef struct {
    char productName[50];
    float price;
} Product;

typedef struct OrderNode {
    int orderID;
    Customer customer;
    Product products[10];
    int productCount;
    char shippingDetails[100];
    struct OrderNode* next;
} OrderNode;

OrderNode* createOrder(int orderID, const char* customerName, const char* email, const char* address,
                       const char* shippingDetails) {
    OrderNode* newOrder = (OrderNode*)malloc(sizeof(OrderNode));
    newOrder->orderID = orderID;
    strcpy(newOrder->customer.customerName, customerName);
    strcpy(newOrder->customer.email, email);
    strcpy(newOrder->customer.address, address);
    newOrder->productCount = 0;
    strcpy(newOrder->shippingDetails, shippingDetails);
    newOrder->next = NULL;
    return newOrder;
}

void addProduct(OrderNode* order, const char* productName, float price) {
    if (order->productCount < 10) {
        strcpy(order->products[order->productCount].productName, productName);
        order->products[order->productCount].price = price;
        order->productCount++;
        printf("Product '%s' added to the order.\n", productName);
    } else {
        printf("Cannot add more products to the order.\n");
    }
}

void displayOrder(OrderNode* order) {
    printf("\nOrder ID: %d\n", order->orderID);
    printf("Customer: %s, Email: %s, Address: %s\n", order->customer.customerName, order->customer.email, order->customer.address);
    printf("Products:\n");
    for (int i = 0; i < order->productCount; ++i) {
        printf("  %s - $%.2f\n", order->products[i].productName, order->products[i].price);
    }
    printf("Shipping Details: %s\n", order->shippingDetails);
}

void freeOrderList(OrderNode* head) {
    OrderNode* current = head;
    OrderNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    OrderNode* orderList = NULL;

    int orderID = 1;
    char customerName[50];
    char email[50];
    char address[100];
    char shippingDetails[100];
    char productName[50];
    float price;
    int choice;

    do {
        printf("\nE-commerce Order Processing Menu:\n");
        printf("1. Create Order\n");
        printf("2. Add Product to Order\n");
        printf("3. Display Orders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                scanf("%s", customerName);
                printf("Enter customer email: ");
                scanf("%s", email);
                printf("Enter customer address: ");
                scanf(" %[^\n]s", address);
                printf("Enter shipping details: ");
                scanf(" %[^\n]s", shippingDetails);

                OrderNode* newOrder = createOrder(orderID++, customerName, email, address, shippingDetails);
                if (orderList == NULL) {
                    orderList = newOrder;
                } else {
                    newOrder->next = orderList;
                    orderList = newOrder;
                }
                printf("Order created successfully.\n");
                break;
            case 2:
                if (orderList == NULL) {
                    printf("No orders to add products to. Create an order first.\n");
                } else {
                    printf("Enter product name: ");
                    scanf("%s", productName);
                    printf("Enter product price: ");
                    scanf("%f", &price);
                    addProduct(orderList, productName, price);
                }
                break;
            case 3:
                if (orderList == NULL) {
                    printf("No orders to display.\n");
                } else {
                    OrderNode* currentOrder = orderList;
                    while (currentOrder != NULL) {
                        displayOrder(currentOrder);
                        currentOrder = currentOrder->next;
                    }
                }
                break;
            case 4:
                // Exit the program
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    // Free memory used by the order list
    freeOrderList(orderList);

    return 0;
}
