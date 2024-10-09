#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <new>

#include "GroceryItem.hpp"

int main() {
  std::vector<std::unique_ptr<GroceryItem>> shoppingCart;

  std::cout << "Welcome to Kroger.  Place grocery items into your shopping cart by entering each item's information.\n"
            << "   enclose string entries in quotes, separate fields with comas\n"
            << "   for example:  \"00016000306707\", \"Betty Crocker\", \"Betty Crocker Double Chocolate Chunk Cookie Mix\", 17.19\n"
            << "   Enter CTL-Z (Windows) or CTL-D (Linux) to quit\n\n";
  while (true) {
    auto item = std::make_unique<GroceryItem>();
    std::cout << "Enter UPC, Product Brand, Product Name, and Price: ";
    if (!(std::cin >> *item)) {
        break;
    }
    std::cout << "\nItem added to shopping cart: " << *item << "\n\n";
    shoppingCart.push_back(std::move(item));
  }
  std::cout << "\n\n\nHere is an itemized list of the items in your shopping cart:\n";
  for (auto i = shoppingCart.rbegin(); i != shoppingCart.rend(); ++i) {
    std::cout << *shoppingCart.back() << '\n';
    shoppingCart.pop_back();
  }
  return 0;
}
