#include <bits/stdc++.h>
#include <chrono>
#include <thread>
using namespace std;

map<char, vector<unordered_map<string, string>>> user; // Global user storage
unordered_map<string, unordered_map<string, int>> menu;
// Global menu storage
unordered_map<string, vector<string>> review;
vector<int> order; // Global order storage
string OrderStatus = "Pending";
// Cross-platform screen clear
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Clear the last 2 lines
void clearLastNLines(int n) {
  for (int i = 0; i < n; ++i) {
    // Move cursor up one line and clear the line
    cout << "\033[A\33[2K\r";
  }
  cout.flush();
}

class User {
protected:
  string password;

public:
  string email;
  string phone;
  string userID; //------+
                 //      |
                 //      V
  User(string userId) : userID(userId) {
    for (const auto &t : user) {
      for (const auto &u : t.second) {
        // u is a map
        if (u.find("userID") != u.end() && u.at("userID") == userID) {
          email = u.at("email");
          phone = u.at("phone");
          password = u.at("password");
          return;
        }
      }
    }
    cout << "User not found!" << endl;
  }

  void manageProfile() {
    string newEmail, newPhone;
    cout << "Enter new information...\n";
    cout << "Email: ";
    cin >> newEmail;
    cout << "Phone: ";
    cin >> newPhone;

    for (auto &t : user) {
      for (auto &u : t.second) {
        if (u["userID"] == userID) {
          u["email"] = newEmail;
          u["phone"] = newPhone;
          email = newEmail;
          phone = newPhone;
          cout << "Profile updated...!\n";
          return;
        }
      }
    }
    cout << "Profile not found!\n";
  }

  void viewProfile() {
    cout << "User ID: " << userID << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Password: *************" << endl;
  }

  void deleteProfile() {
    bool exit = false;
    for (auto &t : user) {
      for (auto it = t.second.begin(); it != t.second.end(); ++it) {
        if (it->at("userID") == userID) {
          t.second.erase(it);
          cout << "Profile deleted successfully!\n";
          return;
        }
      }
    }
    cout << "Profile not found!\n";
  }
};

class Menu {
public:
  string foodItemID;
  string restaurantID;

  void updateMenu() {
    cout << "Updating menu\n";
    string res, menuName, foodPrice;
    cout << "Enter restaurant name: ";
    cin >> res;
    cout << "Enter food name: ";
    cin >> menuName;
    cout << "Enter food price: ";
    cin >> foodPrice;
    try {
      menu[res][menuName] = stoi(foodPrice);
      cout << "Menu updated successfully\n";
    } catch (...) {
      cout << "Invalid price entered\n";
    }
  }
  void giveOffer() { cout << "Giving offer 10%\n"; }
  void removeFoodItem() { cout << "Removing food item\n"; }
};

class FoodItem {
public:
  string name;
  int price;
  string category;

  void updatePrice() {
    cout << "Updating price\n";
    string res, foodName;
    int newPrice;
    cout << "Enter restaurant name: ";
    cin >> res;
    cout << "Enter food name: ";
    cin >> foodName;
    cout << "Enter new price: ";
    cin >> newPrice;
    if (menu.find(res) != menu.end()) {
      menu[res][foodName] = newPrice;
      cout << "Price updated successfully\n";
    } else {
      cout << "Restaurant not found\n";
    }
  }
};

class CartItem {
public:
  string itemName;
  int itemPrice;
  int itemQuantity;
  float itemTotalPrice;

  void totalPrice() {
    cout << "Total Price\n";
    int sum = 0;
    for (int i : order) {
      sum += i;
    }
    cout << "Total Price: " << sum << endl;
  }
};

class Cart {
public:
  string customerID;
  CartItem cartItem;

  void addItem() {
    cout << "Adding item into cart...\n";
    string res, foodName;
    int quantity;
    cout << "Enter restaurant name: ";
    cin >> res;
    cout << "Enter food name: ";
    cin >> foodName;
    cout << "Enter quantity: ";
    cin >> quantity;
    if (menu.find(res) != menu.end() &&
        menu[res].find(foodName) != menu[res].end()) {
      order.push_back(quantity * menu[res][foodName]);
      cout << "Item added successfully\n";
    } else {
      cout << menu[res][foodName] << endl;
      cout << "Item or restaurant not found\n";
    }
  }

  void removeItem() { cout << "Removing item from cart\n"; }

  void placeOrder() {
    int sum = 0;
    for (int i : order) {
      sum += i;
    }
    cout << "Total Price: " << sum << endl;
    cout << "Placing order\n";
  }
};
class Payment {
public:
  string orderID;
  string customerID;
  string paymentMethod;
  string paymentStatus;
  int couponDiscount;

  void printReceipt() { cout << "Printing receipt\n"; }
  void processPayment() {
    cout << "Processing payment\n";
    string name;
    cout << "Enter your name: ";
    cin >> name;
    int pin;
    cout << "Enter your pin: ";
    cin >> pin;
    this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
    cout << "Payment successful\n";
  }
  void refundPayment() { cout << "Refunding payment\n"; }
};
class Restaurant : public User {
public:
  string restaurantName;
  string restaurantLocation;

  Restaurant(string userId) : User(userId) {
    for (const auto &u : user['R']) {
      if (u.at("userID") == userId) {
        restaurantName = u.at("restaurantName");
        restaurantLocation = u.at("restaurantLocation");
        break;
      }
    }
  }

  void manageMenus() {
    cout << "Managing menus\n";
    Menu m1;
    m1.updateMenu();
  }
  void displayMenu() {
    cout << "Displaying menu\n";
    string res;
    cout << "Enter restaurant name: ";
    cin >> res;

    if (menu.find(res) != menu.end()) {
      cout << "Menu for " << res << ":\n";
      for (const auto &item : menu[res]) {
        cout << item.first << " - Rs. " << item.second << endl;
      }
    } else {
      cout << "Restaurant '" << res << "' not found in the system.\n";
    }
  }

  void prepareOrder() { cout << "Preparing order\n"; }

  void updateOrderStatus() {
    OrderStatus = "Ready";
    cout << "Updating order status: " << OrderStatus << endl;
  }

  void replyToReviews() { cout << "Replying to reviews\n"; }
  void offerDiscounts() { cout << "Offering discounts\n"; }
};
class DeliveryPartner : public User {
private:
  string name;
  string deliveryOrders;
  string currentLocation;
  string vehicleNumber;
  string vehicleType;
  string vehicleModel;

public:
  DeliveryPartner(string userId) : User(userId) {
    for (const auto &u : user['D']) {
      if (u.at("userID") == userId) {
        vehicleNumber = u.at("vehicleNumber");
        vehicleType = u.at("vehicleType");
        vehicleModel = u.at("vehicleModel");
        break;
      }
    }
  }

  void updateOrderStatus() {
    OrderStatus = "Delivered";
    cout << "Updating order status: " << OrderStatus << endl;
  }

  void updateDeliveryRequest() { cout << "Updating delivery request\n"; }
  void contactCustomer() { cout << "Contacting customer\n"; }
  void viewEarnings() { cout << "Delivery partner earnings shown\n"; }
};
class Order {
private:
  string orderID;
  string restaurantID;
  string customerID;
  string deliveryPartnerID;
  string status;
  double totalAmount;
  string paymentInfo;

public:
  void placeOrder() {
    cout << "Placing order\n";
    Payment p1;
    p1.processPayment();
    p1.printReceipt();
    this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
    Restaurant r1("pizzahub");
    r1.prepareOrder();
    r1.updateOrderStatus();
    this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
    DeliveryPartner d1("del");
    d1.updateOrderStatus();
    cout << "Order placed successfully\n";
  }

  void addItem() {
    cout << "Adding item\n";
    string res, foodName;
    int quantity;
    cout << "Enter restaurant name: ";
    cin >> res;
    cout << "Enter food name: ";
    cin >> foodName;
    cout << "Enter quantity: ";
    cin >> quantity;
    if (menu.find(res) != menu.end() &&
        menu[res].find(foodName) != menu[res].end()) {
      order.push_back(quantity * menu[res][foodName]);
      cout << "Item added successfully\n";
    } else {
      cout << "Item or restaurant not found\n";
    }
  }

  void changeOrder() {
    cout << "Changing order\n";
    string res, foodName;
    int quantity, choice;
    cout << "Enter restaurant name: ";
    cin >> res;
    cout << "Enter food name: ";
    cin >> foodName;
    cout << "1: Add item \t 2: Remove item\n";
    cin >> choice;
    if (menu.find(res) == menu.end() ||
        menu[res].find(foodName) == menu[res].end()) {
      cout << "Item or restaurant not found\n";
      return;
    }
    if (choice == 1) {
      cout << "Enter quantity to add: ";
      cin >> quantity;
      order.push_back(quantity * menu[res][foodName]);
      cout << "Item added\n";
    } else if (choice == 2) {
      cout << "Enter quantity to remove: ";
      cin >> quantity;
      order.push_back(-quantity * menu[res][foodName]);
      cout << "Item removed\n";
    } else {
      cout << "Invalid choice\n";
    }
  }

  void cancelOrder() { cout << "Cancelling order\n"; }
};
class Review {
private:
  string reviewID;
  map<string, vector<string>> review;
  int deliveryPartnerID;
  double rating;
  string comment;
  string time;

public:
  void submitReview() {
    string res;
    cout << "Enter Restaurant: ";
    cin >> res;
    string r;
    cout << "Enter review (1-5): ";
    string comment;
    cout << "Enter comment: ";
    cin >> comment;
    cin >> r;
    if (stoi(r) >= 1 && stoi(r) <= 5) {
      review[res] = {res, r, comment};
      cout << "Review submitted successfully\n";
    }
  }

  // void modifyReview(string reviewID) {
  //   cout << "You can edit or delete your review\n";
  //   cout << "1. Edit Review \t 2. Delete Review\n";
  //   int choice;
  //   cin >> choice;
  //   cout << "Modifying review....\n";
  //   if (choice == 1) {
  //     editReview(reviewID);
  //   } else {
  //     deleteReview(reviewID);
  //   }
  //   cout << "Modify Review " << reviewID << " successfully.\n";
  // }

  // private:
  //   void editReview(string reviewID) {
  //     if (review.find(reviewID) != review.end()) {
  //       cout << "Enter new rating: ";
  //       cin >> rating;
  //       cout << "Enter new comment: ";
  //       cin >> comment;
  //       time = string(__DATE__) + " " + string(__TIME__);
  //       review[reviewID][3] = to_string(rating);
  //       review[reviewID][4] = comment;
  //       review[reviewID][5] = time;
  //       cout << "User " << review[reviewID][0]
  //            << " edited their review for restaurant " << review[reviewID][1]
  //            << " and delivery partner " << review[reviewID][2] << " with
  //            rating "
  //            << review[reviewID][3] << " and comment " << review[reviewID][4]
  //            << " at time " << review[reviewID][5] << ".\n";
  //       cout << "Editing review " << reviewID << " successfully.\n";
  //     } else {
  //       cout << "Review ID not found\n";
  //     }
  //   }

  //   void deleteReview(string reviewID) {
  //     if (review.erase(reviewID)) {
  //       cout << "Deleting review " << reviewID << " successfully.\n";
  //     } else {
  //       cout << "Review ID not found\n";
  //     }
  //   }
};
class Customer : public User {
public:
  string fullName;
  string address;
  vector<string> cart;

  Customer(string userID) : User(userID) {
    for (const auto &u : user['C']) {
      if (u.at("userID") == userID) {
        fullName = u.at("name");
        address = u.at("address");
        break;
      }
    }
  }
  void showRestaurant() {
    cout << "Showing restaurants\n";
    for (const auto &u : user['R'])
      cout << u.at("restaurantName") << endl;
    cout << "-----------------------------------------------\n";
  }
  bool searchRestaurant() {
    cout << "Searching for restaurants near you\n";
    string search;
    cout << "Enter restaurant name: ";
    getline(cin >> ws, search);

    for (const auto &u : user['R']) {
      if (u.at("restaurantName") == search) {
        cout << "Restaurant " << search << "Found!.." << endl;
        cout << "Email: " << u.at("email") << endl;
        cout << "Phone: " << u.at("phone") << endl;
        cout << "Location: " << u.at("restaurantLocation") << endl;
        cout << "\nDish Name  | Price" << endl;
        cout << "-----------+------" << endl;
        for (auto &i : menu[search]) {
          cout << i.first << "  | " << i.second << endl;
          cout << setw(10) << left << i.first << " | " << setw(5) << left
               << i.second << endl;
        }
        for (auto &i : review) {
          if (i.first == search) {
            cout << "Review: " << i.second[0] << endl;
            cout << "Rating: " << i.second[1] << endl;
            cout << "Comment: " << i.second[2] << endl;
          }
        }
        return true;
      }
    }
    cout << "Restaurant not found\n";
    return false;
  }

  void placeOrder() {
    Order o1;
    int choice;
    cout << "\n1: Add item \t 2: Change item\n 3: Place Order\n";
    cin >> choice;
    while (choice != 3) {
      if (choice == 1) {
        o1.addItem();
      }
      if (choice == 2) {
        o1.changeOrder();
      }
    }
    o1.placeOrder();
  }
  void placeOrderCart() {
    Order o1;
    int choice;
    cout << "\n1: Add item \t 2: Change item\n 3: Place Order\n";
    cin >> choice;
    while (choice != 3) {
      if (choice == 1) {
        o1.addItem();
      }
      if (choice == 2) {
        o1.changeOrder();
      }
    }
    o1.placeOrder();
  }
  void giveReviews() {
    cout << "Giving reviews\n";
    int review;
    cout << "Enter review (1-5): ";
    cin >> review;
    if (review >= 1 && review <= 5) {
      cout << "Review: " << review << endl;
    } else {
      cout << "Invalid review\n";
    }
  }
  void addToCart() {
    Cart c1;
    c1.addItem();
  }
  void removeFromCart() {
    Cart c1;
    c1.removeItem();
  }
  void viewCart() {
    CartItem c1;
    c1.totalPrice();
  }
  void cancelOrder() { cout << "Cancelling order\n"; }
};

class Authentication {
private:
  string sessionToken;
  string passwordHash;

public:
  string email;
  string userId;

public:
  pair<string, char> registration() {
    clearScreen();
    cout << "Welcome to Food Delivery System\n";
    cout << "-----------------------------------------------\n";
    cout << "Registration For New User\n";
    string newUserID, newEmail = "asd", newPhone = "123", newPassword = "asd";

    cout << "Email-ID: ";
    cin >> newEmail;
    cout << "Phone Number: ";
    cin >> newPhone;
    cout << "Password: ";
    cin >> newPassword;

    char newUserType = 'C';
  invalidUserType:

    cout << "Enter User Type (Customer-C, Restaurant-R, DeliveryPartner-D): ";
    cin >> newUserType;

    newUserID = newEmail + to_string(rand() % 1000);
    unordered_map<string, string> newUser = {{"userID", newUserID},
                                             {"email", newEmail},
                                             {"phone", newPhone},
                                             {"password", newPassword}};

    cout << "-----------------------------------------------\n";
    switch (newUserType) {
    case 'C':
    case 'c': {
      newUserType = 'C';
      string firstName = "as", lastName, newAddress = "asdasd", newName;

      cout << "FirstName: ";
      cin >> firstName;
      cout << "LastName : ";
      cin >> lastName;

      clearLastNLines(2); // Clear the last 2 lines

      newName = firstName + " " + lastName;
      cout << "Your Full Name: " << newName << endl;
      newUser["name"] = newName;

      cout << "Enter Address: ";
      cin >> newAddress;
      newUser["address"] = newAddress;
      // newUser["userType"] = "Customer";
      // // {"userType", newUserType}
      break;
    }

    case 'R':
    case 'r': {
      newUserType = 'R';
      string newRestaurantName, newRestaurantLocation;
      unordered_map<string, int> rmenu;

      cout << "Restaurant Name: ";
      getline(cin >> ws, newRestaurantName);
      newUser["restaurantName"] = newRestaurantName;

      cout << "Restaurant Location: ";
      getline(cin >> ws, newRestaurantLocation);
      newUser["restaurantLocation"] = newRestaurantLocation;

      cout << "Enter your Dishes Details (1-stop)\n";
      while (1) {
        string name;
        int am;

        cout << "Enter Your Dish Name: ";
        getline(cin >> ws, name);

        if (name == "1") {
          clearLastNLines(2); // Clear the last 2 lines
          break;
        }

        cout << "Enter Your Dish Amount: ";
        cin >> am;
        clearLastNLines(2); // Clear the last 2 lines
      }
      menu[newUserID] = rmenu;

      // newUser["userType"] = "Restaurant";
      break;
    }

    case 'D':
    case 'd': {
      newUserType = 'D';
      string newVehicleNumber, newVehicleType, newVehicleModel;

      cout << "Enter Vehicle Number: ";
      cin >> newVehicleNumber;
      newUser["vehicleNumber"] = newVehicleNumber;

      cout << "Enter Vehicle Type: ";
      cin >> newVehicleType;
      newUser["vehicleType"] = newVehicleType;

      cout << "Enter Vehicle Model: ";
      cin >> newVehicleModel;
      newUser["vehicleModel"] = newVehicleModel;
      // newUser["userType"] = "DeliveryPartner";
      break;
    }

    default: {
      cout << "Invalid user type!\n";
      this_thread::sleep_for(
          chrono::milliseconds(1500)); // sleep for miliseconds
      clearLastNLines(2);              // Clear the last 2 lines
      goto invalidUserType;
    }
    }

    user[newUserType].push_back(newUser);
    cout << "Registration successful!\n";
    cout << "User ID: " << newUserID << endl;
    this->userId = newUserID;
    cout << "-----------------------------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
    return login();
  }

  pair<string, char> login() {
    clearScreen();
    cout << "Welcome to Food Delivery System\n";
    cout << "-----------------------------------------------\n";
    bool foundId = false, foundPassword = false;
    char userType;
    string uId = "asd41", pass = "asd";

    cout << "Enter User Type (Customer-C, Restaurant-R, DeliveryPartner-D): ";
    cin >> userType;
    clearLastNLines(1); // Clear the last 2 lines

    cout << "Enter UserName: ";
    cin >> uId;

    for (const auto &u : user[userType]) {
      // cout<<uId<<endl;
      if (u.at("name") == uId) {
        foundId = true;

        // cout<<uId;
        cout << "Enter Password: ";
        cin >> pass;

        if (u.at("password") == pass) {
          foundPassword = true;
          cout << "-----------------------------------------------\n";
          cout << "Sent OTP to your registered email ID." << endl;
          this_thread::sleep_for(
              chrono::milliseconds(3000)); // sleep for miliseconds
          clearLastNLines(1);              // Clear the last 2 lines

          if (!verifyOTP()) {
            while (1) {
              cout << "Resent OTP to your registered email ID." << endl;
              this_thread::sleep_for(
                  chrono::milliseconds(1500)); // sleep for miliseconds
              clearLastNLines(1);              // Clear the last 2 lines

              if (!verifyOTP()) {
                cout << "Login Failed.. Try again\n";
                this_thread::sleep_for(
                    chrono::milliseconds(1500)); // sleep for miliseconds
                clearLastNLines(1);              // Clear the last 2 lines
                continue;
              } else {
                goto loginComplete;
              }
            }
          } else {
            goto loginComplete;
          }
        }
      }
    }

    if (!foundId) {
      cout << "Username not found\n";
      cout << "Do you want to register? (y/n): ";
      char choice = 'y';
      cin >> choice;

      clearLastNLines(1); // Clear the last 2 lines

      pair<string, char> us;

      if (choice == 'y' || choice == 'Y') {
        cout << "Registration...\n";
        this_thread::sleep_for(
            chrono::milliseconds(2000)); // sleep for miliseconds
        us = registration();
      } else {
        cout << "Login Failed.. Try again\n";
        this_thread::sleep_for(
            chrono::milliseconds(2000)); // sleep for miliseconds
        us = login();
      }
      return us;
    }

    if (foundId && !foundPassword) {
      cout << "Incorrect Password\n";
      cout << "Do you want to reset your password? (y/n): ";
      char choice;
      cin >> choice;
      clearLastNLines(1); // Clear the last 2 lines
      cout << "-----------------------------------------------\n";

      if (choice == 'y') {
        cout << "Password Resetting...\n";
        this_thread::sleep_for(
            chrono::milliseconds(2000)); // sleep for miliseconds
        clearLastNLines(1);              // Clear the last 2 lines

        resetPassword();
        cout << "Password Reset Successful..";
        this_thread::sleep_for(
            chrono::milliseconds(1500)); // sleep for miliseconds
        clearLastNLines(1);              // Clear the last 2 lines
      } else {
        cout << "Login Failed.. You need to reset Password\n";
        resetPassword();
      }
    }

  loginComplete:
    cout << "Login Successful\n";
    cout << "-----------------------------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
    clearLastNLines(2); // Clear the last 2 lines

    return {uId, userType};
  }

  void logout() {
    cout << "🔒 Logout successful. Thank you for using our service!\n;
    this_thread::sleep_for(chrono::milliseconds(3000)); // sleep for miliseconds
    clearLastNLines(1); // Clear the last 2 lines
  }

  void resetPassword() {
    cout << "Sent OTP to your registered email ID." << endl;
    this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
    clearLastNLines(1); // Clear the last 2 lines

    if (!verifyOTP()) {
      while (1) {
        cout << "Resent OTP to your registered email ID." << endl;
        this_thread::sleep_for(
            chrono::milliseconds(1500)); // sleep for miliseconds
        clearLastNLines(1);              // Clear the last 2 lines

        if (!verifyOTP()) {
          cout << "Password Reset Failed... Try again\n";
          this_thread::sleep_for(
              chrono::milliseconds(1500)); // sleep for miliseconds
          clearLastNLines(1);              // Clear the last 2 lines
          continue;
        } else {
          break;
        }
      }
    }
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Create new password : ";
    string newPassword;
    cin >> newPassword;
  newPassword:
    cout << "Confirm new password: ";
    string confirmPassword;
    cin >> confirmPassword;
    if (newPassword == confirmPassword) {
      for (auto &t : user) {
        for (auto &u : t.second) {
          if (u["userID"] == name) {
            u["password"] = newPassword;
          }
        }
      }
      cout << "Password Reset Successful\n";
      cout << "-----------------------------------------------\n";
      this_thread::sleep_for(
          chrono::milliseconds(2000)); // sleep for miliseconds
      clearLastNLines(4);              // Clear the last 2 lines
      return;
    } else {
      clearLastNLines(1); // Clear the last 2 lines
      goto newPassword;
    }
  }

  bool verifyOTP() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1000, 9999);
    int otp = dist(gen);
    // int otp = rand() % 9000 + 1000; // Generate a 4-digit OTP
    cout << "OTP: " << otp << endl;

    cout << "Please enter the OTP to verify your account.\n";
    int otpEnter;
    cout << "Enter OTP: ";
    cin >> otpEnter;

    clearLastNLines(3); // Clear the last 2 lines

    cout << "Verifying OTP....\n";
    this_thread::sleep_for(chrono::milliseconds(3000)); // sleep for miliseconds
    clearLastNLines(1); // Clear the last 2 lines

    if (otpEnter == otp) {
      cout << "OTP is Valid\n";
      this_thread::sleep_for(
          chrono::milliseconds(2000)); // sleep for miliseconds
      clearLastNLines(1);              // Clear the last 2 lines
      return true;

    } else {
      cout << "OTP is Invalid\n";
      this_thread::sleep_for(
          chrono::milliseconds(2000)); // sleep for miliseconds
      clearLastNLines(1);              // Clear the last 2 lines
      return false;
    }
  }

  void generateSessionToken() {
    cout << "Generating Session Token: " << rand() % 100000000 << endl;
  }
};

int main() {
  clearScreen();

  user['C'].push_back({{"userID", "meet"},
                       {"email", "meet@gmail.com"},
                       {"phone", "1"},
                       {"password", "meet"},
                       {"name", "meet"},
                       {"address", "asdasd"}});

  user['R'].push_back({{"userID", "a"},
                       {"email", "a"},
                       {"phone", "1"},
                       {"password", "a"},
                       {"restaurantName", "pizzahub"},
                       {"restaurantLocation", "asdasd"}});
  menu["pizzahub"]["pizza"] = 250;

  user['D'].push_back({{"userID", "a"},
                       {"email", "a"},
                       {"phone", "1"},
                       {"password", "a"},
                       {"vehicleNumber", "1"},
                       {"vehicleType", "a"},
                       {"vehicleModel", "a"}});

  user['D'].push_back({{"userID", "b"},
                       {"email", "b"},
                       {"phone", "2"},
                       {"password", "b"},
                       {"vehicleNumber", "1"},
                       {"vehicleType", "b"},
                       {"vehicleModel", "b"}});
  review["pizzahub"] = {"pizzahub", "5", "good"};

  cout << "Welcome to Food Delivery System\n";
  cout << "-----------------------------------------------\n";

  Authentication auth;
  auth.login();

  Customer cust("a");
  cust.showRestaurant();
  cust.searchRestaurant();
  cout << "\n1: To Add To Cart\n2: To Place Order\n3: Exit\n";
  int choice;
  cin >> choice;
  while (choice != 3) {
    if (choice == 1) {
      cust.addToCart();
      cout << "\n1: To Add To Cart\n2: To Place Order\n3: total Price\n";
      cin >> choice;
      if (choice == 3) {
        cust.viewCart();
        cout << "\n1: To Add To Cart\n2: To Place Order\n3: Exit\n";

        cin >> choice;
      }
      if (choice == 2) {
        cust.placeOrderCart();
        choice = 3;
      }
    } else if (choice == 2) {
      cust.placeOrder();
      choice = 3;
    } else {
      cout << "Invalid Choice\n";
      cin >> choice;
    }
  }
  cout << "\n1: cancel Order\n2: continue\n";
  cin >> choice;
  if (choice == 1) {
    cust.cancelOrder();
  } else {
    this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
    DeliveryPartner d1("del");
    d1.updateOrderStatus();
    cout << "Order placed successfully\n";
  }
  cout << "\n1: To give review\n2: To exit\n";
  cin >> choice;
  if (choice == 1) {
    cust.giveReviews();
  }
  cout << "Happy to serve you!";
  return 0;
}
