#include <include/crypto/aes.hpp>
#include <include/crypto/keyderive.hpp>
#define AES_KEY_SIZE 256
#define AES_BLOCK_SIZE 16
std::string AES::encryptData(const std::string& data,const std::string& password, const std::string& salt) const
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<unsigned char> ciphertext(data.size() + EVP_MAX_BLOCK_LENGTH);
    int len, ciphertext_len;
    std::vector<unsigned char> iv;
    std::string key = this->key_derive_function_->getKey(password, salt);
        // Initialize AES encryption context with AES-256-CBC
        if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), 0, reinterpret_cast<const unsigned char*>(key.c_str()), iv.data())) {
            
        }

        // Encrypt the plaintext
        if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char*>(data.data()), data.size())) {
            
        }
        ciphertext_len = len;

        // Finalize encryption
        if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len)) {
            
        }
        ciphertext_len += len;
        EVP_CIPHER_CTX_free(ctx);
        ciphertext.resize(ciphertext_len); // Adjust size to actual ciphertext length
        std::string hex = this->hex_function_->unsignedCharToHex(ciphertext);
        return hex;
}
std::string AES::decryptData(const std::string& encryptedText, const std::string& password,const std::string& salt) const
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<unsigned char> decryptedText(encryptedText.size()); // Allocate sufficient space for decrypted text
    int len, decrypted_len;
    std::string key = this->key_derive_function_->getKey(password, salt);
    // Convert hex string to byte array
    std::vector<unsigned char> ciphertext = this->hex_function_->hexToUnsignedChar(encryptedText);
    // Initialize AES decryption context with AES-256-CBC
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), nullptr)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize decryption context");
    }

    // Decrypt the ciphertext
    if (1 != EVP_DecryptUpdate(ctx, decryptedText.data(), &len, ciphertext.data(), ciphertext.size())) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to decrypt data");
    }
    decrypted_len = len;
    // Finalize decryption
    if (1 != EVP_DecryptFinal_ex(ctx, decryptedText.data() + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to finalize decryption");
    }
    decrypted_len += len;
    EVP_CIPHER_CTX_free(ctx);
    decryptedText.resize(decrypted_len); // Adjust size to actual decrypted text length
    return std::string(decryptedText.begin(), decryptedText.end());
}
void AES::setKDF(KeyDerive* keyDeriveFunction)
{
    this->key_derive_function_ = keyDeriveFunction;
}
KeyDerive* AES::getKDF() const
{
    return this->key_derive_function_;
}
void AES::setHex(hexFormating* hexFunctions)
{
    this->hex_function_ = hexFunctions;
}
hexFormating* AES::getHex() const
{
    return this->hex_function_;
}
AES::AES(KeyDerive* keyDeriveFunction,hexFormating* hexFunctions)
{
    this->key_derive_function_ = keyDeriveFunction;
    this->hex_function_ = hexFunctions;
}