#include<include/qt/editEntryDialogue.hpp>

EditEntryDialog::EditEntryDialog(DatabaseWindow* window,std::string serviceName,std::string login ,std::string password,int place) : QDialog(window)
{
    // Create input fields
        this->place = place;
        this->serviceName = new QLineEdit(this);
        this->serviceName->setText(QString::fromStdString(serviceName));
        this->login = new QLineEdit(this);
        this->login->setText(QString::fromStdString(login));
        this->password = new QLineEdit(this);
        this->password->setText(QString::fromStdString(password));
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
        this->layout->addWidget(submitButton);
        setLayout(this->layout);
        // Connect button click to slot
        connect(this->submitButton, &QPushButton::clicked, this, &EditEntryDialog::onSubmit);

}
void EditEntryDialog::onSubmit()
{
    this->window->editEntry(this->serviceName->text().toStdString(),this->login->text().toStdString(),this->password->text().toStdString(),this->place);
    this->accept();
}