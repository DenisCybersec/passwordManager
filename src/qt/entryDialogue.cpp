#include<include/qt/entryDialogue.hpp>
EntryDialog::EntryDialog(DatabaseWindow* window) : QDialog(window)
{
    // Create input fields
        this->service_name_ = new QLineEdit(this);
        this->login_ = new QLineEdit(this);
        this->password_ = new QLineEdit(this);
        this->f_ = f_;
        this->window_=window;
        // Create a button
        this->submit_button_ = new QPushButton("Submit", this);
        // Layout setup
        this->layout_ = new QVBoxLayout(this);
        this->layout_->addWidget(new QLabel("Service Name:"));
        this->layout_->addWidget(this->service_name_);
        this->layout_->addWidget(new QLabel("Login:"));
        this->layout_->addWidget(this->login_);
        this->layout_->addWidget(new QLabel("Password:"));
        this->layout_->addWidget(this->password_);
        this->layout_->addWidget(this->submit_button_);
        setLayout(this->layout_);
        // Connect button click to slot
        connect(this->submit_button_, &QPushButton::clicked, this, &EntryDialog::onSubmit);

}
void EntryDialog::onSubmit()
{
    this->window_->addEntry(this->service_name_->text().toStdString(),this->login_->text().toStdString(),this->password_->text().toStdString());
    this->accept();
}