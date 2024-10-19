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
        QPushButton *submitButton = new QPushButton("Submit", this);
        // Layout setup
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Service Name:"));
        layout->addWidget(this->serviceName);
        layout->addWidget(new QLabel("Login:"));
        layout->addWidget(this->login);
        layout->addWidget(new QLabel("Password:"));
        layout->addWidget(this->password);
        layout->addWidget(submitButton);
        setLayout(layout);
        // Connect button click to slot
        connect(submitButton, &QPushButton::clicked, this, &EntryDialog::onSubmit);

}
void EntryDialog::onSubmit()
{
    this->window->addEntry(this->serviceName->text().toStdString(),this->login->text().toStdString(),this->password->text().toStdString());
    this->accept();
}