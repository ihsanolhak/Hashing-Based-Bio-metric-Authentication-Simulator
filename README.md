# 🔐 Hashing-Based-Bio-metric-Authentication-Simulator
A console-based **biometric authentication simulator** built in **C++**, demonstrating the use of **hashing, unique string generation, and admin-controlled access** for secure user authentication.  

---

## 📌 Features
- **Biometric Enrollment (Admin Protected)**
  - Requires admin password (`securepass` by default) for new user enrollment.
  - Generates a **unique biometric string** based on user responses.
  - Stores only **hashed values** (not raw data) for added security.

- **Authentication**
  - Users provide their saved biometric string.
  - The system **hashes the input** and compares with stored hashes.
  - Grants or denies access based on match.

- **Security Enhancements**
  - Custom hashing function (djb2-inspired).
  - User-friendly unique string creation with obfuscation (character shifting + mnemonics).
  - Limited attempts for admin login (max 5 tries).
  - Supports up to **100 enrolled users**.

---

## 🛠️ How It Works
### 1. Enrollment
- Admin enters the correct password to unlock enrollment.
- User answers four personal questions:
  1. Full Name
  2. Birth Month
  3. Favorite Person
  4. Favorite Thing About Them
### 2. Authentication
- User provides their saved biometric string.
- System **hashes** the input and checks against stored hashes.
- If a match is found → ✅ Authentication Successful  
- If no match → ❌ Authentication Failed

---

