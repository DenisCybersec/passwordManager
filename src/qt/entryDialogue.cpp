#include<include/qt/entryDialogue.hpp>
EntryDialog::EntryDialog(DatabaseWindow* window) : QDialog(window)
{
    // Create input fields
        this->serviceName = new QLineEdit(this);
        this->login = new QLineEdit(this);
        this->password = new QLineEdit(this);
        this->f = f;
        this->window=window;
        // Create a button
        this->submitButton = new QPushButton("Submit", this);
        // Layout setup
        this->layout = new QVBoxLayout(this);
        this->layout->addWidget(new QLabel("Service Name:"));
        this->layout->addWidget(this->serviceName);
        this->layout->addWidget(new QLabel("Login:"));
        this->layout->addWidget(this->login);
        this->layout->addWidget(new QLabel("Password:"));
        this->layout->addWidget(this->password);
        this->layout->addWidget(this->submitButton);
        setLayout(this->layout);
        // Connect button click to slot
        connect(this->submitButton, &QPushButton::clicked, this, &EntryDialog::onSubmit);

}
void EntryDialog::onSubmit()
{
    this->window->addEntry(this->serviceName->text().toStdString(),this->login->text().toStdString(),this->password->text().toStdString());
    this->accept();
}