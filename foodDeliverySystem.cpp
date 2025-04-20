#include <bits/stdc++.h>
#include <thread>
#include <chrono>
using namespace std;

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

map<char, vector<unordered_map<string, string>>> user; // Global user storage
unordered_map<string, unordered_map<string, int>> menu; // Global menu storage
vector<int> order; // Global order storage
string OrderStatus = "Pending";

class User {
    protected:
    string password;

    public:
    string email;
    string phone;
    string userID;  //------+
                    //      |
                    //      V
    User(string userId) : userID(userId) {
        for (const auto& t : user) {
            for (const auto& u : t.second) {
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

        for (auto& t : user) {
            for (auto& u : t.second) {
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
        for (auto &t : user){
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

class Customer : public User {
    public:
    string fullName;
    string address;
    vector<string> cart;
    
    Customer(string userID) : User(userID) {
        for (const auto& u : user['C']) {
            if (u.at("userID") == userID) {
                fullName = u.at("name");
                address = u.at("address");
                break;
            }
        }
    }

    bool searchRestaurant() {
        cout << "Searching for restaurants near you\n";
        string search;
        cout << "Enter restaurant name: ";
        getline(cin >> ws, search);

        for (const auto& u : user['R']) {
            if (u.at("restaurantName") == search) {
                cout << "Restaurant " << search << "Found!.." << endl;
                cout << "Email: " << u.at("email") << endl;
                cout << "Phone: " << u.at("phone") << endl;
                cout << "Location: " << u.at("restaurantLocation") << endl;
                cout << "\nDish Name  | Price" << endl;
                cout << "-----------+------" << endl;
                for(auto &i : menu[u.at("userID")]){
                    cout << setw(10) << left << i.first << " | " 
                         << setw(5) << left << i.second << endl;
                }
                return true;
            }
        }
        cout << "Restaurant not found\n";
        return false;
    }
    
    void placeOrder() { 
        cout << "Placing order\n"; 
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
        // string cartItem;
        // cout << "Enter Dish name you want to add into cart..\n";
        // while(1){
        //     cout << "Enter Dish Name(1-Back): ";
        //     getline(cin >> ws, cartItem);
        //     clearLastNLines(2);         // Clear the last 2 lines
        //     if(cartItem == "1") break;
        //     cart.push_back(cartItem);
        //     cout << cartItem << " Added into cart..\n";
        // }
    }
    void cancelOrder() { cout << "Cancelling order\n"; }
};
    
class Restaurant : public User {
    public:
    string restaurantName;
    string restaurantLocation;

    vector<string> menu;
                             
    Restaurant(string userId) : User(userId) {
        for (const auto& u : user['R']) {
            if (u.at("userID") == userId) {
                restaurantName = u.at("restaurantName");
                restaurantLocation = u.at("restaurantLocation");
                break;
            }
        }
    }
    
    // void manageMenus() {
    //     cout << "Managing menus\n";
    //     string res, menuName, foodPrice;
    //     cout << "Enter restaurant name: ";
    //     cin >> res;
    //     cout << "Enter food name: ";
    //     cin >> menuName;
    //     cout << "Enter food price: ";
    //     cin >> foodPrice;
    //     try {
    //         menu[res][menuName] = stoi(foodPrice);
    //         cout << "Menu managed successfully\n";
    //     } catch (...) {
    //         cout << "Invalid price entered\n";
    //     }
    // }

    // void displayMenu() {
    //     cout << "Displaying menu\n";
    //     string res;
    //     cout << "Enter restaurant name: ";
    //     cin >> res;
    //     if (menu.find(res) != menu.end()) {
    //         for (const auto& item : menu[res]) {
    //             cout << item.first << " " << item.second << endl;
    //         }
    //     } else {
    //         cout << "No menu found for restaurant\n";
    //     }
    // }

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
    // DeliveryPartner(string name, string deliveryOrders, string currentLocation, string vehicleDetails)
    //     : name(name), deliveryOrders(deliveryOrders), currentLocation(currentLocation), vehicleDetails(vehicleDetails) {
    //     cout << "Delivery Partner created\n";
    // }
    DeliveryPartner(string userId) : User(userId) {
        for (const auto& u : user['D']) {
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
        string newUserID, newEmail="asd", newPhone="123", newPassword="asd";
        
        cout << "Email-ID: ";
        cin >> newEmail;
        cout << "Phone Number: ";
        cin >> newPhone;
        cout << "Password: ";
        cin >> newPassword;
        
        char newUserType = 'C';
        invalidUserType :
        
        cout << "Enter User Type (Customer-C, Restaurant-R, DeliveryPartner-D): ";
        cin >> newUserType;
        
        
        newUserID = newEmail + to_string(rand() % 1000);
        unordered_map<string, string> newUser = {
            {"userID", newUserID}, {"email", newEmail}, {"phone", newPhone}, {"password", newPassword}
        };
        
        cout << "-----------------------------------------------\n";
        switch(newUserType){
            case 'C':
            case 'c': {
                newUserType = 'C';
                string firstName="as", lastName, newAddress="asdasd", newName;

                cout << "FirstName: ";
                cin >> firstName;
                cout << "LastName : ";
                cin >> lastName;
                
                clearLastNLines(2);      // Clear the last 2 lines
                
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
                while(1){
                    string name; int am;

                    cout << "Enter Your Dish Name: ";
                    getline(cin >> ws, name);

                    if(name == "1"){ 
                        clearLastNLines(2);         // Clear the last 2 lines
                        break;  
                    }

                    cout << "Enter Your Dish Amount: ";
                    cin >> am;
                    clearLastNLines(2);         // Clear the last 2 lines
                }
                menu[newUserID] = rmenu;

                // newUser["userType"] = "Restaurant";
                break;
            }

            case 'D':
            case 'd':{
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
                this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
                clearLastNLines(2);      // Clear the last 2 lines
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
        string uId="asd41", pass="asd";

        cout << "Enter User Type (Customer-C, Restaurant-R, DeliveryPartner-D): ";
        cin >> userType;
        clearLastNLines(1);         // Clear the last 2 lines

        cout << "Enter UserName: ";
        cin >> uId;

        for (const auto &u : user[userType]) {
            if (u.at("userID") == uId ) {
                foundId = true;
                cout << "Enter Password: ";
                cin >> pass;

                if (u.at("password") == pass) {
                    foundPassword = true;
                    cout << "-----------------------------------------------\n";
                    cout << "Sent OTP to your registered email ID." << endl;
                    this_thread::sleep_for(chrono::milliseconds(3000)); // sleep for miliseconds
                    clearLastNLines(1);         // Clear the last 2 lines

                    if(!verifyOTP()){
                        while(1){
                            cout << "Resent OTP to your registered email ID." << endl;
                            this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
                            clearLastNLines(1);         // Clear the last 2 lines
                            
                            if(!verifyOTP()){
                                cout << "Login Failed.. Try again\n";
                                this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
                                clearLastNLines(1);         // Clear the last 2 lines
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
            
            clearLastNLines(1);         // Clear the last 2 lines

            pair <string, char> us;
            
            if (choice == 'y' || choice == 'Y') {
                cout << "Registration...\n";
                this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
                us = registration();
            } else {
                cout << "Login Failed.. Try again\n";
                this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
                us = login();
            }
            return us;
        }

        if (foundId && !foundPassword) {
            cout << "Incorrect Password\n";
            cout << "Do you want to reset your password? (y/n): ";
            char choice;
            cin >> choice;
            clearLastNLines(1);         // Clear the last 2 lines
            cout << "-----------------------------------------------\n";

            if (choice == 'y'){
                cout << "Password Resetting...\n";
                this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
                clearLastNLines(1);         // Clear the last 2 lines

                resetPassword();
                cout << "Password Reset Successful..";
                this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
                clearLastNLines(1);         // Clear the last 2 lines
            }
        }

        loginComplete:
        cout << "Login Successful\n";
        cout << "-----------------------------------------------\n";
        this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
        clearLastNLines(2);         // Clear the last 2 lines

        return {uId, userType};
    }

    void logout() { 
        cout << "🔒 Logout successful. Thank you for using our service!\n";  
        this_thread::sleep_for(chrono::milliseconds(3000)); // sleep for miliseconds
        clearLastNLines(1);         // Clear the last 2 lines
    }

    void resetPassword() {
        cout << "Sent OTP to your registered email ID." << endl;
        this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
        clearLastNLines(1);         // Clear the last 2 lines 

        if(!verifyOTP()) {
            while(1){
                cout << "Resent OTP to your registered email ID." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
                clearLastNLines(1);         // Clear the last 2 lines
                
                if(!verifyOTP()){
                    cout << "Password Reset Failed... Try again\n";
                    this_thread::sleep_for(chrono::milliseconds(1500)); // sleep for miliseconds
                    clearLastNLines(1);         // Clear the last 2 lines
                    continue;
                } else {
                    break;
                }
            }
        }
        cout << "Create new password : ";
        string newPassword;
        cin >> newPassword;
        newPassword:
        cout << "Confirm new password: ";
        string confirmPassword;
        cin >> confirmPassword;
        if (newPassword == confirmPassword) {
            cout << "Password Reset Successful\n";
            cout << "-----------------------------------------------\n";
            this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
            clearLastNLines(4);         // Clear the last 2 lines
            return;
        } else {
            clearLastNLines(1);         // Clear the last 2 lines
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

        clearLastNLines(3);         // Clear the last 2 lines
        
        cout << "Verifying OTP....\n";
        this_thread::sleep_for(chrono::milliseconds(3000)); // sleep for miliseconds
        clearLastNLines(1);         // Clear the last 2 lines
        
        if (otpEnter == otp) {
            cout << "OTP is Valid\n";
            this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
            clearLastNLines(1);         // Clear the last 2 lines
            return true;
            
        } else {
            cout << "OTP is Invalid\n";
            this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for miliseconds
            clearLastNLines(1);         // Clear the last 2 lines
            return false;
        }
    }

    void generateSessionToken() {
        cout << "Generating Session Token: " << rand() % 100000000 << endl;
    }
};

int main() {
    clearScreen();

    user['C'].push_back({
        {"userID", "a"},
        {"email", "a"},
        {"phone", "1"},
        {"password", "a"},
        {"name", "a b"},
        {"address", "asdasd"}
    });
    user['C'].push_back({
        {"userID", "b"},
        {"email", "b"},
        {"phone", "2"},
        {"password", "b"},
        {"name", "b c"},
        {"address", "asdasd"}
    });

    user['R'].push_back({
        {"userID", "a"},
        {"email", "a"},
        {"phone", "1"},
        {"password", "a"},
        {"restaurantName", "a b"},
        {"restaurantLocation", "asdasd"}
    });
    menu["a"] = {{"asd asd", 12}, {"as as", 123}};
    
    user['R'].push_back({
        {"userID", "b"},
        {"email", "b"},
        {"phone", "2"},
        {"password", "b"},
        {"restaurantName", "b c"},
        {"restaurantLocation", "asdasd"}
    });
    menu["b"] = {{"asd asd", 12}, {"as as", 123}};

    
    user['D'].push_back({
        {"userID", "a"},
        {"email", "a"},
        {"phone", "1"},
        {"password", "a"},
        {"vehicleNumber", "1"},
        {"vehicleType", "a"},
        {"vehicleModel", "a"}
    });

    user['D'].push_back({
        {"userID", "b"},
        {"email", "b"},
        {"phone", "2"},
        {"password", "b"},
        {"vehicleNumber", "1"},
        {"vehicleType", "b"},
        {"vehicleModel", "b"}
    });



    
    cout << "Welcome to Food Delivery System\n";
    cout << "-----------------------------------------------\n";
    
    // cout << "You want to Login(0) OR Registration(1): ";
    // bool choice = true;
    // cin >> choice;
    // this_thread::sleep_for(chrono::milliseconds(200)); // sleep for miliseconds
    
    // Authentication auth;
    // pair <string, char> u;
    // u = {"asd", 'C'};

    // if (choice) {
    //     u = auth.registration();
    // } else {
    //     u = auth.login();
    // }
    

    // Initialize with a valid userID (assuming registration created one)
    // string userID = user.empty() ? "default" : user[0]["userID"];
    
    // 5 lines
    // clearLastNLines(3);         // Clear the last 2 lines


    Customer cust("a");
    bool back1 = false;
    while(1){
        cout << "1. Profile.\n"
                "2. Make Order\n"
                "Enter Your Choise: ";
        int ch1;
        cin >> ch1;

        switch(ch1){
            case 1: {
                clearLastNLines(3);         // Clear the last 2 lines
                bool back = false;
                while(1){
                    cout << "1. View Profile.\n"
                            "2. Manage Profile.\n"
                            "3. Delete Profile.\n"
                            "4. Back.\n"
                            "Enter Your Choise: ";
                    int ch2;
                    cin >> ch2;

                    clearLastNLines(5);         // Clear the last 2 lines
                    switch(ch2){
                        case 1: {
                            cust.viewProfile();
                            bool c;
                            cout << "You want to Back(1) or Exit(0): ";
                            cin >> c;
                            clearLastNLines(4);
                            if(!c) {   cout << "Exitting..."; exit(0);}
                            break;
                        }
                        case 2: {
                            cust.manageProfile();
                            bool c;
                            cout << "You want to Back(1) or Exit(0): ";
                            cin >> c;
                            clearLastNLines(5);
                            if(!c) {   cout << "Exitting..."; exit(0);}
                            break;
                        }
                        case 3: {
                            cust.deleteProfile();
                            bool c;
                            cout << "You want to Back(1) or Exit(0): ";
                            cin >> c;
                            clearLastNLines(2);
                            if(!c) {   cout << "Exitting..."; exit(0);}
                            break;
                        }
                        default: {
                            back = true;
                            break;
                        }
                    }
                    if(back) break;
                }
                break;
            }
            case 2: {
                clearLastNLines(3);         // Clear the last 2 lines
                if(!cust.searchRestaurant()){   clearLastNLines(3); break;}
                cout << "You want to order food (y/n): ";
                char c;
                cin >> c;
                clearLastNLines(1);         // Clear the last 2 lines
                if(c == 'y') {   
                    cust.addToCart();
                    cust.placeOrder();
                }
                clearScreen();
                cout << "Welcome to Food Delivery System\n";
                cout << "-----------------------------------------------\n";
                break;
            }
            default: {
                back1 = true;
                break;
            }
        }
        if(back1) break;
    }
        
    Restaurant res("a");
    DeliveryPartner delPar("a");

   /*  switch(u.second){
        case 'C': {
            Customer cust(u.first);
            bool back1 = false;
            while(1){
                cout << "1. Profile.\n"
                        "2. Make Order\n"
                        "Enter Your Choise: ";
                int ch1;
                cin >> ch1;

                switch(ch1){
                    case 1: {
                        clearLastNLines(3);         // Clear the last 2 lines
                        bool back = false;
                        while(1){
                            cout << "1. View Profile.\n"
                                    "2. Manage Profile.\n"
                                    "3. Delete Profile.\n"
                                    "4. Back.\n"
                                    "Enter Your Choise: ";
                            int ch2;
                            cin >> ch2;

                            clearLastNLines(5);         // Clear the last 2 lines
                            switch(ch2){
                                case 1: {
                                    cust.viewProfile();
                                    bool c;
                                    cout << "You want to Back(1) or Exit(0): ";
                                    cin >> c;
                                    clearLastNLines(4);
                                    if(!c) {   cout << "Exitting..."; exit(0);}
                                    break;
                                }
                                case 2: {
                                    cust.manageProfile();
                                    bool c;
                                    cout << "You want to Back(1) or Exit(0): ";
                                    cin >> c;
                                    clearLastNLines(5);
                                    if(!c) {   cout << "Exitting..."; exit(0);}
                                    break;
                                }
                                case 3: {
                                    cust.deleteProfile();
                                    bool c;
                                    cout << "You want to Back(1) or Exit(0): ";
                                    cin >> c;
                                    clearLastNLines(2);
                                    if(!c) {   cout << "Exitting..."; exit(0);}
                                    break;
                                }
                                default: {
                                    back = true;
                                    break;
                                }
                            }
                            if(back) break;
                        }
                        break;
                    }
                    case 2: {
                        clearLastNLines(3);         // Clear the last 2 lines
                        if(!cust.searchRestaurant()){   clearLastNLines(3); break;}
                        cout << "You want to order food (y/n): ";
                        char c;
                        cin >> c;
                        clearLastNLines(1);         // Clear the last 2 lines
                        if(c == 'y') {   
                            cust.addToCart();
                        }
                        // clearScreen();
                        // cout << "Welcome to Food Delivery System\n";
                        // cout << "-----------------------------------------------\n";
                        break;
                    }
                    default: {
                        back1 = true;
                        break;
                    }
                }
                if(back1) break;
            }
            break;
        }
        
        case 'R': {
            Restaurant res(u.first);
            break;
        }

        case 'D': {
            DeliveryPartner delPar(u.first);
            break;
        }
    }

 */
    
 
    // Cart cart;
    // cart.customerID = userID;
    // cart.addItem();
    // cart.placeOrder();

    return 0;
}

/* 
void a(){     
    

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
}
 */
