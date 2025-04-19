#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include "foodDeliverySystem.cpp" // Assume the original code is included or linked

// Global variables from the original code
extern std::vector<std::unordered_map<std::string, std::string>> user;
extern std::unordered_map<std::string, std::unordered_map<std::string, int>> menu;
extern std::vector<int> order;

// Test fixture for setting up the environment
class FoodDeliverySystemTest : public ::testing::Test {
protected:
	void SetUp() override {
		user.clear();
		menu.clear();
		order.clear();
		srand(0); // Fixed seed for predictable random numbers (e.g., OTP)

		origCin = std::cin.rdbuf();
		origCout = std::cout.rdbuf();
	}

	// Helper function to redirect cout
	void setupOutput() {
		outputStream.str("");
		std::cout.rdbuf(outputStream.rdbuf());
	}

	// Helper function to simulate user input
	void simulateInput(const std::string& input) {
		inputStream.str(input);
		std::cin.rdbuf(inputStream.rdbuf());
	}

	// Helper function to restore cin and cout
	void restoreIO() {
		std::cin.rdbuf(origCin);
		std::cout.rdbuf(origCout);
	}

	std::streambuf* origCin;
	std::streambuf* origCout;
	std::stringstream outputStream;
	std::stringstream inputStream;
};

// Test case 1: User Registration
TEST_F(FoodDeliverySystemTest, UserRegistration) {
	setupOutput();
	Authentication auth;

	simulateInput(
		"JohnDoe\n"
		"john@example.com\n"
		"1234567890\n"
		"Customer\n"
		"password123\n"
		"123 Main St\n"
	);

	auth.registration();

	EXPECT_EQ(user.size(), 1);
	EXPECT_EQ(user[0]["name"], "JohnDoe");
	EXPECT_EQ(user[0]["email"], "john@example.com");
	EXPECT_EQ(user[0]["phone"], "1234567890");
	EXPECT_EQ(user[0]["userType"], "Customer");
	EXPECT_EQ(user[0]["address"], "123 Main St");

	restoreIO();
}

// Test case 2: User Profile Management
TEST_F(FoodDeliverySystemTest, UserProfileManagement) {
	setupOutput();
	user.push_back({
		{"userID", "john123"},
		{"name", "JohnDoe"},
		{"email", "john@example.com"},
		{"phone", "1234567890"},
		{"password", "password123"},
		{"userType", "Customer"},
		{"address", "123 Main St"}
	});

	User u("john123");
	simulateInput(
		"1\n"
		"JaneDoe\n"
		"jane@example.com\n"
		"0987654321\n"
	);

	u.manageProfile();

	EXPECT_EQ(user[0]["name"], "JaneDoe");
	EXPECT_EQ(user[0]["email"], "jane@example.com");
	EXPECT_EQ(user[0]["phone"], "0987654321");

	restoreIO();
}

// Test case 3: Login and OTP Verification
TEST_F(FoodDeliverySystemTest, LoginAndOTP) {
	setupOutput();
	user.push_back({
		{"userID", "john123"},
		{"name", "JohnDoe"},
		{"email", "john@example.com"},
		{"phone", "1234567890"},
		{"password", "password123"},
		{"userType", "Customer"}
	});

	Authentication auth;
	auth.email = "john@example.com";
	auth.passwordHash = "password123";

	simulateInput("1234\n");

	auth.login();

	std::string output = outputStream.str();
	EXPECT_NE(output.find("Login Successful"), std::string::npos);
	EXPECT_NE(output.find("Valid OTP"), std::string::npos); // fixed typo here

	restoreIO();
}

// Test case 4: Restaurant Menu Management
TEST_F(FoodDeliverySystemTest, RestaurantMenuManagement) {
	setupOutput();
	Restaurant res("rest123");

	simulateInput(
		"PizzaHut\n"
		"Margherita\n"
		"10\n"
	);

	res.manageMenus();

	EXPECT_EQ(menu["PizzaHut"]["Margherita"], 10);

	outputStream.str("");
	simulateInput("PizzaHut\n");
	res.displayMenu();

	std::string output = outputStream.str();
	EXPECT_NE(output.find("Margherita 10"), std::string::npos);

	restoreIO();
}

// Test case 5: Cart Operations
TEST_F(FoodDeliverySystemTest, CartOperations) {
	setupOutput();
	menu["PizzaHut"]["Margherita"] = 10;

	Cart cart;
	cart.cutomerID = "john123";

	simulateInput(
		"PizzaHut\n"
		"Margherita\n"
		"2\n"
	);

	cart.addItem();

	EXPECT_EQ(order.size(), 1);
	EXPECT_EQ(order[0], 20);

	outputStream.str("");
	cart.placeOrder();

	std::string output = outputStream.str();
	EXPECT_NE(output.find("Total Price: 20"), std::string::npos);

	restoreIO();
}

// Test case 6: Order Management
TEST_F(FoodDeliverySystemTest, OrderManagement) {
	setupOutput();
	menu["PizzaHut"]["Margherita"] = 10;

	Order ord;

	simulateInput(
		"PizzaHut\n"
		"Margherita\n"
		"3\n"
	);

	ord.addItem();

	EXPECT_EQ(order.size(), 1);
	EXPECT_EQ(order[0], 30);

	OrderItem ordItem;
	outputStream.str("");
	ordItem.totalOrderAmount();

	std::string output = outputStream.str();
	EXPECT_NE(output.find("Total Price: 30"), std::string::npos);

	restoreIO();
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
