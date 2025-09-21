#include <iostream>
#include <string>
using namespace std;

const int MAX_ITEMS = 100; // maximum inventory size

// Inventory Item ADT
struct InventoryItem {
    int ItemID;
    string ItemName;
    int Quantity;
    float Price;
};

// Inventory Management System
class InventorySystem {
private:
    InventoryItem items[MAX_ITEMS]; // array for inventory
    int itemCount;

    // For Price and Quantity Tables
    float priceQuantityTable[MAX_ITEMS][2]; 
    // 0 -> Price, 1 -> Quantity

public:
    InventorySystem() {
        itemCount = 0;
    }

    // Insert item
    void insertItem(int id, string name, int qty, float price) {
        if (itemCount < MAX_ITEMS) {
            items[itemCount].ItemID = id;
            items[itemCount].ItemName = name;
            items[itemCount].Quantity = qty;
            items[itemCount].Price = price;

            // Update 2D table
            priceQuantityTable[itemCount][0] = price;
            priceQuantityTable[itemCount][1] = qty;

            itemCount++;
            cout << "Item inserted successfully.\n";
        } else {
            cout << "Inventory full! Cannot insert more items.\n";
        }
        // Time Complexity: O(1)
        // Space Complexity: O(1) (uses existing array space)
    }

    // Delete item by ID
    void deleteItem(int id) {
        int index = -1;
        for (int i = 0; i < itemCount; i++) {
            if (items[i].ItemID == id) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int i = index; i < itemCount - 1; i++) {
                items[i] = items[i + 1];
                priceQuantityTable[i][0] = priceQuantityTable[i + 1][0];
                priceQuantityTable[i][1] = priceQuantityTable[i + 1][1];
            }
            itemCount--;
            cout << "Item deleted successfully.\n";
        } else {
            cout << "Item not found!\n";
        }
        // Time Complexity: O(n) (shifting elements)
        // Space Complexity: O(1)
    }

    // Search item by ID or Name
    void searchItem(int id, string name = "") {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].ItemID == id || items[i].ItemName == name) {
                cout << "Item Found: " << items[i].ItemID << " - "
                     << items[i].ItemName << ", Qty: " << items[i].Quantity
                     << ", Price: " << items[i].Price << endl;
                return;
            }
        }
        cout << "Item not found!\n";
        // Time Complexity: O(n)
        // Space Complexity: O(1)
    }

    // Display inventory
    void displayInventory() {
        cout << "\nCurrent Inventory:\n";
        for (int i = 0; i < itemCount; i++) {
            cout << items[i].ItemID << " | " << items[i].ItemName
                 << " | Qty: " << items[i].Quantity
                 << " | Price: " << items[i].Price << endl;
        }
    }

    // Row-major ordering display
    void displayRowMajor() {
        cout << "\nPrice-Quantity Table (Row-Major Order):\n";
        for (int i = 0; i < itemCount; i++) {
            cout << "Item " << i + 1 << ": ";
            for (int j = 0; j < 2; j++) {
                cout << priceQuantityTable[i][j] << " ";
            }
            cout << endl;
        }
        // Time Complexity: O(n)
    }

    // Column-major ordering display
    void displayColumnMajor() {
        cout << "\nPrice-Quantity Table (Column-Major Order):\n";
        for (int j = 0; j < 2; j++) {
            cout << "Column " << j << ": ";
            for (int i = 0; i < itemCount; i++) {
                cout << priceQuantityTable[i][j] << " ";
            }
            cout << endl;
        }
        // Time Complexity: O(n)
    }

    // Sparse Representation for rarely restocked products
    void optimizeSparseStorage() {
        cout << "\nSparse Representation (Items with Quantity <= 5):\n";
        cout << "ItemID | Name | Qty | Price\n";
        for (int i = 0; i < itemCount; i++) {
            if (items[i].Quantity <= 5) { // rarely restocked
                cout << items[i].ItemID << " | " << items[i].ItemName
                     << " | " << items[i].Quantity
                     << " | " << items[i].Price << endl;
            }
        }
        // Time Complexity: O(n)
        // Space Complexity: O(1)
    }
};

// Driver Code
int main() {
    InventorySystem store;

    // Insert sample items
    store.insertItem(101, "Rice", 50, 45.5);
    store.insertItem(102, "Sugar", 30, 40.0);
    store.insertItem(103, "Oil", 20, 120.0);
    store.insertItem(104, "Salt", 4, 20.0);  // Rarely restocked
    store.insertItem(105, "Tea", 3, 150.0);  // Rarely restocked

    // Display inventory
    store.displayInventory();

    // Search item
    store.searchItem(102);
    store.searchItem(-1, "Tea");

    // Delete item
    store.deleteItem(101);

    // Display after deletion
    store.displayInventory();

    // Show row-major and column-major orderings
    store.displayRowMajor();
    store.displayColumnMajor();

    // Sparse storage optimization
    store.optimizeSparseStorage();

    return 0;
}
