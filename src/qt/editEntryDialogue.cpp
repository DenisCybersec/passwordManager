#include<include/qt/editEntryDialogue.hpp>

EditEntryDialog::EditEntryDialog(DatabaseWindow* window,std::string serviceName,std::string login ,std::string password,int place) : QDialog(window)
{
    // Create input fields
        this->place_ = place;
        this->service_name_ = new QLineEdit(this);
        this->service_name_->setText(QString::fromStdString(serviceName));
        this->login_ = new QLineEdit(this);
        this->login_->setText(QString::fromStdString(login));
        this->password_ = new QLineEdit(this);
        this->password_->setText(QString::fromStdString(password));
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
        this->layout_->addWidget(submit_button_);
        setLayout(this->layout_);
        // Connect button click to slot
        connect(this->submit_button_, &QPushButton::clicked, this, &EditEntryDialog::onSubmit);
}
void EditEntryDialog::onSubmit()
{
    this->window_->editEntry(this->service_name_->text().toStdString(),this->login_->text().toStdString(),this->password_->text().toStdString(),this->place_);
    this->accept();
}