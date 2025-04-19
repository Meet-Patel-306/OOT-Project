#include <bits/stdc++.h>
using namespace std;

// Cross-platform screen clear
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

vector<unordered_map<string, string>> user; // Global user storage
unordered_map<string, unordered_map<string, int>> menu; // Global menu storage
vector<int> order; // Global order storage
string OrderStatus = "Pending";

class User {
protected:
    string password;

public:
    string userID;
    string name;
    string email;
    string phone;

    User(string userID) : userID(userID) {
        for (const auto& u : user) {
            if (u.at("userID") == userID) {
                name = u.at("name");
                email = u.at("email");
                phone = u.at("phone");
                password = u.at("password");
                return;
            }
        }
        cout << "User not found!" << endl;
    }

    void manageProfile() {
        cout << "User ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Password: [Hidden]" << endl;

        cout << "1. Edit Profile \t 2. No Change\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            string newName, newEmail, newPhone;
            cout << "Enter new information\n";
            cout << "Name: ";
            cin >> newName;
            cout << "Email: ";
            cin >> newEmail;
            cout << "Phone: ";
            cin >> newPhone;
            for (auto& u : user) {
                if (u["userID"] == userID) {
                    u["name"] = newName;
                    u["email"] = newEmail;
                    u["phone"] = newPhone;
                    name = newName;
                    email = newEmail;
                    phone = newPhone;
                    break;
                }
            }
            cout << "Profile updated successfully!\n";
        }
    }

    void deleteProfile() {
        for (auto it = user.begin(); it != user.end(); ++it) {
            if (it->at("userID") == userID) {
                user.erase(it);
                cout << "Profile deleted successfully!\n";
                return;
            }
        }
        cout << "Profile not found!\n";
    }
};

class Authentication {
private:
    string sessionToken;
    string passwordHash;
    string email;

public:
    void registration() {
        clearScreen();
        cout << "Welcome to Food Delivery System\n";
        cout << "-----------------------------------------------\n";
        cout << "Registration For New User\n";
        string newUserID, newName, newEmail, newPhone, newPassword, newUserType;
        cout << "Enter Name: ";
        cin >> newName;
        cout << "Enter Email: ";
        cin >> newEmail;
        cout << "Enter Phone: ";
        cin >> newPhone;
        cout << "Enter User Type (Customer-C, Restaurant-R, DeliveryPartner-D): ";
        cin >> newUserType;
        cout << "Enter Password: ";
        cin >> newPassword;

        newUserID = newEmail + to_string(rand() % 1000);
        unordered_map<string, string> newUser = {
            {"userID", newUserID}, {"name", newName}, {"email", newEmail},
            {"phone", newPhone}, {"password", newPassword}, {"userType", newUserType}
        };

        if (newUserType == "C" || newUserType == "c") {
            string newAddress;
            cout << "Enter Address: ";
            cin >> newAddress;
            newUser["address"] = newAddress;
        } else if (newUserType == "R" || newUserType == "r") {
            string restaurantDetails, newLocation;
            cout << "Enter Location: ";
            cin >> newLocation;
            cout << "Enter Restaurant Details: ";
            cin >> restaurantDetails;
            newUser["restaurantDetails"] = restaurantDetails;
            newUser["location"] = newLocation;
        } else if (newUserType == "D" || newUserType == "d") {
            string newVehicleDetails;
            cout << "Enter Vehicle Details: ";
            cin >> newVehicleDetails;
            newUser["Girish"] = newVehicleDetails;
        } else {
            cout << "Invalid user type!\n";
            return;
        }
        user.push_back(newUser);
        cout << "Registration successful! User ID: " << newUserID << endl;
        cout << "-----------------------------------------------\n";
        login();
    }

    void login() {
        clearScreen();
        cout << "Welcome to Food Delivery System\n";
        cout << "-----------------------------------------------\n";
        bool foundEmail = false, foundPassword = false;

        cout << "Enter Email: ";
        cin >> email;

        for (const auto& u : user) {
            if (u.at("email") == email ) {
                foundEmail = true;
                cout << "Enter Password: ";
                cin >> passwordHash;

                if (u.at("password") == passwordHash) {
                    foundPassword = true;
                    cout << "Login Successful\n";
                    verifyOTP();
                    return;
                }
            }
        }

        if (!foundEmail) {
            cout << "Email not found\n";
            cout << "Do you want to register? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y'){
                registration();
            } else {
                cout;
            }
            cout << "Login Failed\n";
            return;
        }
        if (foundEmail && !foundPassword) {
            cout << "Incorrect Password\n";
            cout << "Login Failed\n";
            return;
        }
    }

    void logout() { cout << "Logout\n"; }
    void resetPassword() { cout << "Reset Password\n"; }

    void verifyOTP() {
        int otp = rand() % 9000 + 1000;
        cout << "OTP: " << otp << endl;
        int otpEnter;
        cout << "Enter OTP: ";
        cin >> otpEnter;
        if (otpEnter == otp) {
            cout << "Valid OTP\n";
        } else {
            cout << "Invalid OTP\n";
        }
    }

    void generateSessionToken() {
        cout << "Generating Session Token: " << rand() % 100000000 << endl;
    }
};

class Customer : public User {
public:
    string address;

    Customer(string userID) : User(userID) {
        for (const auto& u : user) {
            if (u.at("userID") == userID) {
                address = u.at("address");
                break;
            }
        }
    }

    void searchRestaurant() {
        cout << "Searching for restaurants near you\n";
        string search;
        cout << "Enter restaurant name: ";
        cin >> search;
        bool found = false;
        for (const auto& u : user) {
            if (u.at("name") == search && u.at("userType") == "Restaurant") {
                cout << "Restaurant found\n";
                cout << "Name: " << u.at("name") << endl;
                cout << "Location: " << u.at("location") << endl;
                cout << "Phone: " << u.at("phone") << endl;
                cout << "Email: " << u.at("email") << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Restaurant not found\n";
        }
    }

    void placeOrder() { cout << "Placing order\n"; }
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
    void addToCart() { cout << "Adding to cart\n"; }
    void cancelOrder() { cout << "Cancelling order\n"; }
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
        cout << "Adding item to cart\n";
        string res, foodName;
        int quantity;
        cout << "Enter restaurant name: ";
        cin >> res;
        cout << "Enter food name: ";
        cin >> foodName;
        cout << "Enter quantity: ";
        cin >> quantity;
        if (menu.find(res) != menu.end() && menu[res].find(foodName) != menu[res].end()) {
            order.push_back(quantity * menu[res][foodName]);
            cout << "Item added successfully\n";
        } else {
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

class OrderCancelFood {
public:
    string orderID;
    string restaurantID;
    string cancelTime;
    string foodItem;
    float price;
    string orderLocation;

    void cancelDiscount() { cout << "Cancelling discount\n"; }

    void addFoodItem() {
        cout << "Adding food item\n";
        string res, foodName;
        int quantity;
        cout << "Enter restaurant name: ";
        cin >> res;
        cout << "Enter food name: ";
        cin >> foodName;
        cout << "Enter quantity: ";
        cin >> quantity;
        if (menu.find(res) != menu.end() && menu[res].find(foodName) != menu[res].end()) {
            order.push_back(quantity * menu[res][foodName]);
            cout << "Food item added\n";
        } else {
            cout << "Item or restaurant not found\n";
        }
    }
};

class Review {
private:
    string reviewID;
    map<string, vector<string>> review; // reviewID -> {userID, restaurantID, deliveryPartnerID, rating, comment, time}
    int deliveryPartnerID;
    double rating;
    string comment;
    string time;

public:
    Review(int userID, int restaurantID, int deliveryPartnerID, double rating, string comment) {
        this->time = string(__DATE__) + " " + string(__TIME__);
        this->reviewID = to_string(userID) + to_string(restaurantID) + this->time;
        this->rating = rating;
        this->comment = comment;
        this->deliveryPartnerID = deliveryPartnerID;
        this->review[reviewID] = {
            to_string(userID), to_string(restaurantID), to_string(deliveryPartnerID),
            to_string(rating), comment, time
        };
        cout << "Review ID: " << reviewID << endl;
        cout << "Time: " << time << endl;
        cout << "Review " << reviewID << " created successfully.\n";
    }

    void submitReview(string reviewID) {
        if (review.find(reviewID) != review.end()) {
            cout << "User " << review[reviewID][0]
                 << " submitted a review for restaurant " << review[reviewID][1]
                 << " and delivery partner " << review[reviewID][2]
                 << " with rating " << review[reviewID][3]
                 << " and comment \"" << review[reviewID][4] << "\""
                 << " at time " << review[reviewID][5] << ".\n";
            cout << "Submit Review " << reviewID << " successfully.\n";
        } else {
            cout << "Review ID not found\n";
        }
    }

    void modifyReview(string reviewID) {
        cout << "You can edit or delete your review\n";
        cout << "1. Edit Review \t 2. Delete Review\n";
        int choice;
        cin >> choice;
        cout << "Modifying review....\n";
        if (choice == 1) {
            editReview(reviewID);
        } else {
            deleteReview(reviewID);
        }
        cout << "Modify Review " << reviewID << " successfully.\n";
    }

private:
    void editReview(string reviewID) {
        if (review.find(reviewID) != review.end()) {
            cout << "Enter new rating: ";
            cin >> rating;
            cout << "Enter new comment: ";
            cin >> comment;
            time = string(__DATE__) + " " + string(__TIME__);
            review[reviewID][3] = to_string(rating);
            review[reviewID][4] = comment;
            review[reviewID][5] = time;
            cout << "User " << review[reviewID][0]
                 << " edited their review for restaurant " << review[reviewID][1]
                 << " and delivery partner " << review[reviewID][2]
                 << " with rating " << review[reviewID][3]
                 << " and comment " << review[reviewID][4]
                 << " at time " << review[reviewID][5] << ".\n";
            cout << "Editing review " << reviewID << " successfully.\n";
        } else {
            cout << "Review ID not found\n";
        }
    }

    void deleteReview(string reviewID) {
        if (review.erase(reviewID)) {
            cout << "Deleting review " << reviewID << " successfully.\n";
        } else {
            cout << "Review ID not found\n";
        }
    }
};

class DeliveryPartner {
private:
    string name;
    string deliveryOrders;
    string currentLocation;
    string vehicleDetails;

public:
    DeliveryPartner(string name, string deliveryOrders, string currentLocation, string vehicleDetails)
        : name(name), deliveryOrders(deliveryOrders), currentLocation(currentLocation), vehicleDetails(vehicleDetails) {
        cout << "Delivery Partner created\n";
    }

    void updateOrderStatus() {
        OrderStatus = "Delivered";
        cout << "Updating order status: " << OrderStatus << endl;
    }

    void updateDeliveryRequest() { cout << "Updating delivery request\n"; }
    void contactCustomer() { cout << "Contacting customer\n"; }
    void viewEarnings() { cout << "Delivery partner earnings shown\n"; }
};

class Payment {
public:
    string orderID;
    string customerID;
    string paymentMethod;
    string paymentStatus;
    int couponDiscount;

    void printReceipt() { cout << "Printing receipt\n"; }
    void processPayment() { cout << "Processing payment\n"; }
    void refundPayment() { cout << "Refunding payment\n"; }
};

class Coupon {
private:
    string couponCode;
    string couponType;
    double discountAmount;
    string expiryDate;

public:
    void isValid() { cout << "Validating coupon\n"; }
    void applyCoupon() { cout << "Applying coupon\n"; }
    void isUseBefore() { cout << "Use particular coupon before expiry date\n"; }
};

class Restaurant {
public:
    string userID;

    Restaurant(string userID) : userID(userID) {}

    void manageMenus() {
        cout << "Managing menus\n";
        string res, menuName, foodPrice;
        cout << "Enter restaurant name: ";
        cin >> res;
        cout << "Enter food name: ";
        cin >> menuName;
        cout << "Enter food price: ";
        cin >> foodPrice;
        try {
            menu[res][menuName] = stoi(foodPrice);
            cout << "Menu managed successfully\n";
        } catch (...) {
            cout << "Invalid price entered\n";
        }
    }

    void displayMenu() {
        cout << "Displaying menu\n";
        string res;
        cout << "Enter restaurant name: ";
        cin >> res;
        if (menu.find(res) != menu.end()) {
            for (const auto& item : menu[res]) {
                cout << item.first << " " << item.second << endl;
            }
        } else {
            cout << "No menu found for restaurant\n";
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

    void giveOffer() { cout << "Giving offer\n"; }
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
    void placeOrder() { cout << "Placing order\n"; }

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
        if (menu.find(res) != menu.end() && menu[res].find(foodName) != menu[res].end()) {
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
        if (menu.find(res) == menu.end() || menu[res].find(foodName) == menu[res].end()) {
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

class CancelOrder : public Order {
public:
    string orderID;
    string cancellationTime;
    string reason;
    double refundAmount;

    void orderCancellation() { cout << "Cancelling order\n"; }
    void processRefund() { cout << "Processing refund\n"; }
    void notifyCustomer() { cout << "Notifying customer\n"; }
    void notifyRestaurant() { cout << "Notifying restaurant\n"; }
};

class OrderItem {
public:
    FoodItem foodItem;
    int quantity;
    double price;

    void totalOrderAmount() {
        int sum = 0;
        for (int i : order) {
            sum += i;
        }
        cout << "Total Price: " << sum << endl;
    }
};

int main() {
    clearScreen();

    cout << "Welcome to Food Delivery System\n";
    cout << "-----------------------------------------------\n";
    cout << "Enter 1 for Registration OR 2 for Login : ";
    int choice;
    cin >> choice;
    
    Authentication auth;
    if (choice == 1) {
        auth.registration();
    } else if (choice == 2) {
        auth.login();
    } else {
        cout << "Invalid choice\n";
        return 0;
    }

    // Initialize with a valid userID (assuming registration created one)
    string userID = user.empty() ? "default" : user[0]["userID"];
    Restaurant res(userID);
    res.manageMenus();
    res.displayMenu();

    Customer customer(userID);
    customer.searchRestaurant();

    Cart cart;
    cart.customerID = userID;
    cart.addItem();
    cart.placeOrder();

    return 0;
}
