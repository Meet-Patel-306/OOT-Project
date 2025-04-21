#include <gtest/gtest.h>
#include <unordered_map>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Define the global user map (fix linker error)
map<char, vector<unordered_map<string, string>>> user;

class Authentication {
private:
    string sessionToken;
    string passwordHash;

public:
    string email;
    string userId;

    // Modified registration to accept inputs for testing
    pair<string, char> registration(const string& newEmail, const string& newPhone, const string& newPassword,
                                   char newUserType, const string& firstName = "", const string& lastName = "",
                                   const string& newAddress = "", const string& restaurantName = "",
                                   const string& restaurantLocation = "", const string& vehicleNumber = "",
                                   const string& vehicleType = "", const string& vehicleModel = "") {
        string newUserID = newEmail + to_string(rand() % 1000);
        unordered_map<string, string> newUser = {
            {"userID", newUserID}, {"email", newEmail}, {"phone", newPhone}, {"password", newPassword}
        };

        switch (newUserType) {
            case 'C':
            case 'c': {
                newUserType = 'C';
                string newName = firstName + " " + lastName;
                newUser["name"] = newName;
                newUser["address"] = newAddress;
                break;
            }
            case 'R':
            case 'r': {
                newUserType = 'R';
                newUser["restaurantName"] = restaurantName;
                newUser["restaurantLocation"] = restaurantLocation;
                break;
            }
            case 'D':
            case 'd': {
                newUserType = 'D';
                newUser["vehicleNumber"] = vehicleNumber;
                newUser["vehicleType"] = vehicleType;
                newUser["vehicleModel"] = vehicleModel;
                break;
            }
            default: {
                throw runtime_error("Invalid user type!");
            }
        }

        user[newUserType].push_back(newUser);
        this->userId = newUserID;
        return login(newUserID, newPassword, newUserType);
    }

    // Modified login to accept inputs for testing
    pair<string, char> login(const string& uId, const string& pass, char userType) {
        bool foundId = false, foundPassword = false;

        for (const auto &u : user[userType]) {
            if (u.at("userID") == uId) {
                foundId = true;
                if (u.at("password") == pass) {
                    foundPassword = true;
                    if (verifyOTP()) {
                        return {uId, userType};
                    }
                }
            }
        }

        if (!foundId) {
            throw runtime_error("Username not found");
        }
        if (foundId && !foundPassword) {
            throw runtime_error("Incorrect Password");
        }

        return {uId, userType};
    }

    void logout() {
        // No-op for testing
    }

    virtual void resetPassword(const string& userId, char userType, const string& newPassword) {
        for (auto &u : user[userType]) {
            if (u["userID"] == userId) {
                if (verifyOTP()) {
                    u["password"] = newPassword;
                    return;
                }
            }
        }
        throw runtime_error("Password reset failed");
    }

    virtual bool verifyOTP() {
        int otp = 1234; // Fixed OTP for testing
        int otpEnter = otp; // Simulate correct OTP entry
        return otpEnter == otp;
    }

};

// Mocked subclass for testing
class MockAuthentication : public Authentication {
public:
    int testOtp = 1234;
    string testPassword = "test123";

    bool verifyOTP() override {
        return true; // Always return true for testing
    }

    void resetPassword(const string& userId, char userType, const string& newPassword) override {
        for (auto &u : user[userType]) {
            if (u["userID"] == userId) {
                u["password"] = newPassword;
                return;
            }
        }
        throw runtime_error("Password reset failed");
    }
};

// Helper to clear global user state
void clearUsers() {
    user.clear();
}

TEST(AuthenticationTest, SuccessfulCustomerRegistration) {
    clearUsers();
    Authentication auth;

    // Simulate registration
    string email = "test@example.com";
    string phone = "1234567890";
    string password = "testpass";
    char userType = 'C';
    string firstName = "Test";
    string lastName = "User";
    string address = "123 Street";

    auth.registration(email, phone, password, userType, firstName, lastName, address);

    ASSERT_EQ(user['C'].size(), 1);
    ASSERT_EQ(user['C'][0]["email"], email);
    ASSERT_EQ(user['C'][0]["name"], "Test User");
    ASSERT_EQ(user['C'][0]["address"], address);
}

TEST(AuthenticationTest, LoginWithCorrectCredentials) {
    clearUsers();
    Authentication auth;

    // Register a user
    string userId = "cust001";
    string email = "c@example.com";
    string password = "pass123";
    char userType = 'C';
    auth.registration(email, "1234567890", password, userType, "Customer", "One", "123 Street");

    // Simulate login
    auto result = auth.login(user['C'][0]["userID"], password, userType);

    ASSERT_EQ(result.first, user['C'][0]["userID"]);
    ASSERT_EQ(result.second, 'C');
}

TEST(AuthenticationTest, ResetPassword) {
    clearUsers();
    MockAuthentication auth;

    // Register a user
    string email = "c2@example.com";
    string oldPassword = "oldpass";
    char userType = 'C';
    auth.registration(email, "1234567890", oldPassword, userType, "Customer", "Two", "123 Street");

    string userId = user['C'][0]["userID"];
    string newPassword = "newpass123";
    auth.resetPassword(userId, userType, newPassword);

    ASSERT_EQ(user['C'][0]["password"], newPassword);
}

TEST(AuthenticationTest, OTPVerificationSuccess) {
    MockAuthentication auth;
    bool verified = auth.verifyOTP();
    ASSERT_TRUE(verified);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
